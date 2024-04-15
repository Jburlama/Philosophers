/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:15:54 by jburlama          #+#    #+#             */
/*   Updated: 2024/04/15 19:01:37 by Jburlama         ###   ########.fr       */
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
	if (start_diner(&data) == -1)
		return (panic("Error starting dinner!\n"));
	return (0);
}

int	start_diner(t_data *data)
{
	size_t	i;

	pthread_mutex_init(&data->mutex_printf, NULL);
	data->philo = malloc(sizeof(pthread_t) * data->args.philo_num);
	if (data->philo == NULL)
		return (-1);
	data->philo_id = 1;
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
