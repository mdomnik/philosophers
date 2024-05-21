/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:55:31 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/21 17:09:23 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

int	ft_atoi_philo(const char *str, int is_num_eat)
{
	long	i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace_philo(str[i]) == 1)
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		sign = sign * (-1);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10;
		result = result + (str[i] - 48);
		i++;
	}
	result = result * sign;
	if (result > 2147483647 || result < -2147483648 || str[i] != '\0' || (is_num_eat == 0 && result < 1))
	{
		printf("Error: invalid argument\n");
		exit(1);
	}
	return ((int)result);
}

int	ft_isspace_philo(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}