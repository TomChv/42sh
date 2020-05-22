/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Transfrom a string into an array
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "magical_value.h"

static int get_nb_elem(char *str, char delim)
{
    int count = (str != NULL);

    if (str == NULL)
        return count;
    for (int i = 0; str[i]; i++)
        count += (str[i] == delim);
    return count;
}

char **my_str_to_array(char *str, char delim)
{
    char **tab = calloc((get_nb_elem(str, delim) + 1), sizeof(*tab));
    char del[2] = {delim, 0};
    char *token = strtok(str, del);
    index_t i = 0;

    if (tab == NULL)
        return NULL;
    for (; token != 0; i++) {
        tab[i] = token;
        token = strtok(0, del);
    }
    tab[i] = NULL;
    return tab;
}
