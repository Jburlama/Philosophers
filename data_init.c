/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:40:08 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/15 19:01:09 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_data(int argc, char *argv[], t_data *data)
{
	data->args.philo_num = atoul(argv[1]);
	if (data->args.philo_num > MAX_PHILO || data->args.philo_num == 0)
		return (-1);
	data->args.time_die = atoul(argv[2]);
	data->args.time_eat = atoul(argv[3]);
	data->args.time_sleep = atoul(argv[4]);
	if (argc == 6)
		data->args.times_must_eat = atoul(argv[5]);
	return (0);
}

long	atoul(char	*str)
{
	long	result;
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
