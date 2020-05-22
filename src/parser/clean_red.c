/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Clean redirection
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "magical_value.h"
#include "parser.h"

int pass_char(char **line, char red)
{
    size_t nb_red = 0;

    for (; **line == red; (*line)++, nb_red++);
    return nb_red;
}

static int get_nb_redirect(char *cmd)
{
    size_t nb_red = 0;
    bool quote = false;

    for (; *cmd != 0; cmd++) {
        if (*cmd == '"')
            quote = (quote == false);
        if (quote == false && (*cmd == '>' || *cmd == '<'))
            nb_red += pass_char(&cmd, (*cmd == '<') ? '<' : '>');
        if (*cmd == 0)
            break;
    }
    return nb_red;
}

char *clean_red(char *cmd)
{
    size_t red = get_nb_redirect(cmd);
    char *new = calloc((strlen(cmd) + (red * 2) + 1), sizeof(*new));
    index_t i = 0;
    bool quotes[3] = {false, false, false};

    if (new == NULL)
        return NULL;
    for (index_t y = 0; cmd[y]; y++) {
        UPDATE_QUOTES(quotes, cmd[y]);
        new[i++] = cmd[y];
        if (NOT_IN_QUOTES(quotes) && (IS_NEXT_DIR(cmd[y], cmd[y + 1], '>')
            || IS_NEXT_DIR(cmd[y], cmd[y + 1], '<')))
            new[i++] = ' ';
        if (NOT_IN_QUOTES(quotes) && y >= 1
            && IS_SAME(cmd[y], cmd[y - 1], '<', '>'))
            new[i++] = ' ';
    }
    new[i] = 0;
    return new;
}