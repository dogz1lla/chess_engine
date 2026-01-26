/*
 * For reference see
 *
 * https://www.chessprogramming.org/General_Setwise_Operations
 * */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "set_operations.h"
#include "one_step.h"
#include "bitboard.h"


const uint64_t rank4 = ((uint64_t)1 << (8 * 3 + 0))
                     | ((uint64_t)1 << (8 * 3 + 1))
                     | ((uint64_t)1 << (8 * 3 + 2))
                     | ((uint64_t)1 << (8 * 3 + 3))
                     | ((uint64_t)1 << (8 * 3 + 4))
                     | ((uint64_t)1 << (8 * 3 + 5))
                     | ((uint64_t)1 << (8 * 3 + 6))
                     | ((uint64_t)1 << (8 * 3 + 7));
const uint64_t rank5 = ((uint64_t)1 << (8 * 4 + 0))
                     | ((uint64_t)1 << (8 * 4 + 1))
                     | ((uint64_t)1 << (8 * 4 + 2))
                     | ((uint64_t)1 << (8 * 4 + 3))
                     | ((uint64_t)1 << (8 * 4 + 4))
                     | ((uint64_t)1 << (8 * 4 + 5))
                     | ((uint64_t)1 << (8 * 4 + 6))
                     | ((uint64_t)1 << (8 * 4 + 7));


uint64_t combine_all_pieces(Board* b) {
    return (uint64_t)0
        | b->piece_bb[WHITE | KING]
        | b->piece_bb[BLACK | KING]
        | b->piece_bb[WHITE | QUEEN]
        | b->piece_bb[BLACK | QUEEN]
        | b->piece_bb[WHITE | ROOK]
        | b->piece_bb[BLACK | ROOK]
        | b->piece_bb[WHITE | KNIGHT]
        | b->piece_bb[BLACK | KNIGHT]
        | b->piece_bb[WHITE | BISHOP]
        | b->piece_bb[BLACK | BISHOP]
        | b->piece_bb[WHITE | PAWN]
        | b->piece_bb[BLACK | PAWN]
    ;
}

void init_board(Board* b) {
    // NOTE: for testing the moves/captures, every piece is disabled besides pawns
    b->piece_bb[WHITE | KING]   = (uint64_t)0;
    b->piece_bb[BLACK | KING]   = (uint64_t)0;
    b->piece_bb[WHITE | QUEEN]  = (uint64_t)0;
    b->piece_bb[BLACK | QUEEN]  = (uint64_t)0;
    b->piece_bb[WHITE | ROOK]   = (uint64_t)0;
    b->piece_bb[BLACK | ROOK]   = (uint64_t)0;
    b->piece_bb[WHITE | KNIGHT] = (uint64_t)0;
    b->piece_bb[BLACK | KNIGHT] = (uint64_t)0;
    b->piece_bb[WHITE | BISHOP] = (uint64_t)0;
    b->piece_bb[BLACK | BISHOP] = (uint64_t)0;


    // b->piece_bb[WHITE | KING]   =  (uint64_t)1 << (8 * 0 + 4);
    // b->piece_bb[BLACK | KING]   =  (uint64_t)1 << (8 * 7 + 4);
    // b->piece_bb[WHITE | QUEEN]  =  (uint64_t)1 << (8 * 0 + 3);
    // b->piece_bb[BLACK | QUEEN]  =  (uint64_t)1 << (8 * 7 + 3);
    // b->piece_bb[WHITE | ROOK]   = ((uint64_t)1 << (8 * 0 + 0)) | ((uint64_t)1 << (8 * 0 + 7));
    // b->piece_bb[BLACK | ROOK]   = ((uint64_t)1 << (8 * 7 + 0)) | ((uint64_t)1 << (8 * 7 + 7));
    // b->piece_bb[WHITE | KNIGHT] = ((uint64_t)1 << (8 * 0 + 1)) | ((uint64_t)1 << (8 * 0 + 6));
    // b->piece_bb[BLACK | KNIGHT] = ((uint64_t)1 << (8 * 7 + 1)) | ((uint64_t)1 << (8 * 7 + 6));
    // b->piece_bb[WHITE | BISHOP] = ((uint64_t)1 << (8 * 0 + 2)) | ((uint64_t)1 << (8 * 0 + 5));
    // b->piece_bb[BLACK | BISHOP] = ((uint64_t)1 << (8 * 7 + 2)) | ((uint64_t)1 << (8 * 7 + 5));
    b->piece_bb[WHITE | PAWN]   = ((uint64_t)1 << (8 * 1 + 0))
                                | ((uint64_t)1 << (8 * 1 + 1))
                                | ((uint64_t)1 << (8 * 1 + 2))
                                | ((uint64_t)1 << (8 * 1 + 3))
                                | ((uint64_t)1 << (8 * 1 + 4))
                                | ((uint64_t)1 << (8 * 1 + 5))
                                | ((uint64_t)1 << (8 * 1 + 6))
                                | ((uint64_t)1 << (8 * 1 + 7));
    b->piece_bb[BLACK | PAWN]   = ((uint64_t)1 << (8 * 6 + 0))
                                | ((uint64_t)1 << (8 * 6 + 1))
                                // | ((uint64_t)1 << (8 * 6 + 2))
                                // | ((uint64_t)1 << (8 * 6 + 3))
                                | ((uint64_t)1 << (8 * 3 + 3))
                                | ((uint64_t)1 << (8 * 2 + 2))
                                | ((uint64_t)1 << (8 * 6 + 4))
                                | ((uint64_t)1 << (8 * 6 + 5))
                                | ((uint64_t)1 << (8 * 6 + 6))
                                | ((uint64_t)1 << (8 * 6 + 7));
    b->occupied = combine_all_pieces(b);
    b->empty    = bit_complement(b->occupied);
}

