##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Built-ins compilation
##

BUILT_IN_FILE=\
	echo.c					\
	alias/display_alias.c	\
	alias/unset_alias.c		\
	alias/create_alias.c	\
	alias/set_local_env.c	\
	alias/replace_alias.c	\
	alias/sort_alias.c		\
	env.c 					\
	cd_function.c			\
	locate_command.c		\
	repeat.c				\
	exit.c

BUILT_IN_SRC=$(addprefix src/built_ins/, $(BUILT_IN_FILE))