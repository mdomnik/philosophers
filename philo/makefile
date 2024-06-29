# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 15:38:39 by mdomnik           #+#    #+#              #
#    Updated: 2024/06/29 16:21:47 by mdomnik          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =   philo

CC      =   cc

CFLAGS  =   -Wall -Werror -Wextra -g

SRCS    =   src/init.c \
			src/routine.c \
			src/state_change.c \
			src/main.c \
			src/testing.c \
			src/utils/ft_atoi_philo.c \
			src/utils/error_free.c \

OBJS    =   $(SRCS:%.c=out/%.o)

all:        $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

out/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

make memcheck: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 5 800 200 200 7

testNEGINT: all
	./$(NAME) 5 -800 200 200 7

testPLUSINT: all
	./$(NAME) 5 +800 200 200 7

testMAXINT: all
	./$(NAME) 5 800 200 2147483648

testMININT: all
	./$(NAME) 5 800 200 -2147483649

testNONINT: all
	./$(NAME) 5 -12acs 200 200 7

testNEGOPTION: all
	./$(NAME) 5 800 200 200 -7

testARGS: all
	./$(NAME) 5 800 200

clean:
	rm -rf out

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

