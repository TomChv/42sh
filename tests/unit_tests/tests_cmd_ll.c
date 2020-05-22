/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** TU for cmd_ll
*/

#include <criterion/criterion.h>
#include <string.h>
#include "parser.h"
#include "magical_value.h"

cmd_t *cmd_to_list(char *str);

/*
 * Test get sep
 */

Test(cmd_to_list, simple_cmd)
{
    char *str = "echo \"Hello world\"";
    cmd_t *cmd = cmd_to_list(str);
    char *ref[3] = {"echo \"Hello world\"", NULL, NULL};

    cr_expect_str_eq(cmd->args, ref[0]);
    cr_expect_null(cmd->sep);
}

Test(cmd_to_list, double_cmd)
{
    char *str = "echo \"Hello world\" ; cat file";
    cmd_t *cmd = cmd_to_list(str);
    char *ref[4] = {
            "echo \"Hello world\"",
            ";",
            "cat file",
            NULL};

    for (index_t i = 0; i != 3; i++, cmd = cmd->next) {
        cr_expect_str_eq(cmd->args, ref[i]);
        if (cmd->next != NULL)
            cr_expect_str_eq(cmd->sep, ref[i += 1]);
        else
            cr_expect_null(cmd->sep);
    }
}

Test(cmd_to_list, mixed_sep)
{
    char *str = "echo \"Hello world\" ; cat file && ls | wc -l || echo fail";
    cmd_t *cmd = cmd_to_list(str);
    char *ref[10] = {
            "echo \"Hello world\"",
            ";",
            "cat file",
            "&&",
            "ls",
            "|",
            "wc -l",
            "||",
            "echo fail",
            NULL};

    for (index_t i = 0; i != 9; i++, cmd = cmd->next) {
        cr_expect_str_eq(cmd->args, ref[i]);
        if (cmd->next != NULL)
            cr_expect_str_eq(cmd->sep, ref[i += 1]);
        else
            cr_expect_null(cmd->sep);
    }
}

Test(cmd_to_list, backick_and_job_control)
{
    char *str = "echo \"Hello world\" `echo lol` & ; & echo test";
    cmd_t *cmd = cmd_to_list(str);
    char *ref[4] = {
            "echo \"Hello world\" `echo lol`",
            "&",
            "echo test",
            NULL};

    for (index_t i = 0; i != 3; i++, cmd = cmd->next) {
        cr_expect_str_eq(cmd->args, ref[i]);
        if (cmd->next != NULL)
            cr_expect_str_eq(cmd->sep, ref[i += 1]);
        else
            cr_expect_null(cmd->sep);
    }
}