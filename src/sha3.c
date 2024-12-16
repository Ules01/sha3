#include "sha3.h"


// Fonction pour ajouter le padding "10*1"
void add_padding(uint8_t *block, size_t rate_bytes, size_t message_len) {
    memset(block + message_len, 0, rate_bytes - message_len); // Remplit avec des 0
    block[message_len] = 0x06;                               // Ajoute le "10" (0x06)
    block[rate_bytes - 1] |= 0x80;                          // Dernier bit = 1
}

// Conversion de 64 bits little-endian
static void store64(uint8_t *output, uint64_t value) {
    for (int i = 0; i < 8; i++) {
        output[i] = (uint8_t)(value >> (8 * i));
    }
}

static uint64_t load64(const uint8_t *input) {
    uint64_t value = 0;
    for (int i = 0; i < 8; i++) {
        value |= ((uint64_t)input[i]) << (8 * i);
    }
    return value;
}

void sponge(const uint8_t *message, size_t message_len, uint8_t *output, size_t output_len, int r) {
    keccak_state state = {0};
    uint8_t block[200] = {0}; // Taille maximale pour 1600 bits
    size_t rate_bytes = r / 8;
    size_t i;

    // Absorption
    while (message_len >= rate_bytes) {
        for (i = 0; i < rate_bytes / 8; i++) {
            state[i % 5][i / 5] ^= load64(message + i * 8);
        }
        keccak_f(state);
        message += rate_bytes;
        message_len -= rate_bytes;
    }

    // Dernier bloc avec padding
    memset(block, 0, rate_bytes);
    memcpy(block, message, message_len);
    add_padding(block, rate_bytes, message_len);

    for (i = 0; i < rate_bytes / 8; i++) {
        state[i % 5][i / 5] ^= load64(block + i * 8);
    }
    keccak_f(state);

    // Squeezing
    while (output_len > 0) {
        size_t chunk_size = (output_len < rate_bytes) ? output_len : rate_bytes;
        for (i = 0; i < chunk_size / 8; i++) {
            store64(output + i * 8, state[i % 5][i / 5]);
        }
        output += chunk_size;
        output_len -= chunk_size;

        if (output_len > 0) {
            keccak_f(state);
        }
    }
}

void sha3_f(const uint8_t *message, size_t message_len, uint8_t *output, sha3 *sha3){
	sponge(message, message_len, output, sha3->output_len, sha3->r);
	print_hash(output, sha3->output_len);
}