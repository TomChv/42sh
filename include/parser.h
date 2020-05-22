/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Parser header
*/

#ifndef PARSER_H
#define PARSER_H

// Magic enum ma boi
enum {
    QUOTE,
    SIMPLE,
    BACK
};

typedef struct cmd_list cmd_t;

/* Description of the double chained linked list:
 * args: command line
 * sep:  separator
 * job:  job layer
*/
struct cmd_list {
    char *args;
    char *sep;
    int job;
    cmd_t *next;
    cmd_t *prev;
};

// Handle quote
#define IS_QUOTE(x) (x == '"')
#define IS_SIMPLE(x) (x == '\'')
#define IS_BACKTICK(x) (x == '`')
#define IS_ANY_QUOTE(x) (IS_QUOTE(x) || IS_SIMPLE(x) || IS_BACKTICK(x))
#define NOT_IN_QUOTES(b) (b[0] == false && b[1] == false && b[2] == false)

// Handle sep
#define IS_SEP(x) (x == '&' || x == '|' || x == '>' || x == '<')
#define IS_SEPS(x) (x == ';' || IS_SEP(x))

// Handle direction
#define IS_NEXT_DIR(c, n, d) ((c != d && n == d) || (c == d && n != d))
#define IS_SAME(c, p, s1, s2) ((c == s1 && p == s1) || (c == s2 && p == s2))

// Update my quotes boi :)
#define UPDATE_QUOTES(x, c)                            \
        do {                                           \
            x[QUOTE] = IS_QUOTE(c) == !x[QUOTE];       \
            x[SIMPLE] = IS_SIMPLE(c) == !x[SIMPLE];    \
            x[BACK] = IS_BACKTICK(c) == !x[BACK];      \
        } while (0)                                    \

void push_element_cmd(cmd_t **cmd, char *args, char *sep);

// * Handle inhib
void inhib_clean(char *str);

#endif //PARSER_H
