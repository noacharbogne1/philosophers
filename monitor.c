/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:34:21 by ncharbog          #+#    #+#             */
/*   Updated: 2025/02/17 13:37:00 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_simulation_nb(t_philo *cur)
{
	t_philo	*root;

	root = cur;
	if (cur->nb_ate >= cur->data->nb_must_eat
		&& cur->data->nb_must_eat > 0)
	{
		pthread_mutex_unlock(&cur->meal_lock);
		while (cur)
		{
			if (cur->nb_ate < cur->data->nb_must_eat)
				return (1);
			cur = cur->next;
			if (cur == root)
				break ;
		}
		pthread_mutex_lock(&cur->data->dead_lock);
		cur->data->stop_sim = true;
		pthread_mutex_unlock(&cur->data->dead_lock);
		return (0);
	}
	return (1);
}

int	stop_simulation_time(t_philo *cur)
{
	if ((get_time() - cur->last_meal) >= cur->data->time_to_die)
	{
		pthread_mutex_unlock(&cur->meal_lock);
		print_status(cur, DIED);
		pthread_mutex_lock(&cur->data->dead_lock);
		cur->data->stop_sim = true;
		pthread_mutex_unlock(&cur->data->dead_lock);
		return (0);
	}
	return (1);
}

void	*big_brother(void *arg)
{
	t_philo	*cur;

	cur = ((t_data *)arg)->philo;
	delay(cur->data->start_time + 1);
	while (1)
	{
		cur = cur->data->philo;
		while (cur)
		{
			pthread_mutex_lock(&cur->meal_lock);
			if (!stop_simulation_time(cur))
				return (NULL);
			else if (!stop_simulation_nb(cur))
				return (NULL);
			else
				pthread_mutex_unlock(&cur->meal_lock);
			cur = cur->next;
			if (cur == cur->data->philo)
				break ;
		}
	}
	return (NULL);
}
