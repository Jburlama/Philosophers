/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:09:26 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/10 16:58:32 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	mtx_printf(char *str, t_philo *philo, int collor)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->mutex.printf);
	time = get_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->data->mutex.printf);
	if (collor == LEFT_FORK)
		printf_light_gray(str, time, philo);
	else if (collor == RIGHT_FORK)
		printf_dark_gray(str, time, philo);
	else if (collor == EAT)
		printf_green(str, time, philo);
	else if (collor == THINK)
		printf_blue(str, time, philo);
	else if (collor == SLEEP)
		printf_yellow(str, time, philo);
	else if (collor == FULL)
		printf_magenta(str, time, philo);
}

void	printf_green(char *str, size_t time, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.printf);
	printf(GREEN "%zu %zu %s\n" RESET, time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->data->mutex.printf);
}

void	printf_magenta(char *str, size_t time, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.printf);
	printf(MAGENTA "%zu %zu %s\n" RESET, time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->data->mutex.printf);
}
