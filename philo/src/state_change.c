/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:21:28 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/29 17:03:33 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_is_eating(t_philo *philo, struct timeval time)
{
	if (lock_forks(philo) == 0)
	{
		philo->is_eating = 1;
		philo->time_last_meal = get_time_diff(time);
		printf("%ld %d is eating\n", get_time_diff(time), philo->philo_ID);
		philo->meals_count++;
		usleep(philo->args->time_to_eat * 1000);
		unlock_forks(philo);
		philo->is_eating = 0;	
		return (0);
	}
	return (1);
}

void	philo_is_sleeping(t_philo *philo, struct timeval time)
{
	printf("%ld %d is sleeping\n", get_time_diff(time), philo->philo_ID);
	usleep(philo->args->time_to_sleep * 1000);
}

void	philo_is_thinking(t_philo *philo, struct timeval time)
{
	printf("%ld %d is thinking\n", get_time_diff(time), philo->philo_ID);
}

void	philo_is_dead(t_philo *philo, struct timeval time)
{
	printf("%ld %d died\n", get_time_diff(time), philo->philo_ID);
	philo->args->philo_dead = 1;
}