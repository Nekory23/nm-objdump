/*
** EPITECH PROJECT, 2021
** B-PSU-nm_objdump
** File description:
** my_objdump
*/

#include "my_objdump.h"

static bool check_magic(elf_t *elf)
{
    if (elf->ehdr->e_ident[EI_MAG0] == ELFMAG0 
    && elf->ehdr->e_ident[EI_MAG1] == ELFMAG1
    && elf->ehdr->e_ident[EI_MAG2] == ELFMAG2
    && elf->ehdr->e_ident[EI_MAG3] == ELFMAG3)
        return false;
    return true;
}

static bool get_ehdr(const char *file, elf_t *elf)
{
    int fd = open(file, O_RDONLY);
    struct stat s;

    if (fstat(fd, &s) == -1) {
        close(fd);
        perror("fstat");
        return true;
    }
    elf->ehdr = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (elf->ehdr == MAP_FAILED) {
        perror("mmap");
        return true;
    }
    elf->end = (void *)elf->ehdr + s.st_size;
    if ((unsigned long)s.st_size < sizeof(Elf64_Ehdr) && check_magic(elf)) {
        fprintf(stderr, "objdump: %s: file format not recognized\n", file);
        return true;
    }
    return false;
}

static bool check_shdr(elf_t *elf)
{
    if ((void *)elf->shdr > elf->end
        || (void *)&elf->shdr[elf->ehdr->e_shstrndx] > elf->end
        || (void *)elf->ehdr + elf->shdr[elf->ehdr->e_shstrndx].sh_offset
        > elf->end)
        return true;
    return false;
}

static bool get_shdr(elf_t *elf)
{
    void *temp;

    elf->shdr = (Elf64_Shdr *)((void *)elf->ehdr + elf->ehdr->e_shoff);
    if (check_shdr(elf)) {
        fprintf(stderr, "Error: invalid file\n");
        return true;
    }
    temp = ((void *)elf->ehdr + elf->shdr[elf->ehdr->e_shstrndx].sh_offset);
    elf->tab = (char *)temp;
    return false;
}

bool my_objdump(const char *file_name, elf_t *elf)
{
    if (get_ehdr(file_name, elf) || get_shdr(elf))
        return true;
    display_header(elf, file_name);
    if (display_data(elf))
        return true;
    return false;
}