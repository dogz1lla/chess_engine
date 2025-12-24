#pragma once
#include "bitboard.h"
#include "msg_protocol.h"

typedef struct {
    Board* board;
    char last_move[16];
    char turn;
    // Add more (random engine, clients, settings...)
} EngineContext;

int init_engine_context(EngineContext* ctx);
void switch_turn(EngineContext* ctx);
void board_to_full_fen(EngineContext *ctx, char *out_fen);
