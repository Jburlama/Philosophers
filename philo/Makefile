# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 15:55:41 by Jburlama          #+#    #+#              #
#    Updated: 2024/05/14 18:31:22 by Jburlama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLUE = \033[34m
GREEN = \033[32m
RESET = \033[0m

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
CFILES = main.c check_error.c data_init.c utils.c philo.c philo_utils.c \
		 printf.c printf2.c reaper.c
OBJS_DIR = ./objs/
SRC_DIR = ./source/
OBJS = ${addprefix ${OBJS_DIR}, ${CFILES:.c=.o}}


all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o $@
	@echo "${GREEN} ${NAME} done ${RESET}"

${OBJS_DIR}:
	@mkdir $@

${OBJS}: | ${OBJS_DIR}

${OBJS_DIR}%.o: ${SRC_DIR}%.c
	@${CC} ${CFLAGS} -c $^ -o $@
	@echo "${BLUE} compiling ... ${RESET}"

clean:
	@rm -rf ${OBJS}
	@rm -rf ${OBJS_DIR}

fclean: clean
	@rm -rf ${NAME}

re: fclean ${NAME}

.PHONY: clean re fclean
