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
    uint64_t white_pieces;
    uint64_t black_pieces;
} Board;


void init_board(Board*);
void print_bits(uint64_t, int as_column);
uint64_t combine_all_white_pieces(Board* b);
uint64_t combine_all_black_pieces(Board* b);
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

uint64_t king_move_targets(uint64_t kings, uint64_t empty);
uint64_t w_king_moves_bb(Board *b, int idx);
uint64_t b_king_moves_bb(Board *b, int idx);

void move_piece(Board*, Move*);
uint64_t get_possible_moves(Board *b, uint8_t square_idx);

void bb_to_array(uint64_t bb, uint8_t *idxs);
void bb_array_to_str(const uint8_t *bb_array, char *bb_array_str);

uint64_t w_pawn_east_attacks(uint64_t wpawns);
uint64_t w_pawn_west_attacks(uint64_t wpawns);
uint64_t b_pawn_east_attacks(uint64_t bpawns);
uint64_t b_pawn_west_attacks(uint64_t bpawns);

uint64_t w_pawn_any_attacks(uint64_t    wpawns);
uint64_t w_pawn_dbl_attacks(uint64_t    wpawns);
uint64_t w_pawn_single_attacks(uint64_t wpawns);
uint64_t b_pawn_any_attacks(uint64_t    bpawns);
uint64_t b_pawn_dbl_attacks(uint64_t    bpawns);
uint64_t b_pawn_single_attacks(uint64_t bpawns);
uint64_t w_pawn_attacks_bb(Board *b, int idx);
uint64_t b_pawn_attacks_bb(Board *b, int idx);

uint64_t get_possible_attacks(Board *b, uint8_t square_idx);
