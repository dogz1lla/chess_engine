// see https://www.chessprogramming.org/On_an_empty_Board
#include "sliding.h"


const uint64_t ray_north      = (uint64_t)0x0101010101010100;
const uint64_t ray_south      = (uint64_t)0x0080808080808080;
const uint64_t ray_north_east = (uint64_t)0x8040201008040200;
const uint64_t ray_north_west = (uint64_t)0x0102040810204000;  // NOTE: LLM, H1:A8
const uint64_t ray_south_east = (uint64_t)0x0002040810204080;  // NOTE: LLM, A8:H1
const uint64_t ray_south_west = (uint64_t)0x0040201008040201;  // NOTE: LLM, H8:A1


void init_ray_table(RayTable* rt) {
    // north rays
    uint64_t nort = ray_north;
    for (int sq = 0; sq < 64; sq++, nort <<= 1) {
        rt->table[sq][NO] = nort;
    }

    // south rays
    uint64_t sout = ray_south;
    for (int sq = 63; sq >= 0; sq--, sout >>= 1) {
        rt->table[sq][SO] = sout;
    }

    // east rays
    const uint64_t one = 1;
    for (int sq = 0; sq < 64; sq++) {
        rt->table[sq][EA] = 2*((one << (sq|7)) - (one << sq));
    }

    // west rays
    for (int sq = 0; sq < 64; sq++) {
        rt->table[sq][WE] = (one << sq) - (one << (sq & 56));
    }

    // north-east rays
    uint64_t noea = ray_north_east;
    for (int f = 0; f < 8; f++, noea = shift_east(noea)) {
        uint64_t ne = noea;
        for (int r8 = 0; r8 < 8*8; r8 += 8, ne <<= 8) {
            rt->table[r8+f][NE] = ne;
        }
    }

    // north-west rays, H1:A8
    uint64_t nowe = ray_north_west;
    for (int f = 7; f >= 0; f--, nowe = shift_west(nowe)) {
        uint64_t nw = nowe;
        for (int r = 0; r < 8; r++, nw <<= 8) {
            int sq = r * 8 + f;
            rt->table[sq][NW] = nw;
        }
    }

    // south-east rays, A8:H1
    uint64_t soea = ray_south_east;
    for (int f = 0; f < 8; f++, soea = shift_east(soea)) {
        uint64_t se = soea;
        for (int r = 7; r >= 0; r--, se >>= 8) {
            int sq = r * 8 + f;
            rt->table[sq][SE] = se;
        }
    }

    // south-west rays, H8:A1
    uint64_t sowe = ray_south_west;
    for (int f = 7; f >= 0; f--, sowe = shift_west(sowe)) {
        uint64_t sw = sowe;
        for (int r = 7; r >= 0; r--, sw >>= 8) {
            int sq = r * 8 + f;
            rt->table[sq][SW] = sw;
        }
    }
}

uint64_t horizontal_rays_for_square(RayTable* rt, int sq) {
    return rt->table[sq][EA] | rt->table[sq][WE];
}

uint64_t vertical_rays_for_square(RayTable* rt, int sq) {
    return rt->table[sq][NO] | rt->table[sq][SO];
}

uint64_t diagonal_rays_for_square(RayTable* rt, int sq) {
    return rt->table[sq][NE] | rt->table[sq][SW];
}

uint64_t antidiagonal_rays_for_square(RayTable* rt, int sq) {
    return rt->table[sq][NW] | rt->table[sq][SE];
}

uint64_t hv_rays_for_square(RayTable* rt, int sq) {
    return horizontal_rays_for_square(rt, sq) | vertical_rays_for_square(rt, sq);
}

uint64_t da_rays_for_square(RayTable* rt, int sq) {
    return diagonal_rays_for_square(rt, sq) | antidiagonal_rays_for_square(rt, sq);
}

uint64_t hvda_rays_for_square(RayTable* rt, int sq) {
    return hv_rays_for_square(rt, sq) | da_rays_for_square(rt, sq);
}
