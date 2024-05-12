/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:54:23 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/12 19:10:01 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	reaper_init(t_philo *philo)
{
	pthread_create(&philo->reaper_tid, NULL, grim_reaper, philo);
}

void	philo_init(t_data *data)
{
	size_t	i;

	data->philo.data = data;
	data->philo.is_dead = false;
	i = 0;
	while (i < data->args.num_philo)
	{
		data->philo.philo_id = i + 1;
		data->philo_pid[i] = fork();
		if (data->philo_pid[i] == -1)
			exit(1);
		if (data->philo_pid[i] == 0)
			philo_runtime(&data->philo);
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
	parse_sem(data);
	data_sem_unlink(data);
	data_sem_open(data);
	data->forks = sem_open("forks", O_CREAT, S_IRUSR | S_IWUSR,
					  data->args.num_philo);
	if (data->forks == SEM_FAILED)
		panic("error calling sem_open for forks\n", data);
	data->ready = sem_open("ready", O_CREAT, S_IRUSR | S_IWUSR, 0);
	if (data->ready == SEM_FAILED)
		panic("error calling sem_open for ready\n", data);
	data->printf = sem_open("printf", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (data->printf == SEM_FAILED)
		panic("error calling sem_open for printf\n", data);
	data->kill = sem_open("kill", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (data->kill == SEM_FAILED)
		panic("error calling sem_open for kill\n", data);
}

void	data_sem_open(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->args.num_philo)
	{
		data->philo_sem[i] = sem_open(data->philo_sem_name[i],
								O_CREAT, S_IRUSR | S_IWUSR, 1);
		if (data->philo_sem[i] == SEM_FAILED)
			panic("error calling sem_open for philo_sem\n", data);
		i++;
	}
}

void	data_sem_unlink(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->args.num_philo)
		sem_unlink(data->philo_sem_name[i++]);
	sem_unlink("forks");
	sem_unlink("ready");
	sem_unlink("printf");
	sem_unlink("kill");
}
