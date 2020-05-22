/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** 42sh 
*/

#include <stdio.h>
#include "parser.h"
#include "common.h"
#include "exec.h"
#include "input.h"

cmd_t *parser(char *str);
extern char **environ;
int replace_env_vars(head_t *head, char **str);

static void back_term(pos_t *t, char *str)
{
    if (str != NULL)
        free(str);
    if (isatty(0) == 0)
        return;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &t->raw) == -1)
        die("tcsetattr");
    if (get_cursor_position(&t->c) == -1)
        die("get_cursor_position");
    t->ind = 0;
    t->c.x = 4;
    for (int a = 0; t->buffer[a]; a++)
        t->buffer[a] = memset(t->buffer[a], 0, t->win.x + 1);
    t->buffer[t->ind] = strcpy(t->buffer[t->ind], t->prompt);
    dprintf(1, "\r%s\r", t->buffer[t->ind]);
    dprintf(1, "\x1b[%d;%dH", t->c.y, t->c.x);
}

static void free_head(head_t *head)
{
    free_list(head->cmd);
    free_alias(head->alias);
    free_alias(head->local_env);
}

void tmp_print_list(cmd_t *cmd);

int shell(void)
{
    head_t head = {NULL, NULL, NULL};
    pos_t t;
    size_t sz = 0;
    char *str = NULL;

    init_terminal(&t);
    while (1) {
        if ((str = input(&t)) == NULL && getline(&str, &sz, stdin) == -1)
                break;
        if (replace_env_vars(&head, &str) == -1 || !(head.cmd = parser(str))
            || replace_alias(head.cmd, head.alias)) {
            back_term(&t, str);
            continue;
        }
        exec_order(&head);
        free_list(head.cmd);
        back_term(&t, str);
    }
    free_head(&head);
    return 0;
}