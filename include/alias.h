/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Aliases header
*/

#ifndef ALIAS_H
#define ALIAS_H

#include <stdbool.h>

typedef struct alias_s alias_t;
typedef struct verify_alias verify_t;

struct alias_s {
    char *alias;
    char *command;
    bool par;
    alias_t *next;
};

struct verify_alias {
    char *alias;
    verify_t *next;
};

#endif //ALIAS_H
