/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
**
*/

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "magical_value.h"
#include "common.h"
#include "parser.h"

char *erase_space_n_tab(char *str, bool f)
{
    char *new = calloc((strlen(str) + 1), sizeof(*new));
    bool quotes[3] = {false, false, false};
    index_t y = 0;

    if (new == NULL)
        return NULL;
    for (index_t i = 0; str[i]; i++) {
        if (str[i] == '\t')
            str[i] = ' ';
        if (str[i] > ' ' || !NOT_IN_QUOTES(quotes))
            new[y++] = str[i];
        quotes[QUOTE] = IS_QUOTE(str[i]) == !quotes[QUOTE];
        quotes[SIMPLE] = IS_SIMPLE(str[i]) == !quotes[SIMPLE];
        if (str[i] == ' ' && str[i + 1] != ' ' && y != 0
            && NOT_IN_QUOTES(quotes))
            new[y++] = str[i];
    }
    new[y] = 0;
    f == true ? clear_str(&str) : 0;
    return new;
}