#include <stdint.h>


struct Board {
    uint64_t wking;
    uint64_t bking;

    uint64_t wqueen;
    uint64_t bqueen;

    uint64_t wrook;
    uint64_t brook;

    uint64_t wknight;
    uint64_t bknight;

    uint64_t wbishop;
    uint64_t bbishop;

    uint64_t wpawn;
    uint64_t bpawn;
};

struct Board* init_board();
uint64_t overlap_all(struct Board* b);
