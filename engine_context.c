#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine_context.h"


int reset_engine_context(EngineContext* ctx) {
    init_board(ctx->board);
    memset(ctx->last_move, 0, sizeof(ctx->last_move));
    ctx->turn = 'w';

    for (size_t i = 0; i < 64; i++) {
        ctx->move_matrix[i] = (uint64_t)0;
    }
    return 0;
}

int init_engine_context(EngineContext* ctx) {
    Board *b = calloc(1, sizeof(Board));
    if (b == NULL) {
        printf("%s\n", "Board allocation failed (during engine context allocation).");
        return 1;
    }
    ctx->board = b;
    return reset_engine_context(ctx);
}

void switch_turn(EngineContext* ctx) {
    ctx->turn = ctx->turn == 'w' ? 'b' : 'w';
}


// NOTE: TEMP HACK (until castling and en-passante are implemented)
// NOTE: LLM
void board_to_full_fen(EngineContext *ctx, char *out_fen) {
    char placement[128];
    board_to_fen(ctx->board, placement);

    char turn[2];
    strcpy(turn, &ctx->turn);

    // Default:
    // side-to-move = w
    // castling     = KQkq
    // en-passant   = -
    // halfmove     = 0
    // fullmove     = 1

    sprintf(out_fen, "%s %s KQkq - 0 1", placement, turn);
}

void calculate_all_moves(EngineContext *ctx) {
}
