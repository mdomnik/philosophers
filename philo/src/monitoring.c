/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:04:54 by mdomnik           #+#    #+#             */
/*   Updated: 2024/07/03 19:08:58 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	monitoring_status(t_philo *philo, int status)
{
	const char	*status_msg[5] = {FORK, EAT, SLEEP, THINK, DEAD};

	pthread_mutex_lock(&philo->args->monitoring);
	if (philo->args->philo_dead == 0)
	{
		printf("%ld ", get_time_diff(philo->args));
		printf("%d %s\n", philo->philo_id, status_msg[status]);
	}
	pthread_mutex_unlock(&philo->args->monitoring);
}

int	find_lowest_meal_count(t_args *args)
{
	int	i;
	int	lowest;

	i = 0;
	lowest = INT_MAX;
	while (i < args->num_philo)
	{
		if (args->philo[i].meals_count < lowest)
			lowest = args->philo[i].meals_count;
		i++;
	}
	return (lowest);
}
