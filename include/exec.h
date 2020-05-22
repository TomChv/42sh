/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** exec.h
*/

#ifndef EXEC_H
#define EXEC_H

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include "definition.h"

int return_value(int value);

// * Redirection
void my_reverse_redirection(head_t *head, int fd);
void my_redirection(head_t *head, int fd);

// * Separator
void exec_pipe(head_t *head, int fd);
void and_or(head_t *cmd, int fd);

// * Execution
void set_exec(head_t *head, int fd);
void exec_order(head_t *head);
int check_cmd(char *str);

// * Alias
int replace_alias(cmd_t *cmd, alias_t *alias);

#endif
