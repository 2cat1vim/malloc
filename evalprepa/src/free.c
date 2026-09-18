#include "../include/malloc.h"

static bool
free_ptr(t_block* b, t_page* p)
{
	if (b->free == true) {
		print(STDERR_FILENO, "error : free : invalid ptr", true);
		return (false);
	}
	else if (p->type == LARGE) {
		if (p->prev) {
			p->prev->next = p->next;
		}
		else {
			share->page[p->type] = p->next;
		}

		if (munmap(p, p->size) == -1) {
			print(STDERR_FILENO, "error : free : munmap failed", true);
			return (false);
		}
		return (true);
	}
	else {
		b->free = true;
	}
	return (true);
}

void
free(void* ptr)
{
	if (!ptr) {
		return ;
	}

	t_page* page = get_page(ptr);
	if (!page) {
		print(STDERR_FILENO, "error : free : invalid ptr", true);
		return;
	}

	if (!block_exist(page, ptr)) {
		print(STDERR_FILENO, "error : free : invalid ptr", true);
		return;
	}

	char* cast_ptr_block = (char*)ptr - sizeof(t_block);
	if (!free_ptr((t_block *)cast_ptr_block, page)) {
		return ;
	}
}
