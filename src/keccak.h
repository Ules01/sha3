#ifndef KECCAK_H
#define KECCAK_H

#include "utils.h"

#define SIZE_BLOCK 64
#define NB_ROUND 24
#define ROT(x, y) (((x) << (y)) | ((x) >> (SIZE_BLOCK - (y))))

void keccak(uint8_t *Mbytes, size_t Mbits, size_t r, size_t length);

#endif