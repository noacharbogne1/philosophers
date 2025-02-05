/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:13:07 by ncharbog          #+#    #+#             */
/*   Updated: 2025/02/05 10:32:21 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	wait_philosophers(t_data *data)
{
	t_philo	*cur;

	cur = data->philo;
	if (pthread_join(cur->thread, NULL) != 0)
		return (1);
	cur = cur->next;
	while (cur != data->philo)
	{
		if (pthread_join(cur->thread, NULL) != 0)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int	launch_threads(t_data *data)
{
	t_philo		*cur;
	pthread_t	monitor;

	cur = data->philo;
	while (cur)
	{
		if (pthread_create(&cur->thread, NULL, routine, cur) != 0)
			return (1);
		cur = cur->next;
		if (cur == data->philo)
			break;
	}
	if (pthread_create(&monitor, NULL, big_brother, data) != 0)
			return (1);
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	wait_philosophers(data);
	return (0);
}

int	destroy(t_data *data)
{
	t_philo	*cur;

	cur = data->philo;
	while (cur)
	{
		if (pthread_mutex_destroy(&cur->fork) != 0)
			return (1);
		if (pthread_mutex_destroy(&cur->meal_lock) != 0)
			return (1);
		cur = cur->next;
		if (cur == data->philo)
			break;
	}
	if (pthread_mutex_destroy(&data->dead_lock) != 0)
		return (1);
	if (pthread_mutex_destroy(&data->write_lock) != 0)
		return (1);
	free_all(data);
	return (0);
}

int	check_int(char *str)
{
	if (ft_atol(str) < 1)
	{
		printf("%s\n", NEGATIVE);
		return (1);
	}
	if (ft_atol(str) > 2147483647 || ft_atol(str) < -2147483648
		|| ft_count(ft_atol(str)) > 12)
	{
		printf("%s\n", INT_OVERFLOW);
		return (1);
	}
	return (0);
}

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		if (check_int(argv[i]))
			return (1);
		if (argv[i][j] == '+')
			j++;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("%s\n", DIGIT);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	int		j;
	t_data	data;

	i = 1;
	j = 0;
	if (argc >= 5 && argc <= 6)
	{
		if (check_args(argv))
			return (1);
		if (init_data(&data, argv))
			return (1);
		if (launch_threads(&data))
			return (1);
		if (destroy(&data))
			return (1);
		return (0);
	}
	else
		printf("%s\n", NB_ARGUMENTS);
}
