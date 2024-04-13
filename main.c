/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:15:54 by jburlama          #+#    #+#             */
/*   Updated: 2024/04/13 20:24:52 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	memset(&data, 0, sizeof(data));
	if (!check_valid_args(argc, argv))
		return (panic("invalid arguments\n"));
	if (set_data(argc, argv, &data) == -1)
		return (panic("philo number between 0-200\n"));
	return (0);
}
