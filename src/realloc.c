#include "../includes/malloc.h"

static void*
realloc_ptr(t_block *b, size_t size)
{
	char* cast_block_ptr;
	void *newptr;

	if (b->free == true) {
		print(STDERR_FILENO, "error : realloc : invalid ptr", true);
		return (NULL);
	}

	cast_block_ptr = (char*)b;
	if (size <= b->size) {
		b->size = size;
		return (cast_block_ptr + sizeof(t_block));
	}
	else {
		newptr = malloc(size);
		if (!newptr) {
			return (NULL);
		}
		ft_memcpy(
			(char*)newptr,
		 	(char*)cast_block_ptr + sizeof(t_block),
			b->size - sizeof(t_block)
		);
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

	t_page* page = get_page(ptr);
	if (!page) {
		print(STDERR_FILENO, "error : realloc : invalid ptr", true);
		return (NULL);
	}

	if (!block_exist(page, ptr)) {
		print(STDERR_FILENO, "error : realloc : invalid ptr", true);
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
	
	char* cast_ptr_block = (char*)ptr - sizeof(t_block);
	return (realloc_ptr((t_block*)cast_ptr_block, (size + sizeof(t_block))));
}
