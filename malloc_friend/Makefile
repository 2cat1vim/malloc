NAME = malloc.a
CC = clang
CFLAGS = -g -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs

SRC = malloc.c \
	  page.c \
	  block.c \
	  debug.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
