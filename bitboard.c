/*
 * For reference see
 *
 * https://www.chessprogramming.org/General_Setwise_Operations
 * */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <locale.h>

#include "bitboard.h"


const uint64_t notAFile = 0xfefefefefefefefe; // ~0x0101010101010101
const uint64_t notHFile = 0x7f7f7f7f7f7f7f7f; // ~0x8080808080808080


struct Board* init_board() {
    struct Board *b = calloc(1, sizeof(struct Board));
    if (b == NULL) {
        return NULL;
    }

    b->wking = (uint64_t)1 << (8 * 0 + 4);
    b->bking = (uint64_t)1 << (8 * 7 + 4);

    b->wqueen = (uint64_t)1 << (8 * 0 + 3);
    b->bqueen = (uint64_t)1 << (8 * 7 + 3);

    b->wrook = ((uint64_t)1 << (8 * 0 + 0)) | ((uint64_t)1 << (8 * 0 + 7));
    b->brook = ((uint64_t)1 << (8 * 7 + 0)) | ((uint64_t)1 << (8 * 7 + 7));

    b->wknight = ((uint64_t)1 << (8 * 0 + 1)) | ((uint64_t)1 << (8 * 0 + 6));
    b->bknight = ((uint64_t)1 << (8 * 7 + 1)) | ((uint64_t)1 << (8 * 7 + 6));

    b->wbishop = ((uint64_t)1 << (8 * 0 + 2)) | ((uint64_t)1 << (8 * 0 + 5));
    b->bbishop = ((uint64_t)1 << (8 * 7 + 2)) | ((uint64_t)1 << (8 * 7 + 5));

    b->wpawn = ((uint64_t)1 << (8 * 1 + 0))
             | ((uint64_t)1 << (8 * 1 + 1))
             | ((uint64_t)1 << (8 * 1 + 2))
             | ((uint64_t)1 << (8 * 1 + 3))
             | ((uint64_t)1 << (8 * 1 + 4))
             | ((uint64_t)1 << (8 * 1 + 5))
             | ((uint64_t)1 << (8 * 1 + 6))
             | ((uint64_t)1 << (8 * 1 + 7))
    ;
    b->bpawn = ((uint64_t)1 << (8 * 6 + 0))
             | ((uint64_t)1 << (8 * 6 + 1))
             | ((uint64_t)1 << (8 * 6 + 2))
             | ((uint64_t)1 << (8 * 6 + 3))
             | ((uint64_t)1 << (8 * 6 + 4))
             | ((uint64_t)1 << (8 * 6 + 5))
             | ((uint64_t)1 << (8 * 6 + 6))
             | ((uint64_t)1 << (8 * 6 + 7))
    ;
    return b;
}

uint64_t combine_all_pieces(struct Board* b) {
    return (uint64_t)0
        | b->wking
        | b->bking
        | b->wqueen
        | b->bqueen
        | b->wrook
        | b->brook
        | b->wknight
        | b->bknight
        | b->wbishop
        | b->bbishop
        | b->wpawn
        | b->bpawn
    ;
}

uint64_t shift_north(uint64_t b)    {return b << 8;}
uint64_t shift_south(uint64_t b)    {return b >> 8;}
uint64_t shiftEast(uint64_t b)      {return (b << 1) & notAFile;}
uint64_t shiftNortheast(uint64_t b) {return (b << 9) & notAFile;}
uint64_t shiftSoutheast(uint64_t b) {return (b >> 7) & notAFile;}
uint64_t shiftWest(uint64_t b)      {return (b >> 1) & notHFile;}
uint64_t shiftSouthwest(uint64_t b) {return (b >> 9) & notHFile;}
uint64_t shiftNorthwest(uint64_t b) {return (b << 7) & notHFile;}

void print_bits(uint64_t n) {
    for (size_t i=0; i<64; i++) {
        uint64_t bit = n & ((uint64_t)1 << i);
        char* bit_str = bit > 0 ? "1" : "0";
        printf("%s\n", bit_str);
    }
}

int main(void) {
    struct Board *board = init_board();
    print_bits(combine_all_pieces(board));
    free(board);
    return 0;
}
