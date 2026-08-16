#include "malloc.h"

t_block*
add_block(t_page *p, size_t size) {
	t_block* new = (t_block*)p->ptr_end;
	new->size = size;
	new->free = False;
	new->next = NULL;
	p->ptr_end = (void *)p->ptr_end + size; 
	return (new);
}

t_block*
select_block(t_page *p, size_t size) {
	t_block* node = p->blocks;
	t_block* last = NULL;
	p->size += size;
	while (node) {
		if (node->free == True)
			return (node);
		last = node;
		node = node->next;
	}
	if (last) {
		node = add_block(p, size);
		last->next = node;
		return (node);
	}
	last = add_block(p, size);
	p->blocks = last;
	return (last);
}

t_block*
create_block(size_t size, t_type type) {
	t_block* b;
	t_page* p;
	p = lookup_page(size, type);
	if (!p)
		return (NULL);
	b = select_block(p, size + sizeof(t_block));
	if (!b)
		return (NULL);
	return (b);
}
