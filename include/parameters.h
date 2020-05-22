/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** magical_number.c
*/

#ifndef MAGICAL_NUMBER_H
#define MAGICAL_NUMBER_H

// define
#define CTRL_KEY(k) ((k) & 0x1f)
#define CUR_TO_IND(x) (x - 2)

// values
static const char ESCAPE = '\x1b';

// Return value
static const int ERROR = 84;
static const int OK = 0;

// Comparison
static const int DIFF = 1;
static const int SAME = 0;

// Macros
#define EXIT_ERROR(x)                       \
                do {                        \
                    fprintf(stderr, x);     \
                    exit(84);               \
                } while (0)                 \

#define CTRL_L(x)                           \
        do {                                \
            dprintf(x, "\x1b[2J\r");        \
            dprintf(x, "\x1b[H\r");         \
        } while (0)                         \

// inline function
static inline int nbr_length(int nbr, int base)
{
    int a = nbr / base;
    int b = 0;

    for (; a > 0; b++, a = a / base);
    return (b + 1);
}

#endif //PSU_42SH_2019_MAGICAL_NUMBER_H
