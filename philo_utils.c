/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:31:28 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/26 21:34:34 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_even(t_philo *philo)
{
	size_t time_eat;

	pthread_mutex_lock(philo->left_fork);
	mtx_printf("has taken a fork", philo, LEFT_FORK);
	pthread_mutex_lock(philo->rigth_fork);
	mtx_printf("has taken a fork", philo, RIGHT_FORK);
	mtx_printf("is eating", philo, EAT);
	time_eat = get_time();
	while (get_time() - time_eat < philo->data->args.time_eat)
		usleep(500);
	pthread_mutex_unlock(philo->rigth_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

int	philo_odd(t_philo *philo)
{
	size_t time_eat;

	pthread_mutex_lock(philo->rigth_fork);
	mtx_printf("has taken a fork", philo, RIGHT_FORK);
	pthread_mutex_lock(philo->left_fork);
	mtx_printf("has taken a fork", philo, LEFT_FORK);
	mtx_printf("is eating", philo, EAT);
	time_eat = get_time();
	while (get_time() - time_eat < philo->data->args.time_eat)
		usleep(500);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->rigth_fork);
	return (0);
}

bool	philo_check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.global);
	if (philo->data->one_die)
	{
		pthread_mutex_unlock(&philo->data->mutex.global);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->mutex.global);
	return (false);
}

void	philo_reset_deth(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.kill);
	philo->die_time = get_time();
	pthread_mutex_unlock(&philo->data->mutex.kill);
}
