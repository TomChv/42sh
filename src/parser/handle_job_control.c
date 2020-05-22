/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Handle job control
*/

#include "parser.h"
#include <string.h>

static void actualise_job(cmd_t *cmd, size_t job)
{
    while (cmd) {
        cmd->job = job;
        cmd = cmd->prev;
        if (!cmd || !strcmp(cmd->sep, "&"))
            break;
    }
}

void handle_job_control(cmd_t *cmd)
{
    size_t job_control = 0;

    while (cmd) {
        if (cmd->sep && !strcmp(cmd->sep, "&"))
            actualise_job(cmd, ++job_control);
        cmd = cmd->next;
    }
}
