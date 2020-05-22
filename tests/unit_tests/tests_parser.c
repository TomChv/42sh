/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** UT for parser
*/

#include <criterion/criterion.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"
#include "magical_value.h"

cmd_t *parser(char *str);

/*
 * Basic tests
 */

Test(parser, multiple_cmd_1)
{
    char *str = "echo    \"hello world\"    &&   cat   file ;;;;;;;; ech test";
    cmd_t *cmd = parser(str);
    char *ref[6] = {"echo \"hello world\"",
                    "&&",
                    "cat file",
                    ";",
                    "ech test",
                    NULL};
    for (index_t i = 0; i != 5; i++, cmd = cmd->next) {
        cr_expect_str_eq(cmd->args, ref[i]);
        if (cmd->next != NULL)
            cr_expect_str_eq(cmd->sep, ref[i += 1]);
        else
            cr_expect_null(cmd->sep);
    }
}

Test(parser, multiple_cmd_2)
{
    char *str = "echo    \"hello world\"    &&   cat   file ;;;;;;;; ech test"
                "      & ; &&&&&&&&&&&&&&&&&&&&&& locate lol";
    cmd_t *cmd = parser(str);
    char *ref[8] = {"echo \"hello world\"",
                    "&&",
                    "cat file",
                    ";",
                    "ech test",
                    "&",
                    "locate lol",
                    NULL};
    for (index_t i = 0; i != 7; i++, cmd = cmd->next) {
        cr_expect_str_eq(cmd->args, ref[i]);
        if (cmd->next != NULL)
            cr_expect_str_eq(cmd->sep, ref[i += 1]);
        else
            cr_expect_null(cmd->sep);
    }
}

/*
 * Test for job control
 */

Test(parser, simple_job)
{
    char *str = "echo world `ls  main.c`;;;; &&&&& ";
    cmd_t *cmd = parser(str);
    char *ref[4] = {"echo world `ls main.c`", "&", "1", NULL};

    cr_expect_str_eq(cmd->args, ref[0]);
    cr_expect_str_eq(cmd->sep, ref[1]);
    cr_expect_eq(cmd->job, strtol(ref[2], NULL, 10));
}