/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:52:27 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/12 19:09:52 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	int		wstatus;
	size_t	i;

	memset(&data, 0, sizeof(data));
	check_valid_args(argc, argv);
	data_init(argc, argv, &data);
	philo_init(&data);
	monitoring(&data);
	i = 0;
	waitpid(-1, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		while (i < data.args.num_philo)
			kill(data.philo_pid[i++], SIGTERM);
	}
	i = 0;
	while (i < data.args.num_philo)
		sem_close(data.philo_sem[i++]);
	sem_close(data.forks);
	sem_close(data.ready);
	data_sem_unlink(&data);
}

void	monitoring(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->args.num_philo)
	{
		sem_post(data->ready);
		i++;
	}
	data->start_time = get_time();
}

void	*grim_reaper(void *arg)
{
	t_philo		*philo;

	philo = arg;
	while (42)
	{
		sem_wait(philo->data->philo_sem[philo->philo_id - 1]);
		if (get_time() - philo->die_time > philo->data->args.time_to_die)
		{
			philo->is_dead = true;
			sem_post(philo->data->philo_sem[philo->philo_id - 1]);
			break ;
		}
		sem_post(philo->data->philo_sem[philo->philo_id - 1]);
	}
	sem_wait(philo->data->kill);
	sem_printf("die", philo, get_time() - philo->die_time, DIE);
	return (NULL);
}
