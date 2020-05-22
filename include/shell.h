/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** shell.h
*/

#ifndef SHELL_H
#define SHELL_H

#include <stdbool.h>

int shell(char **environ);

// * Parsing
char *erase_space_n_tab(char *str, bool f);
char *clean_red(char *cmd);
char *clean_sep(char *cmd);

// * Built ins
void echo(char **args);

#endif // SHELL_H