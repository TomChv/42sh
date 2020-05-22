/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Sort alias linked list
*/

#include "alias.h"
#include <string.h>

static void swap_node(alias_t *node1, alias_t *node2)
{
    char *tmp_alias = strdup(node1->alias);
    char *tmp_command = strdup(node1->command);

    node1->alias = strdup(node2->alias);
    node1->command = strdup(node2->command);
    node2->alias = tmp_alias;
    node2->command = tmp_command;
}

static bool bridge_swap(alias_t *node1, alias_t *node2)
{
    if (strcmp(node1->alias, node2->alias) < 0) {
        swap_node(node1, node2);
        return true;
    }
    return false;
}

void sort_alias(alias_t **alias)
{
    bool swap = false;
    alias_t *head = NULL;
    alias_t *old = NULL;

    do {
        swap = false;
        head = *alias;
        while (head->next != old) {
            swap = bridge_swap(head, head->next);
            head = head->next;
        }
        old = head;
    } while (swap);
}