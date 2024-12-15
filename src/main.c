#include <stdio.h>
#include <string.h>
#include "sha3.h"

void print_hash(const uint8_t *hash, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    const char *message = "hello world";
    uint8_t hash[64];

    // SHA3-224
    sha3_224((const uint8_t *)message, strlen(message), hash);
    printf("SHA3-224(\"%s\") = ", message);
    print_hash(hash, 28);

    // SHA3-256
    sha3_256((const uint8_t *)message, strlen(message), hash);
    printf("SHA3-256(\"%s\") = ", message);
    print_hash(hash, 32);

    // SHA3-384
    sha3_384((const uint8_t *)message, strlen(message), hash);
    printf("SHA3-384(\"%s\") = ", message);
    print_hash(hash, 48);

    // SHA3-512
    sha3_512((const uint8_t *)message, strlen(message), hash);
    printf("SHA3-512(\"%s\") = ", message);
    print_hash(hash, 64);

    return 0;
}
