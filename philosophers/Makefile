NAME = philo
FLAGS = -Wall -Wextra -Werror
LIBFT = Libft/*.c
SRC = *.c

OBJECTS_SRC = $(SRC:.c=.o)
OBJECTS_LIBFT = $(LIBFT:.c=.o)

.PHONY: all clean fclean re 

all: $(NAME)

$(NAME): $(OBJECTS_SRC)
	cc $(FLAGS) $(SRC) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJECTS_SRC) $(OBJECTS_LIBFT)

fclean: clean
	rm -f $(NAME)

re: fclean all