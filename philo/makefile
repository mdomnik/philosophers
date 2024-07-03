# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 15:38:39 by mdomnik           #+#    #+#              #
#    Updated: 2024/07/03 15:50:40 by mdomnik          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =   philo

CC      =   cc

CFLAGS  =   -Wall -Werror -Wextra

SRCS    =   src/fork_mutex.c \
			src/init.c \
			src/routine.c \
			src/state_change.c \
			src/main.c \
			src/monitoring.c \
			src/utils/ft_atoi_philo.c \
			src/utils/error_free.c \
			src/utils/ft_usleep.c \

OBJS    =   $(SRCS:%.c=out/%.o)

all:        $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

out/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

make memcheck: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 5 800 200 200 7

norminette:
	norminette $(SRCS) inc/philo.h

clean:
	rm -rf out

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

