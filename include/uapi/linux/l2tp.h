<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * L2TP-over-IP socket क्रम L2TPv3.
 *
 * Author: James Chapman <jchapman@katalix.com>
 */

#अगर_अघोषित _UAPI_LINUX_L2TP_H_
#घोषणा _UAPI_LINUX_L2TP_H_

#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>

#घोषणा IPPROTO_L2TP		115

/**
 * काष्ठा sockaddr_l2tpip - the sockaddr काष्ठाure क्रम L2TP-over-IP sockets
 * @l2tp_family:  address family number AF_L2TPIP.
 * @l2tp_addr:    protocol specअगरic address inक्रमmation
 * @l2tp_conn_id: connection id of tunnel
 */
#घोषणा __SOCK_SIZE__	16		/* माप(काष्ठा sockaddr)	*/
काष्ठा sockaddr_l2tpip अणु
	/* The first fields must match काष्ठा sockaddr_in */
	__kernel_sa_family_t l2tp_family; /* AF_INET */
	__be16		l2tp_unused;	/* INET port number (unused) */
	काष्ठा in_addr	l2tp_addr;	/* Internet address */

	__u32		l2tp_conn_id;	/* Connection ID of tunnel */

	/* Pad to size of `काष्ठा sockaddr'. */
	अचिन्हित अक्षर	__pad[__SOCK_SIZE__ -
			      माप(__kernel_sa_family_t) -
			      माप(__be16) - माप(काष्ठा in_addr) -
			      माप(__u32)];
पूर्ण;

/**
 * काष्ठा sockaddr_l2tpip6 - the sockaddr काष्ठाure क्रम L2TP-over-IPv6 sockets
 * @l2tp_family:  address family number AF_L2TPIP.
 * @l2tp_addr:    protocol specअगरic address inक्रमmation
 * @l2tp_conn_id: connection id of tunnel
 */
काष्ठा sockaddr_l2tpip6 अणु
	/* The first fields must match काष्ठा sockaddr_in6 */
	__kernel_sa_family_t l2tp_family; /* AF_INET6 */
	__be16		l2tp_unused;	/* INET port number (unused) */
	__be32		l2tp_flowinfo;	/* IPv6 flow inक्रमmation */
	काष्ठा in6_addr	l2tp_addr;	/* IPv6 address */
	__u32		l2tp_scope_id;	/* scope id (new in RFC2553) */
	__u32		l2tp_conn_id;	/* Connection ID of tunnel */
पूर्ण;

/*****************************************************************************
 *  NETLINK_GENERIC netlink family.
 *****************************************************************************/

/*
 * Commands.
 * Valid TLVs of each command are:-
 * TUNNEL_CREATE	- CONN_ID, pw_type, netns, अगरname, ipinfo, udpinfo, udpcsum
 * TUNNEL_DELETE	- CONN_ID
 * TUNNEL_MODIFY	- CONN_ID, udpcsum
 * TUNNEL_GETSTATS	- CONN_ID, (stats)
 * TUNNEL_GET		- CONN_ID, (...)
 * SESSION_CREATE	- SESSION_ID, PW_TYPE, cookie, peer_cookie, l2spec
 * SESSION_DELETE	- SESSION_ID
 * SESSION_MODIFY	- SESSION_ID
 * SESSION_GET		- SESSION_ID, (...)
 * SESSION_GETSTATS	- SESSION_ID, (stats)
 *
 */
क्रमागत अणु
	L2TP_CMD_NOOP,
	L2TP_CMD_TUNNEL_CREATE,
	L2TP_CMD_TUNNEL_DELETE,
	L2TP_CMD_TUNNEL_MODIFY,
	L2TP_CMD_TUNNEL_GET,
	L2TP_CMD_SESSION_CREATE,
	L2TP_CMD_SESSION_DELETE,
	L2TP_CMD_SESSION_MODIFY,
	L2TP_CMD_SESSION_GET,
	__L2TP_CMD_MAX,
पूर्ण;

#घोषणा L2TP_CMD_MAX			(__L2TP_CMD_MAX - 1)

/*
 * ATTR types defined क्रम L2TP
 */
