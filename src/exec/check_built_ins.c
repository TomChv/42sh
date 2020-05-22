/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** check_built_ins.c
*/

#include "built_ins.h"
#include "common.h"
#include "definition.h"

static const char *BUILT_INS[] = {
    "where",
    "which",
    "cd",
    "env",
    "setenv",
    "unsetenv",
    "repeat",
    "exit",
    "echo",
    "set",
    "unset",
    "alias",
    "unalias",
    NULL
};

void (*fct_built_int[])(char **tab, head_t *head) = {
    where_which,
    where_which,
    cd_fct,
    my_env,
    my_setenv,
    my_unsetenv,
    repeat,
    exit_cmd,
    echo,
    create_local_env,
    unset_alias,
    create_alias,
    unset_alias,
};

int is_cmd_built_in(char **tab, head_t *head)
{
    int a = 0;

    for (; BUILT_INS[a] != NULL; a++)
        if (strcmp(BUILT_INS[a], tab[0]) == 0)
            break;
    if (BUILT_INS[a] == NULL)
        return (0);
    fct_built_int[a](tab, head);
    return (1);
}
