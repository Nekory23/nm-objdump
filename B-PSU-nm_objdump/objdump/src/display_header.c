/*
** EPITECH PROJECT, 2021
** B-PSU-nm_objdump
** File description:
** display_header
*/

#include "my_objdump.h"

static void print_name(elf_t *elf)
{
    size_t size = (sizeof(machines) / sizeof(*machines));

    for (unsigned int i = 0; i < size; i++)
        if (machines[i].key == elf->ehdr->e_machine) {
            printf("architecture: %s,", machines[i].str);
            return;
        }
    printf("architecture: %s,", "i386:x86-64");
}

static void display_flag(elf_t *elf)
{
    int flag = 0;
    char *str = "";
    int size = (sizeof(flags) / sizeof(*flags));

    switch (elf->ehdr->e_type) {
        case ET_EXEC :
            flag = 274;
            break;
        case ET_DYN :
            flag = 336;
            break;
        case ET_REL :
            flag = 17;
            break;
    }
    printf(" flags 0x%08x:\n", flag);
    for (int i = 0; i != size; i++)
        if (flag & flags[i].id) {
            printf("%s%s", str, flags[i].value);
            str = ", ";
        }
    printf("\n");
}

void display_header(elf_t *elf, const char *file_name)
{
    printf("\n%s:     file format %s\n", file_name, "elf64-x86-64");
    print_name(elf);
    display_flag(elf);
    printf("start address 0x%016lx\n\n", elf->ehdr->e_entry);
}