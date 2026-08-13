#include "malloc.h"

static t_zone* zone[3] = {NULL, NULL, NULL};

t_block*
create_block(size_t size, t_type type) {
	t_block* block;
	block = lookup_zone(size, type);
	if (!block)
		return (NULL);
	return (block)
}

void
lookup_zone(size_t size, t_type type) {
	t_zone* zone;
	zone = search_zone_space(size, type)
	if (!zone) {
		zone = create_zone(size, type)
		if (!zone)
			return (NULL);
	}
	block = carve(zone, size);
	if (!block)
		return (NULL);
	return (block);
}

t_zone*
search_zone_space(size_t size, t_type type) {
	t_zone *head;
	if (type == TINY)
		head = zone[ZONE_TINY];
	else if (type == SMALL)
		head = zone[ZONE_SMALL];
	else
		head = zone[ZONE_LARGE];
	size_t c;
	while (head) {
		if (zone_has_space(head, size) == True)
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_bool
zone_has_space(t_zone* zone, size_t size) {
	t_block *block;
	block = zone->blocks;
	while (block) {
		if (block->free && block->size >= size)
			return (True);
		block = block->next;
	}
	return (False);
}

t_zone*
create_zone(size_t size, t_type type) {
	return (NULL);
}

t_block* carve(t_zone zone, size_t size) {
	return (NULL)
}


size_t alloc(size_t size) {
	size_t map_size = size + sizeof(size_t);
	map_size = (map_size + PAGE_SIZE - 1) / PAGE_SIZE;
	map_size = map_size * PAGE_SIZE;
	void *ptr = mmap(NULL, map_size, PROT_READ | PROT_WRITE,
		       	MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);

	*(size_t *)ptr = map_size;
	return (ptr + sizeof(size_t));
}

void*
malloc(size_t size) {
	t_block* block;
	if (size == 0)
		return (NULL);
	if (size <= TINY_MAX)
		block = create_block(size, TINY);
	else if (size <= SMALL)
		block = create_block(size, SMALL);
	else
		block = create_block(size, LARGE);
	if (!block)
		return (NULL);
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
