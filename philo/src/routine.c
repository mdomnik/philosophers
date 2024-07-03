/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:57:38 by mdomnik           #+#    #+#             */
/*   Updated: 2024/07/03 19:12:02 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	table_routine(t_args *args)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < args->num_philo)
	{
		ret = pthread_create(&args->philo[i].thread, NULL,
				philosopher_thread, &args->philo[i]);
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
	if (philo->philo_id % 2 == 0)
		ft_usleep(1);
	while (philo->local_philo_dead == 0)
	{
		get_race_values(philo, 0);
		meal_race_value(philo);
		if (args->num_eat != -1 && philo->meals_count >= args->num_eat)
			break ;
		if (philo_is_eating(philo) == 0)
		{
			if (args->num_eat != -1 && philo->meals_count >= args->num_eat)
				break ;
			philo_is_sleeping(philo);
			monitoring_status(philo, S_THINK);
			usleep(1);
		}
		usleep(1);
	}
	return (NULL);
}

long	get_time_diff(t_args *args)
{
	struct timeval	current_time;
	long			current_time_ms;
	long			ret;

	gettimeofday(&current_time, NULL);
	current_time_ms
		= (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	ret = current_time_ms - args->start_time;
	return (ret);
}

void	get_race_values(t_philo *philo, int status)
{
	t_args	*args;

	args = philo->args;
	pthread_mutex_lock(&args->monitoring);
	if (status == S_DIED)
		args->philo_dead = 1;
	philo->local_philo_dead = args->philo_dead;
	pthread_mutex_unlock(&args->monitoring);
}

void	meal_race_value(t_philo *philo)
{
	t_args	*args;

	args = philo->args;
	pthread_mutex_lock(&args->philo_meal_mutex);
	args->lowest_meal_count = find_lowest_meal_count(args);
	philo->local_lowest_meal = args->lowest_meal_count;
	pthread_mutex_unlock(&args->philo_meal_mutex);
}
