#include "../include/malloc.h"

// BASIC COLORS
# define RST "\e[0m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define CYN "\e[0;36m"

// BOLD COLORS
# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BCYN "\e[1;36m"

// UNDERLINE COLORS
# define URED "\e[4;31m"
# define UGRN "\e[4;32m"
# define UYEL "\e[4;33m"
# define UCYN "\e[4;36m"

static void
print_page(t_page *p) {
    t_type i = p->type;
    pout((i == 0) ? "TINY" : (i == 1) ? "SMALL" : "LARGE");
    pout(" : ");
    print_hex(p);
    write(1, "\n", 1);
}

static void
print_block(t_block *b) {
    print_hex(b);
    pout(" - ");
    print_hex(b + b->size);
    pout(" : ");
    pout((b->free == True) ? "Free" : "Not Free");
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