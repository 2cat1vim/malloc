#include "../include/malloc.h"

t_ptr*
get_infos(void* ptr, t_ptr* info) {
	for (size_t i = 0; i < TYPE_SIZE; i++) {
		info->prev_page = NULL;
		info->head_page = page[i];
		while (info->head_page) {
			info->prev_block = NULL;
			info->head_block = info->head_page->blocks;
			while (info->head_block) {
				if (info->head_block == ptr)
					return (info);
				info->prev_block = info->head_block;
				info->head_block = info->head_block->next;
			}
			info->prev_page = info->head_page;
			info->head_page = info->head_page->next;
		}
	}
	return (NULL);
}

void*
malloc(size_t size) {
	t_block* b;
	if (size == 0)
		return (NULL);
	if (size + sizeof(t_block) <= TINY_BYTES)
		b = create_block(size, TINY);
	else if (size + sizeof(t_block) <= SMALL_BYTES)
		b = create_block(size, SMALL);
	else
		b = create_block(size, LARGE);
	if (!b)
		return (NULL);
	return ((void*)b) + sizeof(t_block);
}