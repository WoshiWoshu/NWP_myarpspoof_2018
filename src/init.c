/*
** EPITECH PROJECT, 2019
** init.c
** File description:
** init for myarp
*/

#include "myarp.h"

void init_sock(char **interface, int sd, uint8_t **src_mac)
{
    struct ifreq ifr;

    if ((sd = socket (AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0)
        my_perror("socket() failed", 84);
    memset(&ifr, 0, sizeof(ifr));
    snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", *interface);
    if (ioctl(sd, SIOCGIFHWADDR, &ifr) < 0)
        my_perror("ioctl() failed", 84);
    close(sd);

    memcpy(*src_mac, ifr.ifr_hwaddr.sa_data, 6 * sizeof(uint8_t));
}

void init_ip(struct sockaddr_ll *device, char **interface,
struct addrinfo *hints)
{
    memset(device, 0, sizeof(*device));
    if ((device->sll_ifindex = if_nametoindex(*interface)) == 0)
        my_perror("if_nametoindex() failed", 84);

    memset(hints, 0, sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = hints->ai_flags | AI_CANONNAME;
}

void memory_init(char **interface, char **target, char **av)
{
    strcpy(*interface, av[3]);
    strcpy(*target, av[2]);
}

void info_addr(char **target, arp_hdr_t *arphdr, struct addrinfo *hints,
char **av)
{
    int status;
    char *src_ip = str_alloc(INET_ADDRSTRLEN);
    strcpy(src_ip, av[1]);
    struct addrinfo *res;

    if ((status = inet_pton(AF_INET, src_ip, arphdr->s_ip)) != 1)
        my_perror("inet_pton() failed", 84);

    if ((status = getaddrinfo(*target, NULL, hints, &res)) != 0)
        my_perror("getaddrinfo() failed\n", 84);
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
    memcpy(arphdr->target_ip, &ipv4->sin_addr, 4 * sizeof(uint8_t));
    freeaddrinfo(res);
    free(src_ip);
}

void send_broadcast(struct sockaddr_ll *device, int sd, uint8_t **src_mac,
uint8_t **ether_frame)
{
    int bytes;
    int frame_length = 6 + 6 + 2 + ARP_HDRLEN;

    device->sll_family = AF_PACKET;
    memcpy(device->sll_addr, *src_mac, 6 * sizeof(uint8_t));
    device->sll_halen = 6;

    if ((sd = socket (PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0)
        my_perror("socket() failed", 84);
    if ((bytes = sendto(sd, *ether_frame, frame_length, 0,
    (struct sockaddr *)device, sizeof(*device))) <= 0)
        my_perror("sendto() failed", 84);

    close(sd);
    free(*src_mac);
    free(*ether_frame);
}
