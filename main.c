#include "malloc_friend/include/malloc.h"

int
main(void) {
	const char* line = "-------------------";
	char* lol = malloc(88);
	char* lol2 = malloc(67);
	(void)lol;
	char* xd = malloc(8200);
	char* xd2 = malloc(8200);
	(void)xd2;
	(void)xd;
	show_alloc_mem();
	puts(line);
	free(lol);
	free(xd);
	show_alloc_mem();
	puts(line);
	char* rlol = realloc(lol, 55);
	char* rlol2 = realloc(lol2, 12);
	show_alloc_mem();
	puts(line);
	char* rlol3 = realloc(rlol2, 111322);
	char* rlol4 = realloc(rlol3, 100000000);
	(void)rlol4;
	show_alloc_mem();
	puts(line);
	(void)rlol3;
	(void)rlol;
	return (0);
}
