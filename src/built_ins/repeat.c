/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** repeat
*/

#include "built_ins.h"
#include "common.h"

int exec(char **tab);

static const char *FEW_ARG = "repeat: Too few arguments.\n";
static const char *BAD_ARG = "repeat: Badly formed number.\n";

void exec_repeat(char **line)
{
    int n = 0;
    int end = 0;

    end = atoi(line[1]);
    while (n != end && line[1][0] != '-') {
        exec(line + 2);
        n++;
    }   
}

void repeat(char **line, UNUSED head_t *head)
{
    int n = 0;

    while (line[n] != NULL)
        n++;
    if (n <= 2) {
        dprintf(2, "%s", FEW_ARG);
        return;
    }
    if (str_is_num(line[1]) == 1 && line[1][0] != '-') {
        dprintf(2, "%s", BAD_ARG);
        return;
    }
    if (n < 3) {
        dprintf(2, "%s", FEW_ARG);
        return;
    }
    exec_repeat(line);
}
