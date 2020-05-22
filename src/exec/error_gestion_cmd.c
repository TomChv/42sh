/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** error_gestion_cmd.c
*/

#include "exec.h"
#include "common.h"

static const char *CMD_NOT_FOUND = ": Command not found.\n";
static const char *PERM_DENIED = ": Permission denied.\n";
extern char **environ;

static int check_perm(char *str)
{
    if (access(str, F_OK) != 0)
        return (1);
    if (access(str, X_OK) != 0)
        return (2);
    return (0);
}

int check_cmd_perm(char **env, char *str)
{
    int perm = -1;
    int a = 0;

    for (; env[a] != NULL; a++) {
        perm = check_perm(env[a]);
        if (perm == 0)
            return (0);
    }
    if (perm != 0)
        dprintf(2, "%s%s", str, (perm == 1 ? CMD_NOT_FOUND : PERM_DENIED));
    return (-1);
}

int check_perm_str(char *str)
{
    int perm = check_perm(str);
    const char *msg = (perm == 1 ? CMD_NOT_FOUND : PERM_DENIED);

    if (perm == 0)
        return (0);
    if (str[0] && str[1] && str[0] == '.' && str[1] == '/') {
        dprintf(2, "%s%s", str, msg);
        return (-1);
    }
    return (-2);
}

void free_tab(char **tab)
{
    for (int a = 0; tab[a] != NULL; a++)
        free(tab[a]);
    free(tab);
}

int check_cmd(char *str)
{
    char *path = strdup(getenv("PATH"));
    char **env = my_str_to_array(path, ':');
    int ret = check_perm_str(str);

    if (ret == 0)
        return (0);
    if (ret < 0 && str[0] == '.' && str[1] == '/')
        return (-1);
    ret = 0;
    if (env == NULL) {
        dprintf(2, "%s: Command not found.\n", str);
        return (-1);
    }
    for (int a = 0; env[a] != NULL; a++) {
        env[a] = strdup(env[a]);
        env[a] = realloc(env[a], strlen(env[a]) + strlen(str) + 2);
        env[a] = strcat(strcat(env[a], "/"), str);
    }
    if (check_cmd_perm(env, str) == -1)
        ret = -1;
    free_tab(env);
    free(path);
    return (ret);
}
