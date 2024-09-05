CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude

NAME = philo

FILES = \
	src/ft_print_utils.c \
	src/ft_libft.c \
	src/main.c \

OBJS = ${FILES:.c=.o}

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean: $(OBJS)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
