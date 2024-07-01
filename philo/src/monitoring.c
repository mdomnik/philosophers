/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:04:54 by mdomnik           #+#    #+#             */
/*   Updated: 2024/07/01 18:03:18 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	monitoring_status(t_philo *philo, int status)
{
	const char *status_msg[4] = {EAT, SLEEP, THINK, DEAD};

	pthread_mutex_lock(&philo->args->monitoring);
	if (philo->args->terminate == 1)
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