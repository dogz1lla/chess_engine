#pragma once
#include <stdint.h>
#include "sliding.h"
#include <stdbool.h>

typedef enum {
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
} Square;

static const uint64_t ONE = (uint64_t)1;
static const uint64_t BB_A1 = ONE << A1;
static const uint64_t BB_B1 = ONE << B1;
static const uint64_t BB_C1 = ONE << C1;
static const uint64_t BB_D1 = ONE << D1;
static const uint64_t BB_E1 = ONE << E1;
static const uint64_t BB_F1 = ONE << F1;
static const uint64_t BB_G1 = ONE << G1;
static const uint64_t BB_H1 = ONE << H1;
static const uint64_t BB_A2 = ONE << A2;
static const uint64_t BB_B2 = ONE << B2;
static const uint64_t BB_C2 = ONE << C2;
static const uint64_t BB_D2 = ONE << D2;
static const uint64_t BB_E2 = ONE << E2;
static const uint64_t BB_F2 = ONE << F2;
static const uint64_t BB_G2 = ONE << G2;
static const uint64_t BB_H2 = ONE << H2;
static const uint64_t BB_A3 = ONE << A3;
static const uint64_t BB_B3 = ONE << B3;
static const uint64_t BB_C3 = ONE << C3;
static const uint64_t BB_D3 = ONE << D3;
static const uint64_t BB_E3 = ONE << E3;
static const uint64_t BB_F3 = ONE << F3;
static const uint64_t BB_G3 = ONE << G3;
static const uint64_t BB_H3 = ONE << H3;
static const uint64_t BB_A4 = ONE << A4;
static const uint64_t BB_B4 = ONE << B4;
static const uint64_t BB_C4 = ONE << C4;
static const uint64_t BB_D4 = ONE << D4;
static const uint64_t BB_E4 = ONE << E4;
static const uint64_t BB_F4 = ONE << F4;
static const uint64_t BB_G4 = ONE << G4;
static const uint64_t BB_H4 = ONE << H4;
static const uint64_t BB_A5 = ONE << A5;
static const uint64_t BB_B5 = ONE << B5;
static const uint64_t BB_C5 = ONE << C5;
static const uint64_t BB_D5 = ONE << D5;
static const uint64_t BB_E5 = ONE << E5;
static const uint64_t BB_F5 = ONE << F5;
static const uint64_t BB_G5 = ONE << G5;
static const uint64_t BB_H5 = ONE << H5;
static const uint64_t BB_A6 = ONE << A6;
static const uint64_t BB_B6 = ONE << B6;
static const uint64_t BB_C6 = ONE << C6;
static const uint64_t BB_D6 = ONE << D6;
static const uint64_t BB_E6 = ONE << E6;
static const uint64_t BB_F6 = ONE << F6;
static const uint64_t BB_G6 = ONE << G6;
static const uint64_t BB_H6 = ONE << H6;
static const uint64_t BB_A7 = ONE << A7;
static const uint64_t BB_B7 = ONE << B7;
static const uint64_t BB_C7 = ONE << C7;
static const uint64_t BB_D7 = ONE << D7;
static const uint64_t BB_E7 = ONE << E7;
static const uint64_t BB_F7 = ONE << F7;
static const uint64_t BB_G7 = ONE << G7;
static const uint64_t BB_H7 = ONE << H7;
static const uint64_t BB_A8 = ONE << A8;
static const uint64_t BB_B8 = ONE << B8;
static const uint64_t BB_C8 = ONE << C8;
static const uint64_t BB_D8 = ONE << D8;
static const uint64_t BB_E8 = ONE << E8;
static const uint64_t BB_F8 = ONE << F8;
static const uint64_t BB_G8 = ONE << G8;
static const uint64_t BB_H8 = ONE << H8;

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
    RayTable ray_table;
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

uint64_t king_move_targets(uint64_t kings);
uint64_t w_king_moves_bb(Board *b, int idx);
uint64_t b_king_moves_bb(Board *b, int idx);

uint64_t knight_move_targets(uint64_t knights);
uint64_t w_knight_moves_bb(Board *b, int idx);
uint64_t b_knight_moves_bb(Board *b, int idx);

void move_piece(Board*, Move*);
uint64_t get_moves_for_piece_on_square(Board *b, Color color, Piece piece, Square square);
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

uint64_t w_king_attacks_bb(Board *b, int idx);
uint64_t b_king_attacks_bb(Board *b, int idx);

uint64_t w_knight_attacks_bb(Board *b, int idx);
uint64_t b_knight_attacks_bb(Board *b, int idx);

uint64_t get_attacks_for_piece_on_square(Board *b, Color color, Piece piece, Square square);
uint64_t get_possible_attacks(Board *b, uint8_t square_idx);

/* Returns the bit position of the least significant non-zero bit via
 * returning the number of trailing 0-bits in x, starting at the least significant bit position.
   If x is 0, the result is undefined.
 * NOTE: __builtin_ctzll is defined in stdint. */
static inline int bit_scan_forward(uint64_t bb) {
    return __builtin_ctzll(bb);
}

/* Returns the bit position of the most significant non-zero bit via
 * Returning the number of leading 0-bits in x, starting at the most significant bit position and
 * then taking the ^ 63 operation.
   If x is 0, the result is undefined.
 * NOTE: __builtin_clzll is defined in stdint. */
static inline int bit_scan_reverse(uint64_t bb) {
    return __builtin_clzll(bb) ^ 63;
}

int bit_scan(uint64_t bb, bool reverse);
bool is_negative_direction(Direction direction);
uint64_t get_ray_attacks(RayTable *rt, uint64_t occupied, Direction direction, Square square);

uint64_t all_rook_attacks_bb(Board *b, int idx);
uint64_t rook_moves_bb(Board *b, int idx);
uint64_t w_rook_moves_bb(Board *b, int idx);
uint64_t b_rook_moves_bb(Board *b, int idx);
uint64_t w_rook_attacks_bb(Board *b, int idx);
uint64_t b_rook_attacks_bb(Board *b, int idx);
uint64_t w_rook_attacks_bb(Board *b, int idx);
uint64_t b_rook_attacks_bb(Board *b, int idx);

uint64_t all_bishop_attacks_bb(Board *b, int idx);
uint64_t bishop_moves_bb(Board *b, int idx);
uint64_t w_bishop_moves_bb(Board *b, int idx);
uint64_t b_bishop_moves_bb(Board *b, int idx);
uint64_t w_bishop_attacks_bb(Board *b, int idx);
uint64_t b_bishop_attacks_bb(Board *b, int idx);

uint64_t all_queen_attacks_bb(Board *b, int idx);
uint64_t queen_moves_bb(Board *b, int idx);
uint64_t w_queen_moves_bb(Board *b, int idx);
uint64_t b_queen_moves_bb(Board *b, int idx);
uint64_t w_queen_attacks_bb(Board *b, int idx);
uint64_t b_queen_attacks_bb(Board *b, int idx);
