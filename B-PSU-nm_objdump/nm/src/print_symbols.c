/*
** EPITECH PROJECT, 2021
** B-PSU-nm_objdump
** File description:
** print_symbols
*/

#include <stdlib.h>
#include "my_nm.h"

static int compare_sym(char const *a, char const *b)
{
    for (; strchr("_@", *a); ++a);
    for (; strchr("_@", *b); ++b);
    return (strcasecmp(a, b));
}

static void sort_list(symbols_t *list)
{
    int i = 0;
    int j = 0;
    symbols_t temp;
    size_t size = sizeof(temp);

    while (list[i].val || list[i].type || list[i].sym_name) {
        j = i - 1;
        while (list[++j].val || list[j].type || list[j].sym_name)
            if (compare_sym(list[i].sym_name, list[j].sym_name) > 0) {
                memcpy(&temp, &list[i], size);
                memcpy(&list[i], &list[j], size);
                memcpy(&list[j], &temp, size);
            }
        j++;
        i++;
    }
}

static symbols_t *get_syms(elf_t *elf)
{
    size_t size = (elf->end_sym - elf->start_sym);
    symbols_t *list = malloc(size * sizeof(symbols_t));
    Elf64_Sym const *temp = elf->start_sym;

    if (list == NULL) {
        fprintf(stderr, "malloc\n");
        return NULL;
    }
    memset(list, 0, size * sizeof(symbols_t));
    for (int i = 0; temp < elf->end_sym; temp++) {
        if (temp->st_info != STT_FILE && temp->st_info != STT_SECTION
        && temp->st_info != STT_NOTYPE) {
            if ((void *)&elf->sym_tab[temp->st_name] > elf->end) {
                fprintf(stderr, "nm: Error: invalid file\n");
                return NULL;
            }
            fill_symbols(elf, temp, &list[i]);
            i++;
        }
    }
    sort_list(list);
    return list;
}

bool print_symbols(elf_t *elf)
{
    symbols_t *l = get_syms(elf);
    int i = 0;

    if (l == NULL)
        return true;
    while(l[i].val || l[i].type || l[i].sym_name) {
        if (l[i].val != 0)
            printf("%016x %c %s\n", l[i].val, l[i].type, l[i].sym_name);
        else
            printf("%18c %s\n", l[i].type, l[i].sym_name);
        i++;
    }
    free(l);
    return false;
}