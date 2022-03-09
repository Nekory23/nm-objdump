/*
** EPITECH PROJECT, 2021
** B-PSU-nm_objdump
** File description:
** display_data
*/

#include "my_objdump.h"

static void print_hexa(uint8_t *data, int size)
{
    for (int i = 0; i < 16; i++) {
        if (i < size)
            printf("%02x", data[i]);
        else
            printf("  ");
        if (!((i + 1) % 4))
            printf(" ");
    }
    printf("  ");
}

static void print_right_col(uint8_t *data, int size)
{
    for (int i = 0; i < 16; i++) {
        if (i < size) {
            if (data[i] >= ' ' && data[i] <= '~')
                printf("%c", data[i]);
            else
                printf(".");
        } else
            printf (" ");
    }
    printf("\n");
}

static bool check_type(Elf64_Shdr const *s, const char *tab, int i)
{
    if (s[i].sh_type == SHT_SYMTAB)
        if (strcmp(&tab[s[i].sh_name], ".dynstr") || !s[i].sh_size)
            return true;
    if (s[i].sh_type == SHT_NOBITS)
        if (strcmp(&tab[s[i].sh_name], ".dynstr") || !s[i].sh_size)
            return true;
    if (s[i].sh_type == SHT_STRTAB)
        if (strcmp(&tab[s[i].sh_name], ".dynstr") || !s[i].sh_size)
            return true;
    return false;
}

bool display_data(elf_t *elf)
{
    int size = 0;
    int print = 0;

    for (unsigned int i = 1, j = 0, temp = 0; i < elf->ehdr->e_shnum; i++) {
        if (check_type(elf->shdr, elf->tab, i))
            continue;
        printf("Contents of section %s:\n", &elf->tab[elf->shdr[i].sh_name]);
        j = elf->shdr[i].sh_offset;
        temp = elf->shdr[i].sh_offset + elf->shdr[i].sh_size;
        while (j < temp) {
            size = elf->shdr[i].sh_offset + elf->shdr[i].sh_size - j;
            print = (int)(elf->shdr[i].sh_addr + j - elf->shdr[i].sh_offset);
            printf(" %04x ", print);
            print_hexa((unsigned char *)elf->ehdr + j, size);
            print_right_col((unsigned char *)elf->ehdr + j, size);
            j += 16;
        }
    }
    return false;
}