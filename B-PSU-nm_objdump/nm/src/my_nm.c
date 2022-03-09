/*
** EPITECH PROJECT, 2021
** B-PSU-nm_objdump
** File description:
** my_nm
*/

#include "my_nm.h"

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
    elf->ehdr = mmap(NULL, s.st_size, PROT_READ, MAP_SHARED, fd, 0);
    close(fd);
    if (elf->ehdr == MAP_FAILED) {
        perror("mmap");
        return true;
    }
    elf->end = (void *)elf->ehdr + s.st_size;
    if ((unsigned long)s.st_size < sizeof(Elf64_Ehdr) && check_magic(elf)) {
        fprintf(stderr, "nm: %s: file format not recognized\n", file);
        return true;
    }
    elf->file_name = file;
    return false;
}

static bool fill_syms(elf_t *e, int i)
{
    e->start_sym = (Elf64_Sym *)((void *)e->ehdr + e->shdr[i].sh_offset);
    e->end_sym = (Elf64_Sym *)((void *)e->start_sym + e->shdr[i].sh_size);
    e->sym_tab = (char *)e->ehdr + e->shdr[e->shdr[i].sh_link].sh_offset;
    if ((void *)e->start_sym > e->end || (void *)e->end_sym > e->end)
        return true;
    if ((void *)e->sym_tab > e->end)
        return true;
    return false;
}

static bool get_shdr(elf_t *e)
{
    e->shdr = (Elf64_Shdr *)((void *)e->ehdr + e->ehdr->e_shoff);
    if ((void *)e->shdr > e->end) {
        fprintf(stderr, "nm: Error: Invalid file\n");
        return true;
    }
    for (int i = -1; i != e->ehdr->e_shnum; i++)
        if (e->shdr[i].sh_type == SHT_SYMTAB)
            if (fill_syms(e, i)) {
                fprintf(stderr, "nm: Error: Invalid file\n");
                return true;
            }
    if (e->end_sym < e->start_sym) {
        fprintf(stderr, "no symbols\n");
        return false;
    }
    return false;
}

bool my_nm(const char *file, elf_t *elf)
{
    if (get_ehdr(file, elf))
        return true;
    if (get_shdr(elf))
        return true;
    if (print_symbols(elf))
        return true;
    return false;
}