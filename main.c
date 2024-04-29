/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:28:04 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/29 21:53:39 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	static t_data	data;

	if (!check_valid_args(argc, argv))
		return (panic("invalid arguments\n"));
	if (data_init(argc, argv, &data) == -1)
		return (panic("philo number between 1-200\n"));
	mutex_init(&data);
	philos_init(&data);
	monitoring(&data);
	join_thread(&data, PHILO);
	destroy_mutex(&data);
	free(data.mutex.fork);
	free(data.philo);
	free(data.reaper);
	return (0);
}

void	monitoring(t_data *data)
{
	wait_last_thread(data);
	pthread_mutex_lock(&data->mutex.global);
	data->start_time = get_time();
	pthread_mutex_unlock(&data->mutex.global);
	join_thread(data, RIPPER);
}

void	*grim_reaper(void *arg)
{
	t_reaper *reaper;
	size_t   time;

	reaper = arg;
	wait_for_monitoring(reaper->data);
	pthread_mutex_lock(&reaper->data->mutex.kill[reaper->philo->philo_id - 1]);
	reaper->time_die = get_time();
	pthread_mutex_unlock(&reaper->data->mutex.kill[reaper->philo->philo_id - 1]);
	while (42)
	{
		pthread_mutex_lock(&reaper->data->mutex.kill[reaper->philo->philo_id - 1]);
		if (get_time() - reaper->time_die >= reaper->data->args.time_die)
		{
			time = get_time() - reaper->data->start_time;
			pthread_mutex_unlock(&reaper->data->mutex.kill[reaper->philo->philo_id - 1]);
			break ;
		}
		pthread_mutex_unlock(&reaper->data->mutex.kill[reaper->philo->philo_id - 1]);
		pthread_mutex_lock(&reaper->mutex->global);
		if (reaper->data->one_die)
		{
			pthread_mutex_unlock(&reaper->mutex->global);
			return (NULL);
		}
		pthread_mutex_unlock(&reaper->mutex->global);
	}
	pthread_mutex_lock(&reaper->mutex->global);
	reaper->data->one_die = true;
	pthread_mutex_unlock(&reaper->mutex->global);
	mtx_printf("die", time, reaper->philo, DIE);
	return (NULL);
}

void	destroy_mutex(t_data *data)
{
	size_t	i;

	pthread_mutex_destroy(&data->mutex.global);
	pthread_mutex_destroy(&data->mutex.printf);
	i = 0;
	while (i < data->args.philo_num)
	{
		pthread_mutex_destroy(&data->mutex.fork[i]);
		pthread_mutex_destroy(&data->mutex.kill[i]);
		i++;
	}
}
