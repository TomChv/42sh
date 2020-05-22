/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Handle aliases
*/

#include "definition.h"
#include "common.h"
#include "magical_value.h"
#include <string.h>
#include <stdio.h>

static void find_alias(alias_t **alias, char *rm)
{
    alias_t *tmp = *alias;

    while (tmp) {
        if (!strcmp(tmp->alias, rm))
            return pop_node(alias, tmp);
        tmp = tmp->next;
    }
}

void unset_alias(char **tab, head_t *head)
{
    if (tab == NULL)
        return;
    if (my_tablen(tab) == 1) {
        dprintf(2, "%s: Too few arguments.\n", tab[0]);
    }
    for (index_t i = 1; tab[i] != NULL; i++)
        find_alias(&(head->alias), tab[i]);
}