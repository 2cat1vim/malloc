#include "../include/malloc.h"

/* NEED GUARDS */

static void*
realloc_ptr(t_block *b, size_t size)
{
	char* cast_block_ptr;
	void *newptr;

	if (b->free == true) {
		epout("error: cannot realloc a freed ptr (");
		print_hex(b);
		epouts(")");
		return (NULL);
	}
	cast_block_ptr = (char*)b;
	if (size <= b->size) {
		b->size = size;
		return (cast_block_ptr + sizeof(t_block));
	}
	else {
		size_t old_data_size;

		newptr = malloc(size);
		if (!newptr) {
			return (NULL);
		}
		old_data_size = b->size - sizeof(t_block);
		ft_memcpy((char*)newptr, (char*)cast_block_ptr + sizeof(t_block), old_data_size);
		free(cast_block_ptr + sizeof(t_block));
		return (newptr);
	}
}

void*
realloc(void* ptr, size_t size)
{
	if (!ptr) {
		return (malloc(size));
	}

	if (size == 0) {
		free(ptr);
		return (NULL);
	}

	char* cast_ptr_block = (char*)ptr - sizeof(t_block);
	t_page* page = find_page_for_ptr(ptr);
	if (!page) {
		epouts("error: invalid ptr");
		return (NULL);
	}

	if (!is_valid_block_ptr(page, ptr)) {
		epouts("error: invalid ptr");
		return (NULL);
	}

	if ((page->type == LARGE) && (size < (size_t)SMALL_MMAP)) {
		void *newptr = malloc(size);
		if (!newptr) {
			return (NULL);
		}
		ft_memcpy((char*)newptr, (char*)ptr, size);
		free(ptr);
		return (newptr);
	}
	
	return (realloc_ptr((t_block*)cast_ptr_block, (size + sizeof(t_block))));
}
