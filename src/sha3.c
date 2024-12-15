#include "sha3.h"



void sha3_f(sha3 *sha3, char *input){
	if(sha3 && input) keccak(convert(input), strlen(input), sha3->r, sha3->length);
	return;
}