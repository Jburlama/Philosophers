# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 17:49:02 by Jburlama          #+#    #+#              #
#    Updated: 2024/04/25 19:10:34 by Jburlama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=thread
CFILES = main.c check_error.c data_init.c utils.c philo.c philo_utils.c \
		 printf.c

all: ${NAME}

${NAME}: ${CFILES}
	${CC} ${CFLAGS} ${CFILES} -o $@

clean:

fclean: clean
	rm -rf ${NAME}

re: fclean ${NAME}

.PHONY: clean re fclean
