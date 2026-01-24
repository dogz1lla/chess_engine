#pragma once
#include <stdbool.h>
#include <stdint.h>


uint32_t encode_move(uint32_t from, uint32_t to, uint32_t flags);
uint32_t get_to(uint32_t move);
uint32_t get_from(uint32_t move);
uint32_t get_flags(uint32_t move);
bool is_capture(uint32_t move);
