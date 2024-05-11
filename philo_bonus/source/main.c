/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:52:27 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/11 19:18:41 by Jburlama         ###   ########.fr       */
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
	return (0);
	philo_init(&data);
	monitoring(&data);
	i = -1;
	while (waitpid(-1, &wstatus, 0) > 0)
	{
		if (WIFEXITED(wstatus))
		{
			while (++i < data.args.num_philo)
				kill(data.philo_pid[i], SIGINT);
		}
	}
	sem_close(data.forks);
	sem_close(data.ready);
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
		sem_wait(philo->data->kill);
		if (get_time() - philo->die_time > philo->data->args.time_to_die)
		{
			philo->is_dead = true;
			sem_printf("die", philo, get_time() - philo->die_time, DIE);
			sem_post(philo->data->kill);
			break ;
		}
		sem_post(philo->data->kill);
	}
	return (NULL);
}
