#include "../include/philo.h"

void	assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->info->nb_philos;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->info->nb_philos;
		philo->fork[1] = philo->id;
	}
}

t_philo    **init_philo(t_info *info)
{
    t_philo **philos;
    unsigned int i;

    philos = malloc(sizeof(t_philo) * info->nb_philos);
    if (!philos)
    {
        error_null(info);
        return (NULL);
    }
    i = 0;
    while (i < info->nb_philos)
    {
        philos[i] = malloc(sizeof(t_philo));
        if (!philos[i])
        {
            error_null(info);
            return (NULL);
        }
        if (pthread_mutex_init(&philos[i]->meal_time_lock, 0) != 0)
        {
            error_null(info);
			return (NULL);
        }
        philos[i]->info = info;
        philos[i]->id = i;
        philos[i]->times_ate = 0;
        assign_forks(philos[i]);
        i++;
    }
    return (philos);
}

pthread_mutex_t	*init_forks(t_info *info)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * info->nb_philos);
	if (!forks)
    {
        error_null(info);
		return (NULL);
    }
    i = 0;
	while (i < info->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
        {
            error_null(info);
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
        error_failure(info);
		return (0);
    }
    if (pthread_mutex_init(&info->write_lock, 0) != 0)
    {
        error_failure(info);
		return (0);
    }
    return (true);
}

t_info  *init_info(int ac, char **av)
{
    int     i = 1;
    t_info  *info;

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
