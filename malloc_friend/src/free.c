#include "../include/malloc.h"

/* NEED GUARDS */

static int
free_ptr(t_block *b, t_page* p) {
	if (b->free == true) {
		write(STDERR_FILENO, "error: ptr already freed\n", strlen("error: ptr already freed\n"));
		return (-1);
	}
	if (p->type == LARGE) {
		if (p->prev)
			p->prev->next = p->next;
		else
			page[p->type] = p->next;
		if (munmap(p, p->size) == -1) {
			write(STDERR_FILENO, "error: munmap\n", strlen("error: munmap\n"));
		}
			return (-1);
		return (0);
	}
	else
		b->free = true;
	return (0);
}

void
free(void *ptr) {
	if (!ptr)
		return ;

    /* Cast ptr and minus it by sizeof(t_block/t_page)
			to get the position of the block/page */
	char* cast_ptr_block = ptr;
	cast_ptr_block -= sizeof(t_block);
	char* cast_ptr_page = cast_ptr_block - (sizeof(t_page));
	
	// NEED TO CHECK
	/* Check that the block is existing and then free it */
	if (free_ptr((t_block*)cast_ptr_block, (t_page*)cast_ptr_page) == -1)
		return ;
}
