/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:54:42 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/30 20:39:05 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void *arg)
{
	t_philo *philo;

	philo = arg;
	if (philo->is_last)
		philo_last(philo);
	wait_for_monitoring(philo->data);
	if (philo->philo_id % 2 == 0)
		usleep(1e4);
	while (42)
	{
		if (philo->philo_id % 2 != 0)
		{
			if (philo_odd(philo) == -1)
				return (NULL);
		}
		else
		{
			if (philo_even(philo) == -1)
				return (NULL);
		}
		if (philo_sleep(philo) == -1)
			return (NULL);
	}
	return (NULL);
}

int	philo_sleep(t_philo *philo)
{
	size_t	time_sleep;
	size_t	time;
	
	if (one_die(philo))
		return (-1);
	time = get_time() - philo->data->start_time;
	mtx_printf("is sleeping", time, philo, SLEEP);
	time_sleep = get_time();
	while (get_time() - time_sleep < philo->data->args.time_sleep)
	{
		if (one_die(philo))
			return (-1);
	}
	if (one_die(philo))
		return (-1);
	return (0);
}

bool	one_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->global);
	if (philo->data->one_die)
	{
		pthread_mutex_unlock(&philo->mutex->global);
		return (true);
	}
	pthread_mutex_unlock(&philo->mutex->global);
	return (false);
}

void	philo_last(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.global);
	philo->data->last_is_ready = true;
	pthread_mutex_unlock(&philo->data->mutex.global);
}
