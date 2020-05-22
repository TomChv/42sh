/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Pop alias from the list
*/

#include <stdlib.h>
#include "definition.h"

void pop_node(alias_t **alias, alias_t *pop)
{
    alias_t *head = *alias;

    if (head == pop) {
        *alias = pop->next;
        free(head->command);
        free(head->alias);
        free(head);
        return;
    }
    while (head) {
        if (head->next == pop) {
            head->next = pop->next;
            free(pop->command);
            free(pop->alias);
            free(pop);
            return;
        }
        head = head->next;
    }
}