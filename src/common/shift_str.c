/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Handle shift str
*/

#include "magical_value.h"
#include <string.h>

void shift_str(char **str)
{
    int a = 0;

    for (; (*str)[a + 1] != '\0'; a++)
        (*str)[a] = (*str)[a + 1];
    (*str)[a] = '\0';
}

void shift_to_left(char *buffer, index_t shift)
{
    size_t size = strlen(buffer);

    if (shift > size)
        return;
    for (index_t i = shift; i < size; i++)
        buffer[i] = buffer[i + 1];
}

void shift_to_right(char *buffer, index_t shift, char ch)
{
    size_t size = strlen(buffer);

    for (index_t i = size; i > shift; i--)
        buffer[i] = buffer[i-1];
    buffer[shift] = ch;
    buffer[size + 1] = '\0';
}