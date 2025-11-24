/* TODO
 * [x] add the pawn to the pieces list */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <locale.h>

#include "chess.h"


char* get_piece_symbol(int piece_code) {
    char *piece_symbol;
    switch (piece_code) {
        case 13:
            // black rook
            piece_symbol = "♜";
            break;
        case 11:
            // black knight
            piece_symbol = "♞";
            break;
        case 12:
            // black bishop
            piece_symbol = "♝";
            break;
        case 14:
            // black queen
            piece_symbol = "♛";
            break;
        case 9:
            // black king
            piece_symbol = "♚";
            break;
        case 10:
            // black pawn
            piece_symbol = "♟";
            break;
        case 21:
            // white rook
            piece_symbol = "♖";
            break;

        case 19:
            // white knight
            piece_symbol = "♘";
            break;
        case 20:
            // white bishop
            piece_symbol = "♗";
            break;
        case 22:
            // white queen
            piece_symbol = "♕";
            break;
        case 17:
            // white king
            piece_symbol = "♔";
            break;
        case 18:
            // white pawn
            piece_symbol = "♙";
            break;
        default:
            piece_symbol = " ";
    }
    return piece_symbol;
}

enum Piece {
    NONE   = 0,
    KING   = 1,
    PAWN   = 2,
    KNIGHT = 3,
    BISHOP = 4,
    ROOK   = 5,
    QUEEN  = 6,

    WHITE  = 8,
    BLACK  = 16,
};

struct Board {
    int squares[64];
};


struct Board* init_board(void) {
    struct Board *b = calloc(1, sizeof(struct Board));
    if (b == NULL) {
        return NULL;
    }
    return b;
}


int load_position_from_fen(struct Board *b, char* fen) {
    size_t file = 0;
    size_t rank = 7;
    int n_spaces = 0;
    size_t i = 0;

    while (fen[i] != ' ') {
        if (fen[i] == '\0') return 1;
        if (fen[i] == '/') {
            file = 0;
            rank--;
        } else {
            if (fen[i] >= 48 && fen[i] <= 57) {
                file += fen[i] - '0';
            } else {
                int piece_color = (fen[i] >= 65 && fen[i] <= 90) ? WHITE : BLACK;
                int piece_type = 0;
                switch (fen[i]) {
                    case 'k':
                    case 'K':
                        piece_type = KING;
                        break;
                    case 'q':
                    case 'Q':
                        piece_type = QUEEN;
                        break;
                    case 'r':
                    case 'R':
                        piece_type = ROOK;
                        break;
                    case 'b':
                    case 'B':
                        piece_type = BISHOP;
                        break;
                    case 'n':
                    case 'N':
                        piece_type = KNIGHT;
                        break;
                    case 'p':
                    case 'P':
                        piece_type = PAWN;
                        break;
                }
                b->squares[rank * 8 + file] = piece_type | piece_color;
                file++;
            }
        }
        i++;
    }

    // FIXME parse the rest of the FEN string
    // char turn;
    // char castling[4];
    // char enpassant[4];
    // char n_halfmoves[4];
    // char n_fullmoves[4];
    for (int i = 0; fen[i] != '\0'; i++) {
        // printf("%c\n", fen[i]);
        if (fen[i] == ' ') n_spaces++;
    }
    if (n_spaces != 5) return 1;
    return 0;
}


void draw_board(struct Board *b) {
    const char* light  = "\033[48;5;230;38;5;0m";
    const char* dark   = "\033[48;5;94;38;5;0m";
    const char* end    = "\033[0m";

    for (size_t rank=0; rank<8; rank++) {
        for (size_t file=0; file<8; file++) {
            const char* square_color = ((file + rank) % 2 == 0) ? light : dark;
            int piece_code = b->squares[rank * 8 + file];
            const char* piece = get_piece_symbol(piece_code);
            printf("%s %s %s", square_color, piece, end);
        }
        printf("\n");
    }
}


int main(void) {
    setlocale(LC_ALL, ""); // enable UTF-8 output

    char* starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    struct Board *board = init_board();
    if (load_position_from_fen(board, starting_fen) > 0){
        printf("%s", "FEN load failed");
        free(board);
        return 1;
    }
    draw_board(board);
    free(board);
    return 0;
}
