/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 18:33:47 by jalamarn          #+#    #+#             */
/*   Updated: 2026/07/18 19:21:50 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_lock);
	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

static void	*lone_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die, philo->data);
	pthread_mutex_unlock(philo->first_fork);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philo == 1)
		return (lone_philo(philo));
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2 + 1, philo->data);
	while (!is_stopped(philo->data))
	{
		eat(philo);
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, philo->data);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
