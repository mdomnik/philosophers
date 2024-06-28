/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:37:55 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/28 17:47:58 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

static int	ft_strlen(const char *s);

int error_philo(char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	return (EXIT_FAILURE);
}
static int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	free_args(t_args *args)
{
	int i;

	i = -1;
	if (args->fork_locks)
	{
		while (i < args->num_philo)
		{
				pthread_mutex_destroy(args->philo[i].left_fork);
			i++;
		}
	}
	if (args->fork_locks)
		free(args->fork_locks);
	if (args->philo)
		free(args->philo);
	return (EXIT_SUCCESS);
}