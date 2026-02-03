#pragma once

#include <stdlib.h>
#include "one_step.h"

typedef enum {
    NO,
    SO,
    EA,
    WE,
    NE,
    NW,
    SE,
    SW,
} Direction;

typedef struct {
    uint64_t table[64][8];
} RayTable;

void init_ray_table(RayTable* rt);
uint64_t horizontal_rays_for_square(RayTable* rt, int sq);
uint64_t vertical_rays_for_square(RayTable* rt, int sq);
uint64_t diagonal_rays_for_square(RayTable* rt, int sq);
uint64_t antidiagonal_rays_for_square(RayTable* rt, int sq);
uint64_t hv_rays_for_square(RayTable* rt, int sq);
uint64_t da_rays_for_square(RayTable* rt, int sq);
uint64_t hvda_rays_for_square(RayTable* rt, int sq);
