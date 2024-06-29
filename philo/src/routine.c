/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:57:38 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/29 18:18:49 by mdomnik          ###   ########.fr       */
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
	long			time_diff;
	struct	timeval	time;

	philo = (t_philo *)arg;
	args = philo->args;
	gettimeofday(&time, NULL);

	while (args->philo_dead == 0)
	{
		time_diff = get_time_diff(time) - philo->time_last_meal;
		printf("time_diff: %ld, philo: %d\n", time_diff, philo->philo_ID);
		if (time_diff > philo->args->time_to_die)
			philo_is_dead(philo, time);
		if (philo_is_eating(philo, time) == 0)
		{
			philo_is_sleeping(philo, time);
			philo_is_thinking(philo, time);
		}
	}
	return (NULL);
}

long	get_time_diff(struct timeval time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - time.tv_sec) * 1000 + (current_time.tv_usec - time.tv_usec) / 1000);
}

int		lock_forks(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
		return (1);
	if (philo->philo_ID % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		return (0);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		return (0);
	}
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}