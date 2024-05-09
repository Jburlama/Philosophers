/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:52:27 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/09 15:47:09 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	check_valid_args(argc, argv);
	data_init(argc, argv, &data);

	printf("%zu\n", data.args.num_philo);
	printf("%zu\n", data.args.time_to_die);
	printf("%zu\n", data.args.time_to_eat);
	printf("%zu\n", data.args.time_to_sleep);
	printf("%zu\n", data.args.times_must_eat);
}

void	data_init(int argc, char *argv[], t_data *data)
{
	data->args.num_philo = atos_t(argv[1]);
	if (data->args.num_philo > MAX_PHILO || data->args.num_philo == 0)
		panic("invalid arguments");
	data->args.time_to_die = atos_t(argv[2]);
	if (data->args.time_to_die < 60)
		panic("invalid arguments");
	data->args.time_to_eat = atos_t(argv[3]);
	if (data->args.time_to_eat < 60)
		panic("invalid arguments");
	data->args.time_to_sleep = atos_t(argv[4]);
	if (data->args.time_to_sleep < 60)
		panic("invalid arguments");
	if (argc == 6)
		data->args.times_must_eat = atos_t(argv[5]);
	else
		data->args.times_must_eat = -1;
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
