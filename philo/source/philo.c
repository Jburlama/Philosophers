/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:54:42 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/08 18:11:38 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo(void *arg)
{
	t_philo	*philo;

	philo = arg;
	pthread_mutex_lock(philo->scythe);
	philo->times_eaten = 0;
	pthread_mutex_unlock(philo->scythe);
	if (philo->is_last)
		philo_last(philo);
	wait_for_monitoring(philo->data);
	if (philo->philo_id % 2 == 0)
	{
		usleep(1e4);
		mtx_printf("is thinking", philo, THINK);
	}
	while (42)
	{
		if (philo_eat(philo) == -1)
			return (NULL);
		if (philo_sleep(philo) == -1)
			return (NULL);
		if (philo_think(philo) == -1)
			return (NULL);
	}
	return (NULL);
}

int	philo_eat(t_philo *philo)
{
	if (philo->philo_id == 1 && philo->is_last)
		return (philo_one(philo));
	if (philo->philo_id % 2 != 0)
	{
		if (philo_odd(philo) == -1)
			return (-1);
	}
	else
	{
		if (philo_even(philo) == -1)
			return (-1);
	}
	pthread_mutex_lock(philo->scythe);
	philo->times_eaten++;
	if (philo->times_eaten == philo->data->args.times_must_eat)
	{
		mtx_printf("is full", philo, FULL);
		pthread_mutex_lock(&philo->mutex->global);
		philo->data->philos_full++;
		pthread_mutex_unlock(&philo->mutex->global);
		pthread_mutex_unlock(philo->scythe);
		return (-1);
	}
	pthread_mutex_unlock(philo->scythe);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	size_t	time_sleep;

	if (one_die(philo))
		return (-1);
	mtx_printf("is sleeping", philo, SLEEP);
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
