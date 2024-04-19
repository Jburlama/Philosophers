/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:17:10 by jburlama          #+#    #+#             */
/*   Updated: 2024/04/19 17:05:48 by Jburlama         ###   ########.fr       */
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

# define MAX_PHILO 200

typedef struct s_args
{
	size_t	philo_num;
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;
	size_t	times_must_eat;
}				t_args;

typedef struct	s_mutex
{
	pthread_mutex_t	printf;
	pthread_mutex_t	*fork;
}				t_mutex;

typedef struct	s_philo
{
	size_t			philo_id;
	pthread_t		philo_pth;
	t_mutex			*mutex;
	bool			is_full;
	bool			is_alive;
}				t_philo;

typedef struct s_data
{
	t_args			args;
	t_philo			*philo;
	t_mutex			mutex;
	struct timeval	tv;
}				t_data;

int		start_diner(t_data *data);
int		monitoring(t_data *data);
void	*philo(void *data);
void	join_threads(t_data *data);
int		clean_thread(t_philo *philo);

// data_init.c
int		set_data(int argc, char *argv[], t_data *data);
size_t	atos_t(char	*str);

// check_error.c
int		panic(char *err_msg);
bool	check_valid_args(int argc, char *argv[]);
bool	is_digit(char c);

#endif
