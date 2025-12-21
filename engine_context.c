#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bitboard.h"
#include "engine_context.h"


int init_engine_context(EngineContext* ctx) {
    Board *b = calloc(1, sizeof(Board));
    if (b == NULL) {
        printf("%s\n", "Board allocation failed (during engine context allocation).");
        return 1;
    }
    ctx->board = b;
    init_board(b);
    memset(ctx->last_move, 0, sizeof(ctx->last_move));
    ctx->turn = 'w';
    return 0;
}
