#include "f_malloc.h"
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

void*
f_malloc(size_t size) {
	size_t map_size = size + sizeof(size_t);
	map_size = (map_size + sysconf(_SC_PAGESIZE) - 1) / sysconf(_SC_PAGESIZE);
	map_size = map_size * sysconf(_SC_PAGESIZE);
	void *ptr = mmap(NULL, map_size, PROT_READ | PROT_WRITE,
		       	MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);

		*(size_t *)ptr = map_size;
	return (ptr + sizeof(size_t));
}

void
f_free(void *ptr) {
	if (!ptr)
		return ; 
	void *pptr = ptr - sizeof(size_t);
	size_t map_size = *(size_t *)pptr;
	if (munmap(pptr, map_size) == -1)
		puts("Free error");
}
