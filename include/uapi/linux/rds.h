<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR Linux-OpenIB) */
/*
 * Copyright (c) 2008, 2018 Oracle and/or its affiliates. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#अगर_अघोषित _LINUX_RDS_H
#घोषणा _LINUX_RDS_H

#समावेश <linux/types.h>
#समावेश <linux/socket.h>		/* For __kernel_sockaddr_storage. */
#समावेश <linux/in6.h>			/* For काष्ठा in6_addr. */

#घोषणा RDS_IB_ABI_VERSION		0x301

#घोषणा	SOL_RDS		276

/*
 * setsockopt/माला_लोockopt क्रम SOL_RDS
 */
#घोषणा RDS_CANCEL_SENT_TO      	1
#घोषणा RDS_GET_MR			2
#घोषणा RDS_FREE_MR			3
/* deprecated: RDS_BARRIER 4 */
#घोषणा RDS_RECVERR			5
#घोषणा RDS_CONG_MONITOR		6
#घोषणा RDS_GET_MR_FOR_DEST		7
#घोषणा SO_RDS_TRANSPORT		8

/* Socket option to tap receive path latency
 *	SO_RDS: SO_RDS_MSG_RXPATH_LATENCY
 *	Format used काष्ठा rds_rx_trace_so
 */
#घोषणा SO_RDS_MSG_RXPATH_LATENCY	10


/* supported values क्रम SO_RDS_TRANSPORT */
#घोषणा	RDS_TRANS_IB	0
#घोषणा	RDS_TRANS_GAP	1
#घोषणा	RDS_TRANS_TCP	2
#घोषणा RDS_TRANS_COUNT	3
#घोषणा	RDS_TRANS_NONE	(~0)
/* करोn't use RDS_TRANS_IWARP - it is deprecated */
#घोषणा RDS_TRANS_IWARP RDS_TRANS_GAP

/* IOCTLS commands क्रम SOL_RDS */
#घोषणा SIOCRDSSETTOS		(SIOCPROTOPRIVATE)
#घोषणा SIOCRDSGETTOS		(SIOCPROTOPRIVATE + 1)

प्रकार __u8	rds_tos_t;

/*
 * Control message types क्रम SOL_RDS.
 *
 * CMSG_RDMA_ARGS (sendmsg)
 *	Request a RDMA transfer to/from the specअगरied
 *	memory ranges.
 *	The cmsg_data is a काष्ठा rds_rdma_args.
 * RDS_CMSG_RDMA_DEST (recvmsg, sendmsg)
 *	Kernel inक्रमms application about पूर्णांकended
 *	source/destination of a RDMA transfer
 * RDS_CMSG_RDMA_MAP (sendmsg)
 *	Application asks kernel to map the given
 *	memory range पूर्णांकo a IB MR, and send the
 *	R_Key aदीर्घ in an RDS extension header.
 *	The cmsg_data is a काष्ठा rds_get_mr_args,
 *	the same as क्रम the GET_MR setsockopt.
 * RDS_CMSG_RDMA_STATUS (recvmsg)
 *	Returns the status of a completed RDMA operation.
 * RDS_CMSG_RXPATH_LATENCY(recvmsg)
 *	Returns rds message latencies in various stages of receive
 *	path in nS. Its set per socket using SO_RDS_MSG_RXPATH_LATENCY
 *	socket option. Legitimate poपूर्णांकs are defined in
 *	क्रमागत rds_message_rxpath_latency. More poपूर्णांकs can be added in
 *	future. CSMG क्रमmat is काष्ठा rds_cmsg_rx_trace.
 */
