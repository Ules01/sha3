#include <stdio.h>
#include <string.h>

#include "sha3.h"
#include "utils.h"

sha3 SHA3_256 = {
    .r          = 1088,
    .output_len = 32 // 256 / 8
};

sha3 SHA3_384 = {
    .r          = 832,
    .output_len = 48 // 384 / 8
};

sha3 SHA3_512 = {
    .r          = 576,
    .output_len = 64 // 512 / 8
};

int main(int argc, char **argv) {
    int i = 1;
    sha3 *sha3 = NULL;
    uint8_t hash[64];
    char *message = NULL;

    while(i < argc){
        if(!strcmp(argv[i], "sha3-256") || !strcmp(argv[i], "256")){
            sha3 = &SHA3_256;
        }

        if(!strcmp(argv[i], "sha3-384") || !strcmp(argv[i], "384")){
            sha3 = &SHA3_384;
        }

        if(!strcmp(argv[i], "sha3-512") || !strcmp(argv[i], "512")){
           sha3 = &SHA3_512;
        }
        if(!strcmp(argv[i], "-m") || !strcmp(argv[i], "message")){
                i++;
                if(argc - i){
                    message = argv[i];
                }
            }
		i++;
    }
    if(!sha3){
		printf("Aucun sha3 n'a ete selectionne. sha3 list:\n");
		printf("  * sha3-256\n");
		printf("  * sha3-384\n");
		printf("  * sha3-512\n");
		return 1;
	}

     if(!message){
        printf("Veuillez spécifier un message avec l'option message ou -m.\n");
        return 1;
    }
    
    uint8_t *Mbytes = convert(message);
    sha3_f(Mbytes, strlen(message), hash, sha3);
    return 0;
}







