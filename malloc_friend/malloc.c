#include "malloc.h"

void*
malloc(size_t size) {
	t_block* b;
	if (size == 0)
		return (NULL);
	if (size + sizeof(t_block) <= TINY_BYTES)
		b = create_block(size, TINY);
	else if (size + sizeof(t_block) <= SMALL_BYTES)
		b = create_block(size, SMALL);
	else
		b = create_block(size, LARGE);
	if (!b)
		return (NULL);
	return ((void*)b) + sizeof(t_block);
}

void
free(void *ptr) {
	if (!ptr)
		return ; 
	void *pptr = ptr - sizeof(size_t);
	size_t map_size = *(size_t *)pptr;
	if (munmap(pptr, map_size) == -1)
		printf("Free error");
}