#घोषणा RDS_CMSG_RDMA_ARGS		1
#घोषणा RDS_CMSG_RDMA_DEST		2
#घोषणा RDS_CMSG_RDMA_MAP		3
#घोषणा RDS_CMSG_RDMA_STATUS		4
#घोषणा RDS_CMSG_CONG_UPDATE		5
#घोषणा RDS_CMSG_ATOMIC_FADD		6
#घोषणा RDS_CMSG_ATOMIC_CSWP		7
#घोषणा RDS_CMSG_MASKED_ATOMIC_FADD	8
#घोषणा RDS_CMSG_MASKED_ATOMIC_CSWP	9
#घोषणा RDS_CMSG_RXPATH_LATENCY		11
#घोषणा	RDS_CMSG_ZCOPY_COOKIE		12
#घोषणा	RDS_CMSG_ZCOPY_COMPLETION	13

#घोषणा RDS_INFO_FIRST			10000
#घोषणा RDS_INFO_COUNTERS		10000
#घोषणा RDS_INFO_CONNECTIONS		10001
/* 10002 aka RDS_INFO_FLOWS is deprecated */
#घोषणा RDS_INFO_SEND_MESSAGES		10003
#घोषणा RDS_INFO_RETRANS_MESSAGES       10004
#घोषणा RDS_INFO_RECV_MESSAGES          10005
#घोषणा RDS_INFO_SOCKETS                10006
#घोषणा RDS_INFO_TCP_SOCKETS            10007
#घोषणा RDS_INFO_IB_CONNECTIONS		10008
#घोषणा RDS_INFO_CONNECTION_STATS	10009
#घोषणा RDS_INFO_IWARP_CONNECTIONS	10010

/* PF_RDS6 options */
#घोषणा RDS6_INFO_CONNECTIONS		10011
#घोषणा RDS6_INFO_SEND_MESSAGES		10012
#घोषणा RDS6_INFO_RETRANS_MESSAGES	10013
#घोषणा RDS6_INFO_RECV_MESSAGES		10014
#घोषणा RDS6_INFO_SOCKETS		10015
#घोषणा RDS6_INFO_TCP_SOCKETS		10016
#घोषणा RDS6_INFO_IB_CONNECTIONS	10017

#घोषणा RDS_INFO_LAST			10017

काष्ठा rds_info_counter अणु
	__u8	name[32];
	__u64	value;
पूर्ण __attribute__((packed));

#घोषणा RDS_INFO_CONNECTION_FLAG_SENDING	0x01
#घोषणा RDS_INFO_CONNECTION_FLAG_CONNECTING	0x02
#घोषणा RDS_INFO_CONNECTION_FLAG_CONNECTED	0x04

#घोषणा TRANSNAMSIZ	16

काष्ठा rds_info_connection अणु
	__u64		next_tx_seq;
	__u64		next_rx_seq;
	__be32		laddr;
	__be32		faddr;
	__u8		transport[TRANSNAMSIZ];		/* null term ascii */
	__u8		flags;
	__u8		tos;
पूर्ण __attribute__((packed));

काष्ठा rds6_info_connection अणु
	__u64		next_tx_seq;
	__u64		next_rx_seq;
	काष्ठा in6_addr	laddr;
	काष्ठा in6_addr	faddr;
	__u8		transport[TRANSNAMSIZ];		/* null term ascii */
	__u8		flags;
पूर्ण __attribute__((packed));

#घोषणा RDS_INFO_MESSAGE_FLAG_ACK               0x01
#घोषणा RDS_INFO_MESSAGE_FLAG_FAST_ACK          0x02

काष्ठा rds_info_message अणु
	__u64		seq;
	__u32		len;
	__be32		laddr;
	__be32		faddr;
	__be16		lport;
	__be16		fport;
	__u8		flags;
	__u8		tos;
पूर्ण __attribute__((packed));

काष्ठा rds6_info_message अणु
	__u64	seq;
	__u32	len;
	काष्ठा in6_addr	laddr;
	काष्ठा in6_addr	faddr;
	__be16		lport;
	__be16		fport;
	__u8		flags;
	__u8		tos;
पूर्ण __attribute__((packed));

काष्ठा rds_info_socket अणु
	__u32		sndbuf;
	__be32		bound_addr;
	__be32		connected_addr;
	__be16		bound_port;
	__be16		connected_port;
	__u32		rcvbuf;
	__u64		inum;
पूर्ण __attribute__((packed));

