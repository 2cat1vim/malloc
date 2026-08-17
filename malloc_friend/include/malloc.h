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

# define PAGE_SIZE (getpagesize())

# define N_ALLOC 100

# define TINY_BYTES 128
# define SMALL_BYTES 1280

typedef enum s_bool {
    False,
    True
} t_bool;

typedef enum s_type {
    TINY,
    SMALL,
    LARGE,
    TYPE_SIZE
} t_type;

typedef struct s_block {
    size_t size;
    t_bool free;
    struct s_block* next;
} t_block;

# define TINY_MMAP (((TINY_BYTES) * N_ALLOC + PAGE_SIZE - 1) / PAGE_SIZE * PAGE_SIZE)
# define SMALL_MMAP (((SMALL_BYTES) * N_ALLOC + PAGE_SIZE - 1) / PAGE_SIZE * PAGE_SIZE)
# define LIMIT(type) \
    (type == SMALL) ? (size_t)SMALL_MMAP : (size_t)TINY_MMAP

typedef struct s_page {
    t_type type;
    size_t size;
    void* ptr_end;
    t_block *blocks;
    struct s_page *next;
} t_page;

typedef struct s_ptr {
    t_block* prev_block;
    t_block* head_block;
    t_page* prev_page;
    t_page* head_page;
} t_ptr;

extern t_page* page[TYPE_SIZE];

void* malloc(size_t size);
void free(void* ptr);
void* realloc(void* ptr, size_t size);

t_bool page_has_space(t_page* page, size_t size);
t_page* search_page_space(size_t size, t_type type);
t_page* create_page(t_type type, size_t size);
t_page* lookup_page(size_t size, t_type type);


t_block* add_block(t_page *p, size_t size);
t_block* select_block(t_page *p, size_t size);
t_block* create_block(size_t size, t_type type);

t_ptr* get_infos(void* ptr, t_ptr* info);

void print_hex(void *p);
void print_nbr(size_t n);
void pout(const char* s);
void pouts(const char* s);

void show_alloc_mem(void);
# endif
