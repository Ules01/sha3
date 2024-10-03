#ifndef KECCAK_H
#define KECCAK_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct bit
{
    unsigned val:1;
} bit;

bit *table = NULL;
int w = 1;

bit TRUE = {val:1};
bit FALSE = {val :0};

#define NB_ROUND 24

const uint64_t RC[24] = {
    0x0000000000000001, 0x0000000000008082,
    0x800000000000808A, 0x8000000080008000,
    0x000000000000808B, 0x0000000080000001,
    0x8000000080008081, 0x8000000000008009,
    0x000000000000008A, 0x0000000000000088,
    0x0000000080008009, 0x000000008000000A,
    0x000000008000808B, 0x800000000000008B,
    0x8000000000008089, 0x8000000000008003,
    0x8000000000008002, 0x8000000000000080,
    0x000000000000800A, 0x800000008000000A,
    0x8000000080008081, 0x8000000000008080,
    0x0000000080000001, 0x8000000080008008
};

//Rotation table
const int r[5][5] = {
    {25, 39,  3, 10, 43},
    {55, 20, 36, 44,  6},
    {28, 27,  0,  1, 62},
    {56, 14, 18,  2, 61},
    {21,  8, 41, 45, 15}
};


#endif