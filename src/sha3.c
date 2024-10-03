#include "sha3.h"

int main(int argc, char **argv){
	printf("Hello from the sha3 world!\n");
	if(argc < 2){
		printf("Sha3 list:\n");
		printf("  * sha3-224\n");
		printf("  * sha3-256\n");
		printf("  * sha3-384\n");
		printf("  * sha3-512\n");
		return 1;
	}
	printf("%s\n", argv[1]);
	return 0;
}
