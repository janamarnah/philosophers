/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 18:33:27 by jalamarn          #+#    #+#             */
/*   Updated: 2026/07/18 19:21:23 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_simulation(t_data *data)
{
	pthread_t	watcher;
	int			i;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, routine,
				&data->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&watcher, NULL, monitor, data) != 0)
		return (1);
	i = 0;
	while (i < data->num_philo)
		pthread_join(data->philos[i++].thread, NULL);
	pthread_join(watcher, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s n_philo t_die t_eat t_sleep [n_meals]\n", argv[0]);
		return (1);
	}
	if (parse_args(argc, argv, &data) != 0)
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	if (init_data(&data) != 0)
	{
		printf("Error: initialization failed\n");
		return (1);
	}
	assign_forks(&data);
	if (data.must_eat != 0)
		start_simulation(&data);
	cleanup(&data);
	return (0);
}
