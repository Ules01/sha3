#include "sha3.h"

sha3 SHA3_224 = {
    .r = 1152,
    .c = 448,
    .length = 224,
    .bits = 112,
    .Mbits = 01,
    .d = 0x06
};

sha3 SHA3_256 = {
    .r = 1088,
    .c = 512,
    .length = 256,
    .bits = 128,
    .Mbits = 01,
    .d = 0x06
};

sha3 SHA3_384 = {
    .r = 832,
    .c = 768,
    .length = 384,
    .bits = 192,
    .Mbits = 01,
    .d = 0x06
};

sha3 SHA3_512 = {
    .r = 576,
    .c = 1024,
    .length = 512,
    .bits = 256,
    .Mbits = 01,
    .d = 0x06
};


int main(int argc, char **argv){
	sha3 *sha3 = NULL;
	char *message = NULL;
    int i = 1;
    
	//Check args
	while(i < argc){
		//Select sha3
		if(!strcmp(argv[i], "sha3-224") || !strcmp(argv[i], "224")){
			sha3 = &SHA3_224;
		}
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

	//Check if a sha3 has been selected
	if(!sha3){
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

	sha3_f(sha3, message);
	return 0;
}


/*int main(void){
    sha3_f(&SHA3_256, "");
    sha3_f(&SHA3_256, "test");
    return 0;
}*/