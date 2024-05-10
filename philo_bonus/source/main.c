/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:52:27 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/10 17:52:42 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	int		status;

	memset(&data, 0, sizeof(data));
	check_valid_args(argc, argv);
	data_init(argc, argv, &data);
	philo_init(&data);
	monitoring(&data);

	while (waitpid(-1, &status, 0) > 0)
		;

	sem_close(data.forks);
	sem_close(data.ready);
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

size_t	get_time(void)
{
	size_t			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1e6) + tv.tv_usec;
	time = time / 1e3;
	return (time);
}
