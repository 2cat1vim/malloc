#include "../include/malloc.h"

/* NEED GUARDS */

void* 
malloc(size_t size)
{
	t_block	*b;

	if (size == 0) {
		return (NULL);
	}

	// NEED TO PROPAGATE share->size ( increment where it need to );
	if (share) {
		if ((long)share->rlim.rlim_cur != (long)RLIM_INFINITY) {
			if ((long)(share->size + size) >= (long)share->rlim.rlim_cur) {
				write(STDERR_FILENO, "error: rlimit: soft limit hit\n", strlen("error: rlimit: soft limit hit\n"));
				return (NULL);
			}
		}
	}

	if (size + sizeof(t_block) <= TINY_BYTES) {
		b = create_block(size, TINY);
	}
	else if (size + sizeof(t_block) <= SMALL_BYTES) {
		b = create_block(size, SMALL);
	}
	else {
		b = create_block(size, LARGE);
	}
	if (!b) {
		return (NULL);
	}
	return ((void *)b) + sizeof(t_block);
}
