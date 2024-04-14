/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:17:10 by jburlama          #+#    #+#             */
/*   Updated: 2024/04/14 16:17:56 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>

# define MAX_PHILO 200

typedef struct s_args
{
	long	philo_num;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	long	times_must_eat;
}				t_args;

typedef struct s_data
{
	t_args			args;
	int				philo_id;
	pthread_t		*philo;
	pthread_mutex_t	mutex_printf;
}				t_data;

int		start_diner(t_data *data);
void	*philo(void *data);
void	join_threads(t_data *data);

// data_init.c
int		set_data(int argc, char *argv[], t_data *data);
long	atoul(char	*str);

// check_error.c
int		panic(char *err_msg);
bool	check_valid_args(int argc, char *argv[]);
bool	is_digit(char c);

#endif
