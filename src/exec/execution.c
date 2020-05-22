/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** execution.c
*/

#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "exec.h"

int return_value(int value)
{
    static int rtn = 0;

    if (value != -1000)
        rtn = value;
    return (rtn);
}

void check_return_exec(int status)
{
    int return_val = 0;

    if (WIFEXITED(status))
        return_val = WEXITSTATUS(status);
    if (WIFSIGNALED(status)) {
        return_val = WTERMSIG(status);
        if (return_val == 11)
            write(2, "Segmentation fault", 18);
        if (return_val == 6)
            write(2, "Abort", 5);
        if (return_val == 8)
            write(2, "Floating exception", 18);
        if (WCOREDUMP(status))
            write(2, " (core dumped)", 14);
        write(2, "\n", 1);
    }
    return_value(return_val);
}

void exec_function(char **tab)
{
    pid_t pid = fork();
    pid_t waiter;
    int status = 0;

    if (pid == 0) {
        if (execvp(tab[0], tab) == -1) {
            dprintf(2, "%s: %s.\n", tab[0], strerror(errno));
            exit(84);
        }
    } else if (pid > 0) {
        waiter = waitpid(pid, &status, 0);
        if (waiter < 0) {
            dprintf(2, "%s: %s.\n", tab[0], strerror(errno));
            exit(84);
        }
        check_return_exec(status);
    } else {
        dprintf(2, "%s: %s.\n", tab[0], strerror(errno));
        exit(84);
    }
}
