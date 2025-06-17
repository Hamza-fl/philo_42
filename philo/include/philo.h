/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:20:47 by hfalati           #+#    #+#             */
/*   Updated: 2025/06/17 17:01:44 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo	t_philo;

typedef struct s_info
{
	time_t			start_time;
	unsigned int	nb_philos;
	pthread_t		manage_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	bool			sim_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philo			**philos;
}	t_info;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		times_ate;
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_lock;
	time_t				last_meal;
	t_info				*info;
}	t_philo;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	FORK = 4,
}	t_status;

bool	handle_input(int ac, char **av);
int		ft_str_to_digit(char *str);
void	*error_null(t_info *info);
int		error_failure(t_info *info);
void	destroy_mutexes(t_info *info);
void	*free_info(t_info *info);
t_info	*init_info(int ac, char **av);
void	all_philo_run(time_t start_time);
time_t	get_time_ms(void);
void	*philosopher(void *data);
void	*manage_philos(void *data);
void	philo_sleep(t_info *info, time_t sleep_time);
bool	check_if_end(t_info *info);
void	write_status(t_philo *philo, bool reaper_report, t_status status);
void	ft_putstr_fd(char *s, int fd);
void	set_sim_stop_flag(t_info *info, bool state);

#endif