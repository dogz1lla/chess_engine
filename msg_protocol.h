#pragma once
#include "bitboard.h"

int algebraic_to_index(char file, char rank);
Move make_move_from_strings(char*, char*, int, int);
char piece_to_fen(int color, int piece);
int get_piece_on_square(Board *b, int sq, int *out_color, int *out_piece);
void board_to_fen(Board *b, char *out_fen);
void board_to_full_fen(Board *b, char *out_fen);
