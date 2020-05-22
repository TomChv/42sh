/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** right_redirection.c
*/

#include <fcntl.h>
#include "exec.h"
#include "parser.h"
#include "common.h"

void my_redirection_right(head_t *head, int fd, int stdout, bool shit)
{
    if (!shit)
        fd = open(head->cmd->next->args, O_WRONLY | O_CREAT | O_TRUNC,
             S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    else
        fd = open(head->cmd->next->args, O_APPEND | O_WRONLY | O_CREAT,
             S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    dup2(fd, 1);
    close(fd);
    set_exec(head, 0);
    dup2(stdout, 1);
}

void concate_args(cmd_t **cmd)
{
    CLEAR(clear_full_tab) char **str = get_parameters((*cmd)->args);
    int n = 1;

    while (str[n] != NULL) {
        (*cmd)->args = my_strconcat_space((*cmd)->args , str[n]);
        n++;
    }
}

void my_redirection(head_t *head, UNUSED int in_fd)
{
    int stdout_copy = dup(1);
    int fd = 0;

    concate_args(&(head->cmd));
    if (head->cmd->sep[1] != '>') {
        if (head->cmd->next != NULL)
            my_redirection_right(head, fd, stdout_copy, false);
    }
    else if (head->cmd->sep[1] == '>') {
        if (head->cmd->next != NULL)
            my_redirection_right(head, fd, stdout_copy, true);
    }
    head->cmd = head->cmd->next;
}
