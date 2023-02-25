# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 21:35:01 by bogunlan          #+#    #+#              #
#    Updated: 2023/02/24 17:46:12 by bogunlan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
FLAGS = -Wall -Werror -Wextra -pthread #-fsanitize=thread -g

RM = rm -rf

SRC = main.c philos_monitor.c philos_utils.c philos_parser.c \
				philos_routine.c philos_end.c philos_error.c philos_time.c

OBJS = $(addprefix objs/, $(notdir $(SRC:.c=.o)))
HEADER = include/philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) 

objs/%.o: %.c | objs
	$(CC) -c $< -o $@

objs:
	mkdir objs

clean:
	$(RM) objs

fclean: clean
	$(RM) $(NAME)

norm:
	@norminette | grep Error!

re:	fclean all

.PHONY: norm all clean fclean re
