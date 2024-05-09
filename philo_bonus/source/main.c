/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:52:27 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/09 17:10:33 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	int status;

	check_valid_args(argc, argv);
	data_init(argc, argv, &data);
	philo_init(&data);

	while (waitpid(-1, &status, 0) > 0)
		;
}

void	philo_init(t_data *data)
{
	size_t	i;
	pid_t pid;

	i = 0;
	while (i < data->args.num_philo)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].data = data;
		pid = fork();
		if (pid == -1)
			exit (1);
		if (pid == 0)
		{
			philo_runtime(&data->philo[i]);
		}
		i++;
	}
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
