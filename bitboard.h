#include <stdint.h>


struct Board {
    uint64_t wking;
    uint64_t bking;

    uint64_t wqueen;
    uint64_t bqueen;

    uint64_t wrook;
    uint64_t brook;

    uint64_t wknight;
    uint64_t bknight;

    uint64_t wbishop;
    uint64_t bbishop;

    uint64_t wpawn;
    uint64_t bpawn;

    uint64_t occupied;
    uint64_t empty;
};

void init_board(struct Board*);
uint64_t overlap_all(struct Board*);
void print_bits(uint64_t, int as_column);
uint64_t combine_all_pieces(struct Board*);

uint64_t w_single_push_targets(uint64_t, uint64_t);
uint64_t b_single_push_targets(uint64_t, uint64_t);
uint64_t w_double_push_targets(uint64_t, uint64_t);
uint64_t b_double_push_targets(uint64_t, uint64_t);
uint64_t w_pawns_able_to_push(uint64_t, uint64_t);
uint64_t b_pawns_able_to_push(uint64_t, uint64_t);
uint64_t w_pawns_able_to_double_push(uint64_t, uint64_t);
uint64_t b_pawns_able_to_double_push(uint64_t, uint64_t);
