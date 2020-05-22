##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Sources for parsing part 
##

## ONLY Allowed to be edited by Edouard and Tom

PARSER_FILE	=\
	parser.c				\
	clean_string.c			\
	clean_red.c				\
	clean_sep.c				\
	sup_space_n_tab.c		\
	lexer_errors.c			\
	cmd_to_list.c			\
	cmd_ll.c				\
	reorganise_line.c		\
	clean_list.c			\
	handle_job_control.c	\
	inhib.c					\
	replace_env_vars.c

PARSER_SRC=$(addprefix src/parser/, $(PARSER_FILE))