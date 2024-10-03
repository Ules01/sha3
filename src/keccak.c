#include "keccak.h"


void *round(void *A, uint64_t rc) {
    // θ step
    for(int x = 0; x < 5; x++){
        C[x] = A[x,0] ^ A[x,1] ^ A[x,2] ^ A[x,3] ^ A[x,4];
    }
    for(int x = 0; x < 5; x++){
        D[x] = C[x-1] ^ rot(C[x+1],1);
    }
    for(int x = 0; x < 5; x++){
        for(int y = 0; y < 5; y++){
            A[x,y] = A[x,y] ^ D[x];
        }
    }

    // ρ and π steps
    for(int x = 0; x < 5; x++){
        for(int y = 0; y < 5; y++){
            B[y,2*x+3*y] = rot(A[x,y], r[x,y]);
        }
    }
                    
    // χ step
    for(int x = 0; x < 5; x++){
        for(int y = 0; y < 5; y++){
            A[x,y] = B[x,y] ^ ((not B[x+1,y]) and B[x+2,y]),  for (x,y) in (0…4,0…4)
        }
    }

    // ι step
    A[0,0] = A[0,0] ^ RC

    return A
}

void *keccak_f(void *A) {
    for(int i = 0; i < NB_ROUND; i++){
        A = round(A, RC[i]);
    }
    return A;
}