/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:52:27 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/09 18:57:57 by Jburlama         ###   ########.fr       */
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

	sem_close(data.sem);
	sem_close(data.ready);
}

void	monitoring(t_data *data)
{
	size_t	i;
	
	i = -1;
	while (++i < data->args.num_philo)
		sem_post(data->ready);
}

void	philo_runtime(t_philo *philo)
{
	sem_wait(philo->data->ready);
	exit(1);
}
