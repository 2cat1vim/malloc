#include "../include/malloc.h"

void
free(void *ptr) {
	if (!ptr)
		return ; 
	void *pptr = ptr - sizeof(size_t);
	size_t map_size = *(size_t *)pptr;
	if (munmap(pptr, map_size) == -1)
		printf("Free error");
}
