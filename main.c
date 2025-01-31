/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:13:07 by ncharbog          #+#    #+#             */
/*   Updated: 2025/01/31 17:24:24 by ncharbog         ###   ########.fr       */
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
	t_philo	*cur;

	cur = data->philo;
	while (cur)
	{
		if (pthread_create(&cur->thread, NULL, routine, cur) != 0)
			return (1);
		cur = cur->next;
		if (cur == data->philo)
			break;
	}
	wait_philosophers(data);
	return (0);
}

int	destroy(t_data *data)
{
	t_philo	*cur;

	cur = data->philo;
	if (pthread_mutex_destroy(&cur->fork) != 0)
		return (1);
	cur = cur->next;
	while (cur != data->philo)
	{
		if (pthread_mutex_destroy(&cur->fork) != 0)
			return (1);
		cur = cur->next;
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
		while (argv[i])
		{
			j = 0;
			while (argv[i][j])
			{
				if (!ft_isdigit((int)argv[i][j]))
					return (printf("Error: invalid argument\n"));
				j++;
			}
			i++;
		}
		if (init_data(&data, argv))
			return (1);
		if (launch_threads(&data))
			return (1);
		if (destroy(&data))
			return (1);
		return (0);
	}
	else
		printf("Error: incorrect number of arguments\n");
}
