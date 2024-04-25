/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:09:26 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/25 19:13:23 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mtx_printf(char *str, t_philo *philo, int collor)
{
	if (collor == LEFT_FORK)
		printf_light_gray(str, philo);
	else if(collor == RIGHT_FORK)
		printf_dark_gray(str, philo);
	else if (collor == EAT)
		printf_green(str, philo);
}

void	printf_green(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.printf);
	printf(GREEN "%zu %zu %s\n" RESET, get_time() - philo->data->start_time, 
		philo->philo_id, str);
	pthread_mutex_unlock(&philo->data->mutex.printf);
}

void	printf_light_gray(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.printf);
	printf(LIGHT_GRAY "%zu %zu %s\n" RESET, get_time() - philo->data->start_time, 
		philo->philo_id, str);
	pthread_mutex_unlock(&philo->data->mutex.printf);
}

void	printf_dark_gray(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.printf);
	printf(DARK_GRAY "%zu %zu %s\n" RESET, get_time() - philo->data->start_time, 
		philo->philo_id, str);
	pthread_mutex_unlock(&philo->data->mutex.printf);
}

