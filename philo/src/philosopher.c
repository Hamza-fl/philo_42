/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:20:38 by hfalati           #+#    #+#             */
/*   Updated: 2025/06/01 14:14:13 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->fork_locks[philo->fork[0]]);
	write_status(philo, false, FORK_1);
	pthread_mutex_lock(&philo->info->fork_locks[philo->fork[1]]);
	write_status(philo, false, FORK_2);
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

void	philo_think(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->info->time_to_die - (get_time_ms() - philo->last_meal) - philo->info->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false)
		write_status(philo, false, THINKING);
	philo_sleep(philo->info, time_to_think);
}

void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->fork_locks[philo->fork[0]]);
	write_status(philo, false, FORK_1);
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
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->info->start_time = get_time_ms();
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (philo->info->time_to_die == 0)
		return (NULL);
	if (philo->info->nb_philos == 1)
		return (one_philo(philo));
	else if (philo->id % 2)
		philo_think(philo, true);
	while (check_if_end(philo->info) == false)    
	{
		philo_start(philo);
		philo_think(philo, false);
	}
	return (NULL);
}