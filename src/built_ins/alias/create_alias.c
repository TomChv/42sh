/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Create alias
*/

#include "alias.h"
#include "common.h"
#include "magical_value.h"
#include <string.h>
#include "definition.h"
#include "built_ins.h"

char *assembly_alias(char **args);

void kill_quote(char *str)
{
    char *tmp = NULL;

    for (index_t i = 0; str[i]; i++) {
        if (str[i] == '"' || str[i] == '\'') {
            tmp = str + i;
            shift_str(&tmp);
            str[i] = *tmp;
        }
        if (!str[i])
            break;
    }
}

static void set_alias(char **args, alias_t **alias)
{
    alias_t *new = calloc(1, sizeof(alias_t));
    char *line = assembly_alias(args);

    if (new == NULL)
        return;
    kill_quote(line);
    kill_quote(args[1]);
    new->command = strdup(line);
    new->alias = strdup(args[1]);
    new->par = (my_tablen(args) > 3);
    new->next = NULL;
    push_alias(alias, new);
    display_alias(*alias);
    printf("----\n");
    sort_alias(alias);
    printf("----\n");
    display_alias(*alias);
}

static void update_alias(char **args, alias_t *alias)
{
    char *line = assembly_alias(args);

    kill_quote(line);
    while (alias) {
        if (!strcmp(args[1], alias->alias)) {
            alias->command = strdup(line);
            alias->par = (my_tablen(args) > 3);
            return;
        }
        alias = alias->next;
    }
}

void create_alias(char **tab, head_t *head)
{
    if (tab == NULL)
        return;
    if (my_tablen(tab) == 1)
        return display_alias(head->alias);
    if (my_tablen(tab) == 2)
        return display_one_alias(head->alias, tab[1]);
    if (get_one_alias(head->alias, tab[1]) == NULL)
        return set_alias(tab, &(head->alias));
    update_alias(tab, head->alias);
}