/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:40:08 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/25 19:31:52 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_init(t_data *data)
{
	size_t	i;

	data->stop = false;
	data->monitoring_is_ready = false;
	data->last_is_ready = false;
	pthread_mutex_init(&data->mutex.printf, NULL);
	pthread_mutex_init(&data->mutex.global, NULL);
	i = 0;
	data->mutex.fork = malloc(sizeof(*data->mutex.fork) * data->args.philo_num);
	if (data->mutex.fork == NULL)
		return ;
	while (i < data->args.philo_num)
	{
		pthread_mutex_init(&data->mutex.fork[i], NULL);
		i++;
	}
}

void	philos_init(t_data *data)
{
	size_t	i;

	data->philo = malloc(sizeof(*data->philo) * data->args.philo_num);
	if (data->philo == NULL)
		return ;
	i = -1;
	while (++i < data->args.philo_num)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].data = data;
		data->philo[i].is_last = false;
		data->philo[i].interromp = false;
		if (i == data->args.philo_num - 1)
		{
			data->philo[i].is_last = true;
			data->philo[i].left_fork = &data->mutex.fork[i];
			data->philo[i].rigth_fork = &data->mutex.fork[0];
		}
		else
		{
			data->philo[i].left_fork = &data->mutex.fork[i];
			data->philo[i].rigth_fork = &data->mutex.fork[i + 1];
		}
		pthread_create(&data->philo[i].tid, NULL, philo, &data->philo[i]);
	}
}

int	data_init(int argc, char *argv[], t_data *data)
{
	data->args.philo_num = atos_t(argv[1]);
	if (data->args.philo_num > MAX_PHILO || data->args.philo_num == 0)
		return (-1);
	data->args.time_die = atos_t(argv[2]);
	data->args.time_eat = atos_t(argv[3]);
	data->args.time_sleep = atos_t(argv[4]);
	if (argc == 6)
		data->args.times_must_eat = atos_t(argv[5]);
	return (0);
}

size_t	atos_t(char	*str)
{
	size_t	result;
	int		i;

	result = 0;
	i = -1;
	if (str[0] == '+')
		i++;
	while (str[++i])
	{
		result = (result * 10) + (str[i] - '0');
	}
	return (result);
}
