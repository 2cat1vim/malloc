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
	malloc(100);
	malloc(8000);
	malloc(400000);
	for (int i = 0; i < 128; i++)
		malloc(96);
	show_alloc_mem();
	return (0);	
}
