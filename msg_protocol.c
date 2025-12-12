#include <string.h>
#include <stdio.h>
#include "bitboard.h"


Move make_move_from_strings(char * color, char* piece, int from, int to) {
    int c = COLOR_NONE;
    if      (strcmp(color, "w") == 0) c = WHITE;
    else if (strcmp(color, "b") == 0) c = BLACK;
    else printf("Invalid color %s\n", color);

    int p = PIECE_NONE;
    if      (strcmp(piece, "k") == 0) p = KING;
    else if (strcmp(piece, "p") == 0) p = PAWN;
    else if (strcmp(piece, "n") == 0) p = KNIGHT;
    else if (strcmp(piece, "b") == 0) p = BISHOP;
    else if (strcmp(piece, "r") == 0) p = ROOK;
    else if (strcmp(piece, "q") == 0) p = QUEEN;
    else printf("Invalid piece type %s\n", piece);

    Move m = { .from = from, .to = to, .color = c, .piece = p };
    return m;
}
