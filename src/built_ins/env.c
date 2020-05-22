/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** All_env_functions
*/

#include "built_ins.h"
#include "common.h"
#include <ctype.h>

extern char **environ;
static const char *TOO_MANY_ARGS = "setenv: Too many arguments.\n";
static const char *FIRST_ALPHA = "setenv: Variable name must "
                                 "begin with a letter.\n";

void my_env(char **tab, UNUSED head_t *head)
{
    char **env = environ;
    int n = 0;

    (void) tab;
    while (env[n] != NULL) {
        printf("%s\n", env[n]);
        n++;
    }
}

void my_setenv(char **name, head_t *head)
{
    int n = my_tablen(name);

    if (n > 3) {
        dprintf(2, "%s", TOO_MANY_ARGS);
        return;
    }
    if (n == 1)
        return my_env(name, head);
    if (isalpha(name[1][0]) == 0) {
        dprintf(2, "%s", FIRST_ALPHA);
        return;
    }
    if (str_is_alpha_num(name[1], name[0]))
        return;
    if (setenv(name[1], name[2], 1) == -1)
        perror("setenv: ");
}

void my_unsetenv(char **name, UNUSED head_t *head)
{
    int n = 1;

    if (my_tablen(name) < 2)
        dprintf(2, "unsetenv: Too few arguments.\n");
    while (name[n] != NULL) {
        unsetenv(name[n]);
        n++;
    }
}
