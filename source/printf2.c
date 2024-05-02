/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:26:49 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/02 17:52:24 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

void	mtx_printf_death(char *str, t_data *data)
{
	pthread_mutex_lock(&data->mutex.printf);
	printf(RED "%zu %zu %s\n" RESET, data->time_death, data->death_pid, str);
	pthread_mutex_unlock(&data->mutex.printf);
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
