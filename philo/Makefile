NAME = philo
CC = cc 
FLAGS = -Wall -Werror -Wextra
HEADER = includes/philo.h

SRC = src/main.c src/init.c src/philosopher.c src/print.c src/handle_input.c src/grim_reaper.c src/get_time.c src/free_mem.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re