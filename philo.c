/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:54:42 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/25 20:41:22 by Jburlama         ###   ########.fr       */
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
		if (philo_eat(philo) == -1)
			break ;
	}
	return (NULL);
}

int	philo_eat(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		usleep(100);
		philo_eat_even(philo);
	}
	else
	{
		philo_eat_odd(philo);
		usleep(100);
	}
	return (0);
}

void	philo_last(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.global);
	philo->data->last_is_ready = true;
	pthread_mutex_unlock(&philo->data->mutex.global);
}
