// NOTE: LLM
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "bitboard.h"
#include "sliding.h"


#define ASSERT_EQ_U64(expected, actual) do { \
    if ((uint64_t)(expected) != (uint64_t)(actual)) { \
        printf("FAIL: %s:%d expected %" PRIu64 " got %" PRIu64 "\n", \
               __FILE__, __LINE__, (uint64_t)(expected), (uint64_t)(actual)); \
        return 1; \
    } \
} while (0)

int test_ray_table_north_west(void) {
    RayTable* rt = calloc(1, sizeof(RayTable));
    init_ray_table(rt);
    ASSERT_EQ_U64(rt->table[E4][NW], (BB_D5 | BB_C6 | BB_B7 | BB_A8));
    free(rt);
    return 0;
}

int test_ray_table_south_east(void) {
    RayTable* rt = calloc(1, sizeof(RayTable));
    init_ray_table(rt);
    ASSERT_EQ_U64(rt->table[E4][SE], (BB_F3 | BB_G2 | BB_H1));
    free(rt);
    return 0;
}

int test_ray_table_south_west(void) {
    RayTable* rt = calloc(1, sizeof(RayTable));
    init_ray_table(rt);
    ASSERT_EQ_U64(rt->table[E4][SW], (BB_D3 | BB_C2 | BB_B1));
    free(rt);
    return 0;
}

int test_bit_scan_reverse(void) {
    ASSERT_EQ_U64(bit_scan_reverse(0x0000000000000001ULL), 0);
    ASSERT_EQ_U64(bit_scan_reverse(0x0000000000000002ULL), 1);
    ASSERT_EQ_U64(bit_scan_reverse(0x0000000000000100ULL), 8);
    ASSERT_EQ_U64(bit_scan_reverse(0x8000000000000000ULL), 63);
    ASSERT_EQ_U64(bit_scan_reverse(0x000000000000FFFFULL), 15);
    ASSERT_EQ_U64(bit_scan_reverse(0x0000F0000000ULL),     31);
    ASSERT_EQ_U64(bit_scan_reverse(0x00FF00FF00000000ULL), 55);
    ASSERT_EQ_U64(bit_scan_reverse(0xFFFFFFFFFFFFFFFFULL), 63); // all bits set
    // Single high bit mixed with low bits
    ASSERT_EQ_U64(bit_scan_reverse(0x0100000000000001ULL), 56);
    // High bit with a couple of lower bits
    ASSERT_EQ_U64(bit_scan_reverse(0x8000000000000005ULL), 63);
    return 0;
}


int main(void) {
    if (test_ray_table_north_west() == 0) {
        printf("PASS\n");
    }
    if (test_ray_table_south_east() == 0) {
        printf("PASS\n");
    }
    if (test_ray_table_south_west() == 0) {
        printf("PASS\n");
    }
    if (test_bit_scan_reverse() == 0) {
        printf("PASS\n");
    }
    return 1;
}

