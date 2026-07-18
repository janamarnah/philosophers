/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 18:33:54 by jalamarn          #+#    #+#             */
/*   Updated: 2026/07/18 19:21:48 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

void	ft_usleep(long ms, t_data *data)
{
	long	start;

	start = get_time();
	while (get_time() - start < ms)
	{
		if (is_stopped(data))
			break ;
		usleep(300);
	}
}

int	is_stopped(t_data *data)
{
	int	stopped;

	pthread_mutex_lock(&data->stop_lock);
	stopped = data->stop;
	pthread_mutex_unlock(&data->stop_lock);
	return (stopped);
}

void	set_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_lock);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_lock);
}

void	print_status(t_philo *philo, char *status)
{
	long	elapsed;

	pthread_mutex_lock(&philo->data->print_lock);
	if (!is_stopped(philo->data))
	{
		elapsed = get_time() - philo->data->start_time;
		printf("%ld %d %s\n", elapsed, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}
