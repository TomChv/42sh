/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** init_exec.c
*/
#include <string.h>
#include <stdlib.h>
#include "input.h"

char *verif_cmd(char *str);

static char *init_exec_new_line(pos_t *t, char *temp)
{
    size_t len = 0;
    char *elem = NULL;

    elem = t->buffer[0];
    elem += 3;
    for (int a = 0; t->buffer[a]; len += strlen(t->buffer[a]), a++);
    temp = calloc(len - 2, sizeof(char));
    if (temp == NULL)
        die("calloc");
    temp = strcpy(temp, elem);
    for (int a = 1; t->buffer[a]; strcat(temp, t->buffer[a]), a++);
    return (temp);
}

char *init_exec(pos_t *t)
{
    char *temp = NULL;

    if (t->ind >= 1)
        temp = init_exec_new_line(t, temp);
    else {
        temp = t->buffer[0];
        temp += 3;
        temp = strdup(temp);
    }
    temp = verif_cmd(temp);
    t->h.history = append(t->h.history, temp);
    t->h.first_time = true;
    if (t->h.temp != NULL)
        free(t->h.temp);
    return (temp);
}
