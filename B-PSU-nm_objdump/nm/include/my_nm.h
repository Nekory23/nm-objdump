/*
** EPITECH PROJECT, 2021
** B-PSU-nm_objdump
** File description:
** my_nm
*/

#ifndef MY_NM_H_
#define MY_NM_H_

/* INCLUDES */
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <elf.h>

/* STRUCTURES */
typedef struct symbols_s {
    unsigned int val;
    char type;
    char const *sym_name;
} symbols_t;

typedef struct elf_s
{
    const char *file_name;
    Elf64_Ehdr const *ehdr;
    Elf64_Shdr const *shdr;
    void *end;
    Elf64_Sym const *start_sym;
    Elf64_Sym const *end_sym;
    char const *sym_tab;
} elf_t;

/* PROTOTYPES */
bool check_file(const char *file_name);

bool my_nm(const char *file, elf_t *elf);
bool print_symbols(elf_t *elf);
void fill_symbols(elf_t *elf, Elf64_Sym const *sym, symbols_t *symbols);

/* CONST VALUES */
static const int ERROR = 84;
static const int SUCCESS = 0;

typedef struct type_s {
    char ch;
    uint32_t type;
    uint64_t flag;
} type_t;

static type_t const	types[] = {
{'B', SHT_NOBITS, SHF_ALLOC | SHF_WRITE},
{'R', SHT_PROGBITS, SHF_ALLOC},
{'D', SHT_PROGBITS, SHF_ALLOC | SHF_WRITE},
{'U', SHT_NULL, 0},
{'T', SHT_PROGBITS, SHF_ALLOC | SHF_EXECINSTR},
{'R', SHT_PROGBITS, 0}
};

#endif /* !MY_NM_H_ */