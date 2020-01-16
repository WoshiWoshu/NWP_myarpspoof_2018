/*
** EPITECH PROJECT, 2019
** display_broadcast.c
** File description:
** display_broadcast for myarp
*/

#include "myarp.h"

void init_sock_display(char **interface, int sd, uint8_t **src_mac)
{
    struct ifreq ifr;

    sd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&ifr, 0, sizeof(ifr));
    snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", *interface);
    ioctl(sd, SIOCGIFHWADDR, &ifr);
    close(sd);

    memcpy(*src_mac, ifr.ifr_hwaddr.sa_data, 6 * sizeof(uint8_t));
}

void config_frame_display(arp_hdr_t *arphdr, uint8_t **src_mac, int sd,
struct sockaddr_ll *device)
{
    uint8_t *ether_frame = ustr_alloc(IP_MAXPACKET);
    uint8_t *dst_mac = ustr_alloc(6);

    memset(dst_mac, 0xff, 6 * sizeof(uint8_t));

    memcpy(ether_frame, dst_mac, 6 * sizeof(uint8_t));
    memcpy(ether_frame + 6, *src_mac, 6 * sizeof(uint8_t));
    ether_frame[12] = ETH_P_ARP / 256;
    ether_frame[13] = ETH_P_ARP % 256;
    memcpy(ether_frame + ETH_HDRLEN, arphdr, ARP_HDRLEN * sizeof(uint8_t));

    sd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    for (int i = 0; i < 41; i++)
        printf("%02x ", (__u_char)ether_frame[i]);
    printf("%02x\n", (__u_char)ether_frame[41]);

    free (dst_mac);
    close(sd);
    free(*src_mac);
    free(ether_frame);
}

void config_reply_display(arp_hdr_t *arphdr, uint8_t **src_mac, char **av,
struct sockaddr_ll *device)
{
    uint8_t *ether_frame = ustr_alloc(IP_MAXPACKET);
    uint8_t *dst_mac = ustr_alloc(6);
    unsigned char mac_spoof[6];
    sscanf(av[5], "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
    &mac_spoof[0], &mac_spoof[1], &mac_spoof[2], &mac_spoof[3],
    &mac_spoof[4], &mac_spoof[5]);
    for (int i = 0; i < 6; i++)
        memset(dst_mac + i, mac_spoof[i], 1 * sizeof(uint8_t));
    memcpy(ether_frame, dst_mac, 6 * sizeof(uint8_t));
    memcpy(ether_frame + 6, *src_mac, 6 * sizeof(uint8_t));
    ether_frame[12] = ETH_P_ARP / 256;
    ether_frame[13] = ETH_P_ARP % 256;
    memcpy(ether_frame + ETH_HDRLEN, arphdr, ARP_HDRLEN * sizeof(uint8_t));
    int sd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    for (int i = 0; i < 41; i++) printf("%02x ", (__u_char)ether_frame[i]);
    printf("%02x\n", (__u_char)ether_frame[41]);
    free (dst_mac);
    close(sd);
    free(*src_mac);
    free(ether_frame);
}