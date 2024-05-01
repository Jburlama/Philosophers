/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:16:38 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/01 17:17:52 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*grim_reaper(void *arg)
{
	t_reaper *reaper;

	reaper = arg;
	wait_for_monitoring(reaper->data);
	pthread_mutex_lock(reaper->scythe);
	reaper->time_die = get_time();
	pthread_mutex_unlock(reaper->scythe);
	while (42)
	{
		pthread_mutex_lock(reaper->scythe);
		if (get_time() - reaper->time_die >= reaper->data->args.time_die)
		{
			pthread_mutex_unlock(reaper->scythe);
			break ;
		}
		pthread_mutex_unlock(reaper->scythe);
		pthread_mutex_lock(&reaper->mutex->global);
		if (reaper->data->one_die)
		{
			pthread_mutex_unlock(&reaper->mutex->global);
			return (NULL);
		}
		pthread_mutex_unlock(&reaper->mutex->global);
	}
	pthread_mutex_lock(&reaper->mutex->global);
	reaper->data->one_die = true;
	pthread_mutex_unlock(&reaper->mutex->global);
	mtx_printf("die", reaper->philo, DIE);
	return (NULL);
}
