/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:52:46 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/14 18:43:19 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo.h"

void	sem_printf(char *str, t_philo *philo, int collor)
{
	size_t	time;

	sem_wait(philo->data->philo_sem[philo->philo_id - 1]);
	time = get_time() - philo->start_time;
	sem_post(philo->data->philo_sem[philo->philo_id - 1]);
	if (collor == LEFT_FORK)
		printf_light_grey(str, philo, time);
	else if (collor == RIGHT_FORK)
		printf_dark_gray(str, philo, time);
	else if (collor == EAT)
		printf_green(str, philo, time);
	else if (collor == DIE)
		printf_red(str, philo, time);
	else if (collor == THINK)
		printf_blue(str, philo, time);
	else if (collor == SLEEP)
		printf_yellow(str, philo, time);
}

void	printf_yellow(char *str, t_philo *philo, size_t time)
{
	sem_wait(philo->data->printf);
	printf(YELLOW "%zu %i %s\n" RESET, time, philo->philo_id, str);
	sem_post(philo->data->printf);
}

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
