/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                            :+:      :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:02:13 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/14 19:26:27 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philo_check_is_full(t_philo *philo)
{
	if (philo->data->args.times_must_eat != -1)
		philo->times_eaten++;
	if (philo->times_eaten == philo->data->args.times_must_eat)
	{
		sem_wait(philo->data->philo_sem[philo->philo_id - 1]);
		philo->is_full = true;
		sem_post(philo->data->philo_sem[philo->philo_id - 1]);
		sem_printf("is full", philo, FULL);
		return (-1);
	}
	return (0);
}

bool	check_stop(t_philo *philo)
{
	sem_wait(philo->data->philo_sem[philo->philo_id - 1]);
	if (philo->is_full || philo->stop)
	{
		sem_post(philo->data->philo_sem[philo->philo_id - 1]);
		return (true);
	}
	sem_post(philo->data->philo_sem[philo->philo_id - 1]);
	return (false);
}

bool	check_philo_is_dead(t_philo *philo)
{
	sem_wait(philo->data->philo_sem[philo->philo_id - 1]);
	if (philo->is_dead)
	{
		sem_post(philo->data->philo_sem[philo->philo_id - 1]);
		return (true);
	}
	sem_post(philo->data->philo_sem[philo->philo_id - 1]);
	return (false);
}

int	one_philo(t_philo *philo)
{
	sem_printf("has taken a fork", philo, LEFT_FORK);
	while (42)
	{
		if (check_philo_is_dead(philo) || check_stop(philo))
		{
			sem_post(philo->data->forks);
			return (-1);
		}
	}
	return (0);
}
