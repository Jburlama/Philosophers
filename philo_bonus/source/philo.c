/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:02:13 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/14 18:53:42 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo.h"

void	philo_runtime(t_philo *philo)
{
	sem_wait(philo->data->ready);
	philo->start_time = get_time();
	philo->die_time = philo->start_time;
	reaper_init(philo);
	if (philo->philo_id % 2 == 0)
	{
		usleep(1e4);
		if (philo_think(philo) == -1)
		{
			close_semaphore(philo->data);
			pthread_join(philo->reaper_tid, NULL);
			pthread_join(philo->stop_tid, NULL);
			exit(0);
		}
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
	close_semaphore(philo->data);
	pthread_join(philo->reaper_tid, NULL);
	pthread_join(philo->stop_tid, NULL);
	exit(0);
}

int	philo_eat(t_philo *philo)
{
	if (philo_forks(philo, PICK) == -1)
		return (-1);
	sem_printf("is eating", philo, EAT);
	sem_wait(philo->data->philo_sem[philo->philo_id - 1]);
	philo->die_time = get_time();
	sem_post(philo->data->philo_sem[philo->philo_id - 1]);
	while (42)
	{
		sem_wait(philo->data->philo_sem[philo->philo_id - 1]);
		if (get_time() - philo->die_time < philo->data->args.time_to_eat)
		{
			sem_post(philo->data->philo_sem[philo->philo_id - 1]);
			break ;
		}
		sem_post(philo->data->philo_sem[philo->philo_id - 1]);
		if (check_philo_is_dead(philo) || check_stop(philo))
			return (-1);
	}
	philo_forks(philo, DROP);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	size_t	time;

	sem_wait(philo->data->philo_sem[philo->philo_id - 1]);
	time = get_time();
	sem_post(philo->data->philo_sem[philo->philo_id - 1]);
	sem_printf("is sleeping", philo, SLEEP);
	while (42)
	{
		sem_wait(philo->data->philo_sem[philo->philo_id - 1]);
		if (get_time() - time < philo->data->args.time_to_sleep)
		{
			sem_post(philo->data->philo_sem[philo->philo_id - 1]);
			break ;
		}
		sem_post(philo->data->philo_sem[philo->philo_id - 1]);
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
		if (check_philo_is_dead(philo) || check_stop(philo))
			return (-1);
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

bool	check_stop(t_philo *philo)
{
	sem_wait(philo->data->philo_sem[philo->philo_id - 1]);
	if (philo->stop)
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

int	philo_think(t_philo *philo)
{
	size_t	time;

	time = get_time();
	sem_printf("is thinking", philo, THINK);
	if (check_philo_is_dead(philo) || check_stop(philo))
		return (-1);
	return (0);
}
