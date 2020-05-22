/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Push an alias to list
*/

#include <stddef.h>
#include "definition.h"

void push_alias(alias_t **head, alias_t *new)
{
    alias_t *tmp = *head;

    if (*head == NULL) {
        *head = new;
        return;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
}
