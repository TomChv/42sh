/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Struct definition here
*/

#ifndef DEFINITION_H
#define DEFINITION_H

#include "parser.h"
#include "alias.h"

typedef struct headmaster {
    cmd_t *cmd;
    alias_t *alias;
    alias_t *local_env;
} head_t;

void pop_node(alias_t **alias, alias_t *pop);
void push_alias(alias_t **head, alias_t *new);

// * Function
alias_t *get_one_alias(alias_t *alias, char *wanted);

void display_alias(alias_t *alias);
void display_one_alias(alias_t *head, char *cmd);

// * Get parameters
char **get_parameters(char *line);


#define UNUSED __attribute__((unused))

#endif // DEFINITION_H