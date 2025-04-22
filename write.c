#include "philo.h"

void write_status (t_philo_status status, t_philo *philo)
{
    long elapsed;

    elapsed = gettime(MILLISECOND);
    if (philo->full)
        return ;
    safe_mutex_handle(&philo->table->write_mutex, LOCK);
    if ((TAKE_FISR_FORK == status || TAKE_SECOND_FORK == status) && !simulation_finished(philo->table))
        printf("%-6ld   %d has take the fork\n",elapsed, philo->id);
    else if (EATING == status && !simulation_finished(philo->table))
        printf("%-6ld   %d is eating\n", elapsed, philo->id);
    else if (SLEEPING == status && !simulation_finished(philo->table))
        printf("%-6ld   %d is sleeping\n",elapsed, philo->id);
    else if (THINKING == status && !simulation_finished(philo->table))
        printf("%-6ld   %d is thinking\n",elapsed, philo->id);
    else if (DIED == status)
        printf("%-6ld   %d died", elapsed,philo->id);
    safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}