ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK_NAME = libft_malloc.so

CC = clang
CFLAGS = -g -Wall -Wextra -Werror -fPIC

SRC = src/malloc.c \
      src/page.c \
      src/block.c \
      src/debug.c \
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
	@if [ -d "$(LIBFT_DIR)" ]; then make -C $(LIBFT_DIR) clean; fi

fclean: clean
	rm -f $(NAME)
	rm -f $(LINK_NAME)
	@if [ -d "$(LIBFT_DIR)" ]; then make -C $(LIBFT_DIR) fclean; fi

re: fclean all

.PHONY: all clean fclean re
