/*
** EPITECH PROJECT, 2021
** B-PSU-nm_objdump
** File description:
** start
*/

#include "my_nm.h"

int multiple_files(int ac, char **av, elf_t *elf)
{
    int ret = SUCCESS;

    for (int i = 1; i != ac; i++) {
        if (check_file(av[i])) {
            ret = ERROR;
            continue;
        }
        printf("\n%s:\n", av[i]);
        if (my_nm(av[i], elf))
            ret = ERROR;
    }
    return ret;
}

int start(int ac, char **av)
{
    int ret = SUCCESS;
    elf_t elf;

    if (ac < 2) {
        if (check_file("a.out"))
            return ERROR;
        if (my_nm("a.out", &elf))
            return ERROR;
    }
    else if (ac == 2) {
        if (check_file(av[1]))
            return ERROR;
        if (my_nm(av[1], &elf))
            return ERROR;
    }
    else
        ret = multiple_files(ac, av, &elf);
    return ret;
}