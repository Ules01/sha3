#include "utils.h" 

void print_hash(const uint8_t *hash, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

void *convert(void *pt){
    return pt;
}

int read_file_content(const char *filename, char **content) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return 1; // Error opening file
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    if (file_size < 0) {
        perror("Failed to determine file size");
        fclose(file);
        return 1;
    }
    rewind(file);

    *content = malloc(file_size + 1);
    long bytes_read = fread(*content, 1, file_size, file);
    if (bytes_read != file_size) {
        perror("Failed to read file content");
        free(*content);
        *content = NULL;
        fclose(file);
        return 1;
    }

    (*content)[file_size] = '\0';
    fclose(file);
    return 0; // Success
}