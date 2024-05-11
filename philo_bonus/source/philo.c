/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:02:13 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/11 18:59:33 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo.h"

void	philo_runtime(t_philo *philo)
{
	free(philo->data->philo_pid);
	sem_wait(philo->data->ready);
	philo->start_time = get_time();
	philo->die_time = philo->start_time;
	reaper_init(philo);
	if (philo->philo_id % 2 == 0)
		usleep(1e6);
	while (42)
	{
		if (philo_eat(philo) == -1)
			exit (0);
		if (philo_sleep(philo) == -1)
			exit (0);
	}
	exit(1);
}

int	philo_eat(t_philo *philo)
{
	size_t	time;

	if (philo_forks(philo, PICK) == -1)
		return (-1);
	if (check_philo_is_dead(philo))
		return (-1);
	time = get_time();
	sem_wait(philo->data->kill);
	philo->die_time = time;
	sem_post(philo->data->kill);
	sem_printf("is eating", philo, time - philo->start_time, EAT);
	while (get_time() - time < philo->data->args.time_to_eat)
	{
		if (check_philo_is_dead(philo))
			return (-1);
	}
	philo_forks(philo, DROP);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	size_t	time;

	time = get_time();
	sem_printf("is sleeping", philo, time - philo->start_time, SLEEP);
	while(get_time() - time < philo->data->args.time_to_sleep)
	{
		if (check_philo_is_dead(philo))
			return (-1);
	}
	return (0);
}

int	philo_forks(t_philo *philo, int action)
{
	if (action == PICK)
	{
		sem_wait(philo->data->forks);
		if (check_philo_is_dead(philo))
			return (-1);
		sem_printf("has taken a fork", philo,
			 get_time() - philo->start_time, LEFT_FORK);
		sem_wait(philo->data->forks);
		sem_printf("has taken a fork", philo,
			 get_time() - philo->start_time, RIGHT_FORK);
	}
	else
	{
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
	}
	return (0);
}

bool	check_philo_is_dead(t_philo *philo)
{
	sem_wait(philo->data->kill);
	if (philo->is_dead)
	{
		sem_post(philo->data->kill);
		return (true);
	}
	sem_post(philo->data->kill);
	return (false);
}
