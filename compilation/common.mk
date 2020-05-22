##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Sources for common part
##

## Allow to edit by all

COMMON_FILE	=	my_str_to_array.c 	\
				my_strcat.c			\
				my_tablen.c			\
				shift_str.c			\
				get_parameters.c	\
				push_alias.c		\
				pop_alias.c			\
				str_is_alpha.c		\
				my_strconcat.c		\
				str_is_num.c

COMMON_SRC=$(addprefix src/common/, $(COMMON_FILE))
