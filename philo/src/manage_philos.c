/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:20:28 by hfalati           #+#    #+#             */
/*   Updated: 2025/06/20 10:03:11 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_sim_stop_flag(t_info *info, bool state)
{
	pthread_mutex_lock(&info->sim_stop_lock);
	info->sim_stop = state;
	pthread_mutex_unlock(&info->sim_stop_lock);
}

bool	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_ms();
	if ((time - philo->last_meal) > philo->info->time_to_die)
	{
		set_sim_stop_flag(philo->info, true);
		write_status(philo, true, DIED);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (true);
	}
	return (false);
}

bool	end_condition_reached(t_info *info)
{
	unsigned int	i;
	bool			ate_enough;

	ate_enough = true;
	i = 0;
	while (i < info->nb_philos)
	{
		pthread_mutex_lock(&info->philos[i]->meal_time_lock);
		if (kill_philo(info->philos[i]))
			return (true);
		if (info->must_eat_count != -1)
			if (info->philos[i]->times_ate < (unsigned int)info->must_eat_count)
				ate_enough = false;
		pthread_mutex_unlock(&info->philos[i]->meal_time_lock);
		i++;
	}
	if (info->must_eat_count != -1 && ate_enough == true)
	{
		set_sim_stop_flag(info, true);
		return (true);
	}
	return (false);
}

void	*manage_philos(void *data)
{
	t_info	*info;

	info = (t_info *)data;
	if (info->must_eat_count == 0)
		return (NULL);
	set_sim_stop_flag(info, false);
	while (true)
	{
		if (end_condition_reached(info) == true)
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
