#pragma once
#include <stdint.h>


typedef enum {
    PIECE_NONE = 0,
    KING   = 1,
    PAWN   = 2,
    KNIGHT = 3,
    BISHOP = 4,
    ROOK   = 5,
    QUEEN  = 6,
} Piece;

typedef enum {
    COLOR_NONE = 0,
    WHITE = 8,
    BLACK = 16,
} Color;

typedef struct {
    int from;
    int to;
    Color color;
    Piece piece;
    Color captured_color;
    Piece captured_piece;
} Move;

typedef struct {
    uint64_t piece_bb[23];
    uint64_t occupied;
    uint64_t empty;
} Board;


void init_board(Board*);
void print_bits(uint64_t, int as_column);
uint64_t combine_all_pieces(Board*);

uint64_t get_square_bit(int idx);
uint64_t w_single_push_targets(uint64_t, uint64_t);
uint64_t b_single_push_targets(uint64_t, uint64_t);
uint64_t w_double_push_targets(uint64_t, uint64_t);
uint64_t b_double_push_targets(uint64_t, uint64_t);
uint64_t w_pawns_able_to_push(uint64_t, uint64_t);
uint64_t b_pawns_able_to_push(uint64_t, uint64_t);
uint64_t w_pawns_able_to_double_push(uint64_t, uint64_t);
uint64_t b_pawns_able_to_double_push(uint64_t, uint64_t);
uint64_t w_pawn_moves_bb(Board *b, int idx);
uint64_t b_pawn_moves_bb(Board *b, int idx);
void move_piece(Board*, Move*);
