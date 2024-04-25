/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:54:42 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/24 19:35:40 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void *arg)
{
	t_philo	*philo;
	int		interromp;

	interromp = 0;
	philo = arg;
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
	printf(YELLOW "%zu philo id %zu pick right fork\n" RESET,
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
	printf(GREEN "%zu philo id %zu pick left fork\n", 
		get_time() - philo->data->start_time, philo->philo_id);
	printf(BLUE "%zu philo id %zu is eating\n",
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
	printf(GREEN "%zu philo id %zu pick left fork\n", 
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
	printf(YELLOW "%zu philo id %zu pick right fork\n" RESET, 
		get_time() - philo->data->start_time, philo->philo_id);
	printf(BLUE "%zu philo id %zu is eating\n", 
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

int	philo_spleeping(t_philo *philo)
{
	size_t	spleep_count;

	spleep_count = get_time();
	while (get_time() - spleep_count < philo->data->args.time_sleep)
	{
		if (!philo_is_alive(philo))
			return (-1);
		if (philo_interomp(philo))
			return (-2);
	}
	return (0);
}

int	philo_eating(t_philo *philo)
{
	size_t	eat_count;

	eat_count = get_time();
	while (get_time() - eat_count < philo->data->args.time_eat)
	{
		if (philo_interomp(philo))
			return (-2);
	}
	philo->die_count = get_time();
	return (0);
}

void	*philo_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.global);
	philo->data->interromp = true;
	pthread_mutex_unlock(&philo->data->mutex.global);

	pthread_mutex_lock(&philo->data->mutex.printf);
	printf(RED "%zu philo id %zu die\n" RESET,
		get_time() - philo->data->start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->data->mutex.printf);
	return (NULL);
}

bool	philo_interomp(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.global);
	if (philo->data->interromp)
	{

		pthread_mutex_unlock(&philo->data->mutex.global);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->mutex.global);
	return (false);
}

void	philo_last(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.global);
	philo->data->last_is_ready = true;
	pthread_mutex_unlock(&philo->data->mutex.global);
}
