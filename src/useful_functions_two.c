/*
** EPITECH PROJECT, 2019
** useful_functions.c
** File description:
** useful_functions for myarp
*/

#include "myarp.h"

void without_args(int ac, char **av)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        my_perror("fork", 84);
    else if (pid == 0)
        send_packet(ac, av, 1, NULL);
    else
        display_mac(ac, av);
}

int last_cond(int ac, char **av)
{
    if (parssing_args(ac, av) == 0)
        without_args(ac, av);
    else
        return (84);
    return (0);
}