/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 18:33:32 by jalamarn          #+#    #+#             */
/*   Updated: 2026/07/18 19:21:52 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data)
{
	int		i;
	long	elapsed;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&data->philos[i].meal_lock);
		elapsed = get_time() - data->philos[i].last_meal;
		pthread_mutex_unlock(&data->philos[i].meal_lock);
		if (elapsed > data->time_to_die)
		{
			pthread_mutex_lock(&data->print_lock);
			set_stop(data);
			printf("%ld %d died\n", get_time() - data->start_time,
				data->philos[i].id);
			pthread_mutex_unlock(&data->print_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_all_ate(t_data *data)
{
	int	i;
	int	full;

	if (data->must_eat == -1)
		return (0);
	i = 0;
	full = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&data->philos[i].meal_lock);
		if (data->philos[i].meals_eaten >= data->must_eat)
			full++;
		pthread_mutex_unlock(&data->philos[i].meal_lock);
		i++;
	}
	if (full == data->num_philo)
		return (set_stop(data), 1);
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data))
			return (NULL);
		if (check_all_ate(data))
			return (NULL);
		usleep(500);
	}
}
