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