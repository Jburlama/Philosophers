/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:16:38 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/08 18:42:08 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*grim_reaper(void *arg)
{
	t_reaper	*reaper;

	reaper = arg;
	wait_for_monitoring(reaper->data);
	philo_update_time_die(reaper->philo);
	while (42)
	{
		pthread_mutex_lock(reaper->scythe);
		if (get_time() - reaper->time_die > reaper->data->args.time_die)
		{
			pthread_mutex_lock(&reaper->mutex->global);
			reaper->data->time_death = get_time() - reaper->data->start_time;
			reaper->data->one_die = true;
			reaper->data->death_pid = reaper->philo->philo_id;
			pthread_mutex_unlock(&reaper->mutex->global);
			pthread_mutex_unlock(reaper->scythe);
			return (NULL);
		}
		pthread_mutex_unlock(reaper->scythe);
		if (one_die(reaper->philo) || is_full(reaper->philo))
			return (NULL);
	}
	return (NULL);
}

bool	is_full(t_philo *philo)
{
	pthread_mutex_lock(philo->scythe);
	if (philo->times_eaten == philo->data->args.times_must_eat)
	{
		pthread_mutex_unlock(philo->scythe);
		return (true);
	}
	pthread_mutex_unlock(philo->scythe);
	return (false);
}
