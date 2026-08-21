#include "../include/malloc.h"

#define SELECT_TYPE(n) (n == 0) ? "TINY" : (n == 1) ? "SMALL" : "LARGE"
#define IS_FREE(f) (f == true) ? "Free" : "Not Free"
#define PTR(op) (op == 0) ? b : b + sizeof(t_block)
#define SIZE(op) (op == 0) ? b->size - sizeof(t_block) : b->size
#define WHERE_AM_I(op) (op == 0) ? "PTR INFOS : " : "BLOCK + PTR INFOS : "
static void	print_page(t_page *p)
{
	t_type	n;

	n = p->type;
	pout(SELECT_TYPE(n));
	pout(" : ");
	print_hex(p);
	pout("\n");
}

static void	print_block(t_block *b, int op)
{
	pout(WHERE_AM_I(op));
	print_hex(PTR(op));
	pout(" - ");
	print_hex(b + b->size);
	pout(" : ");
	pout(IS_FREE(b->free));
	pout(" : ");
	print_nbr(SIZE(op));
	pouts(" bytes");
}

void	show_alloc_mem(void)
{
	t_page	*h_p;
	size_t	total;
	t_block	*h_b;

	total = 0;
	for (size_t i = 0; i < TYPE_SIZE; i++)
	{
		h_p = page[i];
		while (h_p)
		{
			print_page(h_p);
			h_b = h_p->blocks;
			while (h_b)
			{
				print_block(h_b, 0);
				print_block(h_b, 1);
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
