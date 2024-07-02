/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:57:38 by mdomnik           #+#    #+#             */
/*   Updated: 2024/07/02 18:51:20 by mdomnik          ###   ########.fr       */
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
	int				philo_dead;

	philo = (t_philo *)arg;
	args = philo->args;
	if (philo->philo_id % 2 == 0)
		ft_usleep(100);
	while (1)
	{
		pthread_mutex_lock(&args->philo_dead_mutex);
		philo_dead = args->philo_dead;
		pthread_mutex_unlock(&args->philo_dead_mutex);
		if (philo_dead == 1)
			break ;
		if (args->num_eat != -1 && philo->meals_count >= args->num_eat)
			break ;
		if (philo_is_eating(philo) == 0)
		{
			philo_is_sleeping(philo);
			monitoring_status(philo, S_THINK);
		}
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
