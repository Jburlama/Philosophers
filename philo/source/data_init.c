/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:38:39 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/09 15:48:49 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	mutex_init(t_data *data)
{
	size_t	i;

	pthread_mutex_init(&data->mutex.printf, NULL);
	pthread_mutex_init(&data->mutex.global, NULL);
	data->mutex.fork = malloc(sizeof(*data->mutex.fork) * data->args.philo_num);
	if (data->mutex.fork == NULL)
		return ;
	memset(data->mutex.fork, 0, sizeof(*data->mutex.fork));
	data->mutex.scythe = malloc(sizeof(*data->mutex.scythe)
			* data->args.philo_num);
	if (data->mutex.scythe == NULL)
		return ;
	i = 0;
	while (i < data->args.philo_num)
	{
		pthread_mutex_init(&data->mutex.fork[i], NULL);
		pthread_mutex_init(&data->mutex.scythe[i], NULL);
		i++;
	}
}

void	reaper_init(t_data *data)
{
	size_t	i;

	data->reaper = malloc(sizeof(*data->reaper) * data->args.philo_num);
	if (data->reaper == NULL)
		return ;
	i = -1;
	while (++i < data->args.philo_num)
	{
		data->reaper[i].data = data;
		data->reaper[i].mutex = &data->mutex;
		data->reaper[i].philo = &data->philo[i];
		data->reaper[i].scythe = &data->mutex.scythe[i];
		pthread_create(&data->reaper[i].tid, NULL,
			grim_reaper, &data->reaper[i]);
	}
}

void	philos_init(t_data *data)
{
	size_t	i;

	data->philo = malloc(sizeof(*data->philo) * data->args.philo_num);
	if (data->philo == NULL)
		return ;
	memset(data->philo, 0, sizeof(*data->philo));
	reaper_init(data);
	i = 0;
	while (i < data->args.philo_num)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].data = data;
		data->philo[i].scythe = &data->mutex.scythe[i];
		data->philo[i].mutex = &data->mutex;
		data->philo[i].reaper = &data->reaper[i];
		data->philo[i].left_fork = &data->mutex.fork[i];
		if (i == data->args.philo_num - 1)
		{
			data->philo[i].is_last = true;
			data->philo[i].rigth_fork = &data->mutex.fork[0];
		}
		else
			data->philo[i].rigth_fork = &data->mutex.fork[i + 1];
		pthread_create(&data->philo[i].tid, NULL, philo, &data->philo[i]);
		i++;
	}
}

int	data_init(int argc, char *argv[], t_data *data)
{
	data->args.philo_num = atos_t(argv[1]);
	if (data->args.philo_num > MAX_PHILO || data->args.philo_num == 0)
		return (-1);
	data->args.time_die = atos_t(argv[2]);
	if (data->args.time_die < 60)
		return (-1);
	data->args.time_eat = atos_t(argv[3]);
	if (data->args.time_eat < 60)
		return (-1);
	data->args.time_sleep = atos_t(argv[4]);
	if (data->args.time_sleep < 60)
		return (-1);
	if (argc == 6)
		data->args.times_must_eat = atos_t(argv[5]);
	else
		data->args.times_must_eat = -1;
	data->monitoring_is_ready = false;
	data->last_is_ready = false;
	data->one_die = false;
	data->philos_full = 0;
	return (0);
}

// 4294967295
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
