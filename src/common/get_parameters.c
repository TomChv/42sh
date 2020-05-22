/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Get alias params and put it into tables
*/

#include "common.h"
#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include "magical_value.h"

/*
 * Str to array with quote handling
 */
static size_t get_nb_params(const char *line)
{
    size_t nb = 1;
    bool quotes[3] = {false, false, false};

    for (index_t i = 0; line[i]; i++) {
        UPDATE_QUOTES(quotes, line[i]);
        nb += (NOT_IN_QUOTES(quotes) && line[i] == ' ');
    }
    return nb;
}

static char *copy_string(char **line, size_t size)
{
    char *new = calloc((size + 2), sizeof(*new));
    bool quotes[3] = {false, false, false};
    index_t i = 0;

    if (new == NULL)
        return NULL;
    for (; **line; i++, (*line)++) {
        UPDATE_QUOTES(quotes, **line);
        new[i] = **line;
        if (**line == ' ' && NOT_IN_QUOTES(quotes))
            break;
    }
    (*line)++;
    new[i] = 0;
    return new;
}

static char *get_params(char **line)
{
    size_t len = 0;
    char *tmp = strdup(*line);
    bool quotes[3] = {false, false, false};

    for (; *tmp; shift_str(&tmp)) {
        UPDATE_QUOTES(quotes, *tmp);
        len += 1;
        if (*tmp == ' ' && NOT_IN_QUOTES(quotes))
            break;
    }
    free(tmp);
    return copy_string(line, len);
}

char **get_parameters(char *line)
{
    size_t sz = get_nb_params(line);
    char **tab = calloc((sz + 1), sizeof(*tab));
    index_t i = 0;

    if (tab == NULL)
        return NULL;
    for (; i != sz; i++)
        tab[i] = get_params(&line);
    tab[i] = NULL;
    return tab;
}

/*
 * Used for assembly aliases
 */
char *assembly_alias(char **args)
{
    char *alias = args[2];

    for (index_t i = 3; args[i] != NULL; i++) {
        alias = my_strcat(alias, " ", false, false);
        alias = my_strcat(alias, args[i], true, false);
    }
    return alias;
}