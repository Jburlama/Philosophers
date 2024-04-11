/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jburlama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:15:54 by jburlama          #+#    #+#             */
/*   Updated: 2024/04/11 19:26:03 by jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	(void)argv;
	if (argc != 5 && argc != 6)
		return (invalid_args("invalid number of arguments\n"));
	return (0);
}

int	invalid_args(char *err_msg)
{
	int	msg_len;

	msg_len = 0;
	while(err_msg[msg_len])
		msg_len++;
	write(2, err_msg, msg_len);
	return (1);
}
