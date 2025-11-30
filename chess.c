#include <stdlib.h>
#include <stdio.h>

#include "bitboard.h"


int main(void) {
    struct Board *b = calloc(1, sizeof(struct Board));
    if (b == NULL) {
        printf("%s\n", "Board allocation failed.");
        return 1;
    }

    init_board(b);
    print_bits(w_pawns_able_to_double_push(b->wpawn, b->empty));
    free(b);
    return 0;
}
