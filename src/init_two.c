/*
** EPITECH PROJECT, 2019
** init_two.c
** File description:
** init_two for myarp
*/

#include "myarp.h"

void config_frame_reply(arp_hdr_t *arphdr, uint8_t **src_mac, uint8_t *ether,
char **av)
{
    unsigned char mac_spoof[6];
    sscanf(av[5], "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
    &mac_spoof[0], &mac_spoof[1], &mac_spoof[2], &mac_spoof[3],
    &mac_spoof[4], &mac_spoof[5]);
    arphdr->htype = htons(1);
    arphdr->ptype = htons(ETH_P_IP);
    arphdr->hlen = 6;
    arphdr->plen = 4;
    arphdr->opcode = htons(ARPOP_REPLY);
    memcpy(arphdr->sender_mac, *src_mac, 6 * sizeof(uint8_t));
    for (int i = 0; i < 6; i++)
        memset(arphdr->target_mac + i, mac_spoof[i], 1 * sizeof(uint8_t));
}

void config_frame(arp_hdr_t *arphdr, uint8_t **src_mac, uint8_t *ether,
int state)
{
    arphdr->htype = htons(1);
    arphdr->ptype = htons(ETH_P_IP);
    arphdr->hlen = 6;
    arphdr->plen = 4;
    if (state == 1)
        arphdr->opcode = htons(ARPOP_REQUEST);
    else
        arphdr->opcode = htons(ARPOP_REPLY);
    memcpy(arphdr->sender_mac, *src_mac, 6 * sizeof(uint8_t));
    if (state == 1)
        memset(arphdr->target_mac, 255, 6 * sizeof(uint8_t));
    else
        for (int i = 0; i < 6; i++)
            memset(arphdr->target_mac + i, ether[i+6], 1 * sizeof(uint8_t));
}

void config_frame_two(arp_hdr_t *arphdr, uint8_t **src_mac, int sd,
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

    send_broadcast(device, sd, src_mac, &ether_frame);

    free(dst_mac);
}

void config_reply(arp_hdr_t *arphdr, uint8_t **src_mac, int sd,
struct sockaddr_ll *device)
{
    uint8_t *ether_frame = ustr_alloc(IP_MAXPACKET);
    uint8_t *dst_mac = ustr_alloc(6);

    for (int i = 0; i < 6; i++)
        memset(dst_mac + i, (int)arphdr->target_mac[i], 1 * sizeof(uint8_t));

    memcpy(ether_frame, dst_mac, 6 * sizeof(uint8_t));
    memcpy(ether_frame + 6, *src_mac, 6 * sizeof(uint8_t));
    ether_frame[12] = ETH_P_ARP / 256;
    ether_frame[13] = ETH_P_ARP % 256;
    memcpy(ether_frame + ETH_HDRLEN, arphdr, ARP_HDRLEN * sizeof(uint8_t));

    send_reply(device, sd, src_mac, &ether_frame);

    free(dst_mac);
}

void send_reply(struct sockaddr_ll *device, int sd, uint8_t **src_mac,
uint8_t **ether_frame)
{
    int bytes;
    int frame_length = 6 + 6 + 2 + ARP_HDRLEN;

    device->sll_family = AF_PACKET;
    memcpy(device->sll_addr, *src_mac, 6 * sizeof(uint8_t));
    device->sll_halen = 6;

    if ((sd = socket (AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0)
        my_perror("socket() failed", 84);
    if ((bytes = sendto(sd, *ether_frame, frame_length, 0,
    (struct sockaddr *)device, sizeof(*device))) <= 0)
        my_perror("sendto() failed", 84);

    close(sd);
    free(*src_mac);
    free(*ether_frame);
}