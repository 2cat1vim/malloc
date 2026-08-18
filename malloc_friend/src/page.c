#include "../include/malloc.h"

t_page* page[TYPE_SIZE] = {NULL, NULL, NULL};

# define RW \
	PROT_READ | PROT_WRITE
# define PA \
	MAP_PRIVATE | MAP_ANONYMOUS

t_page*
mmap_page(t_page* p, t_type type, size_t size) {
	t_page *mp = p;
	mp = mmap(NULL, size, RW, PA, -1, 0);
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
	if (type == LARGE)
		map_size = size + sizeof(t_page) + sizeof(t_block);
	map_size = LIMIT(type);
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
	head->prev = last;
	last->next = head;
	return (head);
}

t_page*
search_page_space(size_t size, t_type type) {
	t_page *p = page[type];
	while (p) {
		if (page_has_space(p, size) == true)
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

bool
page_has_space(t_page* page, size_t size) {
	if (page->type == LARGE)
		return (false);

	size_t limit = LIMIT(page->type);
	if (page->size + size <= limit)
        return (true);
	return (false);
}

