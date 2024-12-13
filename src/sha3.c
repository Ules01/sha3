#include "sha3.h"


keccak_t perms[7] = {
  {25,   0, 1,  12},
  {50,   1, 2,  14},
  {100,  2, 4,  16},
  {200,  3, 8,  18},
  {400,  4, 16, 20},
  {800,  5, 32, 22},
  {1600, 6, 64, 24},
};


int sha3_pad(uint8_t *message, int blocks, size_t length, uint16_t r, uint8_t *P) {
	int block_size = r/8;
	size_t block_len = (blocks + 1) * block_size;
	memset(P, 0, block_len * sizeof(uint8_t));
	for (size_t i = 0; i < length; ++i) {
      	P[i] = message[i];
  	}
	P[length] = 0x01;
  	P[block_len - 1] = 0x80;
	if (length % block_size == 0) {
    	return length;
  	}
	return block_len;
}

void sha3_absorb(int nr, int r, int w, int l, uint64_t* A, uint8_t* P){
	int blocks = l / (r / 8);
	for(int y = 0; y < blocks; y++){
		uint64_t* block = (uint64_t*)(P + (y * r/w));
		for (int x = 0; x < (r/w); ++x) {
      		A[x] = A[x] ^ block[x];
    	}
		keccak_f(A, nr);
	}
}

void sha3_squeeze(int nr, int r, int n, uint64_t* A, uint8_t* O){
	size_t size = 0;
	int i = 0;
	while(n){
		size = r > n ? n : r;
		memcpy(&O[i], A, size/8);
    	i = i + size/8;
		n = n - size;
		if(n > 0){
			keccak_f(A, nr);
		}
	}
}

// Process message using SHA3
void sha3_process(sha3 *hash_type, uint8_t *message, size_t length, uint8_t *output) {
	int b = hash_type->r + hash_type->c;
	int p = -1;
	for (int i = 0; i < 7; ++i) {
		if (b == perms[i].b) {
			p = i;
			break;
		}
	}

	uint64_t A[25];
	memset(A, 0, 25 * sizeof(uint64_t));
	int w = perms[p].w;
	int nr = perms[p].nr;
	int block_size = hash_type->r/8;
	int blocks = length / block_size;
	uint8_t *P = calloc(block_size * (blocks + 1), sizeof(uint8_t)); 

	length = sha3_pad(message, blocks, length, hash_type->r, P);
	sha3_absorb(nr, hash_type->r, w, length, A, P);
	sha3_squeeze(nr, hash_type->r, hash_type->length, A, output);
	
	free(P);
}


void sha3_f(sha3 *sha3, char *input){

	uint8_t *output = calloc(sha3->length / 8, sizeof(uint8_t));
	sha3_process(sha3, convert(input), strlen(input), output);

	for (size_t i = 0; i < sha3->length / 8; i++) {
        printf("%02x", output[i]);
    }
	printf("\n");
	free(output);
	return;
}