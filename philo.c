/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:54:42 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/25 17:47:11 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void *arg)
{
	t_philo	*philo;
	int		interromp;

	philo = arg;
	interromp = 0;
	if (philo->is_last)
		philo_last(philo);
	wait_for_monitoring(philo->data);
	philo->die_count = get_time();
	while(philo_is_alive(philo))
	{
		if (philo->philo_id % 2 == 0)
		{
			interromp = philo_spleeping(philo);
			if (interromp == -1)
				return (philo_die(philo));
			else if (interromp == -2)
				return (NULL);
			interromp = philo_even(philo);
			if (interromp == -1)
				return (philo_die(philo));
			else if (interromp == -2)
				return (NULL);
		}
		else
		{
			interromp = philo_odd(philo);
			if (interromp == -1)
				return (philo_die(philo));
			else if (interromp == -2)
				return (NULL);
			interromp = philo_spleeping(philo);
			if (interromp == -1)
				return (philo_die(philo));
			else if (interromp == -2)
				return (NULL);
		}
	}
	return (philo_die(philo));
}

int	philo_even(t_philo *philo)
{
	pthread_mutex_lock(philo->rigth_fork);
	if (philo_interomp(philo))
	{
		pthread_mutex_unlock(philo->rigth_fork);
		return (-2);
	}
	if (!philo_is_alive(philo))
	{
		pthread_mutex_unlock(philo->rigth_fork);
		return (-1);
	}
	pthread_mutex_lock(&philo->data->mutex.printf);
	printf(LIGHT_GRAY "%zu %zu has taken a fork\n" RESET,
		get_time() - philo->data->start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->data->mutex.printf);
	pthread_mutex_lock(philo->left_fork);
	if (philo_interomp(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->rigth_fork);
		return (-2);
	}
	if (!philo_is_alive(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->rigth_fork);
		return (-1);
	}
	pthread_mutex_lock(&philo->data->mutex.printf);
	printf(DARK_GRAY "%zu %zu has taken a fork\n", 
		get_time() - philo->data->start_time, philo->philo_id);
	printf(GREEN "%zu %zu is eating\n",
		get_time() - philo->data->start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->data->mutex.printf);
	if (philo_eating(philo) == -2)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->rigth_fork);
		return (-2);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->rigth_fork);
	return (0);
}

int	philo_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (philo_interomp(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (-2);
	}
	if (!philo_is_alive(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (-1);
	}
	pthread_mutex_lock(&philo->data->mutex.printf);
	printf(LIGHT_GRAY "%zu %zu has taken a fork\n", 
		get_time() - philo->data->start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->data->mutex.printf);
	pthread_mutex_lock(philo->rigth_fork);
	if (philo_interomp(philo))
	{
		pthread_mutex_unlock(philo->rigth_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (-2);
	}
	if (!philo_is_alive(philo))
	{
		pthread_mutex_unlock(philo->rigth_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (-1);
	}
	pthread_mutex_lock(&philo->data->mutex.printf);
	printf(DARK_GRAY "%zu %zu has taken a fork\n" RESET, 
		get_time() - philo->data->start_time, philo->philo_id);
	printf(GREEN "%zu %zu is eating\n", 
		get_time() - philo->data->start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->data->mutex.printf);
	if (philo_eating(philo) == -2)
	{
		pthread_mutex_unlock(philo->rigth_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (-2);
	}
	pthread_mutex_unlock(philo->rigth_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

bool philo_is_alive(t_philo *philo)
{
	if (get_time() - philo->die_count >= philo->data->args.time_die)
		return (false);
	return (true);
}
