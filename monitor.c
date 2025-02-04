/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:34:21 by ncharbog          #+#    #+#             */
/*   Updated: 2025/02/04 15:16:48 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*big_brother(void *arg)
{
	t_philo	*cur;

	cur = ((t_data *)arg)->philo;
	delay(cur->data->start_time + 1);
	// pthread_mutex_lock(&cur->meal_lock);
	// pthread_mutex_unlock(&cur->data->dead_lock);
	while (1)
	{
		cur = cur->data->philo;
		while (cur)
		{
			pthread_mutex_lock(&cur->meal_lock);
			if ((get_time() - cur->last_meal) > cur->data->time_to_die)
			{
				//dprintf(2, "philo %d last meal : %ld\n", cur->id, cur->last_meal);
				pthread_mutex_unlock(&cur->meal_lock);
				print_status(cur, DIED);
				pthread_mutex_lock(&cur->data->dead_lock);
				cur->data->stop_sim = true;
				pthread_mutex_unlock(&cur->data->dead_lock);
				return (NULL);
			}
			else
				pthread_mutex_unlock(&cur->meal_lock);
			cur = cur->next;
			if (cur == cur->data->philo)
				break ;
		}
	}
	return (NULL);
}
