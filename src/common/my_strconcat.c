/*
** EPITECH PROJECT, 2020
** 42
** File description:
** 42
*/

#include "common.h"

char *my_strconcat_bsn(char *s1, char *s2)
{
    size_t size = strlen(s1) + strlen(s2);
    int n = 0;
    int t = 0;
    char *end = calloc(size + 2, sizeof(char));

    end[size + 1] = '\0';
    end[size] = '\n';
    while (s1[n]) {
        end[n] = s1[n];
        n++;
    }
    while (s2[t]) {
        end[n] = s2[t];
        t++;
        n++;
    }
    return (end);
}

char *my_strconcat_space(char *s1, char *s2)
{
    size_t size = strlen(s1) + strlen(s2);
    int n = 0;
    int t = 0;
    char *end = calloc(size + 2, sizeof(char));

    end[size] = '\0';
    while (s1[n]) {
        end[n] = s1[n];
        n++;
    }
    end[n++] = ' ';
    while (s2[t]) {
        end[n] = s2[t];
        t++;
        n++;
    }
    end[n] = '\0';
    return (end);
}
