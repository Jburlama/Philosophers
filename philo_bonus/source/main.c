/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:52:27 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/09 18:20:00 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	int		status;

	check_valid_args(argc, argv);
	data_init(argc, argv, &data);
	philo_init(&data);

	while (waitpid(-1, &status, 0) > 0)
		;
}

void	philo_runtime(t_philo *philo)
{
	sem_wait(philo->data->sem);
	sem_wait(philo->data->sem);
	printf("hello from philo %zu\n", philo->philo_id);
	sleep(3);
	sem_post(philo->data->sem);
	sem_post(philo->data->sem);
	exit(1);
}
