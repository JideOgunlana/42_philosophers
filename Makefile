NAME = philo
CC = cc
FLAGS = -Wall -Werror -Wextra -pthread -fsanitize=thread -g
# MAKEFLAG = -j

RM = rm -rf

OBJS_DIR = objs/

MANDATORY_SRC = main philos_monitor philos_utils philos_parser philos_locks \
				philos_routine philos_end philos_error philos_time

MAIN = $(addsuffix .c, $(MANDATORY_SRC))

OBJS = $(addsuffix .o, $(MANDATORY_SRC))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC)  $(FLAGS) $(OBJS_DIR)* -o $(NAME) 

.c.o: $(MAIN)
	$(CC) -c -o $(OBJS_DIR)$@ $<

clean:
	$(RM) $(OBJS_DIR)*

fclean: clean
	$(RM) $(NAME)

norm:
	@norminette | grep Error!

re:	fclean all

.phony: norm
