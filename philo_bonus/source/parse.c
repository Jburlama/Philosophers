/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:58:36 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/12 19:12:15 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	parse_sem(t_data *data)
{
	size_t		id;

	id = 0;
	while (id < data->args.num_philo)
	{
		parse(data->philo_sem_name[id], "philo", id);
		id++;
	}
}

void	parse(char *sem_array, char *name, int id)
{
	char	*number;
	int		i;
	int		j;
	
	number = itos(id + 1);
	i = -1;
	while (name[++i])
		sem_array[i] = name[i];
	j = -1;
	while (number[++j])
	{
		sem_array[i] = number[j];
		i++;
	}
	sem_array[i] = '\0';
	free(number);
}

char	*itos(int id)
{
	char	*str;
	int		len;

	len = int_len(id);
	str = malloc(len + 1);
	str[len] = '\0';
	while (--len > 0)
	{
		str[len] = id % 10 + '0';
		id /= 10;
	}
	str[0] = id % 10 + '0';
	return (str);
}

int int_len(int id)
{
	int len;

	len = 0;
	while (id > 0)
	{
		id /= 10;
		len++;
	}
	return (len);
}

