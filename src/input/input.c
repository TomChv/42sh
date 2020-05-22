/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Input function
*/

#include "magical_value.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "input.h"

char *init_exec(pos_t *t);

typedef struct match_char_s {
    int nbr_p;
    int nbr_p2;
    int nbr_sq;
    int nbr_q;
    int nbr_b;
} char_t;

static char *verif_cmd_condition(char *str, char_t c)
{
    char *temp = str;
    char ch = 'z';

    if ((c.nbr_p + c.nbr_p2) % 2 != 0)
        ch = (c.nbr_p > c.nbr_p2) ? '(' : ')';
    if (c.nbr_b % 2 != 0)
        ch = '`';
    if (c.nbr_sq % 2 != 0)
        ch = 39;
    if (c.nbr_q % 2 != 0)
        ch = '"';
    if (ch != 'z') {
        dprintf(2, "Unmatched '%c'.\n", ch);
        return (strdup(temp += strlen(temp) - 1));
    }
    return (str);
}

char *verif_cmd(char *str)
{
    char_t c = {0, 0, 0, 0, 0 };

    for (index_t a = 0; str[a]; a++) {
        if (str[a] == '(')
            c.nbr_p++;
        if (str[a] == ')')
            c.nbr_p2++;
        if (str[a] == '"')
            c.nbr_q++;
        if (str[a] == '`')
            c.nbr_b++;
        if (str[a] == 39)
            c.nbr_sq++;
    }
    return (verif_cmd_condition(str, c));
}

char *input(pos_t *t)
{
    char ch = '\0';

    if (isatty(0) == 0)
        return (NULL);
    for (; 1; ch = '\0') {
        if (read(STDIN_FILENO, &ch, 1) == -1 && errno != EAGAIN)
            die("read");
        if (command_char(ch, t) == 1)
            break;
    }
    return (builtin_input(t, init_exec(t)));
}
