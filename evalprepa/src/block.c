#include "../include/malloc.h"

bool
block_exist(t_page *page, void *ptr)
{
	t_block *b = page->blocks;
	char *cptr;

	while (b) {
		cptr = (char*)b + sizeof(t_block);
		if (cptr == (char*)ptr) {
			return (true);
		}
		b = b->next;
	}
	return (false);
}

t_block*
add_block(t_page* p, size_t size, t_block* last)
{
	t_block* new;

	new = (t_block*)p->ptr_end;
	new->size = size;
	new->free = false;
	if (last) {
		new->prev = last;
	}
	else {
		new->prev = NULL;
	}
	new->next = NULL;
	p->ptr_end = (void*)p->ptr_end + new->size;
	return (new);
}

t_block*
select_block(t_page* p, size_t size)
{
	t_block* node;
	t_block* last;

	node = p->blocks;
	last = NULL;
	while (node) {
		if (node->free == true && size <= node->size) {
			node->size = size;
			node->free = false;
			return (node);
		}
		last = node;
		node = node->next;
	}
	if (last) {
		node = add_block(p, size, last);
		last->next = node;
		return (node);
	}
	last = add_block(p, size, NULL);
	p->blocks = last;
	return (last);
}

t_block*
create_block(size_t size, t_type type)
{
	t_block* b;
	t_page* p;

	p = lookup_page(size, type);
	if (!p) {
		return (NULL);
	}
	b = select_block(p, size + sizeof(t_block));
	if (!b) {
		return (NULL);
	}
	return (b);
}