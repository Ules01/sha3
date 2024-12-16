#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


struct sha3_struct {
    int r;
    size_t output_len;
};

typedef struct sha3_struct sha3;

void print_hash(const uint8_t *hash, size_t len);
void *convert(void *pt);

#endif // UTILS_H