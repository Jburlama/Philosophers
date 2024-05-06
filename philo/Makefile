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
CFLAGS = -Wall -Wextra -Werror
CFILES = main.c check_error.c data_init.c utils.c philo.c philo_utils.c \
		 printf.c printf2.c reaper.c
OBJS_DIR = ./objs/
SRC_DIR = ./source/
OBJS = ${addprefix ${OBJS_DIR}, ${CFILES:.c=.o}}


all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o $@

${OBJS_DIR}:
	@mkdir $@

${OBJS}: | ${OBJS_DIR}

${OBJS_DIR}%.o: ${SRC_DIR}%.c
	@${CC} ${CFLAGS} -c $^ -o $@

clean:
	@rm -rf ${OBJS}
	@rm -rf ${OBJS_DIR}

fclean: clean
	@rm -rf ${NAME}

re: fclean ${NAME}

.PHONY: clean re fclean
