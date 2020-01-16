/*
** EPITECH PROJECT, 2018
** myarp.h
** File description:
** myarp.h
*/

#ifndef __MY_ARP_H__
#define __MY_ARP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <errno.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/ethernet.h>
#include <sys/ioctl.h>
#include <net/if.h>

typedef struct arp_hdr
{
    uint16_t htype;
    uint16_t ptype;
    uint8_t hlen;
    uint8_t plen;
    uint16_t opcode;
    uint8_t sender_mac[6];
    uint8_t s_ip[4];
    uint8_t target_mac[6];
    uint8_t target_ip[4];
} arp_hdr_t;

#define ETH_HDRLEN 14
#define IP4_HDRLEN 20
#define ARP_HDRLEN 28
#define ARPOP_REQUEST 1
#define ARPOP_REPLY 2

char *str_alloc(int size);
uint8_t *ustr_alloc(int size);
int display_mac(int ac, char **av);
void send_packet(int ac, char **av, int state, uint8_t *ether);
void my_perror(char *binary_name, int code);
void my_ether(uint8_t **ether_frame);
void loop_ether(int ac, char **av, arp_hdr_t *arp, uint8_t *ether);
void print_broadcast(int ac, char **av);
void without_args(int ac, char **av);
int parssing_args(int ac, char **av);
int parssing_ip(char *ip);
int count_pts(char *ip);
int last_cond(int ac, char **av);
void init_sock(char **interface, int sd, uint8_t **src_mac);
void init_ip(struct sockaddr_ll *device, char **interface,
struct addrinfo *hints);
void memory_init(char **interface, char **target, char **av);
void info_addr(char **target, arp_hdr_t *arphdr, struct addrinfo *hints,
char **av);
void send_broadcast(struct sockaddr_ll *device, int sd, uint8_t **src_mac,
uint8_t **ether_frame);
void config_frame(arp_hdr_t *arphdr, uint8_t **src_mac, uint8_t *ether,
int state);
void config_frame_two(arp_hdr_t *arphdr, uint8_t **src_mac, int sd,
struct sockaddr_ll *device);
void print_spoof(int ac, char **av);
void config_frame_reply(arp_hdr_t *arphdr, uint8_t **src_mac, uint8_t *ether,
char **av);
void config_reply_display(arp_hdr_t *arphdr, uint8_t **src_mac, char **av,
struct sockaddr_ll *device);
void send_reply(struct sockaddr_ll *device, int sd, uint8_t **src_mac,
uint8_t **ether_frame);
void config_reply(arp_hdr_t *arphdr, uint8_t **src_mac, int sd,
struct sockaddr_ll *device);
void init_sock_display(char **interface, int sd, uint8_t **src_mac);
void init_ip_display(struct sockaddr_ll *device, char **interface,
struct addrinfo *hints);
void info_addr_display(char **target, arp_hdr_t *arphdr,
struct addrinfo *hints, char **av);
void config_frame_display(arp_hdr_t *arphdr, uint8_t **src_mac, int sd,
struct sockaddr_ll *device);

#endif
