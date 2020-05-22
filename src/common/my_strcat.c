/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** 
*/

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "magical_value.h"
#include "common.h"

char *my_strcat(char *s1, char *s2, bool f1, bool f2)
{
    size_t size = strlen(s1) + strlen(s2);
    char *cat = calloc((size + 1), sizeof(*cat));
    index_t i = 0;
    index_t y = 0;

    if (cat == NULL)
        return NULL;
    if (s1 != NULL)
        for (; s1[i]; i++)
            cat[i] = s1[i];
    if (s2 != NULL)
        for (; s2[y]; y++)
            cat[i + y] = s2[y];
    cat[i + y] = 0;
    f1 == true ? clear_str(&s1) : 0;
    f2 == true ? clear_str(&s2) : 0;
    return cat;
}
