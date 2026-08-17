#include "../include/malloc.h"

void select_free_type(t_type type, void* ptr, size_t size, t_block* b) {
	if (type == LARGE) {
		if (munmap(ptr, size) == -1)
			printf("Free error");
		return ;
	}
	b->free = True;
}

void free_ptr(t_block *match) {
	t_type type;
	for (size_t i = 0; i < 3; i++) {
		t_page* head_page = page[i];
		while (head_page) {
			t_block* head_block = head_page->blocks;
			while (head_block) {
				if (head_block == match) {
					type = (head_page->type == TINY) ? TINY :
						   (head_page->type == SMALL) ? SMALL : LARGE;
					select_free_type(type, head_page, head_page->size, head_block);
					return ;
				}
				head_block = head_block->next;
			}
			head_page = head_page->next;
		}
	}
}

void
free(void *ptr) {
	if (!ptr)
		return ;
	ptr -= sizeof(t_block);
	t_block *match = (t_block*)ptr;
	free_ptr(match);
}
