/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:59:44 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/09 15:47:13 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define MAX_PHILO 200

typedef struct s_args
{
	size_t	num_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	times_must_eat;
} t_args;

typedef struct s_data
{
	t_args	args;
}	t_data;

void	data_init(int argc, char *argv[], t_data *data);
size_t	atos_t(char	*str);

// check_arguments.c
void	check_valid_args(int argc, char *argv[]);
bool	is_digit(char c);
void	panic(char *err_msg);
int		ft_strlen(char *str);

#endif
