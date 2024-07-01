/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:57:38 by mdomnik           #+#    #+#             */
/*   Updated: 2024/07/01 18:10:15 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	table_routine(t_args *args)
{
	int i;
	int	ret;
	
	i = 0;
	ret = 0;
	while (i < args->num_philo)
	{
		ret = pthread_create(&args->philo[i].thread, NULL, philosopher_thread, &args->philo[i]);
		if (ret != 0)
			error_philo(ERR_THREAD);
		i++;
	}
	i = 0;
	while (i < args->num_philo)
	{
		pthread_join(args->philo[i].thread, NULL);
		i++;
	}
}

void	*philosopher_thread(void *arg)
{
	t_philo			*philo;
	t_args			*args;

	philo = (t_philo *)arg;
	args = philo->args;

	while (args->philo_dead == 0)
	{
		if (args->num_eat != -1 && philo->meals_count >= args->num_eat)
			break ;
		if (philo_is_eating(philo) == 0)
		{
			philo_is_sleeping(philo);
			philo_is_thinking(philo);
		}
		// else
		// 	if (get_time_diff(time) - philo->time_last_meal > philo->args->time_to_die)
		// 		philo_is_dead(philo, time);
		if (philo->args->philo_dead == 1)
			break ;
	}
	return (NULL);
}

long	get_time_diff(t_args *args)
{
	struct timeval	current_time;
	long			current_time_ms;
	long			ret;

	gettimeofday(&current_time, NULL);
	current_time_ms = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	ret = current_time_ms - args->start_time;
	return (ret);
}

int		lock_forks(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
		return (1);
	if (philo->philo_ID % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	return (0);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}