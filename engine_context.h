#pragma once
#include "bitboard.h"

typedef struct {
    Board* board;
    char last_move[16];
    // Add more (random engine, clients, settings...)
} EngineContext;
