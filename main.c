#include "malloc_friend/malloc.h"

int main(void) {
	size_t len = strlen("hello");
	size_t len1 = strlen("goodbye");
	char *s = malloc(sizeof(char) * (len + 1));
	char *s1 = malloc(sizeof(char) * (len1 + 1));
	strcpy(s, "hello");
	if (!s)
		fprintf(stderr, "%s\n", strerror(errno));
	strcpy(s1, "goodbye");
	if (!s1)
		fprintf(stderr, "%s\n", strerror(errno));
	else {
		puts(s);
		puts(s1);
	}
	free(s);
	free(s1);
	return (0);	
}
