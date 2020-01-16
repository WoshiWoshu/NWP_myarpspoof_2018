/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main for myarp
*/

#include "myarp.h"

int main(int ac, char **av)
{
    if (parssing_args(ac, av) == 0 &&
    av[4] != NULL && strcmp(av[4], "--printSpoof") == 0)
        print_spoof(ac, av);
    else if (parssing_args(ac, av) == 0 &&
    av[4] != NULL && strcmp(av[4], "--printBroadcast") == 0)
        print_broadcast(ac, av);
    else
        return (last_cond(ac, av));
}