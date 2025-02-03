/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:34:21 by ncharbog          #+#    #+#             */
/*   Updated: 2025/02/03 17:35:29 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	big_brother(void *arg)
{
	t_philo	*cur;

	cur = (t_philo *)arg;
	cur = cur->data->philo;
	while (cur)
	{
		pthread_mutex_lock(&cur->data->dead_lock);
		if (cur->data->flag_dead == true)
		{
			pthread_mutex_unlock(&cur->data->dead_lock);
			return (1);
		}
		pthread_mutex_unlock(&cur->data->dead_lock);
		pthread_mutex_lock(&cur->meal_lock);
		if ((get_time() - cur->last_meal) > cur->data->time_to_die)
		{
			pthread_mutex_unlock(&cur->meal_lock);
			print_status(cur, DIED);
			pthread_mutex_lock(&cur->data->dead_lock);
			cur->data->flag_dead = true;
			pthread_mutex_unlock(&cur->data->dead_lock);
			return (1);
		}
		pthread_mutex_unlock(&cur->meal_lock);
		cur = cur->next;
		if (cur == cur->data->philo)
			break ;
	}
	return (0);
}

// void	*big_brother(void *arg)
// {
// 	t_data	*data;
// 	t_philo	*cur;

// 	data = (t_data *)arg;
// 	cur = data->philo;
// 	while (1)
// 	{
// 		cur = data->philo;
// 		while (cur)
// 		{
// 			pthread_mutex_lock(&data->dead_lock);
// 			if (data->flag_dead == true)
// 			{
// 				pthread_mutex_unlock(&data->dead_lock);
// 				return (NULL);
// 			}
// 			pthread_mutex_unlock(&data->dead_lock);
// 			pthread_mutex_lock(&cur->meal_lock);
// 			if (cur->last_meal > data->time_to_die)
// 			{
// 				pthread_mutex_unlock(&cur->meal_lock);
// 				print_status(cur, DIED);
// 				pthread_mutex_lock(&data->dead_lock);
// 				data->flag_dead = true;
// 				pthread_mutex_unlock(&data->dead_lock);
// 				return (NULL);
// 			}
// 			pthread_mutex_unlock(&cur->meal_lock);
// 			cur = cur->next;
// 			if (cur == data->philo)
// 				break ;
// 		}
// 		usleep(1000);
// 	}
// 	return (NULL);
// }
