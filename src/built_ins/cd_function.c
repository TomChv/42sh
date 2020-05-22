/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** cd_function.c
*/

#include "built_ins.h"
#include "common.h"

static const char *NO_HOME = "cd: No home directory.\n";
static const char *NO_DIR = ": No such file or directory.\n";

char *get_pwd(void)
{
    char *pwd = NULL;

    pwd = getcwd(pwd, 0);
    return (pwd);
}

void check_path(char **str)
{
    char *path = NULL;
    char const *env_var = (*(*str) == '-' ? "OLDPWD" : "HOME");
    char const *msg = (*(*str) == '-' ? NO_DIR : NO_HOME);

    if ((*str)[0] != '~' && (*str)[0] != '-')
        return;
    path = strdup(getenv(env_var));
    if (path == NULL) {
        dprintf(2, "%s", msg);
        return;
    }
    shift_str(str);
    path = realloc(path, strlen(path) + strlen(*str) + 1);
    strcat(path, (*str));
    free(*str);
    (*str) = strdup(path);
    free(path);
}

void cd(char **str, head_t *head)
{
    char *tab_old[4] = {"setenv", "OLDPWD", get_pwd(), NULL};
    char *tab_new[4] = {"setenv", "PWD", NULL, NULL};

    check_path(str);
    if (chdir(*str) == -1) {
        dprintf(2, "%s: %s.\n", *str, strerror(errno));
        return;
    }
    my_setenv(tab_old, head);
    tab_new[2] = get_pwd();
    my_setenv(tab_new, head);
    free(tab_old[2]);
    free(tab_new[2]);
}

void cd_fct(char **tab, head_t *head)
{
    char *str = NULL;

    if (my_tablen(tab) > 2) {
        dprintf(2, "cd: Too many arguments.\n");
        return;
    }
    if (tab[1] == NULL) {
        str = strdup(getenv("HOME"));
        if (str == NULL) {
            dprintf(2, "%s", NO_HOME);
            return;
        }
        cd(&str, head);
        free(str);
    } else
        cd(&tab[1], head);
}
