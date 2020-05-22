/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** linked_list.c
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node_double_s {
    char *data;
    char *date;
    struct node_double_s *next;
    struct node_double_s *prev;
} ndbl_t;

typedef struct double_list_s {
    int length;
    ndbl_t *head;
    ndbl_t *tail;
} dblist_t;

dblist_t *new_double_list(void);
dblist_t *append(dblist_t *list, char *data);
void list_delete(dblist_t **p_list);

#endif //PSU_42SH_2019_LINKED_LIST_H
