/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** lexer_errors
*/

#include <stdio.h>
#include "magical_value.h"
#include "shell.h"
#include "parser.h"
#include <string.h>

static bool other_checks(const char *str)
{
    bool quotes[3] = {false, false, false};

    for (index_t i = 0; str[i]; i++) {
        UPDATE_QUOTES(quotes, str[i]);
        if (!NOT_IN_QUOTES(quotes) || (str[i] == '&' || !IS_SEP(str[i])))
            continue;
        if (!str[i + 1] || IS_SEP(str[i + 2])) {
            dprintf(2, "Invalid null function.\n");
            return false;
        }
    }
    return true;
}

static bool redirect_check(const char *str)
{
    bool invalid = str[0] == '|';
    bool quotes[3] = {false, false, false};

    for (index_t i = 0; str[i]; i++) {
        UPDATE_QUOTES(quotes, str[i]);
        if (invalid || (NOT_IN_QUOTES(quotes) && ((str[i] == ';' || !i)
            && str[i + 1] && str[i + 2] == '|'))) {
            dprintf(2, "Invalid null function.\n");
            return false;
        }
        if (!NOT_IN_QUOTES(quotes) || (str[i] != '>' && str[i] != '<'))
            continue;
        if (!str[i + 1] || IS_SEP(str[i + 2])) {
            dprintf(2, "Missing name for redirect.\n");
            return false;
        }
    }
    return true;
}

static bool and_check(const char *str)
{
    index_t i = 0;

    for (; str[i] == '&' || str[i] == ' '; i++);
    if (!str[i])
        return false;
    for (; str[i]; i++) {
        if (!strncmp(str + i, "&& &", 4) || !strncmp(str + i, "&& ;", 4)) {
            dprintf(2, "Invalid null function.\n");
            return false;
        }
        if (!strncmp(str + i, "&&", 2) && !str[i + 2]) {
            dprintf(2, "Invalid null function.\n");
            return false;
        }
    }
    return true;
}

bool lexer_check(char *str)
{
    if (str == NULL)
        return false;
    return (redirect_check(str) && other_checks(str) && and_check(str));
}
