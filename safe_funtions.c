#include "philo.h"

void *ft_malloc(size_t byte)
{
    void *ret;

    ret = malloc(byte);
    if (ret == NULL)
        error_exit("Error with the malloc");
    return (ret);
}

static void handle_mutex_error (int status, t_opcode opcode)
{
    if (status == 0)
        return ;
    if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
        error_exit("The value specified by mutex is invalid.");
    else if (EINVAL == status && INIT == opcode)
        error_exit("The value specified by attr is invalid.");
    else if (EDEADLK == status)
        error_exit("The mutex is already locked by the calling thread");
    else if (EPERM == status)
        error_exit ("The calling thread does not own the mutex");
    else if (ENOMEM == status)
        error_exit ("Insufficient memory exists to initialize the mutex.");
    else if (EBUSY == status)
        error_exit ("The mutex could not be acquired because it was currently locked.");
}

void safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
    if (LOCK == opcode)
        handle_mutex_error (pthread_mutex_lock(mutex), opcode);
    else if (UNLOCK == opcode)
        handle_mutex_error (pthread_mutex_unlock(mutex), opcode);
    else if (INIT == opcode)
        handle_mutex_error (pthread_mutex_init(mutex, NULL), opcode);
    else if (DESTROY == opcode)
        handle_mutex_error (pthread_mutex_destroy(mutex), opcode);
    else
        error_exit("wrong opcode for mutex handle");
}


static void handle_thread_error (int status, t_opcode opcode)
{
    if (status == 0)
        return ;
    if (EAGAIN == status)
        error_exit ("no resouces for create another thread");
    else if (EPERM == status)
        error_exit ("the caller man ba3d");
    else if (EINVAL == status && CREATE == opcode)
        error_exit ("yarabi mansach hadchi");
    else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
        error_exit("....");
    else if (ESRCH == status)
        error_exit (".....");
    else if (EDEADLK == status)
        error_exit ("......");
}

void safe_thread_handle (pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode)
{
    if (CREATE == opcode)
        handle_thread_error (pthread_create (thread, NULL, foo, data), opcode);
    else if (JOIN == opcode)
        handle_thread_error (pthread_join (*thread, NULL), opcode);
    else if (DETACH == opcode)
        handle_thread_error (pthread_detach (*thread), opcode);
    else
        error_exit ("wrong opcode for the thread handle");
}