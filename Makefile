#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 17:49:02 by Jburlama          #+#    #+#              #
#    Updated: 2024/05/01 20:21:40 by Jburlama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
CFILES = main.c check_error.c data_init.c utils.c philo.c philo_utils.c \
		 printf.c printf2.c reaper.c
OBJS = ${CFILES:.c=.o}
OBJS_DIR = ./objs


all: ${NAME}

${NAME}: ${OBJS}
	@${CC} -o $@ $^

${OBJS_DIR}:
	mkdir -p $@

${OBJ}: ${CFILES} ${OBJS_DIR}
	@${CC} ${CFILES} -c ${CFILES}

clean:
	@rm -rf ${OBJS}
	@rm -rf ${OBJS_DIR}

fclean: clean
	@rm -rf ${NAME}

re: fclean ${NAME}

.PHONY: clean re fclean
