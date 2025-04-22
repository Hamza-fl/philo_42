#include "philo.h"

static void assign_forks (t_philo *philo, t_fork *forks, int philo_possition)
{
    int philo_nbr;

    philo_nbr = philo->table->philo_nbr;
    
    if (philo->id % 2 == 0)
    {
        philo->fist_fork = &forks[philo_possition];
        philo->second_fork = &forks[(philo_possition + 1) % philo_nbr];
    }
    else
    {
        philo->fist_fork = &forks[(philo_possition + 1) % philo_nbr];
        philo->second_fork = &forks[philo_possition];
    }
}

static void philo_init (t_table *table)
{
    int i;
    t_philo *philo;

    i = -1;
    while (++i < table->philo_nbr)
    {
        philo = table->philos + i;
        philo->id = i + 1;
        philo->full = false;
        philo->meals_cont = 0;
        philo->table = table;
        safe_mutex_handle(&philo->philo_mutex, INIT);
        assign_forks(philo, table->forks, i);
    }
}

void data_init(t_table *table)
{
    int i;

    table->end_simulation = false;
    table->all_thread_ready = false;
    table->threads_running_nbr = 0;
    table->philos = ft_malloc(sizeof(t_philo) * table->philo_nbr);
    table->forks = ft_malloc(sizeof(t_fork) * table->philo_nbr);
    safe_mutex_handle(&table->table_mutex, INIT);
    safe_mutex_handle(&table->write_mutex, INIT);
    i = -1;
    while (++i < table->philo_nbr)
    {
        safe_mutex_handle(&table->forks[i].fork, INIT);
        table->forks[i].fork_id = i;
    }
    philo_init (table);
}