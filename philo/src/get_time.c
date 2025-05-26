#include "../include/philo.h"

bool	has_simulation_stopped(t_info *info)
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
	while (get_time_ms() < wake_up)
	{
		if (has_simulation_stopped(info))
			break ;
		usleep(100);
	}
}

time_t	get_time_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	dinner_start(time_t start_time)
{
	while (get_time_ms() < start_time)
		continue ;
}