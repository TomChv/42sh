/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** echo
*/

#include "definition.h"
#include <string.h>
#include <stdio.h>

void echo(char **args, UNUSED head_t *head)
{
    bool n = (args[1] != NULL && !strcmp(args[1], "-n"));

    if (args[1] == NULL)
        return;
    for (int i = 1 + (int)n; args[i] != NULL; i++) {
        printf("%s", args[i]);
        if (args[i + 1] != NULL)
            printf(" ");
    }
    if (!n)
        printf("\n");
}