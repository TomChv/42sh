/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Clean string
*/

#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "magical_value.h"
#include "shell.h"

void ignore_and(char *str);
char *rewrite_line(char *str);

char *clean_cmd(char *cmd)
{
    CLEAR(clear_str) char *cleaned_cmd = NULL;

    if ((cleaned_cmd = clean_red(cmd)) == NULL)
        return NULL;
    if ((cleaned_cmd = clean_sep(cleaned_cmd)) == NULL)
        return NULL;
    return erase_space_n_tab(cleaned_cmd, false);
}

char *order_cmd(char *cmd)
{
    CLEAR(clear_tab) char **tab = my_str_to_array(cmd, ';');
    char *new = NULL;

    if (tab == NULL || tab[0] == NULL)
        return NULL;
    for (index_t i = 0; tab[i]; i++) {
        tab[i] = clean_cmd(tab[i]);
        if (i == 0)
            new = strdup(tab[i]);
        else {
            new = my_strcat(new, " ; ", true, false);
            new = my_strcat(new, tab[i], true, true);
        }
    }
    free(cmd);
    return erase_space_n_tab(new, true);
}

static char *basic_verify(char *str)
{
    size_t len = (str != NULL ? strlen(str) : 0);
    int c = 0;

    if (len == 0)
        return NULL;
    for (index_t i = 0; str[i]; i++)
        c += (str[i] != ' ');
    if (!c)
        return strdup("");
    if (str[len - 1] == '\n')
        str[len - 1] = 0;
    return str;
}

char *clean_string(char *str)
{
    char *clean_cmd = NULL;
    char *real_cmd = NULL;

    if (basic_verify(str) == NULL)
        return NULL;
    ignore_and(str);
    clean_cmd = erase_space_n_tab(str, false);
    clean_cmd = rewrite_line(clean_cmd);
    if ((real_cmd = order_cmd(clean_cmd)) == NULL)
        return NULL;
    if (real_cmd[strlen(real_cmd) - 1] == ' ')
        real_cmd[strlen(real_cmd) - 1] = 0;
    return real_cmd;
}