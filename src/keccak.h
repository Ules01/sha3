#ifndef KECCAK_H
#define KECCAK_H

#include <stdint.h>
#include <stdio.h>

#define KECCAK_WIDTH 1600       // La largeur totale de la mtarice, (25 * W)(notre lane)
#define KECCAK_LANE_SIZE 64     //TAILLE D'UNE LANE EN BITS  (lane est un sous-élément du "state". L'état est divisé en 25 lanes (matrice 5x5), et chaque lane contient w bits.
#define KECCAK_NUM_ROUNDS 24    // On applique 24 rounds pour Keccak-f[1600].

#define ROT(x, y) (((x) << (y)) | ((x) >> (64 - (y))))

typedef uint64_t keccak_state[5][5];

void keccak_initialize_state(keccak_state state);
void keccak_theta(keccak_state state);
void keccak_rho(keccak_state state);
void keccak_pi(keccak_state state);
void keccak_chi(keccak_state state);
void keccak_iota(keccak_state state, int round);

void keccak_f(keccak_state state);


#endif //KECCAK_H
       
