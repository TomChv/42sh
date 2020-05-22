/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** terminal.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "input.h"

void die(const char *s)
{
    perror(s);
    exit(84);
}

void exit_term(void)
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

static void init_struct(pos_t *t)
{
    if (get_window_size(&t->win) == -1)
        die("get_window_size");
    if (get_cursor_position(&t->c) == -1)
        die("get_cursor_position");
    t->h.history = new_double_list();
    t->h.index = 0;
    t->prompt = "$> ";
    t->h.first_time = true;
    t->h.temp = NULL;
    t->ind = 0;
    t->buffer = calloc(3, sizeof(char *));
    t->buffer[2] = NULL;
    if (t->buffer == NULL)
        die("calloc");
    t->buffer[t->ind] = calloc(t->win.x + 1, sizeof(char));
    if (t->buffer[t->ind] == NULL)
        die("calloc");
    t->buffer[t->ind] = strcpy(t->buffer[t->ind], t->prompt);
    t->c.x = 4;
    dprintf(1, "\r%s\r", t->buffer[t->ind]);
    dprintf(1, "\x1b[%d;%dH", t->c.y, t->c.x);
}

void init_terminal(pos_t *t)
{
    if (isatty(0) == 0)
        return;
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcsetattr");
    atexit((void (*)(void)) exit_term);
    t->raw = orig_termios;
    t->raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    t->raw.c_oflag &= ~(OPOST);
    t->raw.c_cflag |= (CS8);
    t->raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    t->raw.c_cc[VMIN] = 0;
    t->raw.c_cc[VTIME] = 1;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &t->raw) == -1)
        die("tcsetattr");
    init_struct(t);
}
