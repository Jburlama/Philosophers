/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:15:54 by jburlama          #+#    #+#             */
/*   Updated: 2024/04/18 21:07:10 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	memset(&data, 0, sizeof(data));
	if (!check_valid_args(argc, argv))
		return (panic("invalid arguments\n"));
	if (set_data(argc, argv, &data) == -1)
		return (panic("philo number between 1-200\n"));
	if (start_diner(&data) == -1)
		return (panic("Error starting dinner!\n"));
	return (0);
}

int		start_diner(t_data *data)
{
	size_t i;

	data->philo = malloc(sizeof(*data->philo) * data->args.philo_num);
	if (data->philo == NULL)
		return (-1);
	data->mutex.fork = malloc(sizeof(*data->mutex.fork) * data->args.philo_num);
	if (data->mutex.fork == NULL)
	{
		free(data->philo);
		return (-1);
	}
	memset(data->philo, 0, sizeof(*data->philo));
	memset(data->mutex.fork, 0, sizeof(*data->mutex.fork));
	pthread_mutex_init(&data->mutex.printf, NULL);
	i = 0;
	while (i < data->args.philo_num)
	{
		pthread_mutex_init(&data->mutex.fork[i], NULL);
 		i++;
	}
	i = 0;
	while (i < data->args.philo_num)
	{
		data->philo[i].mutex = &data->mutex;
		data->philo[i].is_alive = true;
		data->philo[i].is_full = true;
		data->philo[i].philo_id = i + 1;
		if (pthread_create(&data->philo[i].philo_pth, NULL, philo, &data->philo[i]) != 0)
			return (clean_thread(data->philo));
		i++;
	}
	while (42)
	{
		i = 0;
		while (i < data->args.philo_num)
		{
			if (data->philo->philo_id % 2 == 0)
			{
				data->philo[i].is_full = -(data->philo->is_full);
			}
			usleep(200);
			i++;
		}
	}
	join_threads(data);
	free(data->philo);
	return (0);
}

void	*philo(void *data)
{
	t_philo	*philo = data;
	
	while (philo->is_alive)
	{
		if (philo->is_full == false)
		{
			pthread_mutex_lock(&philo->mutex->fork[philo->philo_id]);
			pthread_mutex_lock(&philo->mutex->fork[philo->philo_id + 1]);

			pthread_mutex_lock(&philo->mutex->printf);
			printf("philo %zu is eating\n", philo->philo_id);
			pthread_mutex_unlock(&philo->mutex->printf);

			pthread_mutex_unlock(&philo->mutex->fork[philo->philo_id + 1]);
			pthread_mutex_unlock(&philo->mutex->fork[philo->philo_id]);
			philo->is_full = true;
		}
	}

	return (NULL);
}

void	join_threads(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->args.philo_num)
	{
		pthread_join(data->philo[i].philo_pth, NULL);
		i++;
	}
}

int	clean_thread(t_philo *philo)
{
	free(philo);
	return (-1);
}
