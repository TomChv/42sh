/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Exec function
*/

#include "common.h"
#include "built_ins.h"
#include "parser.h"
#include "exec.h"

void (*separator_functions[])(head_t *cmd, int fd) = {
    my_reverse_redirection,
    my_reverse_redirection,
    my_redirection,
    my_redirection,
    exec_pipe,
    set_exec,
    set_exec, //&
    and_or,
    and_or,
};

static const char *SEPARATOR[] = {
    "<",
    "<<",
    ">",
    ">>",
    "|",
    ";",
    "&",
    "&&",
    "||",
    NULL
};

int is_cmd_built_in(char **tab, head_t *head);
void exec_function(char **tab);

void and_or(head_t *head, int fd)
{
    set_exec(head, fd);
    int value = return_value(-1000);
    bool dog = strcmp(head->cmd->sep, "||") == 0 ? true : false;
    bool ret = value == 0 ? true : false;

    while (head->cmd->next != NULL && head->cmd->sep[0] != ';') {
        if ((dog == true && ret == true) || (dog == false && ret == false))
            head->cmd = head->cmd->next;
        else
            break;
    }
}

int exec(char **tab, head_t *head)
{
    if (is_cmd_built_in(tab, head) == 1)
        return (1);
    if (check_cmd(tab[0]) != 0)
        return (-1);
    exec_function(tab);
    return (0);
}

void set_exec(head_t *head, UNUSED int fd)
{
    CLEAR(clear_full_tab) char **tab = get_parameters(head->cmd->args);

    if (tab == NULL)
        return;
    for (int a = 0; tab[a] != NULL; a++)
        tab[a] = strdup(tab[a]);
    exec(tab, head);
}

static int check_redirections(cmd_t **node)
{
    void *first = (*node);

    while (*node != NULL && (*node)->sep != NULL && (*node)->next != NULL &&
        (*node)->next->sep != NULL) {
        if (((*node)->sep[0] == '<' || (*node)->sep[0] == '>') &&
            strcmp((*node)->sep, (*node)->next->sep) == 0) {
            dprintf(2, "Ambiguous input redirect.\n");
            return (-1);
        }
        if (strcmp((*node)->sep, "|") == 0 && (*node)->next->sep[0] == '<') {
            dprintf(2, "Ambiguous input redirect.\n");
            return (-1);
        }
        if ((*node)->sep[0] == '>' && strcmp((*node)->next->sep, "|") == 0) {
            dprintf(2, "Ambiguous input redirect.\n");
            return (-1);
        }
        (*node) = (*node)->next;
    }
    (*node) = first;
    return (0);
}

void exec_order(head_t *head)
{
    int a = 0;

    if (check_redirections(&(head->cmd)) == -1)
        return;
    while (head->cmd != NULL) {
        for (; head->cmd->sep != NULL && SEPARATOR[a] != NULL; a++)
            if (strcmp(SEPARATOR[a], head->cmd->sep) == 0)
                break;
        if (head->cmd->sep == NULL || SEPARATOR[a] == NULL)
            set_exec(head, 0);
        else
            separator_functions[a](head, 0);
        head->cmd = head->cmd->next;
    }
}
