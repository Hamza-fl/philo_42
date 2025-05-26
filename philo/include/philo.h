#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo	t_philo;

typedef struct s_info
{
	time_t			start_time;
	unsigned int	nb_philos;
	pthread_t		grim_reaper;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	bool			sim_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philo			**philos;
}	t_info;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		times_ate;
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_lock;
	time_t				last_meal;
	t_info				*info;
}	t_philo;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	FORK_1 = 4,
	FORK_2 = 5
}	t_status;

//handle input
bool    handle_input(int ac, char **av);
int ft_str_to_digit(char *str);

//free 
void	*error_null(t_info *info);
int	error_failure(t_info *info);
void	destroy_mutexes(t_info *info);
void	*free_info(t_info *info);

//init
t_info  *init_info(int ac, char **av);

//get time
void	dinner_start(time_t start_time);
time_t	get_time_ms(void);

//dinner
void	*philosopher(void *data);
void	*grim_reaper(void *data);

//time
void	philo_sleep(t_info *info, time_t sleep_time);

//utlis
bool	has_simulation_stopped(t_info *info);

//print
void	write_status(t_philo *philo, bool reaper_report, t_status status);
#endif