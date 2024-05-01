# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 17:49:02 by Jburlama          #+#    #+#              #
#    Updated: 2024/05/01 19:16:27 by Jburlama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
CFILES = main.c check_error.c data_init.c utils.c philo.c philo_utils.c \
		 printf.c printf2.c reaper.c
OBJS = ${CFILES:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} -o $@ $^

${OBJ}: ${CFILES}
	@${CC} ${CFILES} -c $<

clean:
	@rm -rf ${OBJS}

fclean: clean
	@rm -rf ${NAME}

re: fclean ${NAME}

.PHONY: clean re fclean
