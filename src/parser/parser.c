/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Parser function
*/

#include <stdio.h>
#include <stdbool.h>
#include "parser.h"

char *clean_string(char *str);
bool lexer_check(char *str);
cmd_t *cmd_to_list(char *str);

cmd_t *parser(char *str)
{
    char *command = clean_string(str);

    inhib_clean(command);
    if (lexer_check(command) == false)
        return NULL;
    return cmd_to_list(command);
}