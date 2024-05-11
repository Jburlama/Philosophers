/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:52:27 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/10 20:58:41 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	int		wstatus;
	size_t	i;

	memset(&data, 0, sizeof(data));
	check_valid_args(argc, argv);
	data_init(argc, argv, &data);
	philo_init(&data);
	monitoring(&data);
	i = -1;
	while (waitpid(-1, &wstatus, 0) > 0)
	{
		if (WIFEXITED(wstatus))
		{
			while (++i < data.args.num_philo)
				kill(data.philo_pid[i], SIGINT);
		}
	}
	sem_close(data.forks);
	sem_close(data.ready);
	i = -1;
	while (++i < data.args.num_philo)
	{
		pthread_join(data.reaper_tid[i], NULL);
	}
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
	data->start_time = get_time();
}

void	*grim_reaper(void *arg)
{
	t_reaper	*reaper;
	size_t		time;

	reaper = arg;
	sem_wait(reaper->data->ready);
	time = get_time();
	while (get_time() - time < reaper->data->args.time_to_die)
		;
	kill(reaper->philo_pid, SIGINT);
	printf(RED "%zu die\n" RESET, reaper->philo->philo_id);
	return (NULL);
}

size_t	get_time(void)
{
	size_t			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1e6) + tv.tv_usec;
	time = time / 1e3;
	return (time);
}

size_t	atos_t(char	*str)
{
	size_t	result;
	int		i;

	result = 0;
	i = -1;
	if (str[0] == '+')
		i++;
	while (str[++i])
	{
		result = (result * 10) + (str[i] - '0');
	}
	return (result);
}
