/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Set local env variable
*/

#include "definition.h"
#include "common.h"
#include <stdlib.h>
#include <string.h>

static void set_local_env(char *arg, alias_t **env)
{
    alias_t *new = calloc(1, sizeof(alias_t));
    CLEAR(clear_tab) char **values = my_str_to_array(arg, '=');

    if (new == NULL)
        return;
    new->alias = strdup(values[0]);
    new->command = values[1] != NULL ? strdup(values[1]) : NULL;
    new->par = false;
    new->next = NULL;
    push_alias(env, new);
}

static void update_local_env(char *arg, alias_t *env)
{
    CLEAR(clear_tab) char **values = my_str_to_array(arg, '=');

    while (env) {
        if (!strcmp(values[0], env->alias)) {
            env->command = values[1] != NULL ? strdup(values[1]) : NULL;
            return;
        }
        env = env->next;
    }
}

#include <stdio.h>
void create_local_env(char **args, head_t *head)
{
    if (my_tablen(args) == 1)
        return display_alias(head->local_env);
    for (index_t i = 1; args[i] != NULL; i++) {
        if (get_one_alias(head->local_env, args[i]) == NULL)
            set_local_env(args[i], &(head->local_env));
        else
            update_local_env(args[i], head->local_env);
    }

}