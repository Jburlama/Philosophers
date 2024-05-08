/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:43:23 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/08 15:25:06 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <errno.h>

int	main(void)
{
	pid_t	pid;
	int	i;
	int	status;
	sem_t *semafore;

	sem_unlink("test");
	semafore = sem_open("test", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	if (semafore == SEM_FAILED)
	{
		printf("sem failed: %i\n", errno);
		return (-1);
	}

	i = 0;
	while (i < 10)
	{
		pid = fork();
		if (pid == 0)
		{
			sem_wait(semafore);
			printf("hello from child %i %i\n", getpid(), i);
			sleep(2);
			sem_post(semafore);
			return (0);
		}
		i++;
	}
	while (waitpid(-1, &status, 0) > 0)
		;
	printf("hello from parent\n");
}
