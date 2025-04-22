#include "philo.h"

void wait_all_threads (t_table *table)
{
    while (!get_bool(&table->table_mutex, &table->all_thread_ready))
        ;
}


bool all_thread_running(t_mtx *mutex, long *threads, long philo_nbr)
{
    bool ret;
    
    ret = false;
    safe_mutex_handle(mutex, LOCK);
    if (*threads == philo_nbr)
        ret = true;
    safe_mutex_handle(mutex, UNLOCK);
    return (ret);
}

void increase_long (t_mtx *mutex, long *value)
{
    safe_mutex_handle(mutex, LOCK);
    (*value)++;
    safe_mutex_handle(mutex, UNLOCK);
}

void de_synchronize_philo(t_philo *philo)
{
    if (philo->table->philo_nbr % 2 == 0)
    {
        if (philo->id % 2 == 0)
            precise_usleep(10, philo->table);
        else
        {
            if (philo->id % 2)
                thinking(philo, true);
        }
    }
}