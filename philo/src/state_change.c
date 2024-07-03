/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:21:28 by mdomnik           #+#    #+#             */
/*   Updated: 2024/07/03 19:04:26 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_is_eating(t_philo *philo)
{
	int		success;

	success = 0;
	pthread_mutex_lock(&philo->args->philo_meal_mutex);
	if (philo->meals_count <= philo->local_lowest_meal)
		success = 1;
	pthread_mutex_unlock(&philo->args->philo_meal_mutex);
	if (success == 1)
	{
		if (lock_forks(philo) == 0)
			return (forks_locked_lets_eat(philo));
		else
		{
			if (get_time_diff(philo->args) - philo->time_last_meal
				>= philo->args->time_to_die)
				philo_is_dead(philo);
		}
	}
	return (1);
}

int	forks_locked_lets_eat(t_philo *philo)
{
	long	time_diff;

	time_diff = 0;
	pthread_mutex_lock(&philo->args->philo_meal_mutex);
	time_diff = get_time_diff(philo->args) - philo->time_last_meal;
	if (time_diff >= philo->args->time_to_die)
	{
		pthread_mutex_unlock(&philo->args->philo_meal_mutex);
		philo_is_dead(philo);
		return (1);
	}
	philo->is_eating = 1;
	philo->meals_count++;
	philo->time_last_meal = get_time_diff(philo->args);
	pthread_mutex_unlock(&philo->args->philo_meal_mutex);
	monitoring_status(philo, S_EAT);
	ft_usleep(philo->args->time_to_eat);
	unlock_forks(philo);
	philo->is_eating = 0;
	return (0);
}

void	philo_is_sleeping(t_philo *philo)
{
	monitoring_status(philo, S_SLEEP);
	ft_usleep(philo->args->time_to_sleep);
}

void	philo_is_dead(t_philo *philo)
{
	if (philo->args->num_philo > 1)
		unlock_forks(philo);
	monitoring_status(philo, S_DIED);
	get_race_values(philo, S_DIED);
}
