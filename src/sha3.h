#ifndef SHA3_H
#define SHA3_H

#include <string.h> 
#include <stddef.h>

#include "keccak.h"
#include "utils.h"

void add_padding(uint8_t *block, size_t rate_bytes, size_t chunk_size);
void sha3_f(const uint8_t *message, size_t message_len, uint8_t *output, sha3 *sha3);

#endif // SHA3_H
