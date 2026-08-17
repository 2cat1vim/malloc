#include "../include/malloc.h"

static void free_ptr(t_block *match) {
	for (size_t i = 0; i < 3; i++) {
		t_page* prev_page = NULL;
		t_page* head_page = page[i];
		while (head_page) {
			t_block* head_block = head_page->blocks;
			while (head_block) {
				if (head_block == match) {
					if (head_page->type == LARGE) {
						if (prev_page)
							prev_page->next = head_page->next;
						else
							page[i] = head_page->next;
						if (munmap(head_page, head_page->size) == -1)
							printf("Free error");
						return ;
					}
					else {
						head_block->free = True;
					}
				}
				head_block = head_block->next;
			}
			prev_page = head_page;
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
