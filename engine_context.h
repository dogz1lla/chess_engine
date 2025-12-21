#pragma once
#include "bitboard.h"

typedef struct {
    Board* board;
    char last_move[16];
    char turn;
    // Add more (random engine, clients, settings...)
} EngineContext;

int init_engine_context(EngineContext* ctx);
