/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:20:16 by hfalati           #+#    #+#             */
/*   Updated: 2025/06/18 10:12:31 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	start_philo_threads(t_info *info)
{
	unsigned int	i;

	i = 0;
	while (i < info->nb_philos)
	{
		if (pthread_create(&info->philos[i]->thread, NULL, \
			&philosopher, info->philos[i]) != 0)
		{
			set_sim_stop_flag(info, true);
			while (i > 0)
			{
				i--;
				pthread_join(info->philos[i]->thread, NULL);
			}
			return (free_failure(info), false);
		}
		i++;
	}
	return (true);
}

bool	start_manager_thread(t_info *info)
{
	unsigned int	i;

	if (info->nb_philos <= 1)
		return (true);
	if (pthread_create(&info->manage_philos, NULL, \
		&manage_philos, info) != 0)
	{
		set_sim_stop_flag(info, true);
		i = 0;
		while (i < info->nb_philos)
		{
			pthread_join(info->philos[i]->thread, NULL);
			i++;
		}
		return (free_failure(info), false);
	}
	return (true);
}

bool	start_dinner(t_info *info)
{
	if (!start_philo_threads(info))
		return (false);
	if (!start_manager_thread(info))
		return (false);
	return (true);
}

void	stop_dinner(t_info	*info)
{
	unsigned int	i;

	i = 0;
	while (i < info->nb_philos)
	{
		pthread_join(info->philos[i]->thread, NULL);
		i++;
	}
	if (info->nb_philos > 1)
		pthread_join(info->manage_philos, NULL);
	destroy_mutexes(info);
	free_info(info);
}

int	main(int ac, char **av)
{
	t_info	*info;

	info = NULL;
	if (ac < 5 || ac > 6)
	{
		return (ft_putstr_fd("Usage: ./philo number_of_philos time_to_die \
time_to_eat time_to_sleep [must_eat_count]\n", 2), 1);
	}
	if (!handle_input(ac, av))
	{
		return (ft_putstr_fd("Usage: ./philo number_of_philos time_to_die \
time_to_eat time_to_sleep [must_eat_count]\n", 2), 1);
	}
	info = init_info(ac, av);
	if (!info)
	{
		return (ft_putstr_fd("Usage: ./philo number_of_philos time_to_die \
time_to_eat time_to_sleep [must_eat_count]\n", 2), 1);
	}
	if (!start_dinner(info))
		return (ft_putstr_fd("fail to create thread\n", 2), 1);
	stop_dinner(info);
	return (0);
}
