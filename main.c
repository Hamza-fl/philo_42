#include "philo.h"

int main (int ac, char **av)
{
    t_table table;

    if (ac == 5 || ac == 6)
    {
        parse_input(&table, av);
        data_init(&table);

        dinner_start(&table);

       clean(&table);
    }
    else{
        error_exit("wrong input\n");
    }
}