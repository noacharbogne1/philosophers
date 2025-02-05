/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:13:07 by ncharbog          #+#    #+#             */
/*   Updated: 2025/02/05 10:47:59 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int		i;
	int		j;
	t_data	data;

	i = 1;
	j = 0;
	if (argc >= 5 && argc <= 6)
	{
		if (check_args(argv))
			return (1);
		if (init_data(&data, argv))
			return (1);
		if (launch_threads(&data))
			return (1);
		if (destroy(&data))
			return (1);
		return (0);
	}
	else
		printf("%s\n", NB_ARGUMENTS);
}
