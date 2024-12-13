#ifndef KECCAK_H
#define KECCAK_H

#include <stdint.h>

#define SIZE_BLOCK 64
#define ROT(x, y) (((x) << (y)) | ((x) >> (SIZE_BLOCK - (y))))

void keccak_f(uint64_t *A, int nr);

#endif