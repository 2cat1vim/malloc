#include "malloc_friend/include/malloc.h"

int
main(void) {
	char* lol = malloc(88);
	char* lol2 = malloc(67);
	(void)lol;
	char* xd = malloc(8200);
	char* xd2 = malloc(8200);
	(void)xd2;
	(void)xd;
	show_alloc_mem();
	free(lol);
	free(xd);
	show_alloc_mem();
	char* rlol = realloc(lol, 55);
	char* rlol2 = realloc(lol2, 12);
	show_alloc_mem();
	char* rlol3 = realloc(rlol2, 10322);
	show_alloc_mem();
	(void)rlol3;
	(void)rlol;
	return (0);
}
