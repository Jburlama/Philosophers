/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:46:15 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/25 17:48:51 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	philo->interromp = true;
	pthread_mutex_unlock(&philo->data->mutex.global);
	pthread_mutex_lock(&philo->data->mutex.printf);
	printf(RED "%zu %zu died\n" RESET,
		get_time() - philo->data->start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->data->mutex.printf);
	pthread_mutex_lock(&philo->data->mutex.global);
	philo->data->stop = true;
	pthread_mutex_unlock(&philo->data->mutex.global);
	return (NULL);
}

bool	philo_interomp(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.global);
	if (philo->data->philo->interromp)
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
