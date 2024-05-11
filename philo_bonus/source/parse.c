/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:58:36 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/11 19:27:01 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	parse_sem(t_data *data)
{
	size_t		id;

	data->philo_sem = malloc(data->args.num_philo * sizeof(*data->philo_sem) + 1);
	if (data->philo_sem == NULL)
		panic("mallco failed for philo_sem\n", data);
	id = 0;
	while (id < data->args.num_philo)
	{
		data->philo_sem[id] = parse("philo", id + 1);
		if (data->philo_sem[id] == NULL)
			panic("error calling data->philo_sem[id]\n", data);
		id++;
	}
	data->philo_sem[id] = NULL;
}

char	*parse(char *name, int id)
{
	char	*str;
	char	*number;
	int		i;
	int		j;
	
	number = itos(id);
	if (number == NULL)
		return (NULL);
	str = malloc(strlen(name) + strlen(number) + 1);
	i = -1;
	while (name[++i])
		str[i] = name[i];
	j = -1;
	while (number[++j])
		str[i++] = number[j];
	str[i] = '\0';
	free(number);
	return (str);
}

char	*itos(int id)
{
	char	*str;
	int		len;

	len = int_len(id);
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
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