काष्ठा rds6_info_socket अणु
	__u32		sndbuf;
	काष्ठा in6_addr	bound_addr;
	काष्ठा in6_addr	connected_addr;
	__be16		bound_port;
	__be16		connected_port;
	__u32		rcvbuf;
	__u64		inum;
पूर्ण __attribute__((packed));

काष्ठा rds_info_tcp_socket अणु
	__be32          local_addr;
	__be16          local_port;
	__be32          peer_addr;
	__be16          peer_port;
	__u64           hdr_rem;
	__u64           data_rem;
	__u32           last_sent_nxt;
	__u32           last_expected_una;
	__u32           last_seen_una;
	__u8		tos;
पूर्ण __attribute__((packed));

काष्ठा rds6_info_tcp_socket अणु
	काष्ठा in6_addr	local_addr;
	__be16		local_port;
	काष्ठा in6_addr	peer_addr;
	__be16		peer_port;
	__u64		hdr_rem;
	__u64		data_rem;
	__u32		last_sent_nxt;
	__u32		last_expected_una;
	__u32		last_seen_una;
पूर्ण __attribute__((packed));

#घोषणा RDS_IB_GID_LEN	16
काष्ठा rds_info_rdma_connection अणु
	__be32		src_addr;
	__be32		dst_addr;
	__u8		src_gid[RDS_IB_GID_LEN];
	__u8		dst_gid[RDS_IB_GID_LEN];

	__u32		max_send_wr;
	__u32		max_recv_wr;
	__u32		max_send_sge;
	__u32		rdma_mr_max;
	__u32		rdma_mr_size;
	__u8		tos;
	__u8		sl;
	__u32		cache_allocs;
पूर्ण;

काष्ठा rds6_info_rdma_connection अणु
	काष्ठा in6_addr	src_addr;
	काष्ठा in6_addr	dst_addr;
	__u8		src_gid[RDS_IB_GID_LEN];
	__u8		dst_gid[RDS_IB_GID_LEN];

	__u32		max_send_wr;
	__u32		max_recv_wr;
	__u32		max_send_sge;
	__u32		rdma_mr_max;
	__u32		rdma_mr_size;
	__u8		tos;
	__u8		sl;
	__u32		cache_allocs;
पूर्ण;

/* RDS message Receive Path Latency poपूर्णांकs */
क्रमागत rds_message_rxpath_latency अणु
	RDS_MSG_RX_HDR_TO_DGRAM_START = 0,
	RDS_MSG_RX_DGRAM_REASSEMBLE,
	RDS_MSG_RX_DGRAM_DELIVERED,
	RDS_MSG_RX_DGRAM_TRACE_MAX
पूर्ण;

काष्ठा rds_rx_trace_so अणु
	__u8 rx_traces;
	__u8 rx_trace_pos[RDS_MSG_RX_DGRAM_TRACE_MAX];
पूर्ण;

काष्ठा rds_cmsg_rx_trace अणु
	__u8 rx_traces;
	__u8 rx_trace_pos[RDS_MSG_RX_DGRAM_TRACE_MAX];
	__u64 rx_trace[RDS_MSG_RX_DGRAM_TRACE_MAX];
पूर्ण;

/*
 * Congestion monitoring.
 * Congestion control in RDS happens at the host connection
 * level by exchanging a biपंचांगap marking congested ports.
 * By शेष, a process sleeping in poll() is always woken
 * up when the congestion map is updated.
 * With explicit monitoring, an application can have more
 * fine-grained control.
 * The application installs a 64bit mask value in the socket,
 * where each bit corresponds to a group of ports.
 * When a congestion update arrives, RDS checks the set of
 * ports that are now uncongested against the list bit mask
 * installed in the socket, and अगर they overlap, we queue a
 * cong_notअगरication on the socket.
 *
 * To install the congestion monitor biपंचांगask, use RDS_CONG_MONITOR
 * with the 64bit mask.
 * Congestion updates are received via RDS_CMSG_CONG_UPDATE
 * control messages.
 *
 * The correspondence between bits and ports is
 *	1 << (portnum % 64)
 */
