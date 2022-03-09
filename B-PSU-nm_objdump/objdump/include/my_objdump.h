/*
** EPITECH PROJECT, 2021
** B-PSU-nm_objdump
** File description:
** my_objdump
*/

#ifndef MY_OBJDUMP_H_
#define MY_OBJDUMP_H_

/* LIBS */
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <elf.h>

#include "flags.h"

/* STRUCTURES */
typedef struct elf_s {
    Elf64_Ehdr const *ehdr;
    Elf64_Shdr const *shdr;
    void *end;
    char *tab;
} elf_t;

/* PROTOTYPES */
bool check_file(const char *file_name);

bool my_objdump(const char *file_name, elf_t *elf);
void display_header(elf_t *elf, const char *file_name);
bool display_data(elf_t *elf);

/* CONST VALUES */
static const int FAILURE = 84;
static const int SUCCESS = 0;

typedef struct machine_s {
    uint16_t key;
    char const *str;
} machine_t;

static machine_t const machines[] = {
{EM_NONE, "None"}, {EM_M32, "WE32100"},
{EM_SPARC, "Sparc"}, {EM_386, "Intel 80386"},
{EM_68K, "MC68000"}, {EM_88K, "MC88000"},
{EM_860, "Intel 80860"}, {EM_MIPS, "MIPS R3000"},
{EM_PARISC, "HPPA"}, {EM_SPARC32PLUS, "Sparc v8+"},
{EM_PPC, "PowerPC"}, {EM_PPC64, "PowerPC64"},
{EM_S390, "IBM S/390"}, {EM_ARM, "ARM"},
{EM_SH, "Renesas / SuperH SH"}, {EM_SPARCV9, "Sparc v9"},
{EM_IA_64, "Intel IA-64"}, {EM_X86_64, "i386:x86-64"}
};

typedef struct flags_s {
    int id;
    char *value;
} flags_t;

static flags_t const flags[] = {
 {HAS_RELOC, "HAS_RELOC"}, {EXEC_P, "EXEC_P"},
 {HAS_LINENO, "HAS_LINENO"}, {HAS_DEBUG, "HAS_DEBUG"},
 {HAS_SYMS, "HAS_SYMS"}, {HAS_LOCALS, "HAS_LOCALS"},
 {DYNAMIC, "DYNAMIC"}, {WP_TEXT, "WP_TEXT"},
 {D_PAGED, "D_PAGED"}, {BFD_IS_RELAXABLE, "BFD_IS_RELAXABLE"},
 {HAS_LOAD_PAGE, "HAS_LOAD_PAGE"},
};

#endif /* !MY_OBJDUMP_H_ */
