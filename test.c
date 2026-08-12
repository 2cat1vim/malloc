#include "f_malloc.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

int main(void) {
	size_t len = strlen("hello");
	size_t len1 = strlen("goodbye");
	char *s = f_malloc(sizeof(char) * (len + 1));
	char *s1 = f_malloc(sizeof(char) * (len1 + 1));
	strcpy(s, "hello");
	if (!s)
		puts(strerror(errno));
	strcpy(s1, "goodbye");
	if (!s1)
		puts(strerror(errno));
	else
		puts(s);
		puts(s1);
	f_free(s);
	f_free(s1);
	return (0);	
}
