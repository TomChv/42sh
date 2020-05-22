/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** print.c
*/
#include <stdio.h>
#include <string.h>
#include "input.h"

void print_buffer(pos_t *t)
{
    dprintf(1, "\x1b[%d;%dH", t->c.y, 1);
    dprintf(1, "\x1b[?25l");
    dprintf(1, "\x1b[K");
    dprintf(1, "%s", t->buffer[t->ind]);
    dprintf(1, "\x1b[?25h");
    dprintf(1, "\x1b[%d;%dH", t->c.y, t->c.x);
}

static void refresh_line(pos_t * t)
{
    ndbl_t *elem = t->h.history->tail;
    for (int a = 1; a != t->h.index; elem = elem->prev, a++);
    t->buffer[t->ind] = memset(t->buffer[t->ind], 0, t->win.x + 1);
    t->buffer[t->ind] = strcpy(t->buffer[t->ind], t->prompt);
    t->c.x = (int) strlen(t->prompt) + 1;
    for (int i = 0; elem->data[i]; i++)
        add_char(elem->data[i], t);
}

void handle_history(pos_t *t, char seq)
{
    if (seq == 'A' && t->h.index < t->h.history->length) {
        if (t->h.first_time == true)
            t->h.temp = strdup(t->buffer[t->ind]);
        t->h.index++;
        refresh_line(t);
        t->h.first_time = false;
    } else if (seq == 'B') {
        if (t->h.index - 1 > 0) {
            t->h.index--;
            refresh_line(t);
        } else if (t->h.index - 1 == 0) {
            t->buffer[t->ind] = memset(t->buffer[t->ind], 0, t->win.x + 1);
            t->buffer[t->ind] = strcpy(t->buffer[t->ind], t->h.temp);
            t->c.x = (int) strlen(t->buffer[t->ind]) + 1;
            t->h.index = 0;
        }
    }
    print_buffer(t);
}
