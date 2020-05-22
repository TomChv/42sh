/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** cmd_ll
*/

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "parser.h"

void push_element_cmd(cmd_t **cmd, char *args, char *sep)
{
    cmd_t *new = calloc(1, sizeof(cmd_t));
    cmd_t *tmp = *cmd;

    if (new == NULL)
        return;
    new->args = strdup(args);
    new->sep = sep == NULL ? NULL : strdup(sep);
    new->next = NULL;
    new->job = 0;
    new->prev = NULL;
    free(args);
    free(sep);
    if (tmp == NULL) {
        *cmd = new;
        return;
    }
    for (; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new;
    new->prev = tmp;
}