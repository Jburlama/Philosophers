/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:15:54 by jburlama          #+#    #+#             */
/*   Updated: 2024/04/20 19:34:21 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	static t_data	data;

	if (!check_valid_args(argc, argv))
		return (panic("invalid arguments\n"));
	if (set_data(argc, argv, &data) == -1)
		return (panic("philo number between 1-200\n"));
	start_philos(&data);
	usleep(2e6);
	monitoring(&data);
	join_threads(&data);
	return (0);
}

int	start_philos(t_data *data)
{
	size_t i;

	pthread_mutex_init(&data->printf, NULL);
	pthread_mutex_init(&data->mtx_philo, NULL);

	data->fork = malloc(sizeof(*data->fork) * data->args.philo_num);
	memset(data->fork, 0, sizeof(*data->fork) * data->args.philo_num);
	
	data->philo = malloc(sizeof(*data->philo) * data->args.philo_num);
	memset(data->philo, 0, sizeof(*data->philo) * data->args.philo_num);

	i = 0;
	while (i < data->args.philo_num)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		data->philo[i].philo_id = i + 1;
		// data->philo[i].is_alive = true;

		if (data->philo[i].philo_id == data->args.philo_num)
		{
			data->philo[i].left_fork = &data->fork[i];
			data->philo[i].rigth_fork = &data->fork[0];
		}
		else
		{
			data->philo[i].left_fork = &data->fork[i];
			data->philo[i].rigth_fork = &data->fork[i + 1];
		}

		data->philo[i].data = data;

		pthread_create(&data->philo[i].philo_pth, NULL, philo, &data->philo[i]);
		i++;
	}
	return (0);
}

int	monitoring(t_data *data)
{
	// size_t	i;

	// i = 0;
	pthread_mutex_lock(&data->mtx_philo);
	data->ready = true;
	pthread_mutex_unlock(&data->mtx_philo);
	// data->start = get_time();
	// while (i < data->args.philo_num)
	// {
	// 	pthread_mutex_lock(&data->mtx_philo);
	// 	data->philo[i].is_alive = false;
	// 	pthread_mutex_unlock(&data->mtx_philo);
	// 	usleep(2e6);
	// 	i++;
	// }
	return (0);
}

void	*philo(void *data)
{
	t_philo *philo = data;

	wait_to_get_ready(philo);

	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->rigth_fork);

		pthread_mutex_lock(&philo->data->printf);
		printf("philo %zu picked right fork\n", philo->philo_id);
		pthread_mutex_unlock(&philo->data->printf);

		pthread_mutex_lock(philo->left_fork);

		pthread_mutex_lock(&philo->data->printf);
		printf("philo %zu picked left fork\n", philo->philo_id);
		pthread_mutex_unlock(&philo->data->printf);

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->rigth_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);

		pthread_mutex_lock(&philo->data->printf);
		printf("philo %zu picked left fork\n", philo->philo_id);
		pthread_mutex_unlock(&philo->data->printf);

		pthread_mutex_lock(philo->rigth_fork);

		pthread_mutex_lock(&philo->data->printf);
		printf("philo %zu picked right fork\n", philo->philo_id);
		pthread_mutex_unlock(&philo->data->printf);

		pthread_mutex_unlock(philo->rigth_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	return (NULL);
}
