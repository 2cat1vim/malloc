#include "malloc_friend/include/malloc.h"

void
print_debugs(char* ptr) {
    char buf[10000];
    int  len;

    len = snprintf(buf, sizeof(buf), "Pointer: %p : %s\n", ptr, ptr);
    write(2, buf, len);
}

int
main(void) {
	char* lol = malloc(100);
	(void)lol;
	char* xd = malloc(8200);
	char* xd2 = malloc(8200);
	(void)xd2;
	(void)xd;
	show_alloc_mem();
	free(lol);
	free(xd);
	show_alloc_mem();
	return (0);	
}
