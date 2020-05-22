/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Common function header
*/

#ifndef COMMON_H
#define COMMON_H

#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "magical_value.h"
#include "parser.h"
#include "alias.h"

// String manipulation
char **my_str_to_array(char *str, char delim);
int str_is_alpha_num(char *str, char *error);
int str_is_num(const char *str);
int my_tablen(char **tab);
char *my_strcat(char *s1, char *s2, bool f1, bool f2);
int my_tablen(char **tab);

// * The best function
void shift_str(char **str);
void shift_to_left(char *buffer, index_t shift);
void shift_to_right(char *buffer, index_t shift, char ch);

// * Theo concat function
char *my_strconcat_bsn(char *s1, char *s2);
char *my_strconcat_space(char *s1, char *s2);
void concate_args(cmd_t **cmd);

// * Useful define
#define IS_PAIR(x) x % 2 == 0

// * Cleanup
#define CLEAR(c) __attribute__((cleanup(c)))

static inline void clear_str(char **p)
{
    if (*p != NULL)
        free(*p);
}

static inline void clear_tab(char ***p)
{
    if (*p != NULL)
        free(*p);
}

static inline void clear_full_tab(char ***p)
{
    if (*p != NULL) {
        for (int i = 0; (*p)[i] != NULL; free((*p)[i]), i++);
        free(*p);
    }
}

static inline void free_list(cmd_t *list)
{
    cmd_t *tmp = NULL;

    while (list) {
        tmp = list;
        list = list->next;
        free(tmp->args);
        free(tmp->sep);
        free(tmp);
    }
}

static inline void free_alias(alias_t *alias)
{
    alias_t *tmp = NULL;

    while (alias) {
        tmp = alias;
        alias = alias->next;
        free(tmp->alias);
        free(tmp->command);
        free(tmp);
    }
}

#endif // COMMON_H
