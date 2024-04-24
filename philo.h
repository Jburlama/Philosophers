/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:17:10 by jburlama          #+#    #+#             */
/*   Updated: 2024/04/24 18:55:56 by Jburlama         ###   ########.fr       */
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

#define RED     "\x1b[31m"
#define YELLOW  "\x1b[33m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"

# define MAX_PHILO 200

typedef struct s_data t_data;

typedef struct s_args
{
	size_t	philo_num;
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;
	size_t	times_must_eat;
}				t_args;

typedef struct	s_philo
{
	pthread_t		tid;
	size_t			philo_id;
	size_t			die_count;
	t_data			*data;
	bool			is_last;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*rigth_fork;
}				t_philo;

typedef	struct s_mutex
{
	pthread_mutex_t printf;
	pthread_mutex_t global;
	pthread_mutex_t *fork;
} t_mutex;

typedef struct s_data
{
	t_args			args;
	t_philo			*philo;
	t_mutex			mutex;
	bool			monitoring_is_ready;
	bool			last_is_ready;
	size_t			start_time;
} t_data;

void	monitoring(t_data *data);

// philo.c
void	*philo(void *arg);
void	*philo_die(t_philo *philo);
bool	philo_is_alive(t_philo *philo);
int		philo_spleeping(t_philo *philo);
void	philo_eating(t_philo *philo);
int		philo_even(t_philo *philo);
int		philo_odd(t_philo *philo);
void	philo_last(t_philo *philo);

// utils.c
void	wait_for_monitoring(t_data *data);
void	wait_last_thread(t_data *data);
void	join_thread(t_data *data);
size_t	get_time(void);

// data_init.c
void	mutex_init(t_data *data);
void	philos_init(t_data *data);
int		data_init(int argc, char *argv[], t_data *data);
size_t	atos_t(char	*str);

// check_error.c
int		panic(char *err_msg);
bool	check_valid_args(int argc, char *argv[]);
bool	is_digit(char c);

#endif
