<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *	Types and definitions क्रम AF_INET6 
 *	Linux INET6 implementation 
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>	
 *
 *	Sources:
 *	IPv6 Program Interfaces क्रम BSD Systems
 *      <draft-ietf-ipngwg-bsd-api-05.txt>
 *
 *	Advanced Sockets API क्रम IPv6
 *	<draft-stevens-advanced-api-00.txt>
 *
 *	This program is मुक्त software; you can redistribute it and/or
 *      modअगरy it under the terms of the GNU General Public License
 *      as published by the Free Software Foundation; either version
 *      2 of the License, or (at your option) any later version.
 */

#अगर_अघोषित _UAPI_LINUX_IN6_H
#घोषणा _UAPI_LINUX_IN6_H

#समावेश <linux/types.h>
#समावेश <linux/libc-compat.h>

/*
 *	IPv6 address काष्ठाure
 */

#अगर __UAPI_DEF_IN6_ADDR
काष्ठा in6_addr अणु
	जोड़ अणु
		__u8		u6_addr8[16];
#अगर __UAPI_DEF_IN6_ADDR_ALT
		__be16		u6_addr16[8];
		__be32		u6_addr32[4];
#पूर्ण_अगर
	पूर्ण in6_u;
#घोषणा s6_addr			in6_u.u6_addr8
#अगर __UAPI_DEF_IN6_ADDR_ALT
#घोषणा s6_addr16		in6_u.u6_addr16
#घोषणा s6_addr32		in6_u.u6_addr32
#पूर्ण_अगर
पूर्ण;
#पूर्ण_अगर /* __UAPI_DEF_IN6_ADDR */

#अगर __UAPI_DEF_SOCKADDR_IN6
काष्ठा sockaddr_in6 अणु
	अचिन्हित लघु पूर्णांक	sin6_family;    /* AF_INET6 */
	__be16			sin6_port;      /* Transport layer port # */
	__be32			sin6_flowinfo;  /* IPv6 flow inक्रमmation */
	काष्ठा in6_addr		sin6_addr;      /* IPv6 address */
	__u32			sin6_scope_id;  /* scope id (new in RFC2553) */
पूर्ण;
#पूर्ण_अगर /* __UAPI_DEF_SOCKADDR_IN6 */

#अगर __UAPI_DEF_IPV6_MREQ
काष्ठा ipv6_mreq अणु
	/* IPv6 multicast address of group */
	काष्ठा in6_addr ipv6mr_multiaddr;

	/* local IPv6 address of पूर्णांकerface */
	पूर्णांक		ipv6mr_अगरindex;
पूर्ण;
#पूर्ण_अगर /* __UAPI_DEF_IVP6_MREQ */

#घोषणा ipv6mr_acaddr	ipv6mr_multiaddr

काष्ठा in6_flowlabel_req अणु
	काष्ठा in6_addr	flr_dst;
	__be32	flr_label;
	__u8	flr_action;
	__u8	flr_share;
	__u16	flr_flags;
	__u16 	flr_expires;
	__u16	flr_linger;
	__u32	__flr_pad;
	/* Options in क्रमmat of IPV6_PKTOPTIONS */
पूर्ण;

#घोषणा IPV6_FL_A_GET	0
#घोषणा IPV6_FL_A_PUT	1
#घोषणा IPV6_FL_A_RENEW	2

#घोषणा IPV6_FL_F_CREATE	1
#घोषणा IPV6_FL_F_EXCL		2
#घोषणा IPV6_FL_F_REFLECT	4
#घोषणा IPV6_FL_F_REMOTE	8

#घोषणा IPV6_FL_S_NONE		0
#घोषणा IPV6_FL_S_EXCL		1
#घोषणा IPV6_FL_S_PROCESS	2
#घोषणा IPV6_FL_S_USER		3
#घोषणा IPV6_FL_S_ANY		255


/*
 *	Biपंचांगask स्थिरant declarations to help applications select out the 
 *	flow label and priority fields.
 *
 *	Note that this are in host byte order जबतक the flowinfo field of
 *	sockaddr_in6 is in network byte order.
 */

#घोषणा IPV6_FLOWINFO_FLOWLABEL		0x000fffff
#घोषणा IPV6_FLOWINFO_PRIORITY		0x0ff00000

