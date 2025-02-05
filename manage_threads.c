/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:46:30 by ncharbog          #+#    #+#             */
/*   Updated: 2025/02/05 15:44:08 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			break ;
	}
	if (pthread_create(&monitor, NULL, big_brother, data) != 0)
		return (1);
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	if (wait_philosophers(data))
		return (1);
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
			break ;
	}
	if (pthread_mutex_destroy(&data->dead_lock) != 0)
		return (1);
	if (pthread_mutex_destroy(&data->write_lock) != 0)
		return (1);
	free_all(data);
	return (0);
}
