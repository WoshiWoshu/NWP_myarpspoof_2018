/*
** EPITECH PROJECT, 2019
** useful_function.c
** File description:
** useful_function for myarp
*/

#include "myarp.h"

int parssing_args(int ac, char **av)
{
    int success = (-3);

    if (parssing_ip(av[1]) == 0)
        success += 1;
    if (parssing_ip(av[2]) == 0)
        success += 1;
    if (av[3] != NULL)
        success += 1;
    return (success);
}

int parssing_ip(char *ip)
{
    if (count_pts(ip) == 3)
        return (0);
    return (84);
}

int count_pts(char *ip)
{
    int count = 0;

    for (int i = 0; ip[i] != '\0'; i++)
        if (ip[i] == '.')
            count++;
    return (count);
}