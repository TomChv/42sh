/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Replace alias with real command
*/

#include "definition.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tmp_print_list(cmd_t *cmd)
{
    while (cmd) {
        printf("cmd :%s\n", cmd->args);
        printf("sep :%s\n", cmd->sep);
        cmd = cmd->next;
    }
}

static int verify_loop(alias_t *head, char *cmd)
{

}

int replace_cmd(cmd_t *cmd, alias_t *alias)
{
    verify_t *verify = NULL;
    char *tmp = NULL;
    alias_t *head = alias;
    alias_t *tmp_alias = NULL;
    int exist = 0;

    while (alias) {
        if (!strncmp(cmd->args, alias->alias, strlen(alias->alias))) {
            tmp = (&cmd->args[strlen(alias->alias)]);
            cmd->args = my_strcat(alias->command, tmp, false, false);
        //    exist = get_one_alias(head, alias->command) != NULL;
        }
        if (exist)
            return dprintf(2, "Alias loop.\n");
        alias = alias->next;
    }
    return 0;
}

int replace_alias(cmd_t *cmd, alias_t *alias)
{
    return;
    cmd_t *head = cmd;
    tmp_print_list(cmd);
    while (cmd) {
        if (replace_cmd(cmd, alias))
            return 1;
        cmd = cmd->next;
    }
    tmp_print_list(head);
    return 0;
}