/*
** EPITECH PROJECT, 2021
** B-PSU-nm_objdump
** File description:
** fill_symbol
*/

#include "my_nm.h"

static char to_lower(char c)
{
    if (c >= 'A' && c <= 'Z')
        c += 32;
    return c;
}

static char get_type_bis(Elf64_Sym const *sym, char type)
{
    switch (ELF64_ST_BIND(sym->st_info)) {
        case STB_LOCAL :
            type = to_lower(type);
            break;
        case STB_WEAK :
            type = 'w';
            break;
    }
    return type;
}

static char get_type(elf_t *elf, Elf64_Sym const *sym)
{
    unsigned int stop = sizeof(types) / sizeof(*types);

    switch (sym->st_shndx) {
        case SHN_UNDEF :
            return 'u';
        case SHN_COMMON :
            return 'C';
        case SHN_ABS :
            return 'A';
    }
    for (unsigned int i = 0; i < stop; i++) {
        if ((void *)&elf->shdr[sym->st_shndx] > elf->end) {
            fprintf(stderr, "Error: invalid file");
            return true;
        }
        if (elf->shdr[sym->st_shndx].sh_type == types[i].type &&
            elf->shdr[sym->st_shndx].sh_flags == types[i].flag)
            return types[i].ch;
    }
    return '?';
}

void fill_symbols(elf_t *elf, Elf64_Sym const *sym, symbols_t *symbols)
{
    symbols->sym_name = &elf->sym_tab[sym->st_name];
    symbols->type = get_type(elf, sym);
    symbols->type = get_type_bis(sym, symbols->type);
    symbols->val = (unsigned int)sym->st_value;
}