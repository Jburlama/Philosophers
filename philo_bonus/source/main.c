/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:52:27 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/10 17:01:17 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <semaphore.h>

int	main(int argc, char *argv[])
{
	t_data	data;
	int		status;

	memset(&data, 0, sizeof(data));
	check_valid_args(argc, argv);
	data_init(argc, argv, &data);
	philo_init(&data);
	monitoring(&data);

	while (waitpid(-1, &status, 0) > 0)
		;

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
}

void	philo_runtime(t_philo *philo)
{
	sem_wait(philo->data->ready);

	while (42)
	{
		sem_wait(philo->data->forks);
		sem_wait(philo->data->forks);
		printf(GREEN "%zu is eating\n" RESET, philo->philo_id);
		sleep(2);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		sleep(2);
	}
	exit(1);
}
