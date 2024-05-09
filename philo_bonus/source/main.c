/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:52:27 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/09 16:18:47 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	check_valid_args(argc, argv);
	data_init(argc, argv, &data);
	philo_init(&data);

}

void	philo_init(t_data *data)
{
	size_t	i;
	pid_t pid;

	i = 0;
	while (i < data->args.num_philo)
	{
		data->philo[i].philo_id = i + 1;
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
	printf("hello from philo %zu\n", philo->philo_id);
	exit(1);
}
