/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:12:58 by ncharbog          #+#    #+#             */
/*   Updated: 2025/02/04 13:25:15 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	precise_sleep(t_data *data, time_t sleeping_time)
{
	time_t	start;

	start = get_time();
	while ((get_time() - start) < sleeping_time)
	{
		if (check_sim_status(data))
			return ;
		usleep(1);
	}
}

int	check_sim_status(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->stop_sim == true)
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
	if (cur->id % 2 == 1)
		usleep(500);
	while (!check_sim_status(cur->data))
	{
		if (cur->id < cur->prev->id) // forks
		{
			if (check_sim_status(cur->data))
			 	return (0);
			pthread_mutex_lock(&cur->fork);
			if (check_sim_status(cur->data))
			{
				pthread_mutex_unlock(&cur->fork);
			 	return (0);
			}
			print_status(cur, RIGHT_FORK);
			pthread_mutex_lock(&cur->prev->fork);
			print_status(cur, LEFT_FORK);
		}
		else
		{
			if (check_sim_status(cur->data))
			 	return (0);
			pthread_mutex_lock(&cur->prev->fork);
			if (check_sim_status(cur->data))
			{
				pthread_mutex_unlock(&cur->prev->fork);
				return (0);
			}
			print_status(cur, LEFT_FORK);
			pthread_mutex_lock(&cur->fork);
			print_status(cur, RIGHT_FORK);
		}
		pthread_mutex_lock(&cur->meal_lock);
		cur->last_meal = get_time();
		//cur->nb_ate++;
		pthread_mutex_unlock(&cur->meal_lock); // manger
		print_status(cur, EAT);
		precise_sleep(cur->data, cur->data->time_to_eat * 1000);
		if (cur->id < cur->prev->id) // repose les forks
		{
			pthread_mutex_unlock(&cur->prev->fork);
			pthread_mutex_unlock(&cur->fork);
		}
		else
		{
			pthread_mutex_unlock(&cur->fork);
			pthread_mutex_unlock(&cur->prev->fork);
		}
		if (check_sim_status(cur->data))
		 	return (0);
		print_status(cur, SLEEP); // dormir
		precise_sleep(cur->data, cur->data->time_to_sleep * 1000);
		if (check_sim_status(cur->data))
			return (0);
		print_status(cur, THINK); // penser
		precise_sleep(cur->data, 1);
	}
	return (0);
}
