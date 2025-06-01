/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:20:16 by hfalati           #+#    #+#             */
/*   Updated: 2025/06/01 13:35:14 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	start_dinner(t_info *info)
{
	unsigned int	i;

	i = 0;
	while (i < info->nb_philos)
	{
		if (pthread_create(&info->philos[i]->thread, NULL, &philosopher, info->philos[i]) != 0)
			return (error_failure(info), 0);
        i++;
	}
	if (info->nb_philos > 1)
	{
		if (pthread_create(&info->manage_philos, NULL, &manage_philos, info) != 0)
			return (error_failure(info), 0);
    }
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
    t_info  *info;

    info = NULL;
    if (ac < 5 || ac > 6)
        return (1);
    if (!handle_input(ac, av))
        return (1);
    info = init_info(ac, av);
    if (!info)
		return (1);
	if (!start_dinner(info))
		return (1);
	stop_dinner(info);
	return (0);
}