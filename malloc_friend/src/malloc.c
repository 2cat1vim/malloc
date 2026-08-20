#include "../include/malloc.h"

/* NEED GUARDS */

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
