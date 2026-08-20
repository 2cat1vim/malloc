MAKEFLAGS += -s
NAME = malloc_test
CC = clang
CFLAGS = -g -Wall -Wextra -Werror

LIBDIR = malloc_friend
LIBNAME = libft_malloc.so
LIBPATH = $(LIBDIR)/$(LIBNAME)

SRC = main.c
OBJS = $(SRC:.c=.o)

all: $(NAME)
	echo "[MAKEFILE]: Compiling Tester"
	@test -n "$(SILENT_END)" || echo "[MAKEFILE]: Task completed"

$(NAME): $(OBJS) $(LIBPATH)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBDIR) -lft_malloc

$(LIBPATH):
	$(MAKE) -C $(LIBDIR) -f Makefile

clean:    
	echo "[MAKEFILE]: Cleaning Tester"
	rm -f $(OBJS)
	$(MAKE) -C $(LIBDIR) -f Makefile clean
	@test -n "$(SILENT_END)" || echo "[MAKEFILE]: Task completed"

fclean:
	echo "[MAKEFILE]: Cleaning Tester"
	rm -f $(OBJS)
	$(MAKE) -C $(LIBDIR) -f Makefile clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBDIR) -f Makefile fclean
	@test -n "$(SILENT_END)" || echo "[MAKEFILE]: Task completed"

re:
	$(MAKE) fclean SILENT_END=1
	$(MAKE) all

.PHONY: all clean fclean re
