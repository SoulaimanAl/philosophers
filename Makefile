SRC = philo.c utils_philo.c create_philos.c garbage_collector.c monitor.c routine_philo.c
FLAG = -Wall -Werror -Wextra -g #-fsanitize=thread
NAME = philo

all: $(NAME)

$(NAME):
	@cc $(FLAG) $(SRC) -o $(NAME)

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all
