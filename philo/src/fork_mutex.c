/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:10:43 by mdomnik           #+#    #+#             */
/*   Updated: 2024/07/03 17:47:28 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	lock_forks(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
		return (1);
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		monitoring_status(philo, S_FORK);
		pthread_mutex_lock(philo->left_fork);
		monitoring_status(philo, S_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		monitoring_status(philo, S_FORK);
		pthread_mutex_lock(philo->right_fork);
		monitoring_status(philo, S_FORK);
	}
	return (0);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
