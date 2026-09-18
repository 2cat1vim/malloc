#include "../include/malloc.h"

static void
print_page(t_page *p)
{
	t_type	n;

	n = p->type;
	print(STDOUT_FILENO, SELECT_TYPE(n), false);
	print(STDOUT_FILENO, " ->" YEL, false);
	print_hex(p);
	print(STDOUT_FILENO, RST "\n", false);
}

static void
print_block(t_block *b, int op, int pos)
{
	print(STDOUT_FILENO, MAG "ALLOC[" RST, false);
	print_nbr(pos);
	print(STDOUT_FILENO, MAG "]" RST ": ", false);
	print(STDOUT_FILENO, WHERE_AM_I(op), false);
	print_hex(PTR(op));
	print(STDOUT_FILENO, " - ", false);
	print_hex((char*)b + b->size);
	print(STDOUT_FILENO, " : ", false);
	print(STDOUT_FILENO, IS_FREE(b->free), false);
	print(STDOUT_FILENO, " : ", false);
	print_nbr(SIZE(op));
	print(STDOUT_FILENO, " bytes", true);
}

void
show_alloc_mem(void)
{
	t_page	*h_p;
	size_t	total;
	t_block	*h_b;

	total = 0;
	for (size_t i = 0; i < TYPE_SIZE; i++)
	{
		h_p = share->page[i];
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
	print(STDOUT_FILENO, "Total : ", false);
	print_nbr(total);
	print(STDOUT_FILENO, " bytes", true);
}
