/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** special_key.c
*/
#include <stdio.h>
#include <string.h>
#include "input.h"

static int verif_key(char seq[3], pos_t *t)
{
    if ('0' > seq[1] || seq[1] > '9')
        return (0);
    if (read(STDIN_FILENO, &seq[2], 1) != 1)
        return (1);
    if (seq[2] != '~')
        return (0);
    if (seq[1] == '1')
        t->c.x = (int) strlen(t->prompt) + 1;
    if (seq[1] == '4')
        t->c.x = (int) strlen(t->buffer[t->ind]) + 1;
    if (seq[1] == '5')
        handle_history(t, 'A');
    if (seq[1] == '6')
        handle_history(t, 'B');
    if (seq[1] == '7')
        t->c.x = (int) strlen(t->prompt) + 1;
    if (seq[1] == '8')
        t->c.x = (int) strlen(t->buffer[t->ind]) + 1;
    return (0);
}

static int handle_eol(pos_t *t)
{
    if (t->c.x + 1 != (int) strlen(t->buffer[t->ind]) + 2)
        return (1);
    return (0);
}

static void verif_key_letter(char seq, pos_t *t)
{
    if (seq == 'C' && handle_eol(t) == 1)
        t->c.x++;
    if (seq == 'D' && t->c.x - 1 != (int) strlen(t->prompt))
        t->c.x--;
    if (seq == 'H')
        t->c.x = (int) strlen(t->prompt) + 1;
    if (seq == 'F')
        t->c.x = (int) strlen(t->buffer[t->ind]) + 1;
}

void move_cursor(pos_t *t)
{
    char seq[3];

    if (read(STDIN_FILENO, &seq[0], 1) != 1)
        return;
    if (read(STDIN_FILENO, &seq[1], 1) != 1)
        return;
    if (seq[0] == 'O') {
        if (seq[1] == 'H')
            t->c.x = (int) strlen(t->prompt) + 1;
        if (seq[1] == 'F')
            t->c.x = (int) strlen(t->buffer[t->ind]) + 1;
    }
    dprintf(1, "\x1b[%d;%dH", t->c.y, t->c.x);
    if (seq[0] != '[')
        return;
    handle_history(t, seq[1]);
    if (verif_key(seq, t) == 1)
        return;
    verif_key_letter(seq[1], t);
    dprintf(1, "\x1b[%d;%dH", t->c.y, t->c.x);
}