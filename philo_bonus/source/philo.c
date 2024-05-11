/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:02:13 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/11 17:20:33 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo.h"

void	philo_runtime(t_philo *philo)
{
	free(philo->data->philo_pid);
	sem_wait(philo->data->ready);
	philo->start_time = get_time();
	philo->die_time = get_time();
	// reaper_init(philo);
	if (philo->philo_id % 2 == 0)
		usleep(1e6);
	while (42)
	{
		philo_eat(philo);
		philo_sleep(philo);
	}
	exit(1);
}

void	philo_eat(t_philo *philo)
{
	size_t	time;

	philo_forks(philo, PICK);
	sem_wait(philo->data->kill);
	philo->die_time = get_time();
	sem_post(philo->data->kill);
	time = get_time();
	sem_printf("is eating", philo, time - philo->start_time, EAT);
	while (get_time() - time < philo->data->args.time_to_eat)
		;
	philo_forks(philo, DROP);
}

void	philo_sleep(t_philo *philo)
{
	size_t	time;

	time = get_time();
	sem_printf("is sleeping", philo, time - philo->start_time, SLEEP);
	while(get_time() - time < philo->data->args.time_to_sleep)
		;
}

void	philo_forks(t_philo *philo, int action)
{
	if (action == PICK)
	{
		sem_wait(philo->data->forks);
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
}
