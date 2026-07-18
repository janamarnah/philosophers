/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 18:33:20 by jalamarn          #+#    #+#             */
/*   Updated: 2026/07/18 19:21:55 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].meal_lock, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_data(t_data *data)
{
	data->stop = 0;
	if (pthread_mutex_init(&data->stop_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (1);
	if (init_forks(data) != 0)
		return (1);
	if (init_philos(data) != 0)
		return (1);
	return (0);
}

void	assign_forks(t_data *data)
{
	int				i;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

	i = 0;
	while (i < data->num_philo)
	{
		left = &data->forks[i];
		right = &data->forks[(i + 1) % data->num_philo];
		if (data->philos[i].id % 2 == 0)
		{
			data->philos[i].first_fork = right;
			data->philos[i].second_fork = left;
		}
		else
		{
			data->philos[i].first_fork = left;
			data->philos[i].second_fork = right;
		}
		i++;
	}
}
