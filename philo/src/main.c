/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:44:22 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/21 19:06:23 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_args 	init;
	t_philo *philo;
	pthread_mutex_t *forks;

	(void)forks;
	(void)argv;
	if (argc < 5 || argc > 6)
	{
		printf(ERR_ARGS);
		return (1);
	}
	else
		init = pop_philo(argv);
	philo = intialize_philo(init);
	
	free(philo);
	print_philo(init);
	return (0);
}

/**
 * Creates a `t_philo` struct and initializes its fields based on the command line arguments.
 *
 * @param argv The command line arguments.
 * @return The initialized `t_philo` struct.
 */
t_args pop_philo(char **argv)
{
	t_args args;
	args.num_philo = ft_atoi_philo(argv[1], 0);
	args.time_to_die = ft_atoi_philo(argv[2], 0);
	args.time_to_eat = ft_atoi_philo(argv[3], 0);
	args.time_to_sleep = ft_atoi_philo(argv[4], 0);
	if (argv[5])
		args.num_eat = ft_atoi_philo(argv[5], 1);
	else
		args.num_eat = -1;
	return (args);
}

t_philo *intialize_philo(t_args init)
{
	t_philo *philo;
	int i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * init.num_philo);
	if (!philo)
		error_philo(ERR_MALLOC);
	
	while (i < init.num_philo)
	{
		philo[i].philo_num = i + 1;
		philo[i].meals_count = 0;
		philo[i].start_time = 0;
		philo[i].last_meal_time = 0;
		philo[i].args = &init;
		i++;
	}
	return (philo);
}