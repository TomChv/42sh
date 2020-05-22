/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** cmd_to_list
*/

#include <string.h>
#include <stddef.h>
#include "parser.h"
#include <stdlib.h>

void clean_list(cmd_t *list);
void handle_job_control(cmd_t *cmd);

static const char *JOB_CONTROL_SEP = (char *)-2;

size_t skip_string(const char *cmd, char delim)
{
    size_t i = 1;

    for (; cmd[i] && cmd[i] != delim; i++);
    return i;
}

char *get_cmd(char *cmd, int *i)
{
    size_t len = 0;
    char *res = NULL;

    for (; cmd[len] && !IS_SEPS(*(cmd + len)); len++)
        if (IS_ANY_QUOTE(cmd[len]))
            len += skip_string(cmd + len, cmd[len]);
    *i += len;
    res = calloc((len + 1), sizeof(char));
    if (res == NULL)
        return NULL;
    res[len] = 0;
    strncpy(res, cmd, len);
    return res;
}

char *get_sep(char *cmd, int *i)
{
    int len = 1 + IS_SEPS(cmd[0]) + IS_SEPS(cmd[1]);
    char *res = calloc((len + 1), sizeof(char));

    if (!res || len == 1)
        return NULL;
    res[len] = 0;
    *i += len - 1;
    if (len == 2 && *cmd == '&') {
        free(res);
        return (char *) JOB_CONTROL_SEP;
    }
    strncpy(res, cmd, len);
    return res;
}

cmd_t *cmd_to_list(char *str)
{
    cmd_t *cmdline = NULL;
    char *sep = NULL;
    char *args;

    for (int i = 0; str[i]; i++) {
        if ((args = get_cmd(str + i, &i)) == NULL)
            break;
        if (str[i] && (sep = get_sep(str + i, &i)) == JOB_CONTROL_SEP)
            sep = strdup("&");
        push_element_cmd(&cmdline, args, sep);
        sep = NULL;
        if (!str[i])
            break;
    }
    clean_list(cmdline);
    handle_job_control(cmdline);
    return cmdline;
}