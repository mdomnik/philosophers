/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:21:28 by mdomnik           #+#    #+#             */
/*   Updated: 2024/07/01 18:03:09 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_is_eating(t_philo *philo)
{
	long	time_diff;

	time_diff = 0;
	if (lock_forks(philo) == 0)
	{
		time_diff = get_time_diff(philo->args) - philo->time_last_meal;
		if (time_diff > philo->args->time_to_die)
		{
			philo_is_dead(philo);
			return (1);
		}
		philo->is_eating = 1;
		philo->meals_count++;
		philo->time_last_meal = get_time_diff(philo->args);
		monitoring_status(philo, S_EAT);
		usleep(philo->args->time_to_eat * 1000);
		unlock_forks(philo);
		philo->is_eating = 0;	
		return (0);
	}
	return (1);
}

void	philo_is_sleeping(t_philo *philo)
{
	monitoring_status(philo, S_SLEEP);
	usleep(philo->args->time_to_sleep * 1000);
}

void	philo_is_thinking(t_philo *philo)
{
	monitoring_status(philo, S_THINK);
}

void	philo_is_dead(t_philo *philo)
{
	monitoring_status(philo, S_DIED);
	unlock_forks(philo);
	philo->args->philo_dead = 1;
}