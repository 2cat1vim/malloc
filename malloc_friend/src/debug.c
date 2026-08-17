#include "../include/malloc.h"

# define SELECT_TYPE(n) \
    (n == 0) ? "TINY" : (n == 1) ? "SMALL" : "LARGE"
# define IS_FREE(f) \
    (f == True) ? "Free" : "Not Free"

static void
print_page(t_page *p) {
    t_type n = p->type;
    pout(SELECT_TYPE(n));
    pout(" : ");
    print_hex(p);
    pout("\n");
}

static void
print_block(t_block *b) {
    print_hex(b);
    pout(" - ");
    print_hex(b + b->size);
    pout(" : ");
    pout(IS_FREE(b->free));
    pout(" : ");
    print_nbr(b->size);
    pouts(" bytes");
}

void
show_alloc_mem(void) {
    t_page *h_p;
    size_t total = 0;
    for (size_t i = 0; i < TYPE_SIZE; i++) {
        h_p = page[i];
        while (h_p) {
            print_page(h_p);
            t_block *h_b = h_p->blocks;
            while (h_b) {
                print_block(h_b);
                total += h_b->size;
                h_b = h_b->next;
            }
            h_p = h_p->next;
        }
    }
    pout("Total : ");
    print_nbr(total);
    pouts(" bytes");
}