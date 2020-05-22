/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** UT on test_lexer
*/

#include <criterion/criterion.h>

bool lexer_check(char *str);

/*
 * Crash test
 */

Test(crash_test, null_2)
{
    bool result = lexer_check(NULL);

    cr_expect_eq(result, false);
}

/*
 * Basic tests
 */

Test(lexer_check, invalid_red)
{
    char *str = "echo hello && echo world \" echo >>   test\" | echo"
                " \'    ma >> lol\' ; echo >> > test ; | > hello << <"
                " < echo pute";
    bool result = lexer_check(str);

    cr_assert_eq(result, false);
}

Test(lexer_check, strange_cmd)
{
    char *str = "||| echo lol";
    bool result = lexer_check(str);

    cr_assert_eq(result, false);
}

Test(lexer_check, invalid_and)
{
    char *str = "echo hello && & echo pute";
    bool result = lexer_check(str);

    cr_expect_eq(result, false);
}

Test(lexer_check, invalid_and_with_quote)
{
    char *str = "echo test && ; &";
    bool result = lexer_check(str);

    cr_expect_eq(result, false);
}

Test(lexer_check, invalid_sep)
{
    char *str = "echo hello &&&&& echo world \" echo >>   test\" | echo"
                " \'    ma    && >> lol\' ; echo >> > test ; | > hello << <"
                " < echo pute";
    bool result = lexer_check(str);

    cr_assert_eq(result, false);
}

Test(lexer_check, invalid_all)
{
    char *str = "echo hello || | |  && & & & echo world \" echo >>   test\" "
                "| echo \'    ma    && >> lol\' ; echo >> > test ; |"
                " > hello << < < echo pute";
    bool result = lexer_check(str);

    cr_assert_eq(result, false);
}

Test(lexer_check, finish_sep)
{
    char *str = "echo pute &&";
    bool result = lexer_check(str);

    cr_assert_eq(result, false);
}

Test(lexer_check, valid_cmd)
{
    char *str = "echo lol && echo pute >> file | echo then || echo mdr";
    bool result = lexer_check(str);

    cr_assert_eq(result, true);
}