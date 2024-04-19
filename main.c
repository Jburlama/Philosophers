/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:15:54 by jburlama          #+#    #+#             */
/*   Updated: 2024/04/19 20:36:49 by Jburlama         ###   ########.fr       */
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

	start_philos(&data);
	usleep(2e6);
	monitoring(&data);
	join_threads(&data);

	return (0);
}

int	start_philos(t_data *data)
{
	size_t i;

	pthread_mutex_init(&data->printf, NULL);
	pthread_mutex_init(&data->mtx_philo, NULL);
	data->philo = malloc(sizeof(*data->philo) * data->args.philo_num);
	i = 0;
	while (i < data->args.philo_num)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].is_alive = true;
		data->philo[i].table = data;
		pthread_create(&data->philo[i].philo_pth, NULL, philo, &data->philo[i]);
		i++;
	}
	return (0);
}

int	monitoring(t_data *data)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(&data->mtx_philo);
	data->ready = true;
	pthread_mutex_unlock(&data->mtx_philo);
	data->start = get_time();
	while (i < data->args.philo_num)
	{
		pthread_mutex_lock(&data->mtx_philo);
		data->philo[i].is_alive = false;
		pthread_mutex_unlock(&data->mtx_philo);
		usleep(2e6);
		i++;
	}
	return (0);
}

void	*philo(void *data)
{
	t_philo *philo = data;

	while (42)
	{
		pthread_mutex_lock(&philo->table->mtx_philo);
		if (philo->table->ready == false)
		{
			pthread_mutex_unlock(&philo->table->mtx_philo);
			break ;
		}
		pthread_mutex_unlock(&philo->table->mtx_philo);
	}
	while (42)
	{
		pthread_mutex_lock(&philo->table->mtx_philo);
		if (philo->is_alive == false)
		{
			pthread_mutex_unlock(&philo->table->mtx_philo);
			break ;
		}
		pthread_mutex_unlock(&philo->table->mtx_philo);
	}

	pthread_mutex_lock(&philo->table->printf);
	printf("%zu philo id %zu die\n", get_time() - philo->table->start, philo->philo_id);
	pthread_mutex_unlock(&philo->table->printf);

	return (NULL);
}

size_t	get_time(void)
{
	size_t	time;
	struct timeval	tv;
	gettimeofday(&tv, NULL);

	time = (tv.tv_sec * 1e6) + tv.tv_usec;
	time = time / 1e3;
	return (time);
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
