/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:04:54 by mdomnik           #+#    #+#             */
/*   Updated: 2024/07/02 14:23:33 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	monitoring_status(t_philo *philo, int status)
{

	const char *status_msg[5] = {FORK, EAT, SLEEP, THINK, DEAD};

	philo->args->lowest_meal_count = find_lowest_meal_count(philo->args);
	pthread_mutex_lock(&philo->args->monitoring);
	if (philo->args->philo_dead == 1)
	{
		pthread_mutex_unlock(&philo->args->monitoring);
		return ;
	}
	else
	{
		printf("[%ld] ", get_time_diff(philo->args));
		printf("%d %s\n", philo->philo_ID, status_msg[status]);
		pthread_mutex_unlock(&philo->args->monitoring);
	}
	
}

int find_lowest_meal_count(t_args *args)
{
	int	i;
	int	lowest;

	i = 0;
	lowest = args->philo[0].meals_count;
	while (i < args->num_philo)
	{
		if (args->philo[i].meals_count < lowest)
			lowest = args->philo[i].meals_count;
		i++;
	}
	return (lowest);
}