#घोषणा RDS_CONG_MONITOR_SIZE	64
#घोषणा RDS_CONG_MONITOR_BIT(port)  (((अचिन्हित पूर्णांक) port) % RDS_CONG_MONITOR_SIZE)
#घोषणा RDS_CONG_MONITOR_MASK(port) (1ULL << RDS_CONG_MONITOR_BIT(port))

/*
 * RDMA related types
 */

/*
 * This encapsulates a remote memory location.
 * In the current implementation, it contains the R_Key
 * of the remote memory region, and the offset पूर्णांकo it
 * (so that the application करोes not have to worry about
 * alignment).
 */
प्रकार __u64		rds_rdma_cookie_t;

काष्ठा rds_iovec अणु
	__u64		addr;
	__u64		bytes;
पूर्ण;

काष्ठा rds_get_mr_args अणु
	काष्ठा rds_iovec vec;
	__u64		cookie_addr;
	__u64		flags;
पूर्ण;

काष्ठा rds_get_mr_क्रम_dest_args अणु
	काष्ठा __kernel_sockaddr_storage dest_addr;
	काष्ठा rds_iovec 	vec;
	__u64			cookie_addr;
	__u64			flags;
पूर्ण;

काष्ठा rds_मुक्त_mr_args अणु
	rds_rdma_cookie_t cookie;
	__u64		flags;
पूर्ण;

काष्ठा rds_rdma_args अणु
	rds_rdma_cookie_t cookie;
	काष्ठा rds_iovec remote_vec;
	__u64		local_vec_addr;
	__u64		nr_local;
	__u64		flags;
	__u64		user_token;
पूर्ण;

काष्ठा rds_atomic_args अणु
	rds_rdma_cookie_t cookie;
	__u64		local_addr;
	__u64		remote_addr;
	जोड़ अणु
		काष्ठा अणु
			__u64		compare;
			__u64		swap;
		पूर्ण cswp;
		काष्ठा अणु
			__u64		add;
		पूर्ण fadd;
		काष्ठा अणु
			__u64		compare;
			__u64		swap;
			__u64		compare_mask;
			__u64		swap_mask;
		पूर्ण m_cswp;
		काष्ठा अणु
			__u64		add;
			__u64		nocarry_mask;
		पूर्ण m_fadd;
	पूर्ण;
	__u64		flags;
	__u64		user_token;
पूर्ण;

काष्ठा rds_rdma_notअगरy अणु
	__u64		user_token;
	__s32		status;
पूर्ण;

#घोषणा RDS_RDMA_SUCCESS	0
#घोषणा RDS_RDMA_REMOTE_ERROR	1
#घोषणा RDS_RDMA_CANCELED	2
#घोषणा RDS_RDMA_DROPPED	3
#घोषणा RDS_RDMA_OTHER_ERROR	4

#घोषणा	RDS_MAX_ZCOOKIES	8
काष्ठा rds_zcopy_cookies अणु
	__u32 num;
	__u32 cookies[RDS_MAX_ZCOOKIES];
पूर्ण;

/*
 * Common set of flags क्रम all RDMA related काष्ठाs
 */
#घोषणा RDS_RDMA_READWRITE	0x0001
#घोषणा RDS_RDMA_FENCE		0x0002	/* use FENCE क्रम immediate send */
#घोषणा RDS_RDMA_INVALIDATE	0x0004	/* invalidate R_Key after मुक्तing MR */
#घोषणा RDS_RDMA_USE_ONCE	0x0008	/* मुक्त MR after use */
#घोषणा RDS_RDMA_DONTWAIT	0x0010	/* Don't रुको in SET_BARRIER */
#घोषणा RDS_RDMA_NOTIFY_ME	0x0020	/* Notअगरy when operation completes */
#घोषणा RDS_RDMA_SILENT		0x0040	/* Do not पूर्णांकerrupt remote */

#पूर्ण_अगर /* IB_RDS_H */
