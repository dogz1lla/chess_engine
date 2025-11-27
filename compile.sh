#!/bin/sh

gcc -Wall -Wextra -pedantic -Werror chess.c bitboard.c set_operations.c one_step.c -o chess