क्रमागत अणु
	L2TP_ATTR_NONE,			/* no data */
	L2TP_ATTR_PW_TYPE,		/* u16, क्रमागत l2tp_pwtype */
	L2TP_ATTR_ENCAP_TYPE,		/* u16, क्रमागत l2tp_encap_type */
	L2TP_ATTR_OFFSET,		/* u16 (not used) */
	L2TP_ATTR_DATA_SEQ,		/* u16 (not used) */
	L2TP_ATTR_L2SPEC_TYPE,		/* u8, क्रमागत l2tp_l2spec_type */
	L2TP_ATTR_L2SPEC_LEN,		/* u8 (not used) */
	L2TP_ATTR_PROTO_VERSION,	/* u8 */
	L2TP_ATTR_IFNAME,		/* string */
	L2TP_ATTR_CONN_ID,		/* u32 */
	L2TP_ATTR_PEER_CONN_ID,		/* u32 */
	L2TP_ATTR_SESSION_ID,		/* u32 */
	L2TP_ATTR_PEER_SESSION_ID,	/* u32 */
	L2TP_ATTR_UDP_CSUM,		/* u8 */
	L2TP_ATTR_VLAN_ID,		/* u16 (not used) */
	L2TP_ATTR_COOKIE,		/* 0, 4 or 8 bytes */
	L2TP_ATTR_PEER_COOKIE,		/* 0, 4 or 8 bytes */
	L2TP_ATTR_DEBUG,		/* u32, क्रमागत l2tp_debug_flags (not used) */
	L2TP_ATTR_RECV_SEQ,		/* u8 */
	L2TP_ATTR_SEND_SEQ,		/* u8 */
	L2TP_ATTR_LNS_MODE,		/* u8 */
	L2TP_ATTR_USING_IPSEC,		/* u8 */
	L2TP_ATTR_RECV_TIMEOUT,		/* msec */
	L2TP_ATTR_FD,			/* पूर्णांक */
	L2TP_ATTR_IP_SADDR,		/* u32 */
	L2TP_ATTR_IP_DADDR,		/* u32 */
	L2TP_ATTR_UDP_SPORT,		/* u16 */
	L2TP_ATTR_UDP_DPORT,		/* u16 */
	L2TP_ATTR_MTU,			/* u16 (not used) */
	L2TP_ATTR_MRU,			/* u16 (not used) */
	L2TP_ATTR_STATS,		/* nested */
	L2TP_ATTR_IP6_SADDR,		/* काष्ठा in6_addr */
	L2TP_ATTR_IP6_DADDR,		/* काष्ठा in6_addr */
	L2TP_ATTR_UDP_ZERO_CSUM6_TX,	/* flag */
	L2TP_ATTR_UDP_ZERO_CSUM6_RX,	/* flag */
	L2TP_ATTR_PAD,
	__L2TP_ATTR_MAX,
पूर्ण;

#घोषणा L2TP_ATTR_MAX			(__L2TP_ATTR_MAX - 1)

/* Nested in L2TP_ATTR_STATS */
क्रमागत अणु
	L2TP_ATTR_STATS_NONE,		/* no data */
	L2TP_ATTR_TX_PACKETS,		/* u64 */
	L2TP_ATTR_TX_BYTES,		/* u64 */
	L2TP_ATTR_TX_ERRORS,		/* u64 */
	L2TP_ATTR_RX_PACKETS,		/* u64 */
	L2TP_ATTR_RX_BYTES,		/* u64 */
	L2TP_ATTR_RX_SEQ_DISCARDS,	/* u64 */
	L2TP_ATTR_RX_OOS_PACKETS,	/* u64 */
	L2TP_ATTR_RX_ERRORS,		/* u64 */
	L2TP_ATTR_STATS_PAD,
	L2TP_ATTR_RX_COOKIE_DISCARDS,	/* u64 */
	L2TP_ATTR_RX_INVALID,		/* u64 */
	__L2TP_ATTR_STATS_MAX,
पूर्ण;

#घोषणा L2TP_ATTR_STATS_MAX		(__L2TP_ATTR_STATS_MAX - 1)

क्रमागत l2tp_pwtype अणु
	L2TP_PWTYPE_NONE = 0x0000,
	L2TP_PWTYPE_ETH_VLAN = 0x0004,
	L2TP_PWTYPE_ETH = 0x0005,
	L2TP_PWTYPE_PPP = 0x0007,
	L2TP_PWTYPE_PPP_AC = 0x0008,
	L2TP_PWTYPE_IP = 0x000b,
	__L2TP_PWTYPE_MAX
पूर्ण;

क्रमागत l2tp_l2spec_type अणु
	L2TP_L2SPECTYPE_NONE,
	L2TP_L2SPECTYPE_DEFAULT,
पूर्ण;

क्रमागत l2tp_encap_type अणु
	L2TP_ENCAPTYPE_UDP,
	L2TP_ENCAPTYPE_IP,
पूर्ण;

/* For L2TP_ATTR_DATA_SEQ. Unused. */
क्रमागत l2tp_seqmode अणु
	L2TP_SEQ_NONE = 0,
	L2TP_SEQ_IP = 1,
	L2TP_SEQ_ALL = 2,
पूर्ण;

/**
 * क्रमागत l2tp_debug_flags - debug message categories क्रम L2TP tunnels/sessions.
 *
 * Unused.
 *
 * @L2TP_MSG_DEBUG: verbose debug (अगर compiled in)
 * @L2TP_MSG_CONTROL: userspace - kernel पूर्णांकerface
 * @L2TP_MSG_SEQ: sequence numbers
 * @L2TP_MSG_DATA: data packets
 */
क्रमागत l2tp_debug_flags अणु
	L2TP_MSG_DEBUG		= (1 << 0),
	L2TP_MSG_CONTROL	= (1 << 1),
	L2TP_MSG_SEQ		= (1 << 2),
	L2TP_MSG_DATA		= (1 << 3),
पूर्ण;

/*
 * NETLINK_GENERIC related info
 */
#घोषणा L2TP_GENL_NAME		"l2tp"
#घोषणा L2TP_GENL_VERSION	0x1
#घोषणा L2TP_GENL_MCGROUP       "l2tp"

#पूर्ण_अगर /* _UAPI_LINUX_L2TP_H_ */
