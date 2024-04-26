/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:28:04 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/26 21:20:24 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

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
	free(data.mutex.fork);
	free(data.philo);
	return (0);
}

void	monitoring(t_data *data)
{
	size_t	i;
	
	data->ripper = malloc(sizeof(*data->ripper) * data->args.philo_num);
	if (data->ripper == NULL)
		return ;
	i = -1;
	while (++i < data->args.philo_num)
	{
		data->ripper[i].philo = &data->philo[i];
		data->ripper[i].data = data;
		pthread_create(&data->ripper[i].th_ripper, NULL, ripper, &data->ripper[i]);
	}
	wait_last_thread(data);
	join_thread(data, RIPPER);
}

void	*ripper(void *arg)
{
	t_ripper	*r;

	r = arg;
	wait_for_monitoring(r->data);

	return (NULL);
}

void	destroy_mutex(t_data *data)
{
	size_t	i;

	pthread_mutex_destroy(&data->mutex.global);
	pthread_mutex_destroy(&data->mutex.kill);
	pthread_mutex_destroy(&data->mutex.printf);
	i = 0;
	while (i < data->args.philo_num)
	{
		pthread_mutex_destroy(&data->mutex.fork[i]);
		i++;
	}
}
