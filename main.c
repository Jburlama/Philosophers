/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jburlama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:15:54 by jburlama          #+#    #+#             */
/*   Updated: 2024/04/13 17:26:53 by jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data data;

	if (!check_valid_args(argc, argv))
		return (panic("invalid arguments\n"));
	set_data(argc, argv, &data);
	return (0);
}

void	set_data(int argc, char *argv[], t_data *data)
{
	data->args.philo_num = atoul(argv[1]);
	data->args.time_die = atoul(argv[2]);
	data->args.time_eat = atoul(argv[3]);
	data->args.time_sleep = atoul(argv[4]);
	if (argc == 6)
		data->args.times_must_eat = atoul(argv[5]);
	

	printf("%ld\n", data->args.philo_num);
	printf("%ld\n", data->args.time_die);
	printf("%ld\n", data->args.time_eat);
	printf("%ld\n", data->args.time_sleep);
	if (argc == 6)
		printf("%ld\n", data->args.times_must_eat);
}

long	atoul(char	*str)
{
	int	result;
	int	i;

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
