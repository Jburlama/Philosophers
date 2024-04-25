/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:15:10 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/25 16:32:54 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_monitoring(t_data *data)
{
	while (42)
	{
		pthread_mutex_lock(&data->mutex.global);
		if (data->monitoring_is_ready == true)
		{
			pthread_mutex_unlock(&data->mutex.global);
			break ;
		}
		pthread_mutex_unlock(&data->mutex.global);
	}
}

void	wait_last_thread(t_data *data)
{
	while (42)
	{
		pthread_mutex_lock(&data->mutex.global);
		if (data->last_is_ready)
		{
			data->monitoring_is_ready = true;
			data->start_time = get_time();
			pthread_mutex_unlock(&data->mutex.global);
			break ;
		}
		pthread_mutex_unlock(&data->mutex.global);
	}
}

void	join_thread(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->args.philo_num)
	{
		pthread_join(data->philo[i].tid, NULL);
		i++;
	}
}

size_t	get_time(void)
{
	size_t	time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1e6) + tv.tv_usec;
	time = time / 1e3;
	return (time);
}