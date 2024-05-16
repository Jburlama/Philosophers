/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:02:13 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/14 19:26:27 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_runtime(t_philo *philo)
{
	sem_wait(philo->data->ready);
	philo->start_time = get_time();
	philo->die_time = philo->start_time;
	reaper_init(philo);
	if (philo->philo_id % 2 == 0)
	{
		if (philo_think(philo) == -1)
			exit(0);
		usleep(1e4);
	}
	while (42)
	{
		if (philo_eat(philo) == -1)
			break ;
		if (philo_sleep(philo) == -1)
			break ;
		if (philo_think(philo) == -1)
			break ;
	}
	exit(0);
}

int	philo_eat(t_philo *philo)
{
	size_t	time;

	if (philo_forks(philo, PICK) == -1)
		return (-1);
	sem_printf("is eating", philo, EAT);
	time = get_time();
	sem_wait(philo->data->philo_sem[philo->philo_id - 1]);
	philo->die_time = time;
	sem_post(philo->data->philo_sem[philo->philo_id - 1]);
	while (get_time() - time < philo->data->args.time_to_eat)
	{
		if (check_philo_is_dead(philo) || check_stop(philo))
		{
			philo_forks(philo, DROP);
			return (-1);
		}
	}
	philo_forks(philo, DROP);
	if (philo_check_is_full(philo) == -1)
		return (-1);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	size_t	time;

	time = get_time();
	sem_printf("is sleeping", philo, SLEEP);
	while (get_time() - time < philo->data->args.time_to_sleep)
	{
		if (check_philo_is_dead(philo) || check_stop(philo))
			return (-1);
	}
	return (0);
}

int	philo_forks(t_philo *philo, int action)
{
	if (action == PICK)
	{
		sem_wait(philo->data->forks);
		usleep(500);
		if (philo->data->args.num_philo == 1)
			return (one_philo(philo));
		else
		{
			if (check_philo_is_dead(philo) || check_stop(philo))
			{
				sem_post(philo->data->forks);
				return (-1);
			}
		}
		sem_printf("has taken a fork", philo, LEFT_FORK);
		sem_wait(philo->data->forks);
		sem_printf("has taken a fork", philo, RIGHT_FORK);
	}
	else
	{
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
	}
	return (0);
}

int	philo_think(t_philo *philo)
{
	sem_printf("is thinking", philo, THINK);
	if (check_philo_is_dead(philo) || check_stop(philo))
		return (-1);
	return (0);
}
