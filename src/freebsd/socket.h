/*
 * socket.h
 * (C) 2011, all rights reserved,
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __SOCKET_H
#define __SOCKET_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdint.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * We don't use standard BSD-style structs.
 */

/*
 * Ethernet header.
 */
#define ETH_ALEN        6
struct ethhdr
{
    uint8_t h_dest[ETH_ALEN];
    uint8_t h_source[ETH_ALEN];
    uint16_t h_proto;
};

#define ETH_P_IP        0x0800

/*
 * IPv4 header.
 */
struct iphdr
{
    uint8_t  ihl:4;
    uint8_t  version:4;
    uint8_t  tos;
    uint16_t tot_len;
    uint16_t id;
    uint16_t frag_off;
    uint8_t  ttl;
    uint8_t  protocol;
    uint16_t check;
    uint32_t saddr;
    uint32_t daddr;
};

#define IP_MSS          576

/*
 * IPv6 header.
 */
struct ip6_hdr
{
    union
    {
        struct ip6_hdrctl
        {
            uint32_t ip6_un1_flow;
            uint16_t ip6_un1_plen;
            uint8_t  ip6_un1_nxt;
            uint8_t  ip6_un1_hlim;
        } ip6_un1;
        uint8_t ip6_un2_vfc;
    } ip6_ctlun;
    struct in6_addr ip6_src;
    struct in6_addr ip6_dst;
};

#define ip6_vfc   ip6_ctlun.ip6_un2_vfc
#define ip6_flow  ip6_ctlun.ip6_un1.ip6_un1_flow
#define ip6_plen  ip6_ctlun.ip6_un1.ip6_un1_plen
#define ip6_nxt   ip6_ctlun.ip6_un1.ip6_un1_nxt
#define ip6_hlim  ip6_ctlun.ip6_un1.ip6_un1_hlim
#define ip6_hops  ip6_ctlun.ip6_un1.ip6_un1_hlim

#ifdef IN6ADDR_LOOPBACK_INIT
#undef IN6ADDR_LOOPBACK_INIT
#define IN6ADDR_LOOPBACK_INIT {{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}}
#endif

/*
 * TCP header.
 */
struct tcphdr
{
    uint16_t source;
    uint16_t dest;
    uint32_t seq;
    uint32_t ack_seq;
    uint16_t res1:4;
    uint16_t doff:4;
    uint16_t fin:1;
    uint16_t syn:1;
    uint16_t rst:1;
    uint16_t psh:1;
    uint16_t ack:1;
    uint16_t urg:1;
    uint16_t res2:2;
    uint16_t window;
    uint16_t check;
    uint16_t urg_ptr;
};

#define TCPOPT_EOL      0
#define TCPOPT_NOP      1
#define TCPOPT_MAXSEG   2

/*
 * UDP header.
 */
struct udphdr
{
    uint16_t source;
    uint16_t dest;
    uint16_t len;
    uint16_t check;
};

/*
 * ICMP header.
 */
struct icmphdr
{
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    union
    {
        struct
        {
            uint16_t id;
            uint16_t sequence;
        } echo;
        uint32_t gateway;
        struct
        {
            uint16_t unused;
            uint16_t mtu;
        } frag;
    } un;
};

#define ICMP_DEST_UNREACH           3
#define ICMP_FRAG_NEEDED            4
#define ICMP_TIME_EXCEEDED          11
#define ICMP_EXC_TTL                0
#define ICMP_ECHOREPLY              0
#define ICMP_ECHO                   8

typedef int socket_t;

#define SOCKET_T_FMT                "%d"

#define INVALID_SOCKET              (-1)
#define SOCKET_ERROR                (-1)

#define init_sockets()              /* NOP */
#define close_socket(socket)        close(socket)

#define UDP_NO_CHECK_LAYER          SOL_SOCKET
#define UDP_NO_CHECK_OPTION         SO_NO_CHECK

#endif      /* __SOCKET_H */
