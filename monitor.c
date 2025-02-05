/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:34:21 by ncharbog          #+#    #+#             */
/*   Updated: 2025/02/05 10:39:39 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_simulation(t_philo *cur)
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
	else if (cur->nb_ate >= cur->data->nb_must_eat
		&& cur->data->nb_must_eat > 0)
	{
		pthread_mutex_unlock(&cur->meal_lock);
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
			if (!stop_simulation(cur))
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
