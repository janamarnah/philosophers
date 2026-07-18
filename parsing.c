/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 18:33:37 by jalamarn          #+#    #+#             */
/*   Updated: 2026/07/18 19:21:35 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long	ft_atol(char *s)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	if (s[i] == '+')
		i++;
	while (s[i])
	{
		result = result * 10 + (s[i] - '0');
		if (result > 2147483647)
			return (-1);
		i++;
	}
	return (result);
}

static int	valid_value(char *s, long *dst, long min)
{
	long	value;

	if (!is_number(s))
		return (1);
	value = ft_atol(s);
	if (value < min)
		return (1);
	*dst = value;
	return (0);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	data->must_eat = -1;
	if (valid_value(argv[1], &data->num_philo, 1))
		return (1);
	if (valid_value(argv[2], &data->time_to_die, 1))
		return (1);
	if (valid_value(argv[3], &data->time_to_eat, 1))
		return (1);
	if (valid_value(argv[4], &data->time_to_sleep, 1))
		return (1);
	if (argc == 6 && valid_value(argv[5], &data->must_eat, 0))
		return (1);
	return (0);
}
