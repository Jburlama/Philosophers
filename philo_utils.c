/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:31:28 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/01 21:28:57 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_even(t_philo *philo)
{
	philo_update_time_die(philo);
	pthread_mutex_lock(philo->left_fork);
	if (one_die(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (-1);
	}
	mtx_printf("has taken a fork", philo, LEFT_FORK);
	pthread_mutex_lock(philo->rigth_fork);
	if (one_die(philo))
	{
		philo_drop_forks(philo, RIGHT_FORK);
		return (-1);
	}
	mtx_printf("has taken a fork", philo, RIGHT_FORK);
	mtx_printf("is eating", philo, EAT);
	if (philo_eating(philo) == -1)
	{
		philo_drop_forks(philo, RIGHT_FORK);
		return (-1);
	}
	philo_update_time_die(philo);
	philo_drop_forks(philo, RIGHT_FORK);
	return (0);
}

int	philo_odd(t_philo *philo)
{
	philo_update_time_die(philo);
	pthread_mutex_lock(philo->rigth_fork);
	if (one_die(philo))
	{
		pthread_mutex_unlock(philo->rigth_fork);
		return (-1);
	}
	philo_update_time_die(philo);
	mtx_printf("has taken a fork", philo, RIGHT_FORK);
	pthread_mutex_lock(philo->left_fork);
	if (one_die(philo))
	{
		philo_drop_forks(philo, LEFT_FORK);
		return (-1);
	}
	mtx_printf("has taken a fork", philo, LEFT_FORK);
	mtx_printf("is eating", philo, EAT);
	if (philo_eating(philo) == -1)
	{
		philo_drop_forks(philo, LEFT_FORK);
		return (-1);
	}
	philo_update_time_die(philo);
	philo_drop_forks(philo, LEFT_FORK);
	return (0);
}

int	philo_eating(t_philo *philo)
{
	size_t	time_eat;

	time_eat = get_time();
	while (get_time() - time_eat < philo->data->args.time_eat)
	{
		if (one_die(philo))
			return (-1);
	}
	return (0);
}

void	philo_update_time_die(t_philo *philo)
{
	pthread_mutex_lock(philo->scythe);
	philo->reaper->time_die = get_time();
	pthread_mutex_unlock(philo->scythe);
}

void	philo_drop_forks(t_philo *philo, int first)
{
	if (first == RIGHT_FORK)
	{
		pthread_mutex_unlock(philo->rigth_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->rigth_fork);
	}
}
