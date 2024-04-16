/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:15:54 by jburlama          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/16 17:35:35 by jburlama         ###   ########.fr       */
=======
/*   Updated: 2024/04/16 17:18:39 by jburlama         ###   ########.fr       */
>>>>>>> a6365dd43c5eeddd52c73200c4b3102196ca5305
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	memset(&data, 0, sizeof(data));
	if (!check_valid_args(argc, argv))
		return (panic("invalid arguments\n"));
	if (set_data(argc, argv, &data) == -1)
		return (panic("philo number between 1-200\n"));
	start_diner(&data);
	return (0);
}

int		start_diner(t_data *data)
{
<<<<<<< HEAD
=======
	data->args.philo_num = atos_t(argv[1]);
	data->args.time_die = atos_t(argv[2]);
	data->args.time_eat = atos_t(argv[3]);
	data->args.time_sleep = atos_t(argv[4]);
	if (argc == 6)
		data->args.times_must_eat = atos_t(argv[5]);
}

size_t	atos_t(char	*str)
{
>>>>>>> a6365dd43c5eeddd52c73200c4b3102196ca5305
	size_t	result;
	size_t	i;

	pthread_mutex_init(&data->mutex_printf, NULL);
	data->philo = malloc(sizeof(pthread_t) * data->args.philo_num);
	if (data->philo == NULL)
		return (-1);
	data->philo_id = 1;
	result = 0;
	i = -1;
	while (++i < data->args.philo_num)
	{
		pthread_create(&data->philo[i], NULL, philo, data);
	}
	join_threads(data);
	return (0);
}

void	*philo(void *data)
{
	pthread_mutex_lock(&((t_data *)data)->mutex_printf);
	printf("hello from thread id %i\n", ((t_data *)data)->philo_id);
	((t_data *)data)->philo_id++;
	pthread_mutex_unlock(&((t_data *)data)->mutex_printf);
	return (NULL);
}

void	join_threads(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->args.philo_num)
	{
		pthread_join(data->philo[i], NULL);
	}
}
