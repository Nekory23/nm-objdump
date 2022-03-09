/*
** EPITECH PROJECT, 2021
** B-PSU-nm_objdump
** File description:
** test_errors
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

Test(gest_args, no_file_none, .init=redirect_all_stdout)
{
    int ac = 1;
    char *av[1] = {"\0"};

    start(ac, av);
    cr_assert_stderr_eq_str("objdump: 'a.out': No such file\n", "");
}

Test(gest_args, no_file_one, .init=redirect_all_stdout)
{
    int ac = 2;
    char *av[2] = {"\0", "test"};

    start(ac, av);
    cr_assert_stderr_eq_str("objdump: 'test': No such file\n", "");
}

Test(gest_args, no_file_multiple, .init=redirect_all_stdout)
{
    int ac = 3;
    char *av[3] = {"\0", "test", "test2"};

    start(ac, av);
    cr_assert_stderr_eq_str("objdump: 'test': No such file\nobjdump: 'test2': No such file\n", "");
}