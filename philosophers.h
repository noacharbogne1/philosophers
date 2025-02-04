/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:17:30 by ncharbog          #+#    #+#             */
/*   Updated: 2025/02/04 13:54:19 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

enum		e_error
{
	MUTEX_CREATE,
	MUTEX_DESTROY,
	MUTEX_JOIN,
	MUTEX_LOCK,
	MUTEX_UNLOCK,
	INVALID_ARG,
	NB_ARG,
	THREAD_CREATE,
};

enum		e_status
{
	RIGHT_FORK,
	LEFT_FORK,
	EAT,
	SLEEP,
	THINK,
	DIED,
};

typedef	struct	s_data t_data;

typedef	struct	s_philo
{
	pthread_t			thread;
	pthread_mutex_t		fork;
	unsigned int		id;
	time_t				last_meal;
	time_t				timestamp;
	unsigned int		nb_ate;
	pthread_mutex_t		meal_lock;
	t_data				*data;
	struct	s_philo		*next;
	struct	s_philo		*prev;
}				t_philo;

typedef	struct	s_data
{
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	unsigned int		nb_must_eat;
	time_t				start_time;
	bool				stop_sim;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		dead_lock;
	t_philo	*philo;
}	t_data;

int	destroy(t_data *data);
int	launch_threads(t_data *data);
int	wait_philosophers(t_data *data);
int	check_sim_status(t_data *data);

void	*big_brother(void *arg);

// init.c //
int	create_philosophers(t_data *data, char **argv);
int	init_data(t_data *data, char **argv);

// routine.c //
void	*routine(void *arg);

// utils.c //
int		print_status(t_philo *cur, int status);
time_t		get_time(void);
void	delay(time_t time);
void	free_all(t_data *data);

// utils_libft.c //
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
void	*ft_lstnew_generic(size_t data_size);
void	ft_lstadd_back_generic(void **lst, void *new_node, size_t next_offset);

#endif