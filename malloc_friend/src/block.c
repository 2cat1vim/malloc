#include "../include/malloc.h"

t_block*
add_block(t_page* p, size_t size, t_block* last)
{
	t_block* new;

	new = (t_block*)p->ptr_end;
	new->size = ALIGN(size);
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
	p->size += size;
	while (node) {
		if (node->free == true && size <= node->size) {
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
