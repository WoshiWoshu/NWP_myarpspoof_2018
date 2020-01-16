/*
** EPITECH PROJECT, 2019
** error.c
** File description:
** error functions for myarp
*/

#include "myarp.h"

void my_perror(char *binary_name, int code)
{
    perror(binary_name);
    exit(code);
}