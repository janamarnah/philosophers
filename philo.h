/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 18:33:43 by jalamarn          #+#    #+#             */
/*   Updated: 2026/07/18 19:21:05 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	long			meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	long			num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	long			start_time;
	int				stop;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

/* parsing.c */
int		parse_args(int argc, char **argv, t_data *data);

/* init.c */
int		init_data(t_data *data);
void	assign_forks(t_data *data);

/* routine.c */
void	*routine(void *arg);

/* monitor.c */
void	*monitor(void *arg);

/* utils.c */
long	get_time(void);
void	ft_usleep(long ms, t_data *data);
int		is_stopped(t_data *data);
void	set_stop(t_data *data);
void	print_status(t_philo *philo, char *status);

/* utils2.c */
void	cleanup(t_data *data);

#endif
