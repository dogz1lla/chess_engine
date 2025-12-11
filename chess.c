#include <stdlib.h>
#include <stdio.h>

#include "bitboard.h"


int main(void) {
    Board *b = calloc(1, sizeof(Board));
    if (b == NULL) {
        printf("%s\n", "Board allocation failed.");
        return 1;
    }

    init_board(b);
    // print_bits(b->occupied, 0);
    // print_bits(w_pawns_able_to_double_push(b->piece_bb[WHITE | PAWN], b->empty), 0);
    Move m = { .from = 49, .to = 41, .color = BLACK, .piece = PAWN };
    move_piece(b, &m);
    print_bits(b->occupied, 0);
    free(b);
    return 0;
}
