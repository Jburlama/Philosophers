/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:58:42 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/25 22:58:43 by Jburlama         ###   ########.fr       */
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
	join_thread(&data);
	destroy_mutex(&data);
	free(data.mutex.fork);
	free(data.philo);
	return (0);
}

void	monitoring(t_data *data)
{
	wait_last_thread(data);

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
		i++;
	}
}
