#include "philo.h"

static inline bool is_space(char c)
{
    return ((c >= 9 && c <= 13) || c == 32);
}

static inline bool is_digit(char c)
{
     return (c >= '0' && c <= '9');
}

static const char *valid_input(const char *str)
{
    int len;
    const char *number;

    len = 0;
    while (is_space(*str))
        ++str;
    if (*str == '+')
        ++str;
    else if (*str == '-')
        error_exit("only possitve valuse");
    if (!is_digit(*str))
        error_exit("the input is not a correct digit");
    number = str;
    while (is_digit(*str++))
        ++len;
    if (len > 10)
        error_exit("the value is too big, INT_MAX is the limit");
    return (number);
}

static long ft_atoi (const char *str)
{
    long num;

    num = 0;
    str = valid_input(str);
    while (is_digit(*str))
        num = (num * 10) + (*str++ - '0');
    if (num > INT_MAX)
        error_exit("the value is too big, INT_MAX is the limit");
    return (num);
}

void parse_input(t_table *table, char **av)
{
    table->philo_nbr = ft_atoi(av[1]);
    table->time_to_die = ft_atoi(av[2]) * 1000;
    table->time_to_eat = ft_atoi(av[3]) * 1000;
    table->time_to_sleep = ft_atoi(av[4]) * 1000;
    if (av[5])
        table->nbr_limit_meals = ft_atoi(av[5]);
    else
        table->nbr_limit_meals = -1;
}