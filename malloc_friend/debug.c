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
    char buf[1000];
    int  len;
    int capacity = 0;
    if (p->type == TINY)
        capacity = TINY_MMAP;
    else if (p->type == SMALL)
        capacity = SMALL_MMAP;
    else
        capacity = LARGE_BYTES + sizeof(t_page) + sizeof(t_block);

    int i = 0;
    while (p) {
        len = snprintf(buf, sizeof(buf), "<=========>\nPAGE[%d]: %p\nTYPE OF PAGE: %d\nCAPACITY: %d\nUSED SIZE: %zu\n",
                    i, p, p->type, capacity, p->size);
        write(2, buf, len);
        t_block *b = p->blocks;
        int j = 0;
        while (b) {
            len = snprintf(buf, sizeof(buf), "BLOCK[%d]: %p | USED SIZE: %zu\n",
                        j, b, b->size);
            write(2, buf, len);
            b = b->next;
            j++;
        }
        p = p->next;
        i++;
    }
}

void print_mem(void) {
	print_page(page[0]);
    print_page(page[1]);
    print_page(page[2]);
}
