/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** replace_env_vars
*/

#include "definition.h"
#include "common.h"
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

static char *is_in_one_env(head_t *head, char *str)
{
    alias_t *tmp = head->local_env;
    size_t before_space = 0;
    CLEAR(clear_str) char *real_key;
    char *real_value;

    str += (*str == '$');
    for (;str[before_space] && str[before_space] != ' '
        && str[before_space] != '\"'; before_space++);
    real_key = strdup(str);
    real_key[before_space] = 0;
    if ((tmp = get_one_alias(tmp, real_key)) != NULL)
        return tmp->alias;
    else if ((real_value = getenv(real_key)) != NULL)
        return real_value;
    return NULL;
}

static char *replace_var(char *str, char *val, int pos)
{
    char *res = NULL;
    size_t var_len = 0;
    size_t new_alloc;

    for (;str[pos + var_len] && str[pos + var_len] != ' '
            && str[pos + var_len] != '\"'; var_len++);
    new_alloc = strlen(val) - (var_len);
    res = malloc(sizeof(char) * (strlen(str) + (new_alloc > 0 ? new_alloc : 0) + 1));
    *res = 0;
    strncpy(res, str, pos);
    strcpy(res + pos, val);
    strcpy(res + pos + strlen(val), str + pos + var_len);
    free(str);
    return res;
}

static int var_errors(char *str, index_t pos)
{
    if (isalnum(str[pos + 1])) {
        for (int j = 1; str[j + pos]; printf("%c", str[j + pos]), j++);
        printf(": Undefined variable.\n");
    } else
        printf("Illegal variable name.\n");
    return -1;
}

int replace_env_vars(head_t *head, char **str)
{
    char *val;

    for (index_t i = 0; (*str)[i]; i++)
        if ((*str)[i] == '$' && (val = is_in_one_env(head, *str + i)) != NULL)
            *str = replace_var(*str, val, i);
        else if ((*str)[i] == '$')
            return var_errors(*str, i);
    return 0;
}