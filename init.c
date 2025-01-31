/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:10:19 by ncharbog          #+#    #+#             */
/*   Updated: 2025/01/31 17:17:03 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_philosophers(t_data *data, char **argv)
{
	t_philo			*new;
	int				nb_philos;
	int				i;

	data->philo = NULL;
	nb_philos = ft_atoi(argv[1]);
	i = 0;
	while (i < nb_philos)
	{
		new = (t_philo *)ft_lstnew_generic(sizeof(t_philo));
		if (!new)
			return (1);
		new->id = 1 + i;
		if (pthread_mutex_init(&new->fork, NULL) != 0)
			return (1);
		new->data = data;
		new->next = NULL;
		new->prev = NULL;
		ft_lstadd_back_generic((void **)&data->philo, new,
			((size_t)(&((t_philo *)0)->next)));
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->nb_must_eat = ft_atoi(argv[5]);
	data->start_time = get_time() + data->time_to_die * 10;
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (1);
	if (create_philosophers(data, argv))
		return (1);
	return (0);
}
