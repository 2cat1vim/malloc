#include "malloc_friend/malloc.h"

int main(void) {
	char *s = malloc(sizeof(char) * (strlen("hello world") + 1));
	if (!s)
		return (1);
	strcpy(s, "hello world");
	printf("%s\n", s);
	return (0);	
}
