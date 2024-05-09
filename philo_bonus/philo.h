/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:59:44 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/09 17:09:35 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <semaphore.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_PHILO 200

typedef struct s_data t_data;

typedef struct s_args
{
	size_t	num_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		times_must_eat;
} t_args;

typedef struct s_philo
{
	size_t	philo_id;
	t_data	*data;
} t_philo;

typedef struct s_data
{
	t_args	args;
	t_philo	*philo;
	sem_t	*sem;
}	t_data;


void	philo_init(t_data *data);
void	philo_runtime(t_philo *philo);

// data_init.c
void	data_init(int argc, char *argv[], t_data *data);
size_t	atos_t(char	*str);

// check_arguments.c
void	check_valid_args(int argc, char *argv[]);
bool	is_digit(char c);
void	panic(char *err_msg);
int		ft_strlen(char *str);

#endif