/* These definitions are obsolete */
#घोषणा IPV6_PRIORITY_UNCHARACTERIZED	0x0000
#घोषणा IPV6_PRIORITY_FILLER		0x0100
#घोषणा IPV6_PRIORITY_UNATTENDED	0x0200
#घोषणा IPV6_PRIORITY_RESERVED1		0x0300
#घोषणा IPV6_PRIORITY_BULK		0x0400
#घोषणा IPV6_PRIORITY_RESERVED2		0x0500
#घोषणा IPV6_PRIORITY_INTERACTIVE	0x0600
#घोषणा IPV6_PRIORITY_CONTROL		0x0700
#घोषणा IPV6_PRIORITY_8			0x0800
#घोषणा IPV6_PRIORITY_9			0x0900
#घोषणा IPV6_PRIORITY_10		0x0a00
#घोषणा IPV6_PRIORITY_11		0x0b00
#घोषणा IPV6_PRIORITY_12		0x0c00
#घोषणा IPV6_PRIORITY_13		0x0d00
#घोषणा IPV6_PRIORITY_14		0x0e00
#घोषणा IPV6_PRIORITY_15		0x0f00

/*
 *	IPV6 extension headers
 */
#अगर __UAPI_DEF_IPPROTO_V6
#घोषणा IPPROTO_HOPOPTS		0	/* IPv6 hop-by-hop options	*/
#घोषणा IPPROTO_ROUTING		43	/* IPv6 routing header		*/
#घोषणा IPPROTO_FRAGMENT	44	/* IPv6 fragmentation header	*/
#घोषणा IPPROTO_ICMPV6		58	/* ICMPv6			*/
#घोषणा IPPROTO_NONE		59	/* IPv6 no next header		*/
#घोषणा IPPROTO_DSTOPTS		60	/* IPv6 destination options	*/
#घोषणा IPPROTO_MH		135	/* IPv6 mobility header		*/
#पूर्ण_अगर /* __UAPI_DEF_IPPROTO_V6 */

/*
 *	IPv6 TLV options.
 */
#घोषणा IPV6_TLV_PAD1		0
#घोषणा IPV6_TLV_PADN		1
#घोषणा IPV6_TLV_ROUTERALERT	5
#घोषणा IPV6_TLV_CALIPSO	7	/* RFC 5570 */
#घोषणा IPV6_TLV_JUMBO		194
#घोषणा IPV6_TLV_HAO		201	/* home address option */

/*
 *	IPV6 socket options
 */
#अगर __UAPI_DEF_IPV6_OPTIONS
#घोषणा IPV6_ADDRFORM		1
#घोषणा IPV6_2292PKTINFO	2
#घोषणा IPV6_2292HOPOPTS	3
#घोषणा IPV6_2292DSTOPTS	4
#घोषणा IPV6_2292RTHDR		5
#घोषणा IPV6_2292PKTOPTIONS	6
#घोषणा IPV6_CHECKSUM		7
#घोषणा IPV6_2292HOPLIMIT	8
#घोषणा IPV6_NEXTHOP		9
#घोषणा IPV6_AUTHHDR		10	/* obsolete */
#घोषणा IPV6_FLOWINFO		11

#घोषणा IPV6_UNICAST_HOPS	16
#घोषणा IPV6_MULTICAST_IF	17
#घोषणा IPV6_MULTICAST_HOPS	18
#घोषणा IPV6_MULTICAST_LOOP	19
#घोषणा IPV6_ADD_MEMBERSHIP	20
#घोषणा IPV6_DROP_MEMBERSHIP	21
#घोषणा IPV6_ROUTER_ALERT	22
#घोषणा IPV6_MTU_DISCOVER	23
#घोषणा IPV6_MTU		24
#घोषणा IPV6_RECVERR		25
#घोषणा IPV6_V6ONLY		26
#घोषणा IPV6_JOIN_ANYCAST	27
#घोषणा IPV6_LEAVE_ANYCAST	28
#घोषणा IPV6_MULTICAST_ALL	29
#घोषणा IPV6_ROUTER_ALERT_ISOLATE	30
#घोषणा IPV6_RECVERR_RFC4884	31

/* IPV6_MTU_DISCOVER values */
#घोषणा IPV6_PMTUDISC_DONT		0
#घोषणा IPV6_PMTUDISC_WANT		1
#घोषणा IPV6_PMTUDISC_DO		2
#घोषणा IPV6_PMTUDISC_PROBE		3
/* same as IPV6_PMTUDISC_PROBE, provided क्रम symetry with IPv4
 * also see comments on IP_PMTUDISC_INTERFACE
 */
