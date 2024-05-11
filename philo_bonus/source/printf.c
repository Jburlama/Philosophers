/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:52:46 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/11 17:17:12 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo.h"

void	sem_printf(char *str, t_philo *philo, size_t time, int collor)
{
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
	printf(YELLOW "%zu %zu %s\n" RESET, time, philo->philo_id, str);
	sem_post(philo->data->printf);
}

void	printf_blue(char *str, t_philo *philo, size_t time)
{
	sem_wait(philo->data->printf);
	printf(BLUE "%zu %zu %s\n" RESET, time, philo->philo_id, str);
	sem_post(philo->data->printf);
}

void	printf_red(char *str, t_philo *philo, size_t time)
{
	sem_wait(philo->data->printf);
	printf(RED "%zu %zu %s\n" RESET, time, philo->philo_id, str);
	sem_post(philo->data->printf);
}

void	printf_green(char *str, t_philo *philo, size_t time)
{
	sem_wait(philo->data->printf);
	printf(GREEN "%zu %zu %s\n" RESET, time, philo->philo_id, str);
	sem_post(philo->data->printf);
}

void	printf_light_grey(char *str, t_philo *philo, size_t time)
{
	sem_wait(philo->data->printf);
	printf(LIGHT_GRAY "%zu %zu %s\n" RESET, time, philo->philo_id, str);
	sem_post(philo->data->printf);
}

void	printf_dark_gray(char *str, t_philo *philo, size_t time)
{
	sem_wait(philo->data->printf);
	printf(DARK_GRAY "%zu %zu %s\n" RESET, time, philo->philo_id, str);
	sem_post(philo->data->printf);
}
