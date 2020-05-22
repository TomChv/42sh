/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** UT for clean string
*/

#include <criterion/criterion.h>

char *clean_string(char *str);

/*
 * Basic crash test
 */
Test(crash_test, null_1)
{
    char *result = clean_string(NULL);

    cr_expect_null(result);
}

Test(crash_test, special_line)
{
    char *str = strdup("echo hello world\n");
    char *result = clean_string(str);
    char *ref = "echo hello world";

    cr_expect_str_eq(result, ref);
}

Test(crash_red, no_limit)
{
    char *str = "echo >>>>";
    char *result = clean_string(str);
    char *ref = "echo >> > >";

    cr_expect_str_eq(result, ref);
}

/*
 * Test clean string
 */
Test(clean_string, simple_test)
{
    char *str = "echo hello world";
    char *result = clean_string(str);
    char *ref = "echo hello world";

    cr_assert_str_eq(result, ref);
}

Test(clean_string, easy_quote_test)
{
    char *str = "echo    \"hello    world\"";
    char *result = clean_string(str);
    char *ref = "echo \"hello    world\"";

    cr_assert_str_eq(result, ref);
}

Test(clean_string, medium_quote_test)
{
    char *str = "echo    \"hello  \"   \"  world\""
                "       echo mdr";
    char *result = clean_string(str);
    char *ref = "echo \"hello  \" \"  world\" echo mdr";

    cr_assert_str_eq(result, ref);
}

Test(clean_string, hard_quote_test)
{
    char *str = "echo    \"hello  \"   \"  world\""
                "       echo 'mdr    ' `  echo lol`";
    char *result = clean_string(str);
    char *ref = "echo \"hello  \" \"  world\" echo "
                "'mdr    ' ` echo lol`";

    cr_assert_str_eq(result, ref);
}

/*
 * Test clean redirection
 */

Test(clean_red, simple_red)
{
    char *str = "echo >>>> lol";
    char *result = clean_string(str);
    char *ref = "echo >> > > lol";

    cr_assert_str_eq(result, ref);
}

Test(clean_red, medium_red)
{
    char *str = "echo >>>> lol <<>><<<>>>>> echo test";
    char *result = clean_string(str);
    char *ref = "echo >> > > lol << >> << < >> > > > echo test";

    cr_assert_str_eq(result, ref);
}

/*
 * Test for separator
 */

Test(clean_sep, easy_test)
{
    char *str = "echo &&&& mdr |||| &&&&&";
    char *result = clean_string(str);
    char *ref = "echo && & & mdr || | | && & & &";

    cr_assert_str_eq(result, ref);
}

Test(clean_sep, medium_test)
{
    char *str = "echo & &&&&& && &|| \"echo test &&   echo lol&\""
                "  mdr |||| &&&&&";
    char *result = clean_string(str);
    char *ref = "echo & && & & & && & || \"echo test &&   echo lol&\""
                " mdr || | | && & & &";

    cr_assert_str_eq(result, ref);
}

/*
 * Mixed test
 */

Test(mixed_test, easy)
{
    char *str = "echo hello && echo world \" echo >>   test\""
                "   |       echo \'    ma    && >> lol\'";
    char *result = clean_string(str);
    char *ref = "echo hello && echo world \" echo >>   test\" | echo"
                " \'    ma    && >> lol\'";

    cr_assert_str_eq(result, ref);
}

Test(mixed_test, medium)
{
    char *str = "echo hello && echo world \" echo >>   test\""
                "   |       echo \'    ma    && >> lol\' ;   echo>>>test";
    char *result = clean_string(str);
    char *ref = "echo hello && echo world \" echo >>   test\" | echo"
                " \'    ma    && >> lol\' ; echo >> > test";

    cr_assert_str_eq(result, ref);
}

Test(mixed_test, hard)
{
    char *str = "echo hello && echo world \" echo >>   test\""
                "   |       echo \'    ma    && >> lol\' ;   echo>>>test"
                "          ;|> hello<<<< echo pute";
    char *result = clean_string(str);
    char *ref = "echo hello && echo world \" echo >>   test\" | echo"
                " \'    ma    && >> lol\' ; echo >> > test ; | > hello << <"
                " < echo pute";

    cr_assert_str_eq(result, ref);
}

/*
 * And special case
 */

Test(reorganise_line, basic_impair)
{
    char *str = "hello & ;&&& world";
    char *result = clean_string(str);
    char *ref = "hello & ; & world";

    cr_assert_str_eq(result, ref);
}

Test(reorganise_line, basic_pair)
{
    char *str = "hello & ;&& world";
    char *result = clean_string(str);
    char *ref = "hello & ; world";

    cr_assert_str_eq(result, ref);
}