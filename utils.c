/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:11:08 by ncharbog          #+#    #+#             */
/*   Updated: 2025/02/05 10:43:13 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_status(t_philo *cur, int status)
{
	if (pthread_mutex_lock(&cur->data->write_lock) != 0)
		return (1);
	cur->timestamp = get_time() - cur->data->start_time;
	if (status == RIGHT_FORK || status == LEFT_FORK)
		printf("%li ms | philosopher %u has taken a fork\n",
			cur->timestamp, cur->id);
	else if (status == EAT)
		printf("%li ms | philosopher %u is eating\n", cur->timestamp, cur->id);
	else if (status == SLEEP)
		printf("%li ms | philosopher %u is sleeping\n",
			cur->timestamp, cur->id);
	else if (status == THINK)
		printf("%li ms | philosopher %u is thinking\n",
			cur->timestamp, cur->id);
	else if (status == DIED)
		printf("%li ms | philosopher %u died\n", cur->timestamp, cur->id);
	if (pthread_mutex_unlock(&cur->data->write_lock) != 0)
		return (1);
	return (0);
}

time_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	delay(time_t time)
{
	while (get_time() < time)
		continue ;
}

void	free_all(t_data *data)
{
	t_philo	*cur;
	t_philo	*tmp;
	t_philo	*start;

	cur = data->philo;
	start = data->philo;
	while (cur)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
		if (cur == start)
			break ;
	}
}

int	precise_sleep(t_data *data, time_t sleeping_time)
{
	time_t	start;

	start = get_time();
	while ((get_time() - start) < sleeping_time)
	{
		if (check_sim_status(data))
			return (1);
		usleep(50);
	}
	return (0);
}
