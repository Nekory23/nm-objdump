/*
** EPITECH PROJECT, 2021
** B-PSU-nm_objdump
** File description:
** test_return
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my_objdump.h"

int start(int ac, char **av);

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(no_error, binary, .init=redirect_all_stdout)
{
    int ac = 2;
    char *av[] = {"\0", "./tests/binary_ok"};

    start(ac, av);
}