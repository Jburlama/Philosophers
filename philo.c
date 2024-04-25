/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:54:42 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/25 19:45:08 by Jburlama         ###   ########.fr       */
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
	while (42)
	{
		philo_eat(philo);
		// sleep(2);
	}
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		philo_eat_even(philo);
	}
	else
	{
		usleep(2000);
		philo_eat_odd(philo);
	}
}

bool philo_is_alive(t_philo *philo)
{
	if (get_time() - philo->die_count >= philo->data->args.time_die)
		return (false);
	return (true);
}

void	philo_last(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.global);
	philo->data->last_is_ready = true;
	pthread_mutex_unlock(&philo->data->mutex.global);
}
