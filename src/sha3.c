#include "sha3.h"

int main(int argc, char **argv){
	sha3 *sha3 = NULL;
	int i = 1;

	//Check args
	while(i < argc){
		//Select sha3
		if(!strcmp(argv[i], "sha3-224")){
			sha3 = &SHA3_224;
		}
		if(!strcmp(argv[i], "sha3-256")){
			sha3 = &SHA3_256;
		}
		if(!strcmp(argv[i], "sha3-384")){
			sha3 = &SHA3_384;
		}
		if(!strcmp(argv[i], "sha3-512")){
			sha3 = &SHA3_512;
		}

		i++;
	}

	//Check if a sha3 has been selected
	if(!sha3){
		printf("Sha3 list:\n");
		printf("  * sha3-224\n");
		printf("  * sha3-256\n");
		printf("  * sha3-384\n");
		printf("  * sha3-512\n");
		return 1;
	}

	//Start message
	printf("Hello from the sha3 world!\n");

	return 0;
}
