#ifndef SHA3_H
#define SHA3_H

#include "keccak.h"

//Sha3 struct to hold sha3 values
struct sha3_struct {
    uint16_t r;
    uint16_t c;
    uint16_t length;
    uint16_t bits;
    uint8_t Mbits;
    uint8_t d;
};


typedef struct {
	int b, l, w, nr;
} keccak_t;

typedef struct sha3_struct sha3;

void sha3_f(sha3 *sha3, char *input);

#endif