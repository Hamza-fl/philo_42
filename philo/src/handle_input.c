/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:20:31 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/26 19:39:20 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool    is_digits(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (false);
        i++;
    }
    return (true);
}

int ft_str_to_digit(char *str)
{
    unsigned long	nb;
    int i;

    i = 0;
    nb = 0;
    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
    {
        nb = nb * 10 + (str[i] - '0');
        i++;
    }
    if (nb > INT_MAX)
        return (-1);
    return ((int)nb);
}

bool    handle_input(int ac, char **av)
{
    int i;
    int namber;

    i = 1;
    while (i < ac)
    {
        if (!is_digits(av[i]))
            return (false);
        namber = ft_str_to_digit(av[i]);
        // if (i == 1 && (namber <= 0 || namber > INT_MAX))
        //     return (1);
        // if (i != 1 && namber == -1)
        //     return (false);
        if (namber == -1)
            return (false);
        i++;
    }
    return (true);
}
