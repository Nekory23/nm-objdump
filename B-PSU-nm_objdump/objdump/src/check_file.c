/*
** EPITECH PROJECT, 2021
** B-PSU-nm_objdump
** File description:
** check_file
*/

#include "my_objdump.h"

bool check_file(const char *file_name)
{
    int fd = open(file_name, O_RDONLY);

    if (fd == -1) {
        fprintf(stderr, "objdump: '%s': No such file\n", file_name);
        return true;
    }
    close(fd);
    return false;
}