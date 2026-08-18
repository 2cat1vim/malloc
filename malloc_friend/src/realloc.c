#include "../include/malloc.h"

static void*
realloc_ptr(t_block *b, t_page *p, size_t size) {
    (void)p;
    /* Size is already enough, return ptr */
    if (b->size >= size) {
        char* cast_block_ptr = (char*)b;
        return (cast_block_ptr + sizeof(t_block));
    }
    /* To be continued */
    return (NULL);
}

void*
realloc(void* ptr, size_t size) {
    /* PTR is NULL, act like its a call to malloc */
    if (!ptr)
        return (malloc(size));

    /* Size is empty, act like its a call to free */
    if (size == 0) {
        free(ptr);
        return (NULL);
    }

    /* Cast ptr and minus it by sizeof(t_block/t_page) 
			to get the position of the block/page */
    char* cast_ptr_block = ptr;
    cast_ptr_block -= sizeof(t_block);
    char* cast_ptr_page = cast_ptr_block - sizeof(t_page);
    return (realloc_ptr((t_block*)cast_ptr_block, (t_page*)cast_ptr_page, size));    
}