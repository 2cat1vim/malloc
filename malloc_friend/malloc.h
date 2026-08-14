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

# define TINY_MAX 100
# define SMALL_MAX 200

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

typedef struct s_page {
    t_type type;
    size_t map_size;
    size_t size;
    char* ptr_end;
    t_block *blocks;
    struct s_page *next;
} t_page;

void* malloc(size_t size);
void free(void* ptr);

# endif
