CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude

NAME = philo

FILES = \
	src/ft_print_utils.c \
	src/ft_libft.c \
	src/ft_itoa.c \
	src/ft_atoi.c \
	src/ft_putnbr_fd.c \
	src/ft_time.c \
	src/ft_philo.c \
	src/main.c \

OBJS = ${FILES:.c=.o}

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
