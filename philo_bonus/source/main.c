/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:52:27 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/14 19:04:08 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	int		wstatus;

	memset(&data, 0, sizeof(data));
	check_valid_args(argc, argv);
	data_init(argc, argv, &data);
	philo_init(&data);
	monitoring(&data);
	while (waitpid(-1, &wstatus, 0) != 0)
		;
	close_semaphore(&data);
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
	// data->start_time = get_time();
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
			sem_post(philo->data->stop);
			sem_post(philo->data->philo_sem[philo->philo_id - 1]);
			sem_printf("die", philo, DIE);
			break ;
		}
		sem_post(philo->data->philo_sem[philo->philo_id - 1]);
		if (check_stop(philo))
			return (NULL);
	}
	return (NULL);
}

void	*stop_all(void *arg)
{
	t_philo	*philo;

	philo = arg;
	sem_wait(philo->data->stop);
	sem_wait(philo->data->philo_sem[philo->philo_id - 1]);
	philo->stop = true;
	sem_post(philo->data->philo_sem[philo->philo_id - 1]);
	sem_post(philo->data->stop);
	return (NULL);
}

void	close_semaphore(t_data *data)
{
	size_t	i;

	sem_close(data->stop);
	sem_close(data->kill);
	sem_close(data->printf);
	sem_close(data->ready);
	sem_close(data->forks);
	i = 0;
	while (i < data->args.num_philo)
		sem_close(data->philo_sem[i++]);
}
