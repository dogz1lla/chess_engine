// see https://www.chessprogramming.org/Encoding_Moves
#include "moves.h"


#define MOVE_MASK   0xFFFFu
#define TO_MASK     0x3Fu
#define FROM_MASK   0x3Fu
#define FLAGS_MASK  0x0Fu

#define CAPTURE_FLAG  0x04u


uint32_t encode_move(uint32_t from, uint32_t to, uint32_t flags) {
    /*
      takes up 16bits and not 32 actually (16 upper bits for future stuff + there could be cpu
      optimization benefits for 32 bits compared to 16 bit numbers)
      
      first 6 bits:  to
      second 6 bits: from
      next 4 bits:   flags
    */
    return (
        (uint32_t)((flags & FLAGS_MASK) << 12)
        |
        (uint32_t)((from & FROM_MASK) << 6)
        |
        (uint32_t)(to & TO_MASK)
    ) & MOVE_MASK;  // explicitly keeps upper 16 bits zeroed
}

uint32_t get_to(uint32_t move) {
    return (uint32_t)(move & TO_MASK);
}

uint32_t get_from(uint32_t move) {
    return (uint32_t)((move >> 6) & FROM_MASK);
}

uint32_t get_flags(uint32_t move) {
    return (uint32_t)((move >> 12) & FLAGS_MASK);
}

bool is_capture(uint32_t move) {
    uint32_t flags = get_flags(move);
    return (flags & CAPTURE_FLAG) != 0;
}
