/*
** EPITECH PROJECT, 2021
** B-PSU-nm_objdump
** File description:
** start
*/

#include "my_objdump.h"

int multiple_files(int ac, char **av, elf_t elf)
{
    int ret = SUCCESS;

    (void) av;
    for (int i = 1; i != ac; i++) {
        if (check_file(av[i])) {
            ret = FAILURE;
            continue;
        }
        if (my_objdump(av[i], &elf))
            ret = FAILURE;
    }
    return ret;
}

int start(int ac, char **av)
{
    int ret = SUCCESS;
    elf_t elf;

    if (ac < 2) {
        if (check_file("a.out"))
            return FAILURE;
        if (my_objdump("a.out", &elf))
            return FAILURE;
    }
    else if (ac == 2) {
        if (check_file(av[1]))
            return FAILURE;
        if (my_objdump(av[1], &elf))
            return FAILURE;
    }
    else
        ret = multiple_files(ac, av, elf);
    return ret;
}