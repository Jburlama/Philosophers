/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:59:44 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/10 17:57:58 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <semaphore.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define RED 		"\x1b[31m"
# define YELLOW 	"\x1b[33m"
# define GREEN 		"\x1b[32m"
# define BLUE 		"\x1b[34m"
# define LIGHT_GRAY "\x1b[37m"
# define DARK_GRAY  "\x1b[90m"
# define MAGENTA	"\033[1;35m"
# define RESET 		"\x1b[0m"

enum e_collor
{
	LEFT_FORK,
	RIGHT_FORK,
	EAT,
	DIE,
	THINK,
	SLEEP,
	FULL
};

# define MAX_PHILO 200

typedef struct s_data t_data;

typedef struct s_args
{
	size_t	num_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		times_must_eat;
}	t_args;

typedef struct s_philo
{
	size_t	philo_id;
	size_t	start_time;
	t_data	*data;
}	t_philo;

typedef struct s_data
{
	size_t	start_time;
	t_args	args;
	t_philo	*philo;
	sem_t	*forks;
	sem_t	*ready;
	pid_t		*pid;
}	t_data;


void	philo_init(t_data *data);
void	monitoring(t_data *data);
size_t	get_time(void);

// philo.c
void	philo_runtime(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);

// data_init.c
void	data_init(int argc, char *argv[], t_data *data);
void	data_fill(t_data *data);
size_t	atos_t(char	*str);

// check_arguments.c
void	check_valid_args(int argc, char *argv[]);
bool	is_digit(char c);
void	erro_msg(char *err_msg);
void	panic(char	*err_msg, t_data *data);
int		ft_strlen(char *str);

#endif
