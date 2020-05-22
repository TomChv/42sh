/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** builtin_input.c
*/
#include <stdio.h>
#include <string.h>
#include "input.h"
#include "parameters.h"

//static void flag_excla(pos_t *t, char *command)
//{
//    char *elem = strstr(command, "!");
//
//}

static void builtin_history(pos_t *t, char *command)
{
    int i = 1;

//    if (strcmp(command, "!") == 0)
//        flag_excla(t, command);
    if (strstr(command, "history") == NULL)
        return;
    for (ndbl_t *temp = t->h.history->head; temp; temp = temp->next, i++) {
        for (int a = 0; a != 6 - nbr_length(i, 10); dprintf(1, " "), a++);
        dprintf(1, "%d  %s", i, temp->date);
        for (size_t a = 0; a != 8 - strlen(temp->date); dprintf(1, " "), a++);
        dprintf(1, "%s\r\n", temp->data);
    }
}

char *builtin_input(pos_t *t, char *command)
{
    char *temp = command;

    if (strncmp(command, "history", strlen("history")) == 0
        || strncmp(command, "!", strlen("!")) == 0) {
        builtin_history(t, command);
        return (strdup(temp += strlen(temp) - 1));
    }
    return (command);
}