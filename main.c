#include "malloc_friend/malloc.h"

int main(void) {
	char *s = malloc(sizeof(char) * (strlen("hello world") + 1));
	if (!s)
		return (1);
	char *s1 = malloc(sizeof(char) * (strlen("good bye world") + 1));
	if (!s1)
		return (1);
	char *s2 = malloc(sizeof(char) * (strlen("lol") + 1));
	if (!s2)
		return (1);
	return (0);	
}
