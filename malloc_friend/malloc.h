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

# define TINY_MAX 400
# define SMALL_MAX 800
# define LARGE_MAX 1200

# define ZONE_TINY 0
# define ZONE_SMALL 1
# define ZONE_LARGE 2

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
    int free;
    struct s_block* next;
    struct s_block* prev;
} t_block;

typedef struct s_zone {
    t_type type;
    size_t map_size
    t_block *blocks;
    struct s_zone *next;
} t_zone;

void* malloc(size_t size);
void free(void* ptr);

# endif
