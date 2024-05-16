/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:52:46 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/14 18:43:19 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	printf_blue(char *str, t_philo *philo, size_t time)
{
	sem_wait(philo->data->printf);
	printf(BLUE "%zu %i %s\n" RESET, time, philo->philo_id, str);
	sem_post(philo->data->printf);
}

void	printf_red(char *str, t_philo *philo, size_t time)
{
	sem_wait(philo->data->printf);
	printf(RED "%zu %i %s\n" RESET, time, philo->philo_id, str);
	sem_post(philo->data->printf);
}

void	printf_green(char *str, t_philo *philo, size_t time)
{
	sem_wait(philo->data->printf);
	printf(GREEN "%zu %i %s\n" RESET, time, philo->philo_id, str);
	sem_post(philo->data->printf);
}

void	printf_light_grey(char *str, t_philo *philo, size_t time)
{
	sem_wait(philo->data->printf);
	printf(LIGHT_GRAY "%zu %i %s\n" RESET, time, philo->philo_id, str);
	sem_post(philo->data->printf);
}

void	printf_dark_gray(char *str, t_philo *philo, size_t time)
{
	sem_wait(philo->data->printf);
	printf(DARK_GRAY "%zu %i %s\n" RESET, time, philo->philo_id, str);
	sem_post(philo->data->printf);
}
