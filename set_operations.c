#include "set_operations.h"


uint64_t bit_complement(uint64_t b) {return ~b;}
uint64_t bit_intersection(uint64_t a, uint64_t b) {return a & b;}
uint64_t bit_union(uint64_t a, uint64_t b) {return a | b;}
uint64_t bit_xor(uint64_t a, uint64_t b) {return a ^ b;}
