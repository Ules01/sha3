#include <stdint.h>
#include "keccak.h"



//LET'S INITIALISE THE STATE TO 0

void keccak_initialize_state(keccak_state state) {
	for (int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			state[i][j] = 0;
		}
	}

}

//THETA
void keccak_theta(keccak_state state){
	uint64_t C[5] = {0, 0, 0, 0, 0}; //parité des colonnes
	uint64_t D[5] = {0, 0, 0, 0, 0}; // correction des colonnes

	for(int i = 0; i < 5; i++){
		C[i] = state[i][0] ^ state[i][1] ^ state[i][2] ^ state[i][3] ^ state[i][4];
	}	
	for (int i = 0; i < 5; i++) {
        D[i] = C[(i + 4) % 5] ^ ((C[(i + 1) % 5] << 1) | (C[(i + 1) % 5] >> 63));
    }

	for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            state[x][y] ^= D[x];
        }
    }

}

//RHO
const int rx[25] = {
    0, 1, 62, 28, 27,
    36, 44, 6, 55, 20,
    3, 10, 43, 25, 39,
    41, 45, 15, 21, 8,
    18, 2, 61, 56, 14
};

// Fonction pour appliquer la transformation rho
void keccak_rho(keccak_state state) {
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            int offset = rx[y * 5 + x]; // Offset de rotation pour la lane (x, y)
            state[x][y] = (state[x][y] << offset) | (state[x][y] >> (64 - offset));
        }
    }
}

//pi
// Applique la transformation pi
void keccak_pi(keccak_state state) {
    keccak_state temp;

    // Copie temporairement l'état original
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            temp[x][y] = state[x][y];
        }
    }

    // Réorganise les lanes selon la formule de pi
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            int newX = y;
            int newY = (2 * x + 3 * y) % 5;
            state[newX][newY] = temp[x][y];
        }
    }
}

//CHI
// Applique la transformation chi
void keccak_chi(keccak_state state) {
    keccak_state temp;

    // Copie temporairement l'état original
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            temp[x][y] = state[x][y];
        }
    }

    // Applique la transformation chi
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            state[x][y] = temp[x][y] ^ ((~temp[(x + 1) % 5][y]) & temp[(x + 2) % 5][y]);
        }
    }
}

//IOTA
const uint64_t RC[24] = {
    0x0000000000000001, 0x0000000000008082, 0x800000000000808a,
    0x8000000080008000, 0x000000000000808b, 0x0000000080000001,
    0x8000000080008081, 0x8000000000008009, 0x000000000000008a,
    0x0000000000000088, 0x0000000080008009, 0x000000008000000a,
    0x000000008000808b, 0x800000000000008b, 0x8000000000008089,
    0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
    0x000000000000800a, 0x800000008000000a, 0x8000000080008081,
    0x8000000000008080, 0x0000000080000001, 0x8000000080008008
};

// Applique la transformation iota pour un round donné
void keccak_iota(keccak_state state, int round) {
    state[0][0] ^= RC[round]; // XOR de la constante de round sur state[0][0]
}

// Implémente la permutation Keccak-f[1600]
void keccak_f(keccak_state state) {
    for (int round = 0; round < KECCAK_NUM_ROUNDS; round++) {
        keccak_theta(state);  // Étape theta
        keccak_rho(state);    // Étape rho
        keccak_pi(state);     // Étape pi
        keccak_chi(state);    // Étape chi
        keccak_iota(state, round); // Étape iota
    }
}
