/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:17:10 by jburlama          #+#    #+#             */
/*   Updated: 2024/04/13 20:24:47 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <limits.h>

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
	t_args	args;
}				t_data;

// data_init.c
int		set_data(int argc, char *argv[], t_data *data);
long	atoul(char	*str);

// check_error.c
int		panic(char *err_msg);
bool	check_valid_args(int argc, char *argv[]);
bool	is_digit(char c);

#endif
