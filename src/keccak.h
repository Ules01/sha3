#ifndef KECCAK_H
#define KECCAK_H

#include <stdint.h>

#define NB_ROUND 24
#define SIZE_BLOCK 64

uint64_t **keccak_f(uint64_t **A);

#endif