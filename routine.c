/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:12:58 by ncharbog          #+#    #+#             */
/*   Updated: 2025/01/31 17:38:58 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_status(t_philo *cur)
{
	if (cur->last_meal > cur->data->time_to_die)
	{
		print_status(cur, DIED);
		return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*cur;

	cur = (t_philo *)arg;
	delay(cur->data->start_time);
	while (check_status(cur) == 0)
	{
		if (cur->id < cur->prev->id)
		{
			pthread_mutex_lock(&cur->fork);
			print_status(cur, RIGHT_FORK);
			pthread_mutex_lock(&cur->prev->fork);
			print_status(cur, LEFT_FORK);
		}
		else
		{
			pthread_mutex_lock(&cur->prev->fork);
			print_status(cur, LEFT_FORK);
			pthread_mutex_lock(&cur->fork);
			print_status(cur, RIGHT_FORK);
		}
		cur->last_meal = get_time() - cur->data->start_time;
		print_status(cur, EAT);
		usleep(cur->data->time_to_eat * 1000);
		if (cur->id < cur->prev->id)
		{
			pthread_mutex_unlock(&cur->prev->fork);
			pthread_mutex_unlock(&cur->fork);
		}
		else
		{
			pthread_mutex_unlock(&cur->fork);
			pthread_mutex_unlock(&cur->prev->fork);
		}
		print_status(cur, SLEEP);
		usleep(cur->data->time_to_sleep * 1000);
		print_status(cur, THINK);
		usleep(1);
	}
	return (0);
}
