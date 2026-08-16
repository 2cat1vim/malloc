#include "malloc.h"

t_page* page[3] = {NULL, NULL, NULL};

t_page*
mmap_page(t_page* p, t_type type, size_t size) {
	t_page *mp = p;
	mp = mmap(NULL, size,
					PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANONYMOUS,
					-1, 0);
	if (mp == MAP_FAILED)
		return (NULL);
	mp->type = type;
	mp->ptr_end = (void *)mp + sizeof(t_page);
	mp->size = sizeof(t_page);
	mp->blocks = NULL;
	mp->next = NULL;
	return (mp);
}

size_t
get_map_size(t_type type, size_t size) {
	size_t map_size = 0;
	if (type == TINY)
		map_size = (size_t)TINY_MMAP;
	else if (type == SMALL)
		map_size = (size_t)SMALL_MMAP;
	else
		map_size = size + sizeof(t_page) + sizeof(t_block);
	return (map_size);
}

t_page*
create_page(t_type type, size_t size) {
	t_page* head = page[type];
	size_t map_size = get_map_size(type, size);
	if (!head) {
		head = mmap_page(head, type, map_size);
		page[type] = head;
		return (head);
	}
	t_page* last = NULL;
	while (head) {
		last = head;
		head = head->next;
	}
	head = mmap_page(head, type, map_size);
	last->next = head;
	return (head);
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
		p = create_page(type, size);
		if (!p)
			return (NULL);
	}
	return (p);
}

t_bool
page_has_space(t_page* page, size_t size) {
	if (page->type == LARGE)
		return (False);
	if (page->size + size <= (page->type == SMALL) ? (size_t)SMALL_MMAP : (size_t)TINY_MMAP)
        return (True);
	return (False);
}

