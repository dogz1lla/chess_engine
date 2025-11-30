#include <stdlib.h>

#include "set_operations.h"
#include "bitboard.h"


int main(void) {
    struct Board *board = init_board();
    // print_bits(board->occupied);
    print_bits(board->empty);
    free(board);
    return 0;
}
