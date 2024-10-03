#include "keccak.h"



uint64_t *round(uint64_t A[5][5], uint64_t rc) {
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

uint64_t *keccak_f(uint64_t A[5][5]) {
    for(int i = 0; i < NB_ROUND; i++){
        A = round(A, RC[i]);
    }
    return A;
}