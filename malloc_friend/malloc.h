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

# define TINY_BYTES 100
# define SMALL_BYTES 1000
# define LARGE_BYTES 8000

typedef enum s_bool {
    False,
    True
} t_bool;

typedef enum s_type {
    TINY,
    SMALL,
    LARGE
} t_type;

typedef struct s_block {
    size_t size;
    t_bool free;
    struct s_block* next;
    struct s_block* prev;
} t_block;

# define TINY_MMAP (((TINY_BYTES + sizeof(t_block)) * N_ALLOC + PAGE_SIZE - 1) / PAGE_SIZE * PAGE_SIZE)
# define SMALL_MMAP (((SMALL_BYTES + sizeof(t_block)) * N_ALLOC + PAGE_SIZE - 1) / PAGE_SIZE * PAGE_SIZE)

typedef struct s_page {
    t_type type;
    size_t size;
    void* ptr_end;
    t_block *blocks;
    struct s_page *next;
} t_page;

extern t_page* page[3];

void* malloc(size_t size);
void free(void* ptr);

t_bool page_has_space(t_page* page, size_t size);
t_page* search_page_space(size_t size, t_type type);
t_page* create_page(t_type type);
t_page* lookup_page(size_t size, t_type type);


t_block* add_block(t_page *p, size_t size);
t_block* select_block(t_page *p, size_t size);
t_block* create_block(size_t size, t_type type);

void print_debug(char *s);
void print_page(t_page* p);
void print_mem(void);
# endif
