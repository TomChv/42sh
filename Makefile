##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Sources for input part
##

## Include ############################################
include ./compilation/execution.mk
include ./compilation/parser.mk
include ./compilation/input.mk
include ./compilation/common.mk
include ./compilation/tests.mk
include ./compilation/built_ins.mk
#######################################################

## USEFUL DEF ########################################
SHELL	=	/bin/sh
CC		=	gcc
RM		=	rm -f
#######################################################

## Sources ############################################
MAIN	=	main.c

SRC 	=	src/sh42.c		\
			$(COMMON_SRC)	\
			$(EXEC_SRC)		\
			$(PARSER_SRC)	\
			$(INPUT_SRC)	\
			$(BUILT_IN_SRC)

TEST	=	$(TEST_PARSER_SRC)
#######################################################

## OBJ ################################################
MAIN_OBJ	=	$(MAIN:.c=.o)
SRC_OBJ		=	$(SRC:.c=.o)
TEST_OBJ	=	$(TEST:.c=.o)
#######################################################

## FLAGS ##############################################
CFLAGS		=	-Wall -Wextra
CPPFLAGS	=	-iquote include/
LDFLAGS		=
#######################################################

## NAMES ##############################################
BIN			=   42sh
TEST_BIN	=	unit_tests
#######################################################

## RULES ##############################################
.PHONY: all
all:	$(BIN)
$(BIN):	$(MAIN_OBJ) $(SRC_OBJ)
	$(CC) -o $(BIN) $(MAIN_OBJ) $(SRC_OBJ)

## Debug
.PHONY:	debug
debug: fclean
debug:	CFLAGS += -g3
debug:	$(BIN)

## Push (Use it before commit)
.PHONY:	push
push: 	clean
push:	CFLAGS += -Werror -Wshadow -Wformat=2 -Wformat-overflow 		  	\
		-Wformat-truncation -Wundef -Wmissing-attributes -Wmissing-braces 	\
		-Wmultistatement-macros -Wmisleading-indentation
push:	$(BIN)

.PHONY:
tests_run:  CFLAGS += --coverage
tests_run:  LDFLAGS += -lcriterion -DUNIT_TEST
tests_run:	$(SRC_OBJ) $(TEST_OBJ)
	$(CC) -o $(TEST_BIN) $(SRC_OBJ) $(TEST_OBJ) $(LDFLAGS) $(CFLAGS)
	./$(TEST_BIN)
	gcovr -b --exclude-directories tests
	gcovr -r . --exclude-directories tests
	@$(RM) $(TEST_BIN)

## Clear rules
.PHONY: clean
clean:
	@$(RM)	$(MAIN_OBJ)
	@$(RM)	$(SRC_OBJ)
	@$(RM)	$(TEST_OBJ)

.PHONY: fclean
fclean: clean
	@$(RM)	$(BIN)
	@$(RM)  $(TEST_BIN)
	@$(RM)	*.gc*

.PHONY: re
re:	fclean all clean
