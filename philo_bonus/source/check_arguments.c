/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:32:27 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/12 16:14:21 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	check_valid_args(int argc, char *argv[])
{
	int	i;

	if (argc != 5 && argc != 6)
		erro_msg("invalid argument\n");
	while (argc > 1)
	{
		i = 0;
		while (argv[argc - 1][i] == '0')
			i++;
		if (ft_strlen(&argv[argc - 1][i]) > 10)
			erro_msg("invalid argument\n");
		if (argv[argc - 1][i] == '+')
			i++;
		while (argv[argc - 1][i])
		{
			if (!is_digit(argv[argc - 1][i]))
				erro_msg("invalid argument\n");
			i++;
		}
		argc--;
	}
}

void	erro_msg(char *err_msg)
{
	int	msg_len;

	msg_len = 0;
	while (err_msg[msg_len])
		msg_len++;
	write(2, err_msg, msg_len);
	exit (errno);
}

void	panic(char	*err_msg, t_data *data)
{
	if (data->forks)
		sem_close(data->forks);
	if (data->ready)
		sem_close(data->ready);
	erro_msg(err_msg);
}
