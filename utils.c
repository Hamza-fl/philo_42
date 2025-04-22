#include "philo.h"


long gettime(t_time_code time_code)
{
    static long start_time = 0;  // Store the initial reference time
    struct timeval tv;

    if (gettimeofday(&tv, NULL))
        error_exit("get time of day failed");

    long current_time;
    if (SECOND == time_code)
        current_time = (tv.tv_sec + (tv.tv_usec / 1e6));
    else if (MILLISECOND == time_code)
        current_time = ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
    else if (MICROSECOND == time_code)
        current_time = ((tv.tv_sec * 1e6) + tv.tv_usec);
    else
        error_exit("wrong input to gettime");

    if (start_time == 0)  // Set start_time only once
        start_time = current_time;

    return (current_time - start_time);  // Return time relative to start
}


void precise_usleep (long usec, t_table *table)
{
    long start;
    long elapsed;
    long rem;

    start = gettime(MICROSECOND);
    while (gettime(MICROSECOND) - start < usec)
    {
        if (simulation_finished(table))
            break;
        elapsed = gettime(MICROSECOND) - start;
        rem = usec - elapsed;
        if (rem > 1e3)
            usleep(rem / 2);
        else
        {
            while (gettime(MICROSECOND) - start < usec)
              ;
        }
    }
}

void clean (t_table *table)
{
    t_philo *philo;
    int i;

    i = -1;
    while (++i < table->philo_nbr)
    {
        philo = table->philos + i;
        safe_mutex_handle(&philo->philo_mutex, DESTROY);
    }
    safe_mutex_handle(&table->table_mutex, DESTROY);
    safe_mutex_handle(&table->write_mutex, DESTROY);
    free(table->forks);
    free(table->philos);
}

void error_exit(const char *error)
{
    printf ("%s", error);
    exit(EXIT_FAILURE);
}