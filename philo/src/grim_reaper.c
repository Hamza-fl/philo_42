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
	if ((time - philo->last_meal) >= philo->info->time_to_die)
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
	bool			all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < info->nb_philos)
	{
		pthread_mutex_lock(&info->philos[i]->meal_time_lock);
		if (kill_philo(info->philos[i]))
			return (true);
		if (info->must_eat_count != -1)
			if (info->philos[i]->times_ate < (unsigned int)info->must_eat_count)
                all_ate_enough = false;
		pthread_mutex_unlock(&info->philos[i]->meal_time_lock);
		i++;
	}
	if (info->must_eat_count != -1 && all_ate_enough == true)
	{
		set_sim_stop_flag(info, true);
		return (true);
	}
	return (false);
}

void	*grim_reaper(void *data)
{
	t_info			*info;

	info = (t_info *)data;
	if (info->must_eat_count == 0)
		return (NULL);
	set_sim_stop_flag(info, false);
	dinner_start(info->start_time);
	while (true)
	{
		if (end_condition_reached(info) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}