void print_bits(uint64_t n, int as_column) {
    for (size_t i=0; i<64; i++) {
        uint64_t bit = n & ((uint64_t)1 << i);
        char* bit_str = bit > 0 ? "1" : "0";
        char* suffix  = "\n";
        if (as_column < 1) {
            suffix  = (i+1) % 8 == 0 ? "\n" : " ";
        }
        printf("%s%s", bit_str, suffix);
    }
}

void bb_to_array(uint64_t bb, uint8_t *bb_array) {
    for (size_t i=0; i<64; i++) {
        bb_array[i] = (bb & ((uint64_t)1 << i)) > 0;
    }
}

// void (uint8_t *bb_array, char* bb_array_str) {
//     for (size_t i=0; i<64; i++) {
//     }
// }
void bb_array_to_str(const uint8_t *bb_array, char *bb_array_str) {
    for (size_t i = 0; i < 64; i++) {
        bb_array_str[i] = bb_array[i] > 0 ? '1' : '0';
    }
    bb_array_str[64] = '\0';
}

// // NOTE: LLM
// void bb_array_to_str(const int *bb_array, size_t n, char *bb_array_str, size_t buflen) {
//     size_t pos = 0;
//
//     for (size_t i = 0; i < n; i++) {
//         int written = snprintf(bb_array_str + pos, buflen - pos,
//             "%d%s", bb_array[i] > 0, (i + 1 < n) ? " " : "");
//
//         if (written < 0 || (size_t)written >= buflen - pos)
//             break;
//
//         pos += (size_t)written;
//     }
// }

uint64_t get_square_bit(int idx) {return (uint64_t)1 << idx;}

uint64_t w_single_push_targets(uint64_t wpawns, uint64_t empty) {
    return shift_north(wpawns) & empty;
}

uint64_t b_single_push_targets(uint64_t bpawns, uint64_t empty) {
    return shift_south(bpawns) & empty;
}

uint64_t w_double_push_targets(uint64_t wpawns, uint64_t empty) {
    uint64_t single_pushes = w_single_push_targets(wpawns, empty);
    return shift_north(single_pushes) & empty & rank4;
}

uint64_t b_double_push_targets(uint64_t bpawns, uint64_t empty) {
    uint64_t single_pushes = b_single_push_targets(bpawns, empty);
    return shift_south(single_pushes) & empty & rank5;
}

uint64_t w_pawns_able_to_push(uint64_t wpawns, uint64_t empty) {
    return shift_south(empty) & wpawns;
}

uint64_t b_pawns_able_to_push(uint64_t bpawns, uint64_t empty) {
    return shift_north(empty) & bpawns;
}

uint64_t w_pawns_able_to_double_push(uint64_t wpawns, uint64_t empty) {
    const uint64_t empty_rank3 = shift_south(rank4 & empty) & empty;
    return w_pawns_able_to_push(wpawns, empty_rank3);
}

uint64_t b_pawns_able_to_double_push(uint64_t bpawns, uint64_t empty) {
    const uint64_t empty_rank6 = shift_north(rank5 & empty) & empty;
    return b_pawns_able_to_push(bpawns, empty_rank6);
}

uint64_t w_pawn_moves_bb(Board *b, int idx) {
    uint64_t piece_bb = get_square_bit(idx) & b->piece_bb[WHITE | PAWN];
    return w_single_push_targets(piece_bb, b->empty) | w_double_push_targets(piece_bb, b->empty);
}

uint64_t b_pawn_moves_bb(Board *b, int idx) {
    uint64_t piece_bb = get_square_bit(idx) & b->piece_bb[BLACK | PAWN];
    return b_single_push_targets(piece_bb, b->empty) | b_double_push_targets(piece_bb, b->empty);
}

/*
 * Return a bitboard of all the valid moves for a piece that is placed on the square `square_idx`.
 * If there is no piece there (shouldn't happen) then return empty bitboard.
 * FIXME: implement for the following piece types:
 * - [x] pawns
 * - [ ] kings
 * - [ ] queens
 * - [ ] knights
 * - [ ] bishops
 * - [ ] rooks
 *   */
uint64_t get_possible_moves(Board *b, uint8_t square_idx) {
    uint16_t colors[] = { WHITE, BLACK };
    uint16_t pieces[] = { PAWN, KNIGHT, BISHOP, QUEEN, KING, ROOK };
    uint64_t square_idx_bb =  get_square_bit(square_idx);

    for (uint16_t color_idx = 0; color_idx <= 1; color_idx++) {
        uint16_t color = colors[color_idx];
        for (uint16_t piece_idx = 0; piece_idx <= 5; piece_idx++) {
            uint16_t piece = pieces[piece_idx];
            uint64_t piece_bb = b->piece_bb[color | piece];
            if ((piece_bb & square_idx_bb) > 0) {
                // the piece is on the given square -> dispatch on the kind of piece
                if ((color | piece) == (WHITE | PAWN)) {
                    return w_pawn_moves_bb(b, square_idx);
                }
                else if ((color | piece) == (BLACK | PAWN)) {
                    return b_pawn_moves_bb(b, square_idx);
                }
                else {
                    // FIXME: implement the rest of the moves for other piece types
                    return (uint64_t)0;
                }
            }
        }
    }
    // should ideally never reach here
    return (uint64_t)0;
}


/* see
 * https://www.chessprogramming.org/General_Setwise_Operations#Update_by_Move
 * */
void move_piece(Board* b, Move* m) {
    if (m->color == COLOR_NONE || m->piece == PIECE_NONE) {
        // shouldnt happen, there should always be a piece that we are moving
        return;
    }
    uint64_t from_bb = (uint64_t)1 << m->from;
    uint64_t to_bb   = (uint64_t)1 << m->to;
    uint64_t from_to_bb   = from_bb ^ to_bb;

    b->piece_bb[m->color | m->piece] ^= from_to_bb;
    b->occupied ^= from_to_bb;
    b->empty ^= from_to_bb;

    if (m->captured_color > 0 && m->captured_piece > 0) {
        // capture
        b->piece_bb[m->captured_color | m->captured_piece] ^= to_bb;
    }
    return;
}
