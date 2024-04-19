/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:15:54 by jburlama          #+#    #+#             */
/*   Updated: 2024/04/19 19:25:52 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	main(int argc, char *argv[])
{
	t_data	data;

	memset(&data, 0, sizeof(data));
	if (!check_valid_args(argc, argv))
		return (panic("invalid arguments\n"));
	if (set_data(argc, argv, &data) == -1)
		return (panic("philo number between 1-200\n"));

	start_philos(&data);
	// monitoring(&data);
	join_threads(&data);

	return (0);
}

int	start_philos(t_data *data)
{
	size_t i;

	pthread_mutex_init(&data->mutex.printf, NULL);
	data->philo = malloc(sizeof(*data->philo) * data->args.philo_num);
	i = 0;
	while (i < data->philo->philo_pth)
	{
		data->philo[i].philo_id = i + 1;
		pthread_create(&data->philo[i].philo_pth, NULL, philo, &data->philo[i]);
		i++;
	}
	return (0);
}

int	monitoring(t_data *data)
{
	data->ready = true;
	return (0);
}

void	*philo(void *data)
{
	t_philo *philo = data;


	pthread_mutex_lock(&philo->table->mutex.printf);
	printf("hello from philo %zu!\n", philo->philo_id);
	pthread_mutex_unlock(&philo->table->mutex.printf);
	// while (philo->table->ready == false)
	// {
	// 	pthread_mutex_lock(&philo->table->mutex.printf);
	// 	printf("wait!\n");
	// 	pthread_mutex_unlock(&philo->table->mutex.printf);
	// }
	// pthread_mutex_lock(&philo->table->mutex.printf);
	// printf("sucess!\n");
	// pthread_mutex_unlock(&philo->table->mutex.printf);
	return (NULL);
}

void	join_threads(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->args.philo_num)
	{
		pthread_join(data->philo[i].philo_pth, NULL);
		i++;
	}
}

int	clean_thread(t_philo *philo)
{
	free(philo);
	return (-1);
}
