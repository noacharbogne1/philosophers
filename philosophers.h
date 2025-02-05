/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:17:30 by ncharbog          #+#    #+#             */
/*   Updated: 2025/02/05 09:24:14 by ncharbog         ###   ########.fr       */
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

// errors messages

# define DIGIT "Error: invalid characters in argument"
//# define INT_OVERFLOW "Error: argument overflows INT limits"
# define NEGATIVE "Error: argument can't be a negative number"
# define NB_ARGUMENTS "Error: invalid number of arguments"
# define NB_PHILOS "Error: must be at least one philosopher"

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
int			print_status(t_philo *cur, int status);
time_t		get_time(void);
void		delay(time_t time);
void		free_all(t_data *data);
int			precise_sleep(t_data *data, time_t sleeping_time);

// utils_libft.c //
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
void	*ft_lstnew_generic(size_t data_size);
void	ft_lstadd_back_generic(void **lst, void *new_node, size_t next_offset);

#endif