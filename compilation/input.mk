##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Sources for input part 
##

## ONLY Allowed to be edited by Killian


INPUT_NAME	=	input				\
				print				\
				terminal			\
				get_data			\
				init_exec			\
				special_key			\
				linked_list			\
				control_tower		\
				builtin_input		\
				auto_compression	\

INPUT_SRC = $(addprefix src/input/, $(addsuffix .c, $(INPUT_NAME)))
