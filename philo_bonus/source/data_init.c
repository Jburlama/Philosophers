/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:54:23 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/10 18:03:47 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_init(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->args.num_philo)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].data = data;
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			exit(1);
		if (data->pid[i] == 0)
			philo_runtime(&data->philo[i]);
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
		panic("malloc failed for philos\n", data);
	data->pid = malloc(data->args.num_philo * sizeof(*data->pid));
	if (data->pid == NULL)
		panic("malloc failed for pid", data);
	sem_unlink("forks");
	sem_unlink("ready");
	data->forks = sem_open("forks", O_CREAT, S_IRUSR | S_IWUSR,
					  data->args.num_philo);
	if (data->forks == SEM_FAILED)
		panic("error calling sem_open for forks\n", data);
	data->ready = sem_open("ready", O_CREAT, S_IRUSR | S_IWUSR, 0);
	if (data->ready == SEM_FAILED)
		panic("error calling sem_open for ready\n", data);
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
