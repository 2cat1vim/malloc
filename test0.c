#include "malloc.h"

int main(void) {
	char *a = malloc(10);
	a[0] = 'a';
	a[1] = '\0';
	char *b = realloc(a, 10000);
	free(b);
	show_alloc_mem();
}
