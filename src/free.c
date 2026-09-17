#include "../include/malloc.h"

static int
free_ptr(t_block* b, t_page* p)
{
	if (b->free == true) {
		epout("error: This region is set to FREE, you cannot free it again (");
		print_hex((char*)b);
		epouts(")");
		return (-1);
	}
	else if (p->type == LARGE) {
		if (p->prev) {
			p->prev->next = p->next;
		}
		else {
			share->page[p->type] = p->next;
		}

		if (munmap(p, p->size) == -1) {
			epouts("error: munmap failed");
			return (-1);
		}
		return (0);
	}
	else {
		b->free = true;
	}
	return (0);
}

bool
ptr_exist(t_page *page) {
	for (size_t i = 0; i < 3; i++) {
		t_page* head = share->page[i];
		while (head) {
			if (head == page)
				return (true);
			head = head->next;
		}
	}
	return (false);
}

void
free(void* ptr)
{
	char* cast_ptr_block;
	char* cast_ptr_page;

	if (!ptr) {
		epouts("error: invalid ptr");
		return ;
	}

	cast_ptr_block = (char*)ptr - sizeof(t_block);
	cast_ptr_page = cast_ptr_block - (sizeof(t_page));

	if (!ptr_exist((t_page*)cast_ptr_page)) {
		epouts("error: invalid ptr");
		return ;
	}

	if (free_ptr((t_block *)cast_ptr_block, (t_page *)cast_ptr_page) == -1) {
		return ;
	}
}
