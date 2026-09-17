#include "malloc.h"
#include <string.h>
#include <unistd.h>

void show_alloc_mem(void);
void	ft_putstr(char const *str)
{
	while (*str)
		write(1, str++, 1);
}

int		main(void)
{
	malloc(1024);
	malloc(1024 * 32);
	malloc(1024 * 1024);
	malloc(1024 * 1024 * 16);
	malloc(1024 * 1024 * 128);
	ft_putstr("\n---------show_alloc_mem()------------\n");
	show_alloc_mem();
	return (0);
}