#include <stdio.h>
#include <string.h>
#include "sha3.h"

void print_hash(const uint8_t *hash, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    int i = 1;
    int sha3 = 0;
    uint8_t hash[64];
    const char *message = NULL;

    while(i < argc){
        if(!strcmp(argv[i], "sha3-256") || !strcmp(argv[i], "256")){
            sha3 = 256;
        }

        if(!strcmp(argv[i], "sha3-384") || !strcmp(argv[i], "384")){
            sha3 = 384;
        }

        if(!strcmp(argv[i], "sha3-512") || !strcmp(argv[i], "512")){
           sha3 = 512;
        }
        if(!strcmp(argv[i], "-m") || !strcmp(argv[i], "message")){
                i++;
                if(argc - i){
                    message = argv[i];
                }
            }
		i++;
    }
    if(sha3 == 0){
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
    switch (sha3) {
        case 224:
            sha3_224((const uint8_t *)message, strlen(message), hash);
            printf("SHA3-224(\"%s\") = ", message);
            print_hash(hash, 28);
            break;
        case 256:
            sha3_256((const uint8_t *)message, strlen(message), hash);
            printf("SHA3-256(\"%s\") = ", message);
            print_hash(hash, 32);
            break;
        case 384:
            sha3_384((const uint8_t *)message, strlen(message), hash);
            printf("SHA3-384(\"%s\") = ", message);
            print_hash(hash, 48);
            break;
        case 512:
            sha3_512((const uint8_t *)message, strlen(message), hash);
            printf("SHA3-512(\"%s\") = ", message);
            print_hash(hash, 64);
            break;
        default:
            printf("Erreur interne : SHA3 non reconnu.\n");
            return 1;
    }

/*

    while(i < argc){
        if(!strcmp(argv[i], "sha3-256") || !strcmp(argv[i], "256")){
            sha3_256((const uint8_t *)message, strlen(message), hash);
            sha3 = 1;
            printf("SHA3-256(\"%s\") = ", message);
            print_hash(hash, 32);
        }

        if(!strcmp(argv[i], "sha3-384") || !strcmp(argv[i], "384")){
            sha3_384((const uint8_t *)message, strlen(message), hash);
            sha3 = 1;
            printf("SHA3-384(\"%s\") = ", message);
            print_hash(hash, 48);
        }

        if(!strcmp(argv[i], "sha3-512") || !strcmp(argv[i], "512")){
            sha3_((const uint8_t *)message, strlen(message), hash);
            sha3 = 1;
            printf("SHA3-512(\"%s\") = ", message);
            print_hash(hash, 64);
        }
    
    if(!strcmp(argv[i], "-m") || !strcmp(argv[i], "message")){
            i++;
            if(argc - i){
                message = argv[i];
            }
        }
		i++;
	}
    //Check if a sha3 has been selected
	if(sha3 == 0){
		printf("Sha3 list:\n");
		printf("  * sha3-224\n");
		printf("  * sha3-256\n");
		printf("  * sha3-384\n");
		printf("  * sha3-512\n");
		return 1;
	}

    if(!message){
        printf("Enter a message!\n");
        return 1;
    }
*/

    /*
    // SHA3-224
    sha3_224((const uint8_t *)message, strlen(message), hash);
    printf("SHA3-224(\"%s\") = ", message);
    print_hash(hash, 28);
    

    // SHA3-256
    sha3_256((const uint8_t *)message, strlen(message), hash);
    printf("SHA3-256(\"%s\") = ", message);
    print_hash(hash, 32);

    // SHA3-384
    sha3_384((const uint8_t *)message, strlen(message), hash);
    printf("SHA3-384(\"%s\") = ", message);
    print_hash(hash, 48);

    // SHA3-512
    sha3_512((const uint8_t *)message, strlen(message), hash);
    printf("SHA3-512(\"%s\") = ", message);
    print_hash(hash, 64);
    */

    return 0;
}







