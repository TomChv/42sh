/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** my_tablen.c
*/

#include <stddef.h>

int my_tablen(char **tab)
{
    int size = 0;

    for (; tab[size] != NULL; size++);
    return (size);
}
