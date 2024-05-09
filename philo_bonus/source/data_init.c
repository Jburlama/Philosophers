/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:54:23 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/09 18:52:22 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

void	philo_init(t_data *data)
{
	size_t	i;
	pid_t pid;

	i = 0;
	while (i < data->args.num_philo)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].data = data;
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			philo_runtime(&data->philo[i]);
		}
		i++;
	}
}

void	data_init(int argc, char *argv[], t_data *data)
{
	data->args.num_philo = atos_t(argv[1]);
	if (data->args.num_philo > MAX_PHILO || data->args.num_philo == 0)
		erro_msg("invalid arguments\n");
	data->args.time_to_die = atos_t(argv[2]);
	if (data->args.time_to_die < 60)
		erro_msg("invalid arguments\n");
	data->args.time_to_eat = atos_t(argv[3]);
	if (data->args.time_to_eat < 60)
		erro_msg("invalid arguments\n");
	data->args.time_to_sleep = atos_t(argv[4]);
	if (data->args.time_to_sleep < 60)
		erro_msg("invalid arguments\n");
	if (argc == 6)
		data->args.times_must_eat = atos_t(argv[5]);
	else
		data->args.times_must_eat = -1;
	data_fill(data);
}

void	data_fill(t_data *data)
{
	data->philo = malloc(data->args.num_philo * sizeof(*data->philo));
	if (data->philo == NULL)
		panic("malloc failed for philos\n", NULL);
	if (sem_unlink("semaphore") == -1)
	{
		perror("erro: \n");
		panic("error calling sem_unlink semaphore\n", data->philo);
	}
	if (sem_unlink("ready") == -1)
		panic("error calling sem_unlink ready\n", data->philo);
	data->sem = sem_open("semaphore", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR,
					  data->args.num_philo);
	if (data->sem == SEM_FAILED)
		panic("error calling sem_open\n", data->philo);
	data->ready = sem_open("ready", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
	if (data->ready == SEM_FAILED)
		panic("error calling sem_open\n", data->philo);
}

size_t	atos_t(char	*str)
{
	size_t	result;
	int		i;

	result = 0;
	i = -1;
	if (str[0] == '+')
		i++;
	while (str[++i])
	{
		result = (result * 10) + (str[i] - '0');
	}
	return (result);
}
