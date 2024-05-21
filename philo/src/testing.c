/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:42:10 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/21 18:33:24 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void print_philo(t_args philo)
{
	printf("Number of philosophers: %d\n", philo.num_philo);
	printf("Time to die: %d\n", philo.time_to_die);
	printf("Time to eat: %d\n", philo.time_to_eat);
	printf("Time to sleep: %d\n", philo.time_to_sleep);
	printf("Number of times each philosopher must eat: %d\n", philo.num_eat);
}