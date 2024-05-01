/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:50:41 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/01 17:50:48 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>

# define RED 		"\x1b[31m"
# define YELLOW 	"\x1b[33m"
# define GREEN 		"\x1b[32m"
# define BLUE 		"\x1b[34m"
# define LIGHT_GRAY "\x1b[37m"
# define DARK_GRAY  "\x1b[90m"
# define RESET 		"\x1b[0m"

enum e_collor
{
	LEFT_FORK,
	RIGHT_FORK,
	EAT,
	DIE,
	THINK,
	SLEEP
};

enum e_join
{
	PHILO,
	RIPPER,
	WAITER
};

# define MAX_PHILO 200

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_args
{
	size_t	philo_num;
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;
	size_t	times_must_eat;
}	t_args;

typedef struct s_mutex
{
	pthread_mutex_t	printf;
	pthread_mutex_t	global;
	pthread_mutex_t	*scythe;
	pthread_mutex_t	*fork;
}	t_mutex;

typedef struct s_reaper
{
	pthread_t		tid;
	size_t			time_die;
	t_data			*data;
	t_mutex			*mutex;
	t_philo			*philo;
	pthread_mutex_t	*scythe;
}	t_reaper;

typedef struct s_philo
{
	pthread_t		tid;
	size_t			philo_id;
	t_data			*data;
	t_mutex			*mutex;
	t_reaper		*reaper;
	bool			is_last;
	bool			is_death;
	pthread_mutex_t	*scythe;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*rigth_fork;
}	t_philo;

typedef struct s_data
{
	t_args			args;
	t_philo			*philo;
	t_reaper		*reaper;
	t_mutex			mutex;
	bool			monitoring_is_ready;
	bool			last_is_ready;
	bool			one_die;
	size_t			start_time;
}	t_data;

void	monitoring(t_data *data);
void	destroy_mutex(t_data *data);
void	*grim_reaper(void *arg);

// philo.c
void	*philo(void *arg);
int		philo_eat(t_philo *philo);
void	philo_last(t_philo *philo);
int		philo_sleep(t_philo *philo);
bool	one_die(t_philo *philo);

// philo_utils.c
int		philo_even(t_philo *philo);
int		philo_odd(t_philo *philo);
void	philo_update_time_die(t_philo *philo);
int		philo_eating(t_philo *philo);
void	philo_drop_forks(t_philo *philo, int first);

// printf.c
void	mtx_printf(char *str, t_philo *philo, int collor);
void	printf_light_gray(char *str, size_t time, t_philo *philo);
void	printf_dark_gray(char *str, size_t time, t_philo *philo);
void	printf_green(char *str, size_t time, t_philo *philo);
void	printf_red(char *str, size_t time, t_philo *philo);
void	printf_blue(char *str, size_t time, t_philo *philo);
void	printf_yellow(char *str, size_t time, t_philo *philo);

// utils.c
void	wait_for_monitoring(t_data *data);
void	wait_last_thread(t_data *data);
void	join_thread(t_data *data, int join);
size_t	get_time(void);

// data_init.c
void	mutex_init(t_data *data);
void	philos_init(t_data *data);
void	reaper_init(t_data *data);
int		data_init(int argc, char *argv[], t_data *data);
size_t	atos_t(char	*str);

// check_error.c
int		panic(char *err_msg);
bool	check_valid_args(int argc, char *argv[]);
bool	is_digit(char c);

#endif
