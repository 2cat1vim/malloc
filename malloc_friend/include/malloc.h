# ifndef MALLOC_H
# define MALLOC_H

#include <sys/mman.h>
#include <sys/resource.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "impl.h"

typedef enum s_type {
    TINY,
    SMALL,
    LARGE,
    TYPE_SIZE
} t_type;

typedef struct s_block {
    size_t size;
    bool free;
    struct s_block* prev;
    struct s_block* next;
} t_block;

typedef struct s_page {
    t_type type;
    size_t size;
    void* ptr_end;
    t_block *blocks;
    struct s_page *prev;
    struct s_page *next;
} t_page;

extern t_page* page[TYPE_SIZE];

void* malloc(size_t size);
void free(void* ptr);
void* realloc(void* ptr, size_t size);
void show_alloc_mem(void);

bool page_has_space(t_page* page, size_t size);
t_page* search_page_space(size_t size, t_type type);
t_page* create_page(t_type type, size_t size);
t_page* lookup_page(size_t size, t_type type);

t_block* add_block(t_page *p, size_t size, t_block* last);
t_block* select_block(t_page *p, size_t size);
t_block* create_block(size_t size, t_type type);

void print_hex(void *p);
void print_nbr(size_t n);
void pout(const char* s);
void pouts(const char* s);

# endif
