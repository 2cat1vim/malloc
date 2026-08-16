#include "malloc.h"
t_page* page[3] = {NULL, NULL, NULL};

t_page*
create_page(t_type type) {
	size_t map_size = 0;
	if (type == TINY)
		map_size = (size_t)TINY_MMAP;
	else if (type == SMALL)
		map_size = (size_t)SMALL_MMAP;
	else
		map_size = LARGE_BYTES + sizeof(t_page) + sizeof(t_block);
	t_page* p = mmap(NULL, map_size,
					PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANONYMOUS,
					-1, 0);
	if (p == MAP_FAILED)
		return (NULL);
	p->type = type;
	p->ptr_end = (void *)p + sizeof(t_page);
	p->size = sizeof(t_page);
	p->blocks = NULL;
	p->next = NULL;

	page[type] = p;
	return (p);
}

t_page*
search_page_space(size_t size, t_type type) {
	t_page *p = page[type];
	while (p) {
		if (page_has_space(p, size) == True)
			return (p);
		p = p->next;
	}
	return (NULL);
}

t_page*
lookup_page(size_t size, t_type type) {
	t_page* p = search_page_space(size + sizeof(t_block), type);
	if (!p) {
		p = create_page(type);
		if (!p)
			return (NULL);
	}
	return (p);
}

t_bool
page_has_space(t_page* page, size_t size) {
	if (page->size + size <= (size_t)PAGE_SIZE)
        return (True);
	return (False);
}

