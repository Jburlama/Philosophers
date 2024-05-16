/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:52:27 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/14 19:25:14 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	memset(&data, 0, sizeof(data));
	check_valid_args(argc, argv);
	data_init(argc, argv, &data);
	philo_init(&data);
	monitoring(&data);
	while (waitpid(-1, NULL, 0) > 0)
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
}

void	close_semaphore(t_data *data)
{
	size_t	i;

	sem_close(data->stop);
	sem_close(data->printf);
	sem_close(data->printf_die);
	sem_close(data->ready);
	sem_close(data->forks);
	i = 0;
	while (i < data->args.num_philo)
	{
		sem_close(data->philo_sem[i]);
		i++;
	}
}
