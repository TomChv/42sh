/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** str_is_num
*/

#include <ctype.h>

int str_is_num(const char *str)
{
    int n = 0;

    while (str[n]) {
        if (isdigit(str[n]) == 0)
            return (1);
        n++;
    }
    return (0);
}
