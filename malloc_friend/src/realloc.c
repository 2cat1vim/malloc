#include "../include/malloc.h"

/* NEED GUARDS */

static void*
realloc_ptr(t_block *b, t_page *p, size_t size) {
	(void)p;
	if (b->free == true) {
		write(STDERR_FILENO, "error: cannot realloc a freed ptr\n", strlen("error: cannot realloc a freed ptr\n"));
		return (NULL);
	}
	char* cast_block_ptr = (char*)b;
	if ((b->size >= size || b->size <= size) && b->size_max >= size) {
		b->size = size;
        	return (cast_block_ptr + sizeof(t_block));
    	}
	else {
	    	free(cast_block_ptr);
	    	return (malloc(size));
    	}
	// handle tiny large small
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
    void *res_ptr = realloc_ptr((t_block*)cast_ptr_block, (t_page*)cast_ptr_page, size);
    return (res_ptr);
}
