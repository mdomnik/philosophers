/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:40:35 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/21 19:05:08 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

#define ERR_ARGS "Error: wrong number of arguments\n"
#define ERR_NUM "Error: invalid argument\n"
#define ERR_MALLOC "Error: malloc failed\n"

typedef struct s_args
{
	pthread_t thread;

	int num_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_eat;
	pthread_mutex_t	monitoring_tread;
	
}				t_args;

typedef struct s_philo
{
	pthread_t		thread_id;
	int philo_num;
	int meals_count;
	int start_time;
	int last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_args			*args;
}				t_philo;

// main.c
t_args pop_philo(char **argv);
t_philo *intialize_philo(t_args init);

// testing.c
void print_philo(t_args philo);

// utils/ft_atoi_philo.c
int		ft_atoi_philo(const char *str, int is_num_eat);
int		ft_isspace_philo(int c);

// utils/error.c
int	ft_strlen(const char *s);
int error_philo(char *message);

#endif