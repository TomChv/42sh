/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Handle inhib
*/

#include "parser.h"
#include "common.h"
#include <stdbool.h>

static char get_inhib_char(char c)
{
    const char ref[9] = "abtnvfr";
    const char tab[9] = "\a\b\t\n\v\f\r";

    for (int i = 0; ref[i]; i++)
        if (c == ref[i])
            return tab[i];
    return c;
}

void inhib_clean(char *str)
{
    bool quotes[3] = {false, false, false};

    if (str == NULL)
        return;
    for (int i = 0; str[i]; i++) {
        UPDATE_QUOTES(quotes, str[i]);
        if (str[i] != '\\')
            continue;
        shift_to_left(str, i);
        if (quotes[QUOTE] || quotes[SIMPLE])
            str[i] = get_inhib_char(str[i]);
    }
}