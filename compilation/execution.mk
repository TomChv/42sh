##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Sources for execution part 
##

## ONLY Allowed to be edited by Arthur and Théo

EXEC_FILE	=	exec.c			\
			execution.c		\
			check_built_ins.c	\
			left_redirection.c	\
			right_redirection.c	\
			pipe.c			\
			error_gestion_cmd.c	\

EXEC_SRC=$(addprefix src/exec/, $(EXEC_FILE))
