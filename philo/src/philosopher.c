/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:20:38 by hfalati           #+#    #+#             */
/*   Updated: 2025/06/21 15:26:36 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->fork_locks[philo->fork[0]]);
	write_status(philo, false, FORK);
	pthread_mutex_lock(&philo->info->fork_locks[philo->fork[1]]);
	write_status(philo, false, FORK);
	write_status(philo, false, EATING);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->meal_time_lock);
	philo_sleep(philo->info, philo->info->time_to_eat);
	if (check_if_end(philo->info) == false)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->times_ate += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	write_status(philo, false, SLEEPING);
	pthread_mutex_unlock(&philo->info->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->info->fork_locks[philo->fork[0]]);
	philo_sleep(philo->info, philo->info->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->info->time_to_die - (get_time_ms() \
		- philo->last_meal) - philo->info->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_to_think <= 0)
		time_to_think = 0;
	if (time_to_think >= 1)
		write_status(philo, false, THINKING);
}

void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->fork_locks[philo->fork[0]]);
	write_status(philo, false, FORK);
	philo_sleep(philo->info, philo->info->time_to_die);
	write_status(philo, false, DIED);
	pthread_mutex_unlock(&philo->info->fork_locks[philo->fork[0]]);
	return (NULL);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->info->must_eat_count == 0)
		return (NULL);
	if (philo->info->time_to_die == 0)
		return (NULL);
	if (philo->info->nb_philos == 1)
		return (one_philo(philo));
	if (philo->id % 2 == 0)
		usleep(philo->info->time_to_eat / 2);
	pthread_mutex_lock(&philo->info->start_mutex);
	pthread_mutex_unlock(&philo->info->start_mutex);
	while (check_if_end(philo->info) == false)
	{
		philo_start(philo);
		philo_think(philo);
	}
	return (NULL);
}
