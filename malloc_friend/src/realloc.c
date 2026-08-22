#include "../include/malloc.h"

/* NEED GUARDS */

static void*
realloc_ptr(t_block *b, size_t size)
{
	char* cast_block_ptr;

	if (b->free == true) {
		write(STDERR_FILENO, "error: cannot realloc a freed ptr\n",
			strlen("error: cannot realloc a freed ptr\n"));
		return (NULL);
	}
	cast_block_ptr = (char*)b;
	if (size <= b->size) {
		b->size = size;
		return (cast_block_ptr + sizeof(t_block));
	}
	else {
		free(cast_block_ptr + sizeof(t_block));
		return (malloc(size - sizeof(t_block)));
	}
	// handle tiny large small
}

void*
realloc(void* ptr, size_t size)
{
	char* cast_ptr_block;
	/* PTR is NULL, act like its a call to malloc */
	if (!ptr) {
		return (malloc(size));
	}
	/* Size is empty, act like its a call to free */
	if (size == 0) {
		free(ptr);
		return (NULL);
	}
	/* Cast ptr and minus it by sizeof(t_block/t_page)
			to get the position of the block/page */
	cast_ptr_block = ptr;
	cast_ptr_block -= sizeof(t_block);
	return (realloc_ptr((t_block*)cast_ptr_block, (size + sizeof(t_block))));
}
