/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:09:26 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/29 20:14:42 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mtx_printf(char *str, size_t time, t_philo *philo, int collor)
{
	if (collor == LEFT_FORK)
		printf_light_gray(str, time, philo);
	else if(collor == RIGHT_FORK)
		printf_dark_gray(str, time, philo);
	else if (collor == EAT)
		printf_green(str, time, philo);
	else if (collor == DIE)
		printf_red(str, time, philo);
	else if (collor == THINK)
		printf_blue(str, time, philo);
	else if (collor == SLEEP)
		printf_yellow(str, time, philo);
}

void	printf_green(char *str, size_t time, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.printf);
	printf(GREEN "%zu %zu %s\n" RESET, time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->data->mutex.printf);
}

void	printf_light_gray(char *str, size_t time, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.printf);
	printf(LIGHT_GRAY "%zu %zu %s\n" RESET, time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->data->mutex.printf);
}

void	printf_dark_gray(char *str, size_t time, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.printf);
	printf(DARK_GRAY "%zu %zu %s\n" RESET, time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->data->mutex.printf);
}

void	printf_red(char *str, size_t time, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.printf);
	printf(RED "%zu %zu %s\n" RESET, time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->data->mutex.printf);
}

void	printf_blue(char *str, size_t time, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.printf);
	printf(BLUE "%zu %zu %s\n" RESET, time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->data->mutex.printf);
}

void	printf_yellow(char *str, size_t time, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.printf);
	printf(YELLOW "%zu %zu %s\n" RESET, time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->data->mutex.printf);
}
