/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:40:08 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/18 17:20:25 by jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_data(int argc, char *argv[], t_data *data)
{
	data->args.philo_num = atos_t(argv[1]);
	if (data->args.philo_num > MAX_PHILO || data->args.philo_num == 0)
		return (-1);
	data->args.time_die = atos_t(argv[2]);
	data->args.time_eat = atos_t(argv[3]);
	data->args.time_sleep = atos_t(argv[4]);
	if (argc == 6)
		data->args.times_must_eat = atos_t(argv[5]);
	return (0);
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
