/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:52:32 by hfalati           #+#    #+#             */
/*   Updated: 2025/06/19 11:31:20 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0 || !s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	assign_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->info->nb_philos;
		philo->fork[1] = philo->id;
	}
	else
	{
		philo->fork[0] = philo->id;
		philo->fork[1] = (philo->id + 1) % philo->info->nb_philos;
	}
}

int	init_single_philo(t_philo **philos, t_info *info, unsigned int i)
{
	if (!philos)
		return (0);
	philos[i] = malloc(sizeof(t_philo));
	if (!philos[i])
		return (0);
	if (pthread_mutex_init(&philos[i]->meal_time_lock, 0) != 0)
	{
		free(philos[i]);
		return (0);
	}
	philos[i]->info = info;
	philos[i]->id = i;
	philos[i]->times_ate = 0;
	assign_forks(philos[i]);
	return (1);
}
