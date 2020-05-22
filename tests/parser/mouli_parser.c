/*
** EPITECH PROJECT, 2020
** tests
** File description:
** mouli_parser
*/

#include "mouli_parser.h"
#include <stdlib.h>
char *clean_string(char *str);

// * Les tests se font en mettant la ligne que t'envois au
// * cleaner en premier et la ligne que t'attends en deuxieme

int mouli(FILE *fp)
{
    int res = 0;
    size_t tmp = {0};
    bool passed = false;
    char *test_input = NULL;
    char *test_output = NULL;

    printf("\t\t\t\t%s----- Parser Tests -----%s\n", BLUE, RESET);
    while (getline(&test_input, &tmp, fp) != -1
        && getline(&test_output, &tmp, fp) != -1) {

        // Init
        test_input[strlen(test_input) - 1] = 0;
        printf("\nTesting : \n%s|END\n", test_input);
        // test_input[strlen(test_input)] = '\n';
        if (test_output[strlen(test_output) - 1] == '\n')
            test_output[strlen(test_output) - 1] = 0;

        // Exec
        test_input = clean_string(test_input); // My function

        // Result
        passed = strcmp(test_input, test_output) == 0;
        printf("%s\n", passed ? OK : NOTOK);
        if (!passed) {
            printf("\t✖ -> %s%s%s|END\n", RED, test_input, RESET);
            printf("\t✔️ -> %s%s%s|END\n", BLUE, test_output, RESET);
            res = 84;
        }
        tmp = getline(&test_input, &tmp, fp);
        if (tmp != 1 && tmp != -1){
            printf("Blank line between each test. %s\n", test_input);
            exit(84);
        }
        free(test_input);
        free(test_output);
        test_input = NULL;
        test_output = NULL;
    }
    return (res);
}

int main(int argc, char const *argv[])
{
    FILE *fp = fopen(TEST_PATH, "r");

    return (fp ? mouli(fp) : 84);
}
