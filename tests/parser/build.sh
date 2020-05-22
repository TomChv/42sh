#!/bin/sh
gcc -o mouli_parser tests/parser/mouli_parser.c                     \
src/parser/clean_string.c src/common/my_str_to_array.c              \
src/parser/clean_red.c src/parser/clean_sep.c                       \
src/parser/sup_space_n_tab.c src/common/my_strcat.c                 \
src/parser/reorganise_line.c src/parser/lexer_errors.c             \
-I include/ -g