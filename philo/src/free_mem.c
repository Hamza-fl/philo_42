/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:20:21 by hfalati           #+#    #+#             */
/*   Updated: 2025/06/18 10:12:31 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_mutexes(t_info *info)
{
	unsigned int	i;

	i = 0;
	while (&info->fork_locks[i] && i < info->nb_philos)
	{
		pthread_mutex_destroy(&info->fork_locks[i]);
		pthread_mutex_destroy(&info->philos[i]->meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&info->write_lock);
	pthread_mutex_destroy(&info->sim_stop_lock);
}

void	*free_info(t_info *info)
{
	unsigned int	i;

	if (!info)
		return (NULL);
	if (info->fork_locks != NULL)
		free(info->fork_locks);
	if (info->philos != NULL)
	{
		i = 0;
		while (i < info->nb_philos)
		{
			if (info->philos[i] != NULL)
				free(info->philos[i]);
			i++;
		}
		free(info->philos);
	}
	free(info);
	return (NULL);
}

int	free_failure(t_info *info)
{
	if (info != NULL)
		destroy_mutexes(info);
	if (info != NULL)
		free_info(info);
	return (0);
}

void	*free_error(t_info *info)
{
	if (info != NULL)
		destroy_mutexes(info);
	if (info != NULL)
		free_info(info);
	return (NULL);
}
