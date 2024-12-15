#ifndef SHA3_H
#define SHA3_H

#include <stdint.h>
#include <stddef.h> // Pour size_t

void add_padding(uint8_t *block, size_t rate_bytes, size_t chunk_size);

// Fonction générique pour la construction Sponge (interne)
void sponge(const uint8_t *message, size_t message_len, uint8_t *output, size_t output_len, int r, int c);

// SHA3-224 : produit un hash de 224 bits
void sha3_224(const uint8_t *message, size_t message_len, uint8_t *output);

// SHA3-256 : produit un hash de 256 bits
void sha3_256(const uint8_t *message, size_t message_len, uint8_t *output);

// SHA3-384 : produit un hash de 384 bits
void sha3_384(const uint8_t *message, size_t message_len, uint8_t *output);

// SHA3-512 : produit un hash de 512 bits
void sha3_512(const uint8_t *message, size_t message_len, uint8_t *output);

#endif // SHA3_H
