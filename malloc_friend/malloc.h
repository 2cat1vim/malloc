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

typedef enum s_ztype {
    TINY,
    SMALL,
    LARGE
} t_ztype;

typedef struct s_block {

    t_ztype type;
    size_t msize;
    struct s_zone* next;
} t_block;


void* malloc(size_t size);
void free(void* ptr);

# endif
