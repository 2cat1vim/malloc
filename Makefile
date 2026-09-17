ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK_NAME = libft_malloc.so

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -fPIC

SRC = src/malloc.c \
      src/page.c \
      src/block.c \
      src/show_alloc_mem.c \
      src/free.c \
      src/realloc.c \
      src/utils.c 

OBJS = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -shared -o $(NAME) $(OBJS) $(LIBFT)
	@rm -f $(LINK_NAME)
	@ln -s $(NAME) $(LINK_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	find . -name '*.so' -delete

re: fclean all

.PHONY: all clean fclean re
