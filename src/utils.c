#include "../include/malloc.h"

size_t
len(const char *str) {
	size_t i = 0;
	while (str[i]) {
		i++;
	}
	return (i);
}


void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src && n > 0)
	{
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

void
pout(const char* s)
{
	if (!s) {
		return ;
	}
	write(1, s, len(s));
}

void
pouts(const char* s)
{
	pout(s);
	write(1, "\n", 1);
}

void
epout(const char* s)
{
	if (!s) {
		return ;
	}
	write(2, s, len(s));
}

void
epouts(const char* s)
{
	pout(s);
	write(2, "\n", 1);
}

void
print_hex(void* p)
{
	unsigned long addr;
	char base[17] = "0123456789ABCDEF";
	char buffer[17];
	int i;

	addr = (unsigned long)p;
	i = 0;
	if (addr == 0) {
		pout("0x0");
		return ;
	}
	pout("0x");
	while (addr > 0) {
		buffer[i++] = base[addr % 16];
		addr /= 16;
	}
	while (--i >= 0) {
		write(1, &buffer[i], 1);
	}
}

void
print_nbr(size_t n)
{
	char c;
	if (n >= 10) {
		print_nbr(n / 10);
	}
	c = (n % 10) + '0';
	write(1, &c, 1);
}
