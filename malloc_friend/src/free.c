#include "../include/malloc.h"

static void
free_ptr(t_block *b, t_page* p) {
	if (p->type == LARGE) {
		if (p->prev)
			p->prev->next = p->next;
		else
			page[p->type] = p->next;
		if (munmap(p, p->size) == -1)
			printf("Free error");
		return ;
	}
	else
		b->free = True;
}

void
free(void *ptr) {
	if (!ptr)
		return ;

	/* Cast ptr and minus it by sizeof(t_block) 
			to get the position of the block */
	char* cast_ptr_block = ptr;
	cast_ptr_block -= sizeof(t_block);
	char* cast_ptr_page = cast_ptr_block - (sizeof(t_page));

	// NEED TO CHECK
	/* Check that the block is existing and then free it */
	free_ptr((t_block*)cast_ptr_block, (t_page*)cast_ptr_page);
}
