#include "../include/malloc.h"

static void	print_page(t_page *p)
{
	t_type	n;

	n = p->type;
	pout(SELECT_TYPE(n));
	pout(" -> " YEL);
	print_hex(p);
	pout(RST "\n");
}

static void	print_block(t_block *b, int op, int pos)
{
	pout(MAG "ALLOC[" RST );
	print_nbr(pos);
	pout(MAG "]" RST ": ");
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
			int pos = 0;
			print_page(h_p);
			h_b = h_p->blocks;
			while (h_b)
			{
				print_block(h_b, 0, pos);
				print_block(h_b, 1, pos);
				total += h_b->size;
				h_b = h_b->next;
				pos++;
			}
			h_p = h_p->next;
		}
	}
	pout("Total : ");
	print_nbr(total);
	pouts(" bytes");
}
