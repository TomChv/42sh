/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Reorganise line
*/

#include "magical_value.h"
#include "common.h"

char *erase_space_n_tab(char *str, bool f);

void ignore_and(char *str)
{
    for (index_t i = 0; str[i]; i++)
        if (str[i] == '&' || str[i] == ' ')
            str[i] = ' ';
        else
            break;
}

static size_t count_nb_and(const char *str, index_t i)
{
    size_t count = 0;

    for (; str[i] == ' ' || str[i] == '&'; i++)
        count += (str[i] == '&');
    return count;
}

char *rewrite_line(char *str)
{
    size_t cnt = 0;
    bool cmd = false;

    for (index_t i = 0; str[i]; i++) {
        if (str[i] != '&' && str[i] != ' ')
            cmd = true;
        if (str[i] == ';')
            cmd = false;
        if (!cmd && str[i] == '&') {
            cnt = count_nb_and(str, i);
            for (cnt += i - (cnt % 2); str[i] && i != cnt; str[i] = ' ', i++);
        }
        if (!str[i])
            break;
    }
    return erase_space_n_tab(str, true);
}