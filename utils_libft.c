/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:47:03 by ncharbog          #+#    #+#             */
/*   Updated: 2025/02/05 10:45:10 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_lstnew_generic(size_t data_size)
{
	void	*new_node;

	new_node = malloc(data_size);
	if (!new_node)
		return (NULL);
	memset(new_node, 0, data_size);
	return (new_node);
}

void	ft_lstadd_back_generic(void **lst, void *new_node, size_t next_offset)
{
	void	*last;
	void	*first;
	void	**next_ptr;
	void	**prev_ptr;

	if (!lst || !new_node)
		return ;
	next_ptr = (void **)((char *)new_node + next_offset);
	prev_ptr = (void **)((char *)new_node + next_offset + sizeof(void *));
	if (*lst == NULL)
	{
		*lst = new_node;
		*next_ptr = new_node;
		*prev_ptr = new_node;
		return ;
	}
	first = *lst;
	last = *(void **)((char *)first + next_offset + sizeof(void *));
	*next_ptr = first;
	*prev_ptr = last;
	*(void **)((char *)last + next_offset) = new_node;
	*(void **)((char *)first + next_offset + sizeof(void *)) = new_node;
}

int	ft_isdigit(int c)
{
	if (!(c >= '0' && c <= '9'))
		return (0);
	return (2048);
}

long	ft_atol(const char *nptr)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_count(long n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n = n * -1;
		count++;
	}
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}
