#!/bin/sh

gcc -Wall -Wextra -pedantic -Werror bitboard.c set_operations.c one_step.c -o bitboard
