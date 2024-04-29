/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:31:28 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/29 22:04:58 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_even(t_philo *philo)
{
	size_t	time_eat;
	size_t	time;

	pthread_mutex_lock(philo->left_fork);
	if (one_die(philo))
		return (-1);
	time = get_time() - philo->data->start_time;
	mtx_printf("has taken a fork", time, philo, LEFT_FORK);
	pthread_mutex_lock(philo->rigth_fork);
	pthread_mutex_lock(philo->kill);
	philo->reaper->time_die = get_time();
	pthread_mutex_unlock(philo->kill);
	if (one_die(philo))
		return (-1);
	time = get_time() - philo->data->start_time;
	mtx_printf("has taken a fork", time, philo, RIGHT_FORK);
	mtx_printf("is eating", time, philo, EAT);
	time_eat = get_time();
	while (get_time() - time_eat <= philo->data->args.time_eat)
	{
		pthread_mutex_lock(philo->kill);
		philo->reaper->time_die = get_time();
		pthread_mutex_unlock(philo->kill);
		if (one_die(philo))
			return (-1);
	}
	pthread_mutex_lock(philo->kill);
	philo->reaper->time_die = get_time();
	pthread_mutex_unlock(philo->kill);
	pthread_mutex_unlock(philo->rigth_fork);
	pthread_mutex_unlock(philo->left_fork);

	return (0);
}

int	philo_odd(t_philo *philo)
{
	size_t	time_eat;
	size_t	time;

	pthread_mutex_lock(philo->rigth_fork);
	if (one_die(philo))
		return (-1);
	time = get_time() - philo->data->start_time;
	mtx_printf("has taken a fork", time, philo, RIGHT_FORK);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->kill);
	philo->reaper->time_die = get_time();
	pthread_mutex_unlock(philo->kill);
	if (one_die(philo))
		return (-1);
	time = get_time() - philo->data->start_time;
	mtx_printf("has taken a fork", time, philo, LEFT_FORK);
	mtx_printf("is eating", time, philo, EAT);
	time_eat = get_time();
	while (get_time() - time_eat <= philo->data->args.time_eat)
	{
		pthread_mutex_lock(philo->kill);
		philo->reaper->time_die = get_time();
		pthread_mutex_unlock(philo->kill);
		if (one_die(philo))
			return (-1);
	}
	pthread_mutex_lock(philo->kill);
	philo->reaper->time_die = get_time();
	pthread_mutex_unlock(philo->kill);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->rigth_fork);
	return (0);
}
