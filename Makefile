# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 18:19:12 by jburlama          #+#    #+#              #
#    Updated: 2024/04/24 16:30:45 by Jburlama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=thread
CFILES = main.c check_error.c data_init.c utils.c philo.c

all: ${NAME}

${NAME}: ${CFILES}
	${CC} ${CFLAGS} ${CFILES} -o $@

clean:

fclean: clean
	rm -rf ${NAME}

re: fclean ${NAME}

.PHONY: clean re fclean
