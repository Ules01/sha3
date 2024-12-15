#include "utils.h"

void *convert(void *pt){
    return pt;
}

void dump_hash(uint8_t *hash, size_t length){
	for (size_t i = 0; i < length; i++) {
        printf("%02x", hash[i]);
    }
	printf("\n");
}