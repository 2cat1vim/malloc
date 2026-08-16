#include "malloc_friend/malloc.h"

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
	malloc(10);
	malloc(35);
	print_mem();
	return (0);	
}
