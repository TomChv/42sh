/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** locate_command.c
*/

#include <stdbool.h>
#include "built_ins.h"
#include "common.h"

static const char *BUILT_INS[] = {
    "where",
    "which",
    "cd",
    "env",
    "setenv",
    "unsetenv",
    "foreach",
    "if",
    "repeat",
    "exit",
    "echo",
    NULL
};

void print_path(char **tab, bool where, char *str)
{
    int w = 0;
    int perm = -1;
    bool ok = false;

    for (; tab[w] != NULL; w++) {
        perm = access(tab[w], F_OK);
        if (!perm) {
            printf("%s\n", tab[w]);
            ok = true;
        }
        if (!perm && !where)
            break;
    }
    if (ok == false)
        dprintf(2, "%s: Command not found.\n", str);
}

void where_which_func(char *str, bool where)
{
    char *path = strdup(getenv("PATH"));
    char **tab = my_str_to_array(path, ':');

    if (tab == NULL) {
        dprintf(2, "%s: Command not found.\n", str);
        return;
    }
    for (int a = 0; tab[a] != NULL; a++) {
        tab[a] = strdup(tab[a]);
        tab[a] = realloc(tab[a], strlen(tab[a]) + strlen(str) + 2);
        tab[a] = strcat(strcat(tab[a], "/"), str);
    }
    print_path(tab, where, str);
    for (int a = 0; tab[a] != NULL; a++)
        free(tab[a]);
    free(tab);
    free(path);
}

bool is_shell_built_in(char *str)
{
    for (int a = 0; BUILT_INS[a] != NULL; a++)
        if (strcmp(BUILT_INS[a], str) == 0) {
            dprintf(2, "%s: shell built-in command.\n", BUILT_INS[a]);
            return (true);
        }
    return (false);
}

void where_which(char **tab, UNUSED head_t *head)
{
    bool where = !strcmp(tab[0], "where");

    if (my_tablen(tab) < 2) {
        dprintf(2, "%s: Too few arguments.\n", tab[0]);
        return;
    }
    for (int a = 1; tab[a]; a++) {
        if (is_shell_built_in(tab[a]) == true)
            continue;
        where_which_func(tab[a], where);
    }
}
