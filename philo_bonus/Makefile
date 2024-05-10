# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 18:56:44 by Jburlama          #+#    #+#              #
#    Updated: 2024/05/10 18:07:35 by Jburlama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLUE = \033[34m
GREEN = \033[32m
RESET = \033[0m

NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
CFILES = main.c check_arguments.c data_init.c philo.c
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
