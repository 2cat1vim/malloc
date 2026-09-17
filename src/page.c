#include "../include/malloc.h"

t_share* share = NULL;

t_page* get_page(void *ptr) {
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

t_page*
mmap_page(t_page* p, t_type type, size_t size)
{
	t_page* mp = NULL;

	if (getrlimit(RLIMIT_AS, &share->rlim) == -1) {
		epouts("error: getrlimit failed\n");
	}
	if (size > share->rlim.rlim_cur) {
		print(STDERR_FILENO, "error : page : map size is larger than rlimit", true);
		return (NULL);	
	}

	mp = p;
	mp = mmap(NULL, size, RW, PA, -1, 0);
	if (mp == MAP_FAILED) {
		print(STDERR_FILENO, "error : page : mmap failed", true);
		return (NULL);
	}

	mp->type = type;
	mp->size = size;
	mp->ptr_end = (void*)mp + sizeof(t_page);
	mp->blocks = NULL;
	mp->next = NULL;
	mp->prev = NULL;
	return (mp);
}

size_t
get_map_size(t_type type, size_t size)
{
	size_t map_size;

	map_size = 0;
	if (type == LARGE) {
		map_size = size + sizeof(t_page) + sizeof(t_block);
		return (ALIGN(map_size));
	}
	map_size = LIMIT(type);
	return (map_size);
}

t_page*
create_page(t_type type, size_t size)
{
	t_page* head;
	t_page* last;
	size_t map_size;

	head = share->page[type];
	map_size = get_map_size(type, size);
	if (!head) {
		head = mmap_page(head, type, map_size);
		if (!head) {
			return (NULL);
		}
		share->page[type] = head;
		return (head);
	}
	last = NULL;
	while (head) {
		last = head;
		head = head->next;
	}
	head = mmap_page(head, type, map_size);
	if (!head) {
		return (NULL);
	}
	head->prev = last;
	last->next = head;
	return (head);
}

bool
page_has_space(t_page* page, size_t size)
{
	size_t limit;
	size_t used;

	if (page->type == LARGE) {
		return (false);
	}
	limit = LIMIT(page->type);
	used = (size_t)((char*)page->ptr_end - (char*)page);
	if (used + size <= limit) {
		return (true);
	}
	return (false);
}

bool
create_share() {
	if (!share) {
		share = mmap(NULL, sizeof(t_share), RW, PA, -1, 0);
		if (share == MAP_FAILED) {
			print(STDERR_FILENO, "error : page : mmap failed", true);
			return (false);
		}
		for (size_t i = 0; i < 3; i++) {
			share->page[i] = NULL;
		}
	}
	return (true);
}


t_page
*search_page_space(size_t size, t_type type)
{
	t_page* p;

	if (!share) {
		if (!create_share()) {
			return (NULL);
		}
	}
	p = share->page[type];
	while (p) {
		if (page_has_space(p, size) == true) {
			return (p);
		}
		p = p->next;
	}
	return (NULL);
}

t_page*
lookup_page(size_t size, t_type type)
{
	t_page* p;

	p = search_page_space(size + sizeof(t_block), type);
	if (!p) {
		p = create_page(type, size);
		if (!p) {
			return (NULL);
		}
	}
	return (p);
}