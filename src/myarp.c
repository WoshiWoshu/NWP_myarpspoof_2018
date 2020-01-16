/*
** EPITECH PROJECT, 2019
** myarp.c
** File description:
** myarp
*/

#include "myarp.h"

int display_mac(int ac, char **av)
{
    int sd;
    int status;
    uint8_t *ether;
    arp_hdr_t *arp;
    ether = ustr_alloc(IP_MAXPACKET);
    if ((sd = socket(PF_PACKET, SOCK_RAW, htons (ETH_P_ALL))) < 0)
        my_perror("socket() failed ", 84);
    arp = (arp_hdr_t *)(ether + 6 + 6 + 2);
    while (((((ether[12]) << 8) + ether[13]) != ETH_P_ARP) ||
    (ntohs(arp->opcode) != ARPOP_REPLY))
        if ((status = recv(sd, ether, IP_MAXPACKET, 0)) < 0)
            my_ether(&ether);
    close(sd);
    printf("Found victim’s MAC address: '");
    for (int i = 0; i < 5; i++)
        printf ("%02x:", ether[i+6]);
    printf ("%02x'\n", ether[11]);
    loop_ether(ac, av, arp, ether);
    free(ether);
    return (0);
}

void send_packet(int ac, char **av, int state, uint8_t *ether)
{
    int sd;
    arp_hdr_t arphdr;
    struct addrinfo hints;
    struct sockaddr_ll device;
    uint8_t *src_mac = ustr_alloc(6);
    char *interface = str_alloc(40);
    char *target = str_alloc(40);

    memory_init(&interface, &target, av);
    init_sock(&interface, sd, &src_mac);
    init_ip(&device, &interface, &hints);
    info_addr(&target, &arphdr, &hints, av);
    config_frame(&arphdr, &src_mac, ether, state);
    if (state == 1)
        config_frame_two(&arphdr, &src_mac, sd, &device);
    else
        config_reply(&arphdr, &src_mac, sd, &device);
    free(interface);
    free(target);
}

char *str_alloc(int size)
{
    void *tmp;

    if (size <= 0)
        my_perror("Cannot allocate memory\n", 84);

    tmp = (char *) malloc(size * sizeof(char));
    if (tmp != NULL) {
        memset(tmp, 0, size * sizeof(char));
        return (tmp);
    } else
        my_perror("Cannot allocate memory\n", 84);
}

uint8_t *ustr_alloc(int size)
{
    void *tmp;

    if (size <= 0)
        my_perror("Cannot allocate memory\n", 84);

    tmp = (uint8_t *)malloc(size * sizeof(uint8_t));
    if (tmp != NULL) {
        memset(tmp, 0, size * sizeof(uint8_t));
        return (tmp);
    } else
        my_perror("Cannot allocate memory\n", 84);
}