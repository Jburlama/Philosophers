/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:54:42 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/29 20:20:57 by Jburlama         ###   ########.fr       */
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
			philo_odd(philo);
		else
			philo_even(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	philo_sleep(t_philo *philo)
{
	size_t	time_sleep;
	size_t	time;
	
	time = get_time() - philo->data->start_time;
	mtx_printf("is sleeping", time, philo, SLEEP);
	time_sleep = get_time();
	while (get_time() - time_sleep <= philo->data->args.time_sleep)
		;
}

void	philo_last(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.global);
	philo->data->last_is_ready = true;
	pthread_mutex_unlock(&philo->data->mutex.global);
}
