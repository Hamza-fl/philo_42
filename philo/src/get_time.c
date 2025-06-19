/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:20:25 by hfalati           #+#    #+#             */
/*   Updated: 2025/06/19 10:30:54 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	check_if_end(t_info *info)
{
	bool	r;

	r = false;
	pthread_mutex_lock(&info->sim_stop_lock);
	if (info->sim_stop == true)
		r = true;
	pthread_mutex_unlock(&info->sim_stop_lock);
	return (r);
}

void	philo_sleep(t_info *info, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_ms() + sleep_time;
	while (get_time_ms() < (wake_up - 1))
	{
		if (check_if_end(info))
			break ;
		usleep(500);
	}
}

time_t	get_time_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
