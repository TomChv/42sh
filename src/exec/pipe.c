/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** pipe.c
*/

#include <sys/wait.h>
#include "common.h"
#include "exec.h"

static void redirect(int oldfd, int newfd)
{
    if (oldfd != newfd) {
        if (dup2(oldfd, newfd) != -1)
            close(oldfd);
        else
            exit(84);
    }
}

static void child_father(int fd[2], head_t *head, int in_fd)
{
    int status = 0;

    switch (fork()) {
    case -1:
        dprintf(2, "%s: %s.\n", "fork", strerror(errno));
        exit(84);
    case 0:
        close(fd[0]);
        redirect(in_fd, STDIN_FILENO);
        redirect(fd[1], STDOUT_FILENO);
        set_exec(head, 0);
        exit(0);
    default:
        close(fd[1]);
        close(in_fd);
        head->cmd = head->cmd->next;
        exec_pipe(head, fd[0]);
        waitpid(in_fd, &status, 0);
    }
}

void exec_pipe(head_t *head, int in_fd)
{
    int fd[2];
    int du = dup(0);

    if (head->cmd->next == NULL || strcmp("|", head->cmd->sep) != 0) {
        redirect(in_fd, STDIN_FILENO);
        if (head->cmd->sep != NULL && (strcmp(head->cmd->sep, ">") == 0 ||
            strcmp(head->cmd->sep, ">>") == 0)) {
            my_redirection(head, 0);
            head->cmd = head->cmd->next;
            return;
        }
        set_exec(head, 0);
    } else {
        if (pipe(fd) == -1) {
            dprintf(2, "%s: %s.\n", "pipe", strerror(errno));
            exit(84);
        }
        child_father(fd, head, in_fd);
    }
    dup2(du, 0);
}
