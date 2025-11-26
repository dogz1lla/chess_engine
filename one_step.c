#include "one_step.h"


const uint64_t notAFile = 0xfefefefefefefefe; // ~0x0101010101010101
const uint64_t notHFile = 0x7f7f7f7f7f7f7f7f; // ~0x8080808080808080


uint64_t shift_north(uint64_t b)    {return b << 8;}
uint64_t shift_south(uint64_t b)    {return b >> 8;}
uint64_t shiftEast(uint64_t b)      {return (b << 1) & notAFile;}
uint64_t shiftNortheast(uint64_t b) {return (b << 9) & notAFile;}
uint64_t shiftSoutheast(uint64_t b) {return (b >> 7) & notAFile;}
uint64_t shiftWest(uint64_t b)      {return (b >> 1) & notHFile;}
uint64_t shiftSouthwest(uint64_t b) {return (b >> 9) & notHFile;}
uint64_t shiftNorthwest(uint64_t b) {return (b << 7) & notHFile;}
uint64_t rotateLeft (uint64_t x, int s) {return (x << s) | (x >> (64-s));}
uint64_t rotateRight(uint64_t x, int s) {return (x >> s) | (x << (64-s));}
