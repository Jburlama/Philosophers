/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:59:44 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/12 16:35:27 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <signal.h>
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

enum e_action
{
	PICK,
	DROP
};

# define MAX_PHILO 200

typedef struct s_data t_data;
typedef struct s_philo t_philo;

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
	int		philo_id;
	size_t		start_time;
	size_t		die_time;
	pthread_t	reaper_tid;
	bool 		is_dead;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	size_t 		start_time;
	t_args 		args;
	t_philo		philo;
	char		philo_sem_name[200][9];
	sem_t		*philo_sem[200];
	sem_t  		*forks;
	sem_t  		*ready;
	sem_t		*printf;
	sem_t		*kill;
	pid_t 	 	*philo_pid;
}	t_data;


void	monitoring(t_data *data);
void	*grim_reaper(void *arg);

// philo.c
void	philo_runtime(t_philo *philo);
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_forks(t_philo *philo, int action);
bool	check_philo_is_dead(t_philo *philo);

// data_init.c
void	reaper_init(t_philo *philo);
void	philo_init(t_data *data);
void	data_init(int argc, char *argv[], t_data *data);
void	data_fill(t_data *data);
void	data_sem_unlink(t_data *data);
void	data_sem_open(t_data *data);

// check_arguments.c
void	check_valid_args(int argc, char *argv[]);
void	erro_msg(char *err_msg);
void	panic(char	*err_msg, t_data *data);

// utils.c
size_t	get_time(void);
size_t	atos_t(char	*str);
bool	is_digit(char c);
int		ft_strlen(char *str);

// printf.c
void	sem_printf(char *str, t_philo *philo, size_t time, int collor);
void	printf_yellow(char *str, t_philo *philo, size_t time);
void	printf_blue(char *str, t_philo *philo, size_t time);
void	printf_red(char *str, t_philo *philo, size_t time);
void	printf_green(char *str, t_philo *philo, size_t time);
void	printf_light_grey(char *str, t_philo *philo, size_t time);
void	printf_dark_gray(char *str, t_philo *philo, size_t time);

// parce_sem.c
void	parse_sem(t_data *data);
void	parse(char *sem_array, char *name, int id);
char	*itos(int id);
int		int_len(int id);

#endif
