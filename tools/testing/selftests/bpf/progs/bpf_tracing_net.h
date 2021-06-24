<शैली गुरु>
/* SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause) */
#अगर_अघोषित __BPF_TRACING_NET_H__
#घोषणा __BPF_TRACING_NET_H__

#घोषणा AF_INET			2
#घोषणा AF_INET6		10

#घोषणा ICSK_TIME_RETRANS	1
#घोषणा ICSK_TIME_PROBE0	3
#घोषणा ICSK_TIME_LOSS_PROBE	5
#घोषणा ICSK_TIME_REO_TIMEOUT	6

#घोषणा IFNAMSIZ		16

#घोषणा RTF_GATEWAY		0x0002

#घोषणा TCP_INFINITE_SSTHRESH	0x7fffffff
#घोषणा TCP_PINGPONG_THRESH	3

#घोषणा fib_nh_dev		nh_common.nhc_dev
#घोषणा fib_nh_gw_family	nh_common.nhc_gw_family
#घोषणा fib_nh_gw6		nh_common.nhc_gw.ipv6

#घोषणा inet_daddr		sk.__sk_common.skc_daddr
#घोषणा inet_rcv_saddr		sk.__sk_common.skc_rcv_saddr
#घोषणा inet_dport		sk.__sk_common.skc_dport

#घोषणा ir_loc_addr		req.__req_common.skc_rcv_saddr
#घोषणा ir_num			req.__req_common.skc_num
#घोषणा ir_rmt_addr		req.__req_common.skc_daddr
#घोषणा ir_rmt_port		req.__req_common.skc_dport
#घोषणा ir_v6_rmt_addr		req.__req_common.skc_v6_daddr
#घोषणा ir_v6_loc_addr		req.__req_common.skc_v6_rcv_saddr

#घोषणा sk_family		__sk_common.skc_family
#घोषणा sk_rmem_alloc		sk_backlog.rmem_alloc
#घोषणा sk_refcnt		__sk_common.skc_refcnt
#घोषणा sk_state		__sk_common.skc_state
#घोषणा sk_v6_daddr		__sk_common.skc_v6_daddr
#घोषणा sk_v6_rcv_saddr		__sk_common.skc_v6_rcv_saddr

#घोषणा s6_addr32		in6_u.u6_addr32

#घोषणा tw_daddr		__tw_common.skc_daddr
#घोषणा tw_rcv_saddr		__tw_common.skc_rcv_saddr
#घोषणा tw_dport		__tw_common.skc_dport
#घोषणा tw_refcnt		__tw_common.skc_refcnt
#घोषणा tw_v6_daddr		__tw_common.skc_v6_daddr
#घोषणा tw_v6_rcv_saddr		__tw_common.skc_v6_rcv_saddr

#पूर्ण_अगर
