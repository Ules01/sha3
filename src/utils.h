#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void *convert(void *pt);
void dump_hash(uint8_t *hash, size_t length);

#endif //UTILS_H