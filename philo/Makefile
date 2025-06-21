NAME    = philo
CC      = cc
CFLAGS  = -Wall -Werror -Wextra -fsanitize=thread -g
HEADER = include/philo.h

SRCS    = src/main.c src/init.c src/philosopher.c \
          src/print.c src/handle_input.c src/manage_philos.c \
          src/get_time.c src/free_mem.c src/utils.c
 
OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re