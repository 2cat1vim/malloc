# ifndef MALLOC_H
# define MALLOC_H

#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdint.h>
#include <stddef.h>
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

typedef struct s_share {
    t_page *page[TYPE_SIZE];
    struct rlimit rlim;
} t_share;

extern t_share* share;

void* malloc(size_t size);
void free(void* ptr);
void* realloc(void* ptr, size_t size);
void show_alloc_mem(void);

bool page_has_space(t_page* page, size_t size);
t_page* search_page_space(size_t size, t_type type);
t_page* create_page(t_type type, size_t size);
t_page* lookup_page(size_t size, t_type type);
t_page* find_page_for_ptr(void *ptr);

t_block* add_block(t_page *p, size_t size, t_block* last);
t_block* select_block(t_page *p, size_t size);
t_block* create_block(size_t size, t_type type);
bool is_valid_block_ptr(t_page *page, void *ptr);

void print_hex(void *p);
void print_nbr(size_t n);
void pout(const char* s);
void pouts(const char* s);
void epout(const char* s);
void epouts(const char* s);
size_t len(const char *s);
void *ft_memcpy(void *dest, const void *src, size_t n);

# endif
