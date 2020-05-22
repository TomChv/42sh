/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Built_ins
*/

#ifndef BUILT_H
#define BUILT_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "definition.h"

// * Env handling
void my_env(char **tab, head_t *head);
void my_setenv(char **name, head_t *head);
void my_unsetenv(char **name, head_t *head);

// * Local
void create_local_env(char **args, head_t *head);

// * Kill Quote
void kill_quote(char *str);

// * Repeat
void repeat(char **line, head_t *head);

// * Where and which
void where_which(char **tab, head_t *head);

// * Cd
void cd_fct(char **tab, head_t *head);

// * Echo
void echo(char **args, head_t *head);

// * Alias
void create_alias(char **args, head_t *head);
void unset_alias(char **args, head_t *head);
void sort_alias(alias_t **alias);

// * Exit
void exit_cmd(char **tab, head_t *head);

#endif
