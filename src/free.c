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

t_page* find_page_for_ptr(void *ptr) {
    for (size_t i = 0; i < 3; i++) {
        t_page* head = share->page[i];
        while (head) {
            char *page_start = (char*)head;
            char *page_end = page_start + head->size;
            
            if ((char*)ptr >= page_start && (char*)ptr < page_end) {
                return head;
            }
            head = head->next;
        }
    }
    return NULL;
}

void
free(void* ptr)
{
	char* cast_ptr_block = (char*)ptr - sizeof(t_block);
	t_page* page = find_page_for_ptr(ptr);

	if (!page) {
		epouts("error: invalid ptr");
		print_hex(ptr);
		epouts("");
		return;
	}

	if (free_ptr((t_block *)cast_ptr_block, page) == -1) {
		return ;
	}
}
