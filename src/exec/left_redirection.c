/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** left_redirection.c
*/

#include <stdio.h>
#include <fcntl.h>
#include "common.h"
#include "parser.h"
#include "exec.h"

void my_simple_reverse_redirection(head_t *head, int fd, int stdout)
{
    fd = open(head->cmd->next->args, O_RDONLY);
    dup2(fd, 0);
    close(fd);
    set_exec(head, 0);
    dup2(stdout, 0);
}

void my_double_reverse_redirection(head_t *head)
{
    char *str = NULL;
    char *end = calloc(1, sizeof(char));
    size_t t = 0;
    int fd = -1;

    end[0] = '\0';
    while (1) {
        printf("? ");
        if (getline(&str, &t, stdin) == -1 ||
            strcmp(head->cmd->next->args, str) == 0)
            break;
        end = my_strconcat_bsn(end, str);
    }
    fd = open("/tmp/arg.arg", O_CREAT | O_WRONLY, 0744);
    write(fd, end, strlen(end));
    close(fd);
}

void my_reverse_redirection(head_t *head, int in_fd)
{
    int stdout_copy = dup(1);
    int fd = 0;

    (void) in_fd;
    if (head->cmd->args[0] == '\0' && head->cmd->next != NULL)
        concate_args(&(head->cmd));
    if (head->cmd->sep[1] != '<') {
        if (head->cmd->next != NULL)
            my_simple_reverse_redirection(head, fd, stdout_copy);
    }
    else if (head->cmd->sep[1] == '<') {
        if (head->cmd->next != NULL)
            my_double_reverse_redirection(head);
    }
    head->cmd = head->cmd->next;
}
