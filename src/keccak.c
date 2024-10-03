#include "keccak.h"

bit parite(int j, int k){
    bit value = table[j * w + k];
    for(int i = 1; i < 5; i++){
        if(table[(i * 5 + j) * w + k].val != value.val){
            return FALSE;
        }
    }
    return TRUE;
}

void theta(int i, int j){
    for(int k = 0; k < w; k++){
        table[(i * 5 + j) * w + k].val = table[(i * 5 + j) * w + k].val ^ parite(j - 1, k).val ^ parite(j + 1, k - 1).val;
    }
}

void rho(int i, int j){
    if(i == 0 && j == 0)
        return;
    for(int t = 0; t < 24; t++){
        for(int k = 0; k < w; k++){
            table[(i * 5 + j) * w + k].val = table[(i * 5 + j) * w + k - (t + 1) * (t + 2) / 2].val;
        }
    }
}


void swap(bit *dest, bit *src){
    for(int i = 0; i < w; i++){
        dest[i].val = src[i].val;
    }
}

void pi(int i, int j){
    swap(&table[((3 * i + 2 * j) * 5 + i) * w], &table[(i * 5 + j) * w]);
}

void chi(int i, int j){
    for(int k = 0; k < w; k++){
        table[(i * 5 + j) * w + k].val = table[(i * 5 + j) * w + k].val ^ !(table[(i * 5 + j + 1) * w + k].val) & (table[(i * 5 + j + 2) * w + k].val);z
    }
}

void iota(int i, int j){

}