#घोषणा IPV6_PMTUDISC_INTERFACE		4
/* weaker version of IPV6_PMTUDISC_INTERFACE, which allows packets to
 * get fragmented अगर they exceed the पूर्णांकerface mtu
 */
#घोषणा IPV6_PMTUDISC_OMIT		5

/* Flowlabel */
#घोषणा IPV6_FLOWLABEL_MGR	32
#घोषणा IPV6_FLOWINFO_SEND	33

#घोषणा IPV6_IPSEC_POLICY	34
#घोषणा IPV6_XFRM_POLICY	35
#घोषणा IPV6_HDRINCL		36
#पूर्ण_अगर

/*
 * Multicast:
 * Following socket options are shared between IPv4 and IPv6.
 *
 * MCAST_JOIN_GROUP		42
 * MCAST_BLOCK_SOURCE		43
 * MCAST_UNBLOCK_SOURCE		44
 * MCAST_LEAVE_GROUP		45
 * MCAST_JOIN_SOURCE_GROUP	46
 * MCAST_LEAVE_SOURCE_GROUP	47
 * MCAST_MSFILTER		48
 */

/*
 * Advanced API (RFC3542) (1)
 *
 * Note: IPV6_RECVRTHDRDSTOPTS करोes not exist. see net/ipv6/datagram.c.
 */

#घोषणा IPV6_RECVPKTINFO	49
#घोषणा IPV6_PKTINFO		50
#घोषणा IPV6_RECVHOPLIMIT	51
#घोषणा IPV6_HOPLIMIT		52
#घोषणा IPV6_RECVHOPOPTS	53
#घोषणा IPV6_HOPOPTS		54
#घोषणा IPV6_RTHDRDSTOPTS	55
#घोषणा IPV6_RECVRTHDR		56
#घोषणा IPV6_RTHDR		57
#घोषणा IPV6_RECVDSTOPTS	58
#घोषणा IPV6_DSTOPTS		59
#घोषणा IPV6_RECVPATHMTU	60
#घोषणा IPV6_PATHMTU		61
#घोषणा IPV6_DONTFRAG		62
#अगर 0	/* not yet */
#घोषणा IPV6_USE_MIN_MTU	63
#पूर्ण_अगर

/*
 * Netfilter (1)
 *
 * Following socket options are used in ip6_tables;
 * see include/linux/netfilter_ipv6/ip6_tables.h.
 *
 * IP6T_SO_SET_REPLACE / IP6T_SO_GET_INFO		64
 * IP6T_SO_SET_ADD_COUNTERS / IP6T_SO_GET_ENTRIES	65
 */

/*
 * Advanced API (RFC3542) (2)
 */
#घोषणा IPV6_RECVTCLASS		66
#घोषणा IPV6_TCLASS		67

/*
 * Netfilter (2)
 *
 * Following socket options are used in ip6_tables;
 * see include/linux/netfilter_ipv6/ip6_tables.h.
 *
 * IP6T_SO_GET_REVISION_MATCH	68
 * IP6T_SO_GET_REVISION_TARGET	69
 * IP6T_SO_ORIGINAL_DST		80
 */

#घोषणा IPV6_AUTOFLOWLABEL	70
/* RFC5014: Source address selection */
#घोषणा IPV6_ADDR_PREFERENCES	72

#घोषणा IPV6_PREFER_SRC_TMP		0x0001
#घोषणा IPV6_PREFER_SRC_PUBLIC		0x0002
#घोषणा IPV6_PREFER_SRC_PUBTMP_DEFAULT	0x0100
#घोषणा IPV6_PREFER_SRC_COA		0x0004
#घोषणा IPV6_PREFER_SRC_HOME		0x0400
#घोषणा IPV6_PREFER_SRC_CGA		0x0008
#घोषणा IPV6_PREFER_SRC_NONCGA		0x0800

/* RFC5082: Generalized Ttl Security Mechanism */
#घोषणा IPV6_MINHOPCOUNT		73

#घोषणा IPV6_ORIGDSTADDR        74
#घोषणा IPV6_RECVORIGDSTADDR    IPV6_ORIGDSTADDR
#घोषणा IPV6_TRANSPARENT        75
#घोषणा IPV6_UNICAST_IF         76
#घोषणा IPV6_RECVFRAGSIZE	77
#घोषणा IPV6_FREEBIND		78

/*
 * Multicast Routing:
 * see include/uapi/linux/mroute6.h.
 *
 * MRT6_BASE			200
 * ...
 * MRT6_MAX
 */
#पूर्ण_अगर /* _UAPI_LINUX_IN6_H */
