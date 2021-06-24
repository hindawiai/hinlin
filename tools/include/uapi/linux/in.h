<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions of the Internet Protocol.
 *
 * Version:	@(#)in.h	1.0.1	04/21/93
 *
 * Authors:	Original taken from the GNU Project <netinet/in.h> file.
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _UAPI_LINUX_IN_H
#घोषणा _UAPI_LINUX_IN_H

#समावेश <linux/types.h>
#समावेश <linux/libc-compat.h>
#समावेश <linux/socket.h>

#अगर __UAPI_DEF_IN_IPPROTO
/* Standard well-defined IP protocols.  */
क्रमागत अणु
  IPPROTO_IP = 0,		/* Dummy protocol क्रम TCP		*/
#घोषणा IPPROTO_IP		IPPROTO_IP
  IPPROTO_ICMP = 1,		/* Internet Control Message Protocol	*/
#घोषणा IPPROTO_ICMP		IPPROTO_ICMP
  IPPROTO_IGMP = 2,		/* Internet Group Management Protocol	*/
#घोषणा IPPROTO_IGMP		IPPROTO_IGMP
  IPPROTO_IPIP = 4,		/* IPIP tunnels (older KA9Q tunnels use 94) */
#घोषणा IPPROTO_IPIP		IPPROTO_IPIP
  IPPROTO_TCP = 6,		/* Transmission Control Protocol	*/
#घोषणा IPPROTO_TCP		IPPROTO_TCP
  IPPROTO_EGP = 8,		/* Exterior Gateway Protocol		*/
#घोषणा IPPROTO_EGP		IPPROTO_EGP
  IPPROTO_PUP = 12,		/* PUP protocol				*/
#घोषणा IPPROTO_PUP		IPPROTO_PUP
  IPPROTO_UDP = 17,		/* User Datagram Protocol		*/
#घोषणा IPPROTO_UDP		IPPROTO_UDP
  IPPROTO_IDP = 22,		/* XNS IDP protocol			*/
#घोषणा IPPROTO_IDP		IPPROTO_IDP
  IPPROTO_TP = 29,		/* SO Transport Protocol Class 4	*/
#घोषणा IPPROTO_TP		IPPROTO_TP
  IPPROTO_DCCP = 33,		/* Datagram Congestion Control Protocol */
#घोषणा IPPROTO_DCCP		IPPROTO_DCCP
  IPPROTO_IPV6 = 41,		/* IPv6-in-IPv4 tunnelling		*/
#घोषणा IPPROTO_IPV6		IPPROTO_IPV6
  IPPROTO_RSVP = 46,		/* RSVP Protocol			*/
#घोषणा IPPROTO_RSVP		IPPROTO_RSVP
  IPPROTO_GRE = 47,		/* Cisco GRE tunnels (rfc 1701,1702)	*/
#घोषणा IPPROTO_GRE		IPPROTO_GRE
  IPPROTO_ESP = 50,		/* Encapsulation Security Payload protocol */
#घोषणा IPPROTO_ESP		IPPROTO_ESP
  IPPROTO_AH = 51,		/* Authentication Header protocol	*/
#घोषणा IPPROTO_AH		IPPROTO_AH
  IPPROTO_MTP = 92,		/* Multicast Transport Protocol		*/
#घोषणा IPPROTO_MTP		IPPROTO_MTP
  IPPROTO_BEETPH = 94,		/* IP option pseuकरो header क्रम BEET	*/
#घोषणा IPPROTO_BEETPH		IPPROTO_BEETPH
  IPPROTO_ENCAP = 98,		/* Encapsulation Header			*/
#घोषणा IPPROTO_ENCAP		IPPROTO_ENCAP
  IPPROTO_PIM = 103,		/* Protocol Independent Multicast	*/
#घोषणा IPPROTO_PIM		IPPROTO_PIM
  IPPROTO_COMP = 108,		/* Compression Header Protocol		*/
#घोषणा IPPROTO_COMP		IPPROTO_COMP
  IPPROTO_SCTP = 132,		/* Stream Control Transport Protocol	*/
#घोषणा IPPROTO_SCTP		IPPROTO_SCTP
  IPPROTO_UDPLITE = 136,	/* UDP-Lite (RFC 3828)			*/
#घोषणा IPPROTO_UDPLITE		IPPROTO_UDPLITE
  IPPROTO_MPLS = 137,		/* MPLS in IP (RFC 4023)		*/
#घोषणा IPPROTO_MPLS		IPPROTO_MPLS
  IPPROTO_ETHERNET = 143,	/* Ethernet-within-IPv6 Encapsulation	*/
#घोषणा IPPROTO_ETHERNET	IPPROTO_ETHERNET
  IPPROTO_RAW = 255,		/* Raw IP packets			*/
#घोषणा IPPROTO_RAW		IPPROTO_RAW
  IPPROTO_MPTCP = 262,		/* Multipath TCP connection		*/
#घोषणा IPPROTO_MPTCP		IPPROTO_MPTCP
  IPPROTO_MAX
पूर्ण;
#पूर्ण_अगर

#अगर __UAPI_DEF_IN_ADDR
/* Internet address. */
काष्ठा in_addr अणु
	__be32	s_addr;
पूर्ण;
#पूर्ण_अगर

#घोषणा IP_TOS		1
#घोषणा IP_TTL		2
#घोषणा IP_HDRINCL	3
#घोषणा IP_OPTIONS	4
#घोषणा IP_ROUTER_ALERT	5
#घोषणा IP_RECVOPTS	6
#घोषणा IP_RETOPTS	7
#घोषणा IP_PKTINFO	8
#घोषणा IP_PKTOPTIONS	9
#घोषणा IP_MTU_DISCOVER	10
#घोषणा IP_RECVERR	11
#घोषणा IP_RECVTTL	12
#घोषणा	IP_RECVTOS	13
#घोषणा IP_MTU		14
#घोषणा IP_FREEBIND	15
#घोषणा IP_IPSEC_POLICY	16
#घोषणा IP_XFRM_POLICY	17
#घोषणा IP_PASSSEC	18
#घोषणा IP_TRANSPARENT	19

/* BSD compatibility */
#घोषणा IP_RECVRETOPTS	IP_RETOPTS

/* TProxy original addresses */
#घोषणा IP_ORIGDSTADDR       20
#घोषणा IP_RECVORIGDSTADDR   IP_ORIGDSTADDR

#घोषणा IP_MINTTL       21
#घोषणा IP_NODEFRAG     22
#घोषणा IP_CHECKSUM	23
#घोषणा IP_BIND_ADDRESS_NO_PORT	24
#घोषणा IP_RECVFRAGSIZE	25
#घोषणा IP_RECVERR_RFC4884	26

/* IP_MTU_DISCOVER values */
#घोषणा IP_PMTUDISC_DONT		0	/* Never send DF frames */
#घोषणा IP_PMTUDISC_WANT		1	/* Use per route hपूर्णांकs	*/
#घोषणा IP_PMTUDISC_DO			2	/* Always DF		*/
#घोषणा IP_PMTUDISC_PROBE		3       /* Ignore dst pmtu      */
/* Always use पूर्णांकerface mtu (ignores dst pmtu) but करोn't set DF flag.
 * Also incoming ICMP frag_needed notअगरications will be ignored on
 * this socket to prevent accepting spoofed ones.
 */
#घोषणा IP_PMTUDISC_INTERFACE		4
/* weaker version of IP_PMTUDISC_INTERFACE, which allows packets to get
 * fragmented अगर they exeed the पूर्णांकerface mtu
 */
#घोषणा IP_PMTUDISC_OMIT		5

#घोषणा IP_MULTICAST_IF			32
#घोषणा IP_MULTICAST_TTL 		33
#घोषणा IP_MULTICAST_LOOP 		34
#घोषणा IP_ADD_MEMBERSHIP		35
#घोषणा IP_DROP_MEMBERSHIP		36
#घोषणा IP_UNBLOCK_SOURCE		37
#घोषणा IP_BLOCK_SOURCE			38
#घोषणा IP_ADD_SOURCE_MEMBERSHIP	39
#घोषणा IP_DROP_SOURCE_MEMBERSHIP	40
#घोषणा IP_MSFILTER			41
#घोषणा MCAST_JOIN_GROUP		42
#घोषणा MCAST_BLOCK_SOURCE		43
#घोषणा MCAST_UNBLOCK_SOURCE		44
#घोषणा MCAST_LEAVE_GROUP		45
#घोषणा MCAST_JOIN_SOURCE_GROUP		46
#घोषणा MCAST_LEAVE_SOURCE_GROUP	47
#घोषणा MCAST_MSFILTER			48
#घोषणा IP_MULTICAST_ALL		49
#घोषणा IP_UNICAST_IF			50

#घोषणा MCAST_EXCLUDE	0
#घोषणा MCAST_INCLUDE	1

/* These need to appear somewhere around here */
#घोषणा IP_DEFAULT_MULTICAST_TTL        1
#घोषणा IP_DEFAULT_MULTICAST_LOOP       1

/* Request काष्ठा क्रम multicast socket ops */

#अगर __UAPI_DEF_IP_MREQ
काष्ठा ip_mreq  अणु
	काष्ठा in_addr imr_multiaddr;	/* IP multicast address of group */
	काष्ठा in_addr imr_पूर्णांकerface;	/* local IP address of पूर्णांकerface */
पूर्ण;

काष्ठा ip_mreqn अणु
	काष्ठा in_addr	imr_multiaddr;		/* IP multicast address of group */
	काष्ठा in_addr	imr_address;		/* local IP address of पूर्णांकerface */
	पूर्णांक		imr_अगरindex;		/* Interface index */
पूर्ण;

काष्ठा ip_mreq_source अणु
	__be32		imr_multiaddr;
	__be32		imr_पूर्णांकerface;
	__be32		imr_sourceaddr;
पूर्ण;

काष्ठा ip_msfilter अणु
	__be32		imsf_multiaddr;
	__be32		imsf_पूर्णांकerface;
	__u32		imsf_भ_शेषe;
	__u32		imsf_numsrc;
	__be32		imsf_slist[1];
पूर्ण;

#घोषणा IP_MSFILTER_SIZE(numsrc) \
	(माप(काष्ठा ip_msfilter) - माप(__u32) \
	+ (numsrc) * माप(__u32))

काष्ठा group_req अणु
	__u32				 gr_पूर्णांकerface;	/* पूर्णांकerface index */
	काष्ठा __kernel_sockaddr_storage gr_group;	/* group address */
पूर्ण;

काष्ठा group_source_req अणु
	__u32				 gsr_पूर्णांकerface;	/* पूर्णांकerface index */
	काष्ठा __kernel_sockaddr_storage gsr_group;	/* group address */
	काष्ठा __kernel_sockaddr_storage gsr_source;	/* source address */
पूर्ण;

काष्ठा group_filter अणु
	__u32				 gf_पूर्णांकerface;	/* पूर्णांकerface index */
	काष्ठा __kernel_sockaddr_storage gf_group;	/* multicast address */
	__u32				 gf_भ_शेषe;	/* filter mode */
	__u32				 gf_numsrc;	/* number of sources */
	काष्ठा __kernel_sockaddr_storage gf_slist[1];	/* पूर्णांकerface index */
पूर्ण;

#घोषणा GROUP_FILTER_SIZE(numsrc) \
	(माप(काष्ठा group_filter) - माप(काष्ठा __kernel_sockaddr_storage) \
	+ (numsrc) * माप(काष्ठा __kernel_sockaddr_storage))
#पूर्ण_अगर

#अगर __UAPI_DEF_IN_PKTINFO
काष्ठा in_pktinfo अणु
	पूर्णांक		ipi_अगरindex;
	काष्ठा in_addr	ipi_spec_dst;
	काष्ठा in_addr	ipi_addr;
पूर्ण;
#पूर्ण_अगर

/* Structure describing an Internet (IP) socket address. */
#अगर  __UAPI_DEF_SOCKADDR_IN
#घोषणा __SOCK_SIZE__	16		/* माप(काष्ठा sockaddr)	*/
काष्ठा sockaddr_in अणु
  __kernel_sa_family_t	sin_family;	/* Address family		*/
  __be16		sin_port;	/* Port number			*/
  काष्ठा in_addr	sin_addr;	/* Internet address		*/

  /* Pad to size of `काष्ठा sockaddr'. */
  अचिन्हित अक्षर		__pad[__SOCK_SIZE__ - माप(लघु पूर्णांक) -
			माप(अचिन्हित लघु पूर्णांक) - माप(काष्ठा in_addr)];
पूर्ण;
#घोषणा sin_zero	__pad		/* क्रम BSD UNIX comp. -FvK	*/
#पूर्ण_अगर

#अगर __UAPI_DEF_IN_CLASS
/*
 * Definitions of the bits in an Internet address पूर्णांकeger.
 * On subnets, host and network parts are found according
 * to the subnet mask, not these masks.
 */
#घोषणा	IN_CLASSA(a)		((((दीर्घ पूर्णांक) (a)) & 0x80000000) == 0)
#घोषणा	IN_CLASSA_NET		0xff000000
#घोषणा	IN_CLASSA_NSHIFT	24
#घोषणा	IN_CLASSA_HOST		(0xffffffff & ~IN_CLASSA_NET)
#घोषणा	IN_CLASSA_MAX		128

#घोषणा	IN_CLASSB(a)		((((दीर्घ पूर्णांक) (a)) & 0xc0000000) == 0x80000000)
#घोषणा	IN_CLASSB_NET		0xffff0000
#घोषणा	IN_CLASSB_NSHIFT	16
#घोषणा	IN_CLASSB_HOST		(0xffffffff & ~IN_CLASSB_NET)
#घोषणा	IN_CLASSB_MAX		65536

#घोषणा	IN_CLASSC(a)		((((दीर्घ पूर्णांक) (a)) & 0xe0000000) == 0xc0000000)
#घोषणा	IN_CLASSC_NET		0xffffff00
#घोषणा	IN_CLASSC_NSHIFT	8
#घोषणा	IN_CLASSC_HOST		(0xffffffff & ~IN_CLASSC_NET)

#घोषणा	IN_CLASSD(a)		((((दीर्घ पूर्णांक) (a)) & 0xf0000000) == 0xe0000000)
#घोषणा	IN_MULTICAST(a)		IN_CLASSD(a)
#घोषणा	IN_MULTICAST_NET	0xe0000000

#घोषणा	IN_BADCLASS(a)		(((दीर्घ पूर्णांक) (a) ) == (दीर्घ पूर्णांक)0xffffffff)
#घोषणा	IN_EXPERIMENTAL(a)	IN_BADCLASS((a))

#घोषणा	IN_CLASSE(a)		((((दीर्घ पूर्णांक) (a)) & 0xf0000000) == 0xf0000000)
#घोषणा	IN_CLASSE_NET		0xffffffff
#घोषणा	IN_CLASSE_NSHIFT	0

/* Address to accept any incoming messages. */
#घोषणा	INADDR_ANY		((अचिन्हित दीर्घ पूर्णांक) 0x00000000)

/* Address to send to all hosts. */
#घोषणा	INADDR_BROADCAST	((अचिन्हित दीर्घ पूर्णांक) 0xffffffff)

/* Address indicating an error वापस. */
#घोषणा	INADDR_NONE		((अचिन्हित दीर्घ पूर्णांक) 0xffffffff)

/* Dummy address क्रम src of ICMP replies अगर no real address is set (RFC7600). */
#घोषणा	INADDR_DUMMY		((अचिन्हित दीर्घ पूर्णांक) 0xc0000008)

/* Network number क्रम local host loopback. */
#घोषणा	IN_LOOPBACKNET		127

/* Address to loopback in software to local host.  */
#घोषणा	INADDR_LOOPBACK		0x7f000001	/* 127.0.0.1   */
#घोषणा	IN_LOOPBACK(a)		((((दीर्घ पूर्णांक) (a)) & 0xff000000) == 0x7f000000)

/* Defines क्रम Multicast INADDR */
#घोषणा INADDR_UNSPEC_GROUP		0xe0000000U	/* 224.0.0.0   */
#घोषणा INADDR_ALLHOSTS_GROUP		0xe0000001U	/* 224.0.0.1   */
#घोषणा INADDR_ALLRTRS_GROUP		0xe0000002U	/* 224.0.0.2 */
#घोषणा INADDR_ALLSNOOPERS_GROUP	0xe000006aU	/* 224.0.0.106 */
#घोषणा INADDR_MAX_LOCAL_GROUP		0xe00000ffU	/* 224.0.0.255 */
#पूर्ण_अगर

/* <यंत्र/byteorder.h> contains the htonl type stuff.. */
#समावेश <यंत्र/byteorder.h> 


#पूर्ण_अगर /* _UAPI_LINUX_IN_H */
