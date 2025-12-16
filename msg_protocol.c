#include <string.h>
#include <stdio.h>
#include "bitboard.h"

// NOTE: LLM
int algebraic_to_index(char file, char rank) {
    int f = file - 'a';     // a–h  -> 0–7
    int r = rank - '1';     // 1–8  -> 0–7
    return r * 8 + f;       // your board indexing
}

// NOTE: LLM
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

// NOTE: LLM
char piece_to_fen(int color, int piece) {
    char c = '?';
    switch (piece) {
        case PAWN:   c = 'p'; break;
        case KNIGHT: c = 'n'; break;
        case BISHOP: c = 'b'; break;
        case ROOK:   c = 'r'; break;
        case QUEEN:  c = 'q'; break;
        case KING:   c = 'k'; break;
        default:     return '?';
    }
    return (color == WHITE ? c - 32 : c); // uppercase for white
}

// NOTE: LLM
int get_piece_on_square(Board *b, int sq, int *out_color, int *out_piece) {
    uint64_t mask = (uint64_t)1 << sq;
    int colors[] = { WHITE, BLACK };
    int pieces[] = { PAWN, KNIGHT, BISHOP, QUEEN, KING, ROOK };

    for (int color_idx = 0; color_idx <= 1; color_idx++) {
        int color = colors[color_idx];
        for (int piece_idx = 0; piece_idx <= 5; piece_idx++) {
            int piece = pieces[piece_idx];
            int idx = color | piece;
            if (b->piece_bb[idx] & mask) {
                *out_color = color;
                *out_piece = piece;
                return 1;
            }
        }
    }
    return 0;
}

// NOTE: LLM
void board_to_fen(Board *b, char *out_fen) {
    char buf[128] = {0};
    int buf_i = 0;

    for (int rank = 7; rank >= 0; rank--) {
        int empty_count = 0;

        for (int file = 0; file < 8; file++) {
            int sq = rank * 8 + file;

            int color = -1, piece = -1;

            if (get_piece_on_square(b, sq, &color, &piece)) {
                // flush empties
                if (empty_count > 0) {
                    buf[buf_i++] = '0' + empty_count;
                    empty_count = 0;
                }
                // write the piece char
                buf[buf_i++] = piece_to_fen(color, piece);
            } else {
                empty_count++;
            }
        }

        // flush trailing empties
        if (empty_count > 0) {
            buf[buf_i++] = '0' + empty_count;
        }

        if (rank > 0)
            buf[buf_i++] = '/';
    }

    buf[buf_i] = '\0';
    strcpy(out_fen, buf);
}

// NOTE: TEMP HACK (until castling and en-passante are implemented)
// NOTE: LLM
void board_to_full_fen(Board *b, char *out_fen) {
    char placement[128];
    board_to_fen(b, placement);

    // Default:
    // side-to-move = w
    // castling     = KQkq
    // en-passant   = -
    // halfmove     = 0
    // fullmove     = 1

    sprintf(out_fen, "%s w KQkq - 0 1", placement);
}

