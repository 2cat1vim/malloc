#include "malloc.h"

void
print_debug(char *s) {
    char buf[400];
    int  len;

    len = snprintf(buf, sizeof(buf), "%s\n", s);
    write(2, buf, len);
}

void
print_page(t_page* p) {
    char buf[400];
    int  len;

    len = snprintf(buf, sizeof(buf), "PAGE -> page p: %p\ntype: %d\nsize: %zu\nptr_end: %p\nsize - page: %zu\n",
	               p, p->type, p->size, p->ptr_end, p->size - sizeof(t_page));
    write(2, buf, len);
}

void
print_block(t_block* b) {
    char buf[400];
    int  len;

    len = snprintf(buf, sizeof(buf), "BLOCK -> \nfree: %d\nsize: %zu\nsize - block: %zu\n",
				   b->free, b->size, b->size - sizeof(t_block));
    write(2, buf, len);
}