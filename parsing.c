/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:45:54 by ncharbog          #+#    #+#             */
/*   Updated: 2025/02/05 10:46:19 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_int(char *str)
{
	if (ft_atol(str) < 1)
	{
		printf("%s\n", NEGATIVE);
		return (1);
	}
	if (ft_atol(str) > 2147483647 || ft_atol(str) < -2147483648
		|| ft_count(ft_atol(str)) > 12)
	{
		printf("%s\n", INT_OVERFLOW);
		return (1);
	}
	return (0);
}

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		if (check_int(argv[i]))
			return (1);
		if (argv[i][j] == '+')
			j++;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("%s\n", DIGIT);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
