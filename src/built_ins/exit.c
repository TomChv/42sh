/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Exit function
*/

#include "common.h"
#include <ctype.h>
#include <stdio.h>
#include "definition.h"

static int verify_number(char *nb, int neg)
{
    int nbr = 0;
    int status = 0;

    for (; *nb; nb++) {
        nbr += (!(status = isdigit(*nb)));
        if (status && neg)
            return dprintf(2, "exit: Badly formed number.\n");
        if (status && !nbr)
            return dprintf(2, "exit: Badly formed number.\n");
        if (status && !neg)
            return dprintf(2, "exit: Expression Syntax.\n");
    }
    return 0;
}

static int verify_argument(char **arg)
{
    int neg = 0;
    char *tmp = strdup(arg[1]);

    if (*tmp == '-') {
        neg = 1;
        tmp++;
    }
    if (my_tablen(arg) > 2 || (!isdigit(*tmp) && !neg))
        return dprintf(2, "exit: Expression Syntax.\n");
    return verify_number(tmp, neg);
}

static int get_value(char *nb)
{
    int neg = 1;
    int num = 0;

    if (*nb == '-') {
        neg = -1;
        nb++;
    }
    num = atoi(nb);
    return num * neg;
}

void exit_cmd(char **arg, UNUSED head_t *head)
{
    if (my_tablen(arg) == 1) {
        printf("exit\n");
        exit(0);
    }
    if (verify_argument(arg))
        return;
    printf("exit\n");
    exit(get_value(arg[1]));
}