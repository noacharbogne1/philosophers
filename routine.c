/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:12:58 by ncharbog          #+#    #+#             */
/*   Updated: 2025/02/03 17:42:58 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_flag(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->flag_dead == true)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*cur;

	cur = (t_philo *)arg;
	delay(cur->data->start_time);
	while (!big_brother(cur))
	{
		if (cur->id < cur->prev->id)
		{
			if (big_brother(cur))
			 	return (0);
			pthread_mutex_lock(&cur->fork);
			print_status(cur, RIGHT_FORK);
			pthread_mutex_lock(&cur->prev->fork);
			print_status(cur, LEFT_FORK);
		}
		else
		{
			if (big_brother(cur))
				return (0);
			pthread_mutex_lock(&cur->prev->fork);
			print_status(cur, LEFT_FORK);
			pthread_mutex_lock(&cur->fork);
			print_status(cur, RIGHT_FORK);
		}
		pthread_mutex_lock(&cur->meal_lock);
		cur->last_meal = get_time();
		pthread_mutex_unlock(&cur->meal_lock);
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
		if (big_brother(cur))
			return (0);
		print_status(cur, SLEEP);
		usleep(cur->data->time_to_sleep * 1000);
		if (big_brother(cur))
			return (0);
		print_status(cur, THINK);
		usleep(0);
	}
	return (0);
}
