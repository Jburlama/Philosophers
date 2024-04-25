/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:31:28 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/25 19:43:13 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat_even(t_philo *philo)
{
	size_t time_eat;

	pthread_mutex_lock(philo->left_fork);
	mtx_printf("has taken a fork", philo, LEFT_FORK);
	pthread_mutex_lock(philo->rigth_fork);
	mtx_printf("has taken a fork", philo, RIGHT_FORK);
	mtx_printf("is eating", philo, EAT);
	time_eat = get_time();
	while (get_time() - time_eat < philo->data->args.time_eat)
		;
	pthread_mutex_unlock(philo->rigth_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_eat_odd(t_philo *philo)
{
	size_t time_eat;

	pthread_mutex_lock(philo->rigth_fork);
	mtx_printf("has taken a fork", philo, RIGHT_FORK);
	pthread_mutex_lock(philo->left_fork);
	mtx_printf("has taken a fork", philo, LEFT_FORK);
	mtx_printf("is eating", philo, EAT);
	time_eat = get_time();
	while (get_time() - time_eat < philo->data->args.time_eat)
		;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->rigth_fork);
}
