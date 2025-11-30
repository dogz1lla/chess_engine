/*
 * For reference see
 *
 * https://www.chessprogramming.org/General_Setwise_Operations
 * */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "set_operations.h"
#include "one_step.h"
#include "bitboard.h"


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

void init_board(struct Board* b) {
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

    b->occupied = combine_all_pieces(b);
    b->empty    = bit_complement(b->occupied);
}

void print_bits(uint64_t n) {
    for (size_t i=0; i<64; i++) {
        uint64_t bit = n & ((uint64_t)1 << i);
        char* bit_str = bit > 0 ? "1" : "0";
        printf("%s\n", bit_str);
    }
}

uint64_t get_square_bit(int idx) {return (uint64_t)1 << idx;}

uint64_t w_single_push_targets(uint64_t wpawns, uint64_t empty) {
    return shift_north(wpawns) & empty;
}

uint64_t b_single_push_targets(uint64_t bpawns, uint64_t empty) {
    return shift_south(bpawns) & empty;
}

uint64_t w_double_push_targets(uint64_t wpawns, uint64_t empty) {
    const uint64_t rank4 = ((uint64_t)1 << (8 * 3 + 0))
                         | ((uint64_t)1 << (8 * 3 + 1))
                         | ((uint64_t)1 << (8 * 3 + 2))
                         | ((uint64_t)1 << (8 * 3 + 3))
                         | ((uint64_t)1 << (8 * 3 + 4))
                         | ((uint64_t)1 << (8 * 3 + 5))
                         | ((uint64_t)1 << (8 * 3 + 6))
                         | ((uint64_t)1 << (8 * 3 + 7));
    uint64_t single_pushes = w_single_push_targets(wpawns, empty);
    return shift_north(single_pushes) & empty & rank4;
}

uint64_t b_double_push_targets(uint64_t bpawns, uint64_t empty) {
    const uint64_t rank5 = ((uint64_t)1 << (8 * 4 + 0))
                         | ((uint64_t)1 << (8 * 4 + 1))
                         | ((uint64_t)1 << (8 * 4 + 2))
                         | ((uint64_t)1 << (8 * 4 + 3))
                         | ((uint64_t)1 << (8 * 4 + 4))
                         | ((uint64_t)1 << (8 * 4 + 5))
                         | ((uint64_t)1 << (8 * 4 + 6))
                         | ((uint64_t)1 << (8 * 4 + 7));
    uint64_t single_pushes = b_single_push_targets(bpawns, empty);
    return shift_south(single_pushes) & empty & rank5;
}

uint64_t w_pawns_able_to_push(uint64_t wpawns, uint64_t empty) {
    return shift_south(empty) & wpawns;
}

uint64_t b_pawns_able_to_push(uint64_t bpawns, uint64_t empty) {
    return shift_north(empty) & bpawns;
}

uint64_t w_pawns_able_to_double_push(uint64_t wpawns, uint64_t empty) {
    const uint64_t rank4 = ((uint64_t)1 << (8 * 3 + 0))
                         | ((uint64_t)1 << (8 * 3 + 1))
                         | ((uint64_t)1 << (8 * 3 + 2))
                         | ((uint64_t)1 << (8 * 3 + 3))
                         | ((uint64_t)1 << (8 * 3 + 4))
                         | ((uint64_t)1 << (8 * 3 + 5))
                         | ((uint64_t)1 << (8 * 3 + 6))
                         | ((uint64_t)1 << (8 * 3 + 7));
    const uint64_t empty_rank3 = shift_south(rank4 & empty) & empty;
    return w_pawns_able_to_push(wpawns, empty_rank3);
}

uint64_t b_pawns_able_to_double_push(uint64_t bpawns, uint64_t empty) {
    const uint64_t rank5 = ((uint64_t)1 << (8 * 4 + 0))
                         | ((uint64_t)1 << (8 * 4 + 1))
                         | ((uint64_t)1 << (8 * 4 + 2))
                         | ((uint64_t)1 << (8 * 4 + 3))
                         | ((uint64_t)1 << (8 * 4 + 4))
                         | ((uint64_t)1 << (8 * 4 + 5))
                         | ((uint64_t)1 << (8 * 4 + 6))
                         | ((uint64_t)1 << (8 * 4 + 7));
    const uint64_t empty_rank6 = shift_north(rank5 & empty) & empty;
    return b_pawns_able_to_push(bpawns, empty_rank6);
}
