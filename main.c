/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:28:04 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/01 17:18:32 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	static t_data	data;

	if (!check_valid_args(argc, argv))
		return (panic("invalid arguments\n"));
	if (data_init(argc, argv, &data) == -1)
		return (panic("philo number between 1-200\n"));
	mutex_init(&data);
	philos_init(&data);
	monitoring(&data);
	join_thread(&data, PHILO);
	destroy_mutex(&data);
	return (0);
}

void	monitoring(t_data *data)
{
	wait_last_thread(data);
	pthread_mutex_lock(&data->mutex.global);
	data->start_time = get_time();
	pthread_mutex_unlock(&data->mutex.global);
	join_thread(data, RIPPER);
}

void	destroy_mutex(t_data *data)
{
	size_t	i;

	pthread_mutex_destroy(&data->mutex.global);
	pthread_mutex_destroy(&data->mutex.printf);
	i = 0;
	while (i < data->args.philo_num)
	{
		pthread_mutex_destroy(&data->mutex.fork[i]);
		pthread_mutex_destroy(&data->mutex.scythe[i]);
		i++;
	}
	free(data->mutex.fork);
	free(data->philo);
	free(data->reaper);
}
