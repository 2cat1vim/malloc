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
	char *s = malloc(sizeof(char) * (strlen("hello world") + 1));
	if (!s)
		return (1);
	char *s1 = malloc(sizeof(char) * (strlen("good bye world") + 1));
	if (!s1)
		return (1);
	char *s2 = malloc(sizeof(char) * (strlen("lol") + 1));
	if (!s2)
		return (1);
	char *big = malloc(sizeof(char) * (strlen("qzhdiuhqzuduiqzhduhquidhqzuhcxuiq"
		"huchqsuiodhqhzuduqhdhqzudhqzudhgbuiqfbuiqzbfiybzeyu"
		"ijfhbqzyuihjfbyuihjqbduiyqbzdiubqzyuidbqziyudbyuiqz") + 1));
	if (!big)
		return (1);
	char *enorme_comme_mes_couilles = malloc(sizeof(char) * (8000 + 1));
	if (!enorme_comme_mes_couilles)
		return (1);
	for (size_t i = 0; i < 8000; i++)
		enorme_comme_mes_couilles[i] = '0';
	strcpy(s, "hello world");
	strcpy(s1, "good bye world");
	strcpy(s2, "lol");
	strcpy(big, "qzhdiuhqzuduiqzhduhquidhqzuhcxuiq"
		"huchqsuiodhqhzuduqhdhqzudhqzudhgbuiqfbuiqzbfiybzeyu"
		"ijfhbqzyuihjfbyuihjqbduiyqbzdiubqzyuidbqziyudbyuiqz");
	print_debugs(s);
	print_debugs(s1);
	print_debugs(s2);
	print_debugs(big);
	print_debugs(enorme_comme_mes_couilles);
	return (0);	
}
