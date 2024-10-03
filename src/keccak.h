#ifndef KECCAK_H
#define KECCAK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct bit
{
    unsigned val:1;
} bit;

bit *table = NULL;
int w = 1;

bit TRUE = {val:1};
bit FALSE = {val :0};

int RC[24];

#endif
