#include "keccak.h"

const uint64_t RC[24]={
    0x0000000000000001,
    0x0000000000008082,
    0x800000000000808A,
    0x8000000080008000,
    0x000000000000808B,
    0x0000000080000001,
    0x8000000080008081,
    0x8000000000008009,
    0x000000000000008A,
    0x0000000000000088,
    0x0000000080008009,
    0x000000008000000A,
    0x000000008000808B,
    0x800000000000008B,
    0x8000000000008089,
    0x8000000000008003,
    0x8000000000008002,
    0x8000000000000080,
    0x000000000000800A,
    0x800000008000000A,
    0x8000000080008081,
    0x8000000000008080,
    0x0000000080000001,
    0x8000000080008008
};

//Rotation table
const int r[25] = {
    0, 1, 62, 28, 27,
    36, 44, 6, 55, 20,
    3, 10, 43, 25, 39,
    41, 45, 15, 21, 8,
    18, 2, 61, 56, 14
};

void keccak_round(uint64_t *A, uint64_t rc) {
    
    uint64_t B[25] = {0};
    uint64_t C[5]  = {0};
    uint64_t D[5]  = {0};
    
    
    // θ step
    for(int x = 0; x < 5; x++){
        C[x] = A[x] ^ A[5 + x] ^ A[2 * 5 + x] ^ A[3 * 5 + x] ^ A[4 * 5 + x];
    }
    for(int x = 0; x < 5; x++){
        D[x] = C[(x + 4) % 5] ^ ROT(C[(x+1) % 5], 1);
    }
    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 5; x++){
            A[y * 5 + x] ^= D[x]; 
        }
    }

    // ρ step and π step
    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 5; x++){
            B[y * 5 + (2 * x + 3 * y) % 5] = ROT(A[y * 5 + x], r[y * 5 + x]);
        }
    }
                    
    // χ step
    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 5; x++){
            A[y * 5 + x] = B[y * 5 + x] ^ ((!B[y * 5 + (x + 1) % 5]) && B[y * 5 + (x + 2) % 5]);
        }
    }
    
    // ι step
    A[0] = A[0] ^ rc;
}

void keccak_f(uint64_t *A) {
    for(int i = 0; i < NB_ROUND; i++){
        keccak_round(A, RC[i]);
    }
}


void pad_message(const uint8_t *Mbytes, size_t Mbits, uint8_t **P, size_t *P_len){
    size_t d = 2;
    size_t padded_size = (Mbits + 7) / 8 + 1;
    *P = calloc(padded_size, sizeof(uint8_t));

    memcpy(*P, Mbytes, Mbits / 8);
    (*P)[Mbits / 8] |= (1 << Mbits % 8);
    (*P)[padded_size -1] |= d << 7;
    *P_len = padded_size;
}

void absorbing_phase(uint64_t *A, size_t r, uint8_t *P, size_t P_len){
    for(size_t i = 0; i < P_len; i += r / 8){
        for(size_t y = 0; y < 5; y++){
            for(size_t x = 0; x < 5; x++){
                if(x + 5 * y < r / 64){
                    A[x + y * 5] ^= ((uint64_t *)(&P[i]))[x + 5 * y];
                }
            }
        }
        keccak_f(A);
    }
}

void squeezing_phase(uint8_t *Z, uint64_t *A, size_t r, size_t output_len){
    size_t z_offset = 0;
    while(z_offset < output_len){
        for(size_t y = 0; y < 5; y++){
            for(size_t x = 0; x < 5; x++){
                if(x + 5 * y <  r / 64){
                    memcpy(Z + z_offset, &A[y * 5 + x], sizeof(uint64_t));
                    z_offset += sizeof(uint64_t);
                    if(z_offset >= output_len) return;
                }
            }
        }
        keccak_f(A);
    }
}

void keccak(uint8_t *Mbytes, size_t Mbits, size_t r, size_t length){
    uint8_t *P = NULL;
    size_t P_len = 0;
    pad_message(Mbytes, Mbits, &P, &P_len);
    uint64_t A[25] = {0};
    absorbing_phase(A, r, P, P_len);
    uint8_t *O = calloc(length / 8, sizeof(uint8_t));
    squeezing_phase(O, A, r, length / 8);
    dump_hash(O, 32);
    free(O);
    /*keccak_f(A);
    for(int i = 0; i < 25; i++){
        printf("%08lx ",A[i]);
    }
    if(r) printf("\n");
    */
}