#include "../include/malloc.h"

static void
free_ptr(t_ptr* i_ptr) {
	if (i_ptr->head_page->type == LARGE) {
		if (i_ptr->prev_page)
			i_ptr->prev_page->next = i_ptr->head_page->next;
		else
			page[i_ptr->head_page->type] = i_ptr->head_page->next;
		if (munmap(i_ptr->head_page, i_ptr->head_page->size) == -1)
			printf("Free error");
		return ;
	}
	else
		i_ptr->head_block->free = True;
}

void
free(void *ptr) {
	if (!ptr)
		return ;
	t_ptr info;
	ptr -= sizeof(t_block);
	t_ptr* i_ptr = get_infos((t_block*)ptr, &info);
	if (!i_ptr)
		return ;
	free_ptr(i_ptr);
}
