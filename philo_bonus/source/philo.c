/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:02:13 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/10 19:14:22 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo.h"

void	philo_runtime(t_philo *philo)
{
	sem_wait(philo->data->ready);
	philo->start_time = get_time();
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

	sem_wait(philo->data->forks);
	sem_wait(philo->data->forks);
	time = get_time();
	printf(GREEN "%zu %zu is eating\n" RESET,
		time - philo->start_time, philo->philo_id);
	while (get_time() - time < philo->data->args.time_to_eat)
		;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	philo_sleep(t_philo *philo)
{
	size_t	time;

	time = get_time();
	printf(YELLOW "%zu %zu is sleeping\n" RESET,
		time - philo->start_time, philo->philo_id);
	while(get_time() - time < philo->data->args.time_to_sleep)
		;
}
