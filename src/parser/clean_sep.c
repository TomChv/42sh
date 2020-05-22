/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** 
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "common.h"
#include "magical_value.h"
#include "parser.h"

int pass_char(char **line, char red);

#include <stdio.h>

//   if (IS_QUOTE(*cmd))


static int get_nb_sep(char *cmd)
{
    size_t sep = 0;
    bool quotes[3] = {false, false, false};

    for (; *cmd != 0; cmd++) {
        UPDATE_QUOTES(quotes, *cmd);
        if ((*cmd == '|' || *cmd == '&') && NOT_IN_QUOTES(quotes)) {
            sep += pass_char(&cmd, (*cmd == '|') ? '|' : '&');
        }
        if (*cmd == 0)
            break;
    }
    return sep;
}

char *clean_sep(char *cmd)
{
    size_t sep = get_nb_sep(cmd);
    char *new = calloc((strlen(cmd) + (sep * 2) + 1), sizeof(*new));
    index_t i = 0;
    bool quotes[3] = {false, false, false};

    if (new == NULL)
        return NULL;
    for (index_t y = 0; cmd[y]; y++) {
        quotes[QUOTE] = IS_QUOTE(cmd[y]) == !quotes[QUOTE];
        quotes[SIMPLE] = IS_SIMPLE(cmd[y]) == !quotes[SIMPLE];
        new[i++] = cmd[y];
        if (NOT_IN_QUOTES(quotes) && (IS_NEXT_DIR(cmd[y], cmd[y + 1], '|')
            || IS_NEXT_DIR(cmd[y], cmd[y + 1], '&')))
            new[i++] = ' ';
        if (NOT_IN_QUOTES(quotes) && y >= 1
            && IS_SAME(cmd[y], cmd[y - 1], '|', '&'))
            new[i++] = ' ';
    }
    new[i] = 0;
    free(cmd);
    return new;
}