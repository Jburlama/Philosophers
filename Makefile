# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jburlama <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 18:19:12 by jburlama          #+#    #+#              #
#    Updated: 2024/04/13 16:43:16 by jburlama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
CFILES = main.c check_error.c

all: ${NAME}

${NAME}: ${CFILES}
	${CC} ${CFLAGS} ${CFILES} -o $@

clean:

fclean: clean
	rm -rf ${NAME}

re:
	make fclean
	make ${NAME}

.PHONY: clean re fclean
