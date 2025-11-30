#include "one_step.h"


const uint64_t not_a_file = 0xfefefefefefefefe; // ~0x0101010101010101
const uint64_t not_h_file = 0x7f7f7f7f7f7f7f7f; // ~0x8080808080808080


uint64_t shift_north(uint64_t b)    {return b << 8;}
uint64_t shift_south(uint64_t b)    {return b >> 8;}
uint64_t shift_east(uint64_t b)      {return (b << 1) & not_a_file;}
uint64_t shift_north_east(uint64_t b) {return (b << 9) & not_a_file;}
uint64_t shift_south_east(uint64_t b) {return (b >> 7) & not_a_file;}
uint64_t shift_west(uint64_t b)      {return (b >> 1) & not_h_file;}
uint64_t shift_south_west(uint64_t b) {return (b >> 9) & not_h_file;}
uint64_t shift_north_west(uint64_t b) {return (b << 7) & not_h_file;}
uint64_t rotate_left (uint64_t x, int s) {return (x << s) | (x >> (64-s));}
uint64_t rotate_right(uint64_t x, int s) {return (x >> s) | (x << (64-s));}
