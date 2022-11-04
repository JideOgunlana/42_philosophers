NAME = philo
CC = cc
FLAGS = -Wall -Werror -Wextra

RM = rm -rf

MANDATORY_SRC = main.c utils.c parser.c philos_routine.c

NAME:
	$(CC) $(FLAGS) $(MANDATORY_SRC) -o $(NAME)

fclean:
	$(RM) $(NAME)

clean: fclean
