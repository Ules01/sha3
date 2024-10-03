#include "keccak.h"

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

uint64_t rot(uint64_t val, int n){
    n = n % SIZE_BLOCK;
    uint64_t right_side = val << n;               //first bits go to the last positions
    uint64_t left_side = val >> (SIZE_BLOCK - n); //n last bits go to the first postions
    return left_side | right_side;
}

uint64_t **keccak_round(uint64_t **A, uint64_t rc) {
    uint64_t B[5][5];
    uint64_t C[5];
    uint64_t D[5];
    
    // θ step
    for(int x = 0; x < 5; x++){
        C[x] = A[0][x] ^ A[1][x] ^ A[2][x] ^ A[3][x] ^ A[4][x];
    }
    for(int x = 0; x < 5; x++){
        D[x] = C[x-1] ^ rot(C[x+1],1); //may go out of range
    }
    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 5; x++){
            A[y][x] = A[y][x] ^ D[x];
        }
    }

    // ρ and π steps
    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 5; x++){
            B[2*x+3*y][y] = rot(A[y][x], r[y][x]);
        }
    }
                    
    // χ step
    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 5; x++){
            A[y][x] = B[y][x] ^ (!B[y][x+1] && B[y][x+2]);
        }
    }

    // ι step
    A[0][0] = A[0][0] ^ rc;

    return A;
}

uint64_t **keccak_f(uint64_t **A) {
    for(int i = 0; i < NB_ROUND; i++){
        A = keccak_round(A, RC[i]);
    }
    return A;
}