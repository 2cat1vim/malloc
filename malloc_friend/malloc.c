#include "malloc.h"

static t_page* page[3] = {NULL, NULL, NULL};

t_bool
page_has_space(t_page* page, size_t size) {
	t_block *b;
	b = page->blocks;
	while (b) {
		if (b->free && b->size >= size)
			return (True);
		b = b->next;
	}
	return (False);
}

t_page*
search_page_space(size_t size, t_type type) {
	t_page *p;
	switch (type) {
		case TINY:
			p = page[TINY];
			break;
		case SMALL:
			p = page[SMALL];
			break;
		default:
			p = page[LARGE];
			break;
	}
	while (p) {
		if (page_has_space(p, size) == True)
			return (p);
		p = p->next;
	}
	return (NULL);
}

t_page*
create_page(t_type type) {
	size_t map_size;
	map_size = ((sizeof(t_page) + (PAGE_SIZE - 1)) / PAGE_SIZE) * PAGE_SIZE;
	t_page* p = mmap(NULL, map_size,
					PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANONYMOUS,
					-1, 0);
	if (p == MAP_FAILED)
		return (NULL);
	p->type = type;
	p->map_size = map_size;
	p->blocks = NULL;
	p->next = NULL;

	page[type] = p;
	return (p);
}

void
print_page(t_page* p) {
    char buf[128];
    int  len;

    len = snprintf(buf, sizeof(buf), "type: %d\nmap_size: %zu\n", p->type, p->map_size);
    write(2, buf, len);
}

void
print_block(t_block* b) {
    char buf[128];
    int  len;

    len = snprintf(buf, sizeof(buf), "free: %d\nsize: %zu\n", b->free, b->size);
    write(2, buf, len);
}

t_page*
lookup_page(size_t size, t_type type) {
	t_page* p;
	p = search_page_space(size, type);
	if (!p) {
		p = create_page(type);
		if (!p)
			return (NULL);
		print_page(p);
	}
	if (!p)
		return (NULL);
	return (p);
}

t_block*
add_block(size_t size) {
	t_block* b = NULL;
	while (b) {
		if (b->free == True) {
			b->size = (size + sizeof(t_block));
			b->free = False;
			return (b);
		}
		b = b->next;
	}
	return (NULL);
}

t_block*
create_block(size_t size, t_type type) {
	t_block* b;
	t_page* p;
	p = lookup_page(size, type);
	if (!p)
		return (NULL);
	b = add_block(size);
	if (!b)
		return (NULL);
	print_block(b);
	return (b);
}

/*size_t alloc(size_t size) {
	size_t map_size = size + sizeof(size_t);
	map_size = (map_size + PAGE_SIZE - 1) / PAGE_SIZE;
	map_size = map_size * PAGE_SIZE;
	void *ptr = mmap(NULL, map_size, PROT_READ | PROT_WRITE,
		       	MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);

	*(size_t *)ptr = map_size;
	return (ptr + sizeof(size_t));
}*/

void*
malloc(size_t size) {
	t_block* b;
	if (size == 0)
		return (NULL);
	if (size + sizeof(t_block) <= TINY_MAX)
		b = create_block(size, TINY);
	else if (size + sizeof(t_block) <= SMALL_MAX)
		b = create_block(size, SMALL);
	else
		b = create_block(size, LARGE);
	if (!b)
		return (NULL);
	return (NULL); // TEMP RETURN TO SILENCE WARNING
}

void
free(void *ptr) {
	if (!ptr)
		return ; 
	void *pptr = ptr - sizeof(size_t);
	size_t map_size = *(size_t *)pptr;
	if (munmap(pptr, map_size) == -1)
		printf("Free error");
}
