/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:12:58 by ncharbog          #+#    #+#             */
/*   Updated: 2025/02/05 09:34:34 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	take_forks(t_philo *cur)
{
	pthread_mutex_lock(&cur->fork);
	if (check_sim_status(cur->data))
	{
		pthread_mutex_unlock(&cur->fork);
		return (0);
	}
	print_status(cur, RIGHT_FORK);
	if (cur->prev != cur)
		pthread_mutex_lock(&cur->prev->fork);
	else
	{
		pthread_mutex_unlock(&cur->fork);
		return (0);
	}
	if (check_sim_status(cur->data))
	{
		pthread_mutex_unlock(&cur->prev->fork);
		return (0);
	}
	print_status(cur, LEFT_FORK);
	return (1);
}

int	lunch_time(t_philo *cur)
{
	pthread_mutex_lock(&cur->meal_lock);
	cur->last_meal = get_time();
	cur->nb_ate++;
	pthread_mutex_unlock(&cur->meal_lock);
	if (check_sim_status(cur->data))
	{
		pthread_mutex_unlock(&cur->prev->fork);
		return (0);
	}
	print_status(cur, EAT);
	precise_sleep(cur->data, cur->data->time_to_eat);
	pthread_mutex_unlock(&cur->prev->fork);
	pthread_mutex_unlock(&cur->fork);
	return (1);
}

int	sleep_think(t_philo *cur)
{
	if (check_sim_status(cur->data))
			return (0);
	print_status(cur, SLEEP);
	if (precise_sleep(cur->data, cur->data->time_to_sleep))
		return (0);
	if (check_sim_status(cur->data))
		return (0);
	print_status(cur, THINK);
	if (precise_sleep(cur->data, 1))
		return (0);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*cur;

	cur = (t_philo *)arg;
	delay(cur->data->start_time);
	pthread_mutex_lock(&cur->meal_lock);
	cur->last_meal = get_time();
	pthread_mutex_unlock(&cur->meal_lock);
	if (cur->id % 2 == 1)
		usleep(500);
	while (!check_sim_status(cur->data))
	{
		if (!take_forks(cur))
			return (0);
		if (!lunch_time(cur))
			return (0);
		if (!sleep_think(cur))
			return (0);
	}
	return (0);
}
