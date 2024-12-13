#include "sha3.h"

uint8_t *read_file(const char *filename, size_t *file_len) {
	FILE *fp;
	fp = fopen(filename,"rb");
	
	if (fp == NULL)
   	{
   		fprintf(stderr,"File cannot be open or does not exist!\n");
   		exit(1);
   	}

	
	//deplacement du pointeur vers la fin du fichier pour connaitre la len
	fseek(fp , 0, SEEK_END);
	*file_len = ftell(fp);
	//redeplacement du fichier au debut
	rewind(fp);

	uint8_t *buffer = malloc(*file_len);
    	if (!buffer) {
        	fprintf(stderr, "Erreur : allocation mémoire échouée pour le fichier\n");
        	fclose(fp);
        	exit(EXIT_FAILURE);
    	}

    	// Lire le fichier
    	fread(buffer, 1, *file_len, fp);
	fclose(fp);
    	return buffer;



}

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
	printf("What is your file name?\n");
	char file_name[256];
	scanf("%s", file_name);
	size_t file_size;
	uint8_t *file_data = read_file(file_name, &file_size);
	printf("The file '%s' was read successfully. The lengeth is: %zu bytes.\n", file_name, file_size);
	free(file_data);

	return 0;
}
