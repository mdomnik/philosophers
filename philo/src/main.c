/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:44:22 by mdomnik           #+#    #+#             */
/*   Updated: 2024/07/02 17:15:06 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_args	args;

	(void)argv;
	if (argc < 5 || argc > 6)
	{
		error_philo(ERR_ARGS);
		return (1);
	}
	if (init_args(&args, argv))
	{
		error_philo(ERR_INIT);
		return (1);
	}
	table_routine(&args);
	free_args(&args);
	return (0);
}
