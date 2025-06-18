/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:20:34 by hfalati           #+#    #+#             */
/*   Updated: 2025/06/18 10:12:31 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philo	**init_philo(t_info *info)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * info->nb_philos);
	if (!philos)
		return (free_error(info), NULL);
	i = 0;
	while (i < info->nb_philos)
	{
		if (!init_single_philo(philos, info, i))
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&philos[i]->meal_time_lock);
				free(philos[i]);
			}
			free(philos);
			return (free_error(info), NULL);
		}
		i++;
	}
	return (philos);
}

pthread_mutex_t	*init_forks(t_info *info)
{
	pthread_mutex_t	*forks;
	unsigned int	i;
	unsigned int	j;

	forks = malloc(sizeof(pthread_mutex_t) * info->nb_philos);
	if (!forks)
	{
		free_error(info);
		return (NULL);
	}
	i = 0;
	j = -1;
	while (i < info->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
		{
			while (++j < i)
				pthread_mutex_destroy(&forks[i]);
			free(forks);
			free_error(info);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

bool	init_mutexes(t_info *info)
{
	info->fork_locks = init_forks(info);
	if (!info->fork_locks)
		return (false);
	if (pthread_mutex_init(&info->sim_stop_lock, 0) != 0)
	{
		free_failure(info);
		return (0);
	}
	if (pthread_mutex_init(&info->write_lock, 0) != 0)
	{
		free_failure(info);
		return (0);
	}
	return (true);
}

t_info	*init_info(int ac, char **av)
{
	int		i;
	t_info	*info;

	i = 1;
	info = malloc(sizeof(t_info));
	if (!info)
		return (0);
	info->nb_philos = ft_str_to_digit(av[i++]);
	info->time_to_die = ft_str_to_digit(av[i++]);
	info->time_to_eat = ft_str_to_digit(av[i++]);
	info->time_to_sleep = ft_str_to_digit(av[i++]);
	info->must_eat_count = -1;
	if (ac == 6)
		info->must_eat_count = ft_str_to_digit(av[i]);
	info->philos = init_philo(info);
	if (!info->philos)
		return (NULL);
	if (!init_mutexes(info))
		return (NULL);
	info->sim_stop = false;
	return (info);
}
