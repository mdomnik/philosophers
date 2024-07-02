/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:42:10 by mdomnik           #+#    #+#             */
/*   Updated: 2024/07/02 16:16:53 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_philo(t_args philo)
{
	int	i;

	printf("Number of philosophers: %d\n", philo.num_philo);
	printf("Time to die: %d\n", philo.time_to_die);
	printf("Time to eat: %d\n", philo.time_to_eat);
	printf("Time to sleep: %d\n", philo.time_to_sleep);
	printf("Number of times each philosopher must eat: %d\n", philo.num_eat);
	printf("Philo dead: %d\n", philo.philo_dead);
	i = 0;
	while (i < philo.num_philo)
	{
		printf("====================================\n");
		printf("philo[%d].id: %d\n", i, philo.philo[i].philo_id);
		printf("------------------------------------\n");
		printf("philo[%d].time_last_meal: %d\n",
			i, philo.philo[i].time_last_meal);
		printf("philo[%d].is_eating: %d\n", i, philo.philo[i].is_eating);
		printf("philo[%d].meals_count: %d\n", i, philo.philo[i].meals_count);
		printf("philo[%d].left_fork: %p\n", i, philo.philo[i].left_fork);
		printf("philo[%d].right_fork: %p\n", i, philo.philo[i].right_fork);
		i++;
	}
}
