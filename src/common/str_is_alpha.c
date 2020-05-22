/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** str_is_alpha.c
*/

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

static const char *ALPHA_NUM =
": Variable name must contain alphanumeric characters.\n";

int str_is_alpha_num(char *str, char *error)
{
    int n = 0;

    while (str[n]) {
        if (isalnum(str[n]) == 0) {
            dprintf(2, "%s", error);
            dprintf(2, "%s", ALPHA_NUM);
            return (1);
        }
        n++;
    }
    return (0);
}
