/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** linked_list.c
*/
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "linked_list.h"

void die(const char *s);

dblist_t *new_double_list(void)
{
    dblist_t *new_node = calloc(1, sizeof(dblist_t));

    if (new_node == NULL)
        die("calloc");
    new_node->length = 0;
    new_node->head = NULL;
    new_node->tail = NULL;
    return (new_node);
}

static char *get_time(void)
{
    char *str = NULL;
    unsigned int length = 2;
    time_t raw_time;
    struct tm * time_info;

    time(&raw_time);
    time_info = localtime(&raw_time);
    str = asctime(time_info);
    if (str[strcspn(str, ":") - 2] == '0')
        length = 1;
    str += strcspn(str, ":") - length;
    str[3+length] = '\0';
    return (strdup(str));
}

dblist_t *append(dblist_t *list, char *data)
{
    ndbl_t *new_node;

    if (list == NULL)
        return (list);
    new_node = calloc(1, sizeof(ndbl_t));
    if (new_node == NULL)
        die("calloc");
    new_node->data = strdup(data);
    new_node->date = get_time();
    new_node->next = NULL;
    if (list->tail == NULL) {
        new_node->prev = NULL;
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }
    list->length++;
    return (list);
}

void list_delete(dblist_t **p_list)
{
    ndbl_t *elem;
    ndbl_t *temp;

    if (*p_list == NULL)
        return;
    temp = (*p_list)->head;
    while (temp != NULL) {
        elem = temp;
        free(temp->data);
        free(temp->date);
        temp = temp->next;
        free(elem);
    }
    free(*p_list);
    *p_list = NULL;
}
