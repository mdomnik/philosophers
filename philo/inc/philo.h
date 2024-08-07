/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:40:35 by mdomnik           #+#    #+#             */
/*   Updated: 2024/07/03 16:28:19 by mdomnik          ###   ########.fr       */
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
# include <limits.h>

# define ERR_ARGS "Error: wrong number of arguments\n"
# define ERR_INIT "Error: initialization failed\n"
# define ERR_MUTEX_INIT "Error: mutex initialization failed\n"
# define ERR_NUM "Error: invalid argument\n"
# define ERR_MALLOC "Error: malloc failed\n"
# define ERR_THREAD "Error: thread creation failed\n"

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "died"

typedef enum e_status
{
	S_FORK,
	S_EAT,
	S_SLEEP,
	S_THINK,
	S_DIED
}				t_status;

typedef struct s_philo
{
	int				philo_id;
	int				is_eating;
	int				meals_count;
	int				time_last_meal;
	int				local_philo_dead;
	int				local_lowest_meal;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	struct s_args	*args;

}				t_philo;

typedef struct s_args
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eat;
	int				philo_dead;
	int				lowest_meal_count;
	long			start_time;

	t_philo			*philo;
	pthread_mutex_t	philo_meal_mutex;
	pthread_mutex_t	monitoring;
	pthread_mutex_t	*fork_locks;

}				t_args;

//fork_mutex.c
int		lock_forks(t_philo *philo);
void	unlock_forks(t_philo *philo);

//init.c
int		init_args(t_args *args, char **argv);
int		init_fork_locks(t_args *args);
int		init_monitoring_thread(t_args *args);
int		init_philo(t_args *args);

//monitoring.c
void	monitoring_status(t_philo *philo, int status);
int		find_lowest_meal_count(t_args *args);

//routine.c
void	table_routine(t_args *args);
void	*philosopher_thread(void *arg);
long	get_time_diff(t_args *args);
void	get_race_values(t_philo *philo, int status);
void	meal_race_value(t_philo *philo);

//state_change.c
int		philo_is_eating(t_philo *philo);
int		forks_locked_lets_eat(t_philo *philo);
void	philo_is_sleeping(t_philo *philo);
void	philo_is_dead(t_philo *philo);

// utils/ft_atoi_philo.c
int		ft_atoi_philo(const char *str, long i);

//utils/error.c
int		error_philo(char *message);
int		free_args(t_args *args);

//utils/ft_usleep.c
void	ft_usleep(long time);
long	current_time(void);

#endif