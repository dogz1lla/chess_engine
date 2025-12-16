#include <stdlib.h>
#include <stdio.h>

#include "bitboard.h"
#include "msg_protocol.h"


int main(void) {
    Board *b = calloc(1, sizeof(Board));
    if (b == NULL) {
        printf("%s\n", "Board allocation failed.");
        return 1;
    }

    init_board(b);
    // print_bits(b->occupied, 0);
    // print_bits(w_pawns_able_to_double_push(b->piece_bb[WHITE | PAWN], b->empty), 0);
    Move m = { .from = 12, .to = 28, .color = WHITE, .piece = PAWN };
    move_piece(b, &m);
    print_bits(b->occupied, 0);
    // char out_fen[128];
    // board_to_full_fen(b, out_fen);
    // printf("%s\n", out_fen);
    free(b);
    return 0;
}
