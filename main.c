/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:28:04 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/22 17:17:11 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	static t_data	data;

	if (!check_valid_args(argc, argv))
		return (panic("invalid arguments\n"));
	if (set_data(argc, argv, &data) == -1)
		return (panic("philo number between 1-200\n"));

	pthread_mutex_init(&data.printf, NULL);
	pthread_mutex_init(&data.mtx_general, NULL);

	data.fork = malloc(sizeof(*data.fork) * data.args.philo_num);
	memset(data.fork, 0, sizeof(*data.fork) * data.args.philo_num);

	data.philo = malloc(sizeof(*data.philo) * data.args.philo_num);
	memset(data.philo, 0, sizeof(*data.philo) * data.args.philo_num);

	start_philos(&data);

	pthread_create(&data.monitoring, NULL, monitoring, &data);

	pthread_join(data.monitoring, NULL);

	return (0);
}

void	*monitoring(void *data)
{
	while (42)
	{
		if (((t_data *)data)->last_is_ready)
		{
			pthread_mutex_lock(&((t_data *)data)->mtx_general);
			((t_data *)data)->ready = true;
			pthread_mutex_unlock(&((t_data *)data)->mtx_general);
		}
	}
	return (NULL);
}
