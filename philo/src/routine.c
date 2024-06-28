/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:57:38 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/28 19:01:11 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	get_time_diff(struct timeval time);
void	lock_forks(t_philo *philo);
void	unlock_forks(t_philo *philo);
void	*routine(t_args *args, int i ,struct timeval time);


void	table_routine(t_args *args)
{
	struct	timeval	time;

	gettimeofday(&time, NULL);
	while (args->philo_dead == 0)
	{
		int i;
		
		i = 0;
		while (i < args->num_philo)
		{
			pthread_create(args->philo[i].thread, NULL, routine(args, i ,time), NULL);
			i++;
		}
	}
}

void	*routine(t_args *args, int i , struct timeval time)
{
	if (get_time_diff(time) - args->philo[i].time_last_meal > args->time_to_die)
	{
		args->philo_dead = 1;
		printf("%ld %d died\n", get_time_diff(time), args->philo[i].philo_ID);
	}
	lock_forks(&args->philo[i]);
	args->philo[i].is_eating = 1;
	args->philo[i].time_last_meal = get_time_diff(time);
	printf("%ld %d is eating\n", get_time_diff(time), args->philo[i].philo_ID);
	usleep(args->time_to_eat * 1000);
	args->philo[i].is_eating = 0;
	unlock_forks(&args->philo[i]);
	printf("%ld %d is sleeping\n", get_time_diff(time), args->philo[i].philo_ID);
	usleep(args->time_to_sleep * 1000);
	printf("%ld %d is thinking\n", get_time_diff(time), args->philo[i].philo_ID);
	return (NULL);
}

long	get_time_diff(struct timeval time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - time.tv_sec) * 1000 + (current_time.tv_usec - time.tv_usec) / 1000);
}

void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}