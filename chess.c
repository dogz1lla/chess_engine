#include <stdlib.h>

#include "set_operations.h"
#include "bitboard.h"


int main(void) {
    struct Board *board = init_board();
    print_bits(bit_complement(combine_all_pieces(board)));
    free(board);
    return 0;
}
