/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Clean the list
*/

#include "parser.h"
#include <string.h>
#include <stdlib.h>

static void pop_elem(cmd_t *elem, cmd_t *old)
{
    if (old->next != NULL)
        old->next->prev = elem;
    elem->next = old->next;
    free(old->args);
    free(old->sep);
    free(old);
}

static void clean_end_space(cmd_t *list)
{
    size_t len_args = 0;
    size_t len_sep = 0;

    while (list) {
        len_args = strlen(list->args);
        if (list->args[len_args - 1] == ' ')
            list->args[len_args - 1] = 0;
        if (!list->sep)
            break;
        len_sep = strlen(list->sep);
        if (list->sep[len_sep - 1] == ' ')
            list->sep[len_sep - 1] = 0;
        list = list->next;
    }
}

void clean_list(cmd_t *list)
{
    cmd_t *tmp = list;

    while (tmp->next) {
        if (!strcmp(tmp->sep, "; ") && !strlen(tmp->next->args))
            tmp->sep = strdup("&");
        if (!strcmp(tmp->sep, "&") && !strlen(tmp->next->args)) {
            pop_elem(tmp, tmp->next);
            tmp = list;
            continue;
        }
        tmp = tmp->next;
    }
    clean_end_space(list);
}