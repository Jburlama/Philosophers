/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                            :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:02:13 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/14 19:26:27 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	reaper_init(t_philo *philo)
{
	pthread_create(&philo->reaper_tid, NULL, grim_reaper, philo);
	pthread_create(&philo->stop_tid, NULL, stop_all, philo);
	pthread_detach(philo->reaper_tid);
	pthread_detach(philo->stop_tid);
}

void	*grim_reaper(void *arg)
{
	t_philo		*philo;

	philo = arg;
	while (42)
	{
		sem_wait(philo->data->philo_sem[philo->philo_id - 1]);
		if (get_time() - philo->die_time > philo->data->args.time_to_die)
		{
			philo->is_dead = true;
			sem_post(philo->data->philo_sem[philo->philo_id - 1]);
			break ;
		}
		sem_post(philo->data->philo_sem[philo->philo_id - 1]);
		if (check_stop(philo))
			return (NULL);
	}
	sem_wait(philo->data->printf_die);
	sem_printf("die", philo, DIE);
	sem_post(philo->data->stop);
	return (NULL);
}

void	*stop_all(void *arg)
{
	t_philo	*philo;

	philo = arg;
	sem_wait(philo->data->stop);
	sem_wait(philo->data->philo_sem[philo->philo_id - 1]);
	philo->stop = true;
	sem_post(philo->data->philo_sem[philo->philo_id - 1]);
	sem_post(philo->data->stop);
	return (NULL);
}
