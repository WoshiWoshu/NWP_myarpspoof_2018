/*
** EPITECH PROJECT, 2019
** useful_functions.c
** File description:
** useful_functions for myarp
*/

#include "myarp.h"

void loop_ether(int ac, char **av, arp_hdr_t *arp, uint8_t *ether)
{
    while (1) {
        send_packet(ac, av, 0, ether);
        printf("Spoofed packet sent to '%u.%u.%u.%u'\n",
            arp->s_ip[0], arp->s_ip[1], arp->s_ip[2], arp->s_ip[3]);
        sleep(1);
    }
}

void my_ether(uint8_t **ether)
{
    if (errno == EINTR)
        memset(*ether, 0, IP_MAXPACKET * sizeof(uint8_t));
    else
        my_perror("recv() failed:", 84);
}

void print_broadcast(int ac, char **av)
{
    int sd;
    arp_hdr_t arphdr;
    struct addrinfo hints;
    struct sockaddr_ll device;
    uint8_t *src_mac = ustr_alloc(6);
    char *interface = str_alloc(40);
    char *target = str_alloc(40);

    memory_init(&interface, &target, av);
    init_sock_display(&interface, sd, &src_mac);
    init_ip(&device, &interface, &hints);
    info_addr(&target, &arphdr, &hints, av);
    config_frame(&arphdr, &src_mac, NULL, 1);
    config_frame_display(&arphdr, &src_mac, sd, &device);

    free (interface);
    free (target);
}

void print_spoof(int ac, char **av)
{
    int sd;
    arp_hdr_t arphdr;
    uint8_t *ether = ustr_alloc(IP_MAXPACKET);
    struct addrinfo hints;
    struct sockaddr_ll device;
    uint8_t *src_mac = ustr_alloc(6);
    char *interface = str_alloc(40);
    char *target = str_alloc(40);

    memory_init(&interface, &target, av);
    init_sock_display(&interface, sd, &src_mac);
    init_ip(&device, &interface, &hints);
    info_addr(&target, &arphdr, &hints, av);
    config_frame_reply(&arphdr, &src_mac, ether, av);
    config_reply_display(&arphdr, &src_mac, av, &device);

    free (interface);
    free (target);
}