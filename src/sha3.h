#ifndef SHA3_H
#define SHA3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct sha3_struct sha3;

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


void sha3_compute(sha3 *sha3, uint8_t *message, size_t message_len, uint8_t *output);
#endif
