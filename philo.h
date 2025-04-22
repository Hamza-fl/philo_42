#ifndef PHILO_H
#define PHILO_H

#include <stdio.h> //printf
#include <stdlib.h> // malloc free
#include <unistd.h> // write usleep
#include <stdbool.h> 
#include <pthread.h> 
#include <sys/time.h>
#include <limits.h> 
#include <errno.h>

typedef pthread_mutex_t t_mtx;
typedef struct s_table t_table;

typedef enum e_opcode
{
    LOCK,
    UNLOCK,
    INIT,
    DESTROY,
    CREATE,
    JOIN,
    DETACH,
} t_opcode;

typedef enum e_time_code
{
    SECOND,
    MILLISECOND,
    MICROSECOND,
}   t_time_code;

typedef enum e_status
{
    EATING,
    SLEEPING,
    THINKING,
    TAKE_FISR_FORK,
    TAKE_SECOND_FORK,
    DIED,
}   t_philo_status;

typedef struct s_fork
{
    t_mtx fork;
    int fork_id;
} t_fork;

typedef struct s_philo
{
    int id;
    long meals_cont;
    bool full;
    long last_meal_time;
    t_fork *fist_fork;
    t_fork *second_fork;
    pthread_t thread_id;
    t_mtx philo_mutex;
    t_table *table;
} t_philo;

typedef struct s_table
{
    long philo_nbr;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long nbr_limit_meals;
    long start_simulation;
    bool end_simulation;
    bool all_thread_ready;
    long threads_running_nbr;
    pthread_t monitor;
    t_mtx table_mutex;
    t_mtx write_mutex;
    t_fork *forks;
    t_philo *philos;
} t_table;

void error_exit(const char *error);
void parse_input(t_table *table, char **av);

void *ft_malloc(size_t byte);
void safe_thread_handle (pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);
void safe_mutex_handle(t_mtx *mutex, t_opcode opcode); // 44 min

void data_init(t_table *table);

void set_bool (t_mtx *mutex, bool *dest, bool value);
bool get_bool (t_mtx *mutex, bool *value);
void set_loog (t_mtx *mutex, long *dest, long value);
long get_long (t_mtx *mutex, long *value);
bool simulation_finished(t_table *table);

void wait_all_threads (t_table *table);

long gettime(t_time_code time_code);

void precise_usleep (long usec, t_table *table);

void write_status (t_philo_status status, t_philo *philo);

void dinner_start (t_table *table);

void increase_long (t_mtx *mutex, long *value);

bool all_thread_running(t_mtx *mutex, long *threads, long philo_nbr);

void *monitor_dinner(void *data);

void clean (t_table *table);

void thinking (t_philo *philo, bool pre_simulation);

void de_synchronize_philo(t_philo *philo);
#endif