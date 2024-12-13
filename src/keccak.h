#ifndef KECCAK_H
#define KECCAK_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define NB_ROUND 24
#define SIZE_BLOCK 64

uint64_t **keccak_f(uint64_t **A);

uint64_t **init_matrice_sha3();
void destruction_matrice_sha3(uint64_t **A);
void adding_padding(uint8_t *msg, size_t *msg_len, size_t rate);
void absorb(uint64_t **A, uint8_t *msg, size_t mmsg_len, size_t rate);
void extract(uint64_t **A, uint8_t *output, size_t output_len, size_t rate);
void squeezing(uint64_t **A, uint8_t *res, size_t res_len, size_t rate);


#endif
