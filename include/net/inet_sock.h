<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम inet_sock
 *
 * Authors:	Many, reorganised here by
 * 		Arnalकरो Carvalho de Melo <acme@mandriva.com>
 */
#अगर_अघोषित _INET_SOCK_H
#घोषणा _INET_SOCK_H

#समावेश <linux/bitops.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/jhash.h>
#समावेश <linux/netdevice.h>

#समावेश <net/flow.h>
#समावेश <net/sock.h>
#समावेश <net/request_sock.h>
#समावेश <net/netns/hash.h>
#समावेश <net/tcp_states.h>
#समावेश <net/l3mdev.h>

/** काष्ठा ip_options - IP Options
 *
 * @faddr - Saved first hop address
 * @nexthop - Saved nexthop address in LSRR and SSRR
 * @is_strictroute - Strict source route
 * @srr_is_hit - Packet destination addr was our one
 * @is_changed - IP checksum more not valid
 * @rr_needaddr - Need to record addr of outgoing dev
 * @ts_needसमय - Need to record बारtamp
 * @ts_needaddr - Need to record addr of outgoing dev
 */
काष्ठा ip_options अणु
	__be32		faddr;
	__be32		nexthop;
	अचिन्हित अक्षर	optlen;
	अचिन्हित अक्षर	srr;
	अचिन्हित अक्षर	rr;
	अचिन्हित अक्षर	ts;
	अचिन्हित अक्षर	is_strictroute:1,
			srr_is_hit:1,
			is_changed:1,
			rr_needaddr:1,
			ts_needसमय:1,
			ts_needaddr:1;
	अचिन्हित अक्षर	router_alert;
	अचिन्हित अक्षर	cipso;
	अचिन्हित अक्षर	__pad2;
	अचिन्हित अक्षर	__data[];
पूर्ण;

काष्ठा ip_options_rcu अणु
	काष्ठा rcu_head rcu;
	काष्ठा ip_options opt;
पूर्ण;

काष्ठा ip_options_data अणु
	काष्ठा ip_options_rcu	opt;
	अक्षर			data[40];
पूर्ण;

काष्ठा inet_request_sock अणु
	काष्ठा request_sock	req;
#घोषणा ir_loc_addr		req.__req_common.skc_rcv_saddr
#घोषणा ir_rmt_addr		req.__req_common.skc_daddr
#घोषणा ir_num			req.__req_common.skc_num
#घोषणा ir_rmt_port		req.__req_common.skc_dport
#घोषणा ir_v6_rmt_addr		req.__req_common.skc_v6_daddr
#घोषणा ir_v6_loc_addr		req.__req_common.skc_v6_rcv_saddr
#घोषणा ir_iअगर			req.__req_common.skc_bound_dev_अगर
#घोषणा ir_cookie		req.__req_common.skc_cookie
#घोषणा ireq_net		req.__req_common.skc_net
#घोषणा ireq_state		req.__req_common.skc_state
#घोषणा ireq_family		req.__req_common.skc_family

	u16			snd_wscale : 4,
				rcv_wscale : 4,
				tstamp_ok  : 1,
				sack_ok	   : 1,
				wscale_ok  : 1,
				ecn_ok	   : 1,
				acked	   : 1,
				no_srccheck: 1,
				smc_ok	   : 1;
	u32                     ir_mark;
	जोड़ अणु
		काष्ठा ip_options_rcu __rcu	*ireq_opt;
#अगर IS_ENABLED(CONFIG_IPV6)
		काष्ठा अणु
			काष्ठा ipv6_txoptions	*ipv6_opt;
			काष्ठा sk_buff		*pktopts;
		पूर्ण;
#पूर्ण_अगर
	पूर्ण;
पूर्ण;

अटल अंतरभूत काष्ठा inet_request_sock *inet_rsk(स्थिर काष्ठा request_sock *sk)
अणु
	वापस (काष्ठा inet_request_sock *)sk;
पूर्ण

अटल अंतरभूत u32 inet_request_mark(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अगर (!sk->sk_mark && sock_net(sk)->ipv4.sysctl_tcp_fwmark_accept)
		वापस skb->mark;

	वापस sk->sk_mark;
पूर्ण

अटल अंतरभूत पूर्णांक inet_request_bound_dev_अगर(स्थिर काष्ठा sock *sk,
					    काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
	काष्ठा net *net = sock_net(sk);

	अगर (!sk->sk_bound_dev_अगर && net->ipv4.sysctl_tcp_l3mdev_accept)
		वापस l3mdev_master_अगरindex_by_index(net, skb->skb_iअगर);
#पूर्ण_अगर

	वापस sk->sk_bound_dev_अगर;
पूर्ण

अटल अंतरभूत पूर्णांक inet_sk_bound_l3mdev(स्थिर काष्ठा sock *sk)
अणु
#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
	काष्ठा net *net = sock_net(sk);

	अगर (!net->ipv4.sysctl_tcp_l3mdev_accept)
		वापस l3mdev_master_अगरindex_by_index(net,
						      sk->sk_bound_dev_अगर);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल अंतरभूत bool inet_bound_dev_eq(bool l3mdev_accept, पूर्णांक bound_dev_अगर,
				     पूर्णांक dअगर, पूर्णांक sdअगर)
अणु
	अगर (!bound_dev_अगर)
		वापस !sdअगर || l3mdev_accept;
	वापस bound_dev_अगर == dअगर || bound_dev_अगर == sdअगर;
पूर्ण

काष्ठा inet_cork अणु
	अचिन्हित पूर्णांक		flags;
	__be32			addr;
	काष्ठा ip_options	*opt;
	अचिन्हित पूर्णांक		fragsize;
	पूर्णांक			length; /* Total length of all frames */
	काष्ठा dst_entry	*dst;
	u8			tx_flags;
	__u8			ttl;
	__s16			tos;
	अक्षर			priority;
	__u16			gso_size;
	u64			transmit_समय;
	u32			mark;
पूर्ण;

काष्ठा inet_cork_full अणु
	काष्ठा inet_cork	base;
	काष्ठा flowi		fl;
पूर्ण;

काष्ठा ip_mc_socklist;
काष्ठा ipv6_pinfo;
काष्ठा rtable;

/** काष्ठा inet_sock - representation of INET sockets
 *
 * @sk - ancestor class
 * @pinet6 - poपूर्णांकer to IPv6 control block
 * @inet_daddr - Foreign IPv4 addr
 * @inet_rcv_saddr - Bound local IPv4 addr
 * @inet_dport - Destination port
 * @inet_num - Local port
 * @inet_saddr - Sending source
 * @uc_ttl - Unicast TTL
 * @inet_sport - Source port
 * @inet_id - ID counter क्रम DF pkts
 * @tos - TOS
 * @mc_ttl - Multicasting TTL
 * @is_icsk - is this an inet_connection_sock?
 * @uc_index - Unicast outgoing device index
 * @mc_index - Multicast device index
 * @mc_list - Group array
 * @cork - info to build ip hdr on each ip frag जबतक socket is corked
 */
काष्ठा inet_sock अणु
	/* sk and pinet6 has to be the first two members of inet_sock */
	काष्ठा sock		sk;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा ipv6_pinfo	*pinet6;
#पूर्ण_अगर
	/* Socket demultiplex comparisons on incoming packets. */
#घोषणा inet_daddr		sk.__sk_common.skc_daddr
#घोषणा inet_rcv_saddr		sk.__sk_common.skc_rcv_saddr
#घोषणा inet_dport		sk.__sk_common.skc_dport
#घोषणा inet_num		sk.__sk_common.skc_num

	__be32			inet_saddr;
	__s16			uc_ttl;
	__u16			cmsg_flags;
	__be16			inet_sport;
	__u16			inet_id;

	काष्ठा ip_options_rcu __rcu	*inet_opt;
	पूर्णांक			rx_dst_अगरindex;
	__u8			tos;
	__u8			min_ttl;
	__u8			mc_ttl;
	__u8			pmtudisc;
	__u8			recverr:1,
				is_icsk:1,
				मुक्तbind:1,
				hdrincl:1,
				mc_loop:1,
				transparent:1,
				mc_all:1,
				nodefrag:1;
	__u8			bind_address_no_port:1,
				recverr_rfc4884:1,
				defer_connect:1; /* Indicates that fastखोलो_connect is set
						  * and cookie exists so we defer connect
						  * until first data frame is written
						  */
	__u8			rcv_tos;
	__u8			convert_csum;
	पूर्णांक			uc_index;
	पूर्णांक			mc_index;
	__be32			mc_addr;
	काष्ठा ip_mc_socklist __rcu	*mc_list;
	काष्ठा inet_cork_full	cork;
पूर्ण;

#घोषणा IPCORK_OPT	1	/* ip-options has been held in ipcork.opt */
#घोषणा IPCORK_ALLFRAG	2	/* always fragment (क्रम ipv6 क्रम now) */

/* cmsg flags क्रम inet */
#घोषणा IP_CMSG_PKTINFO		BIT(0)
#घोषणा IP_CMSG_TTL		BIT(1)
#घोषणा IP_CMSG_TOS		BIT(2)
#घोषणा IP_CMSG_RECVOPTS	BIT(3)
#घोषणा IP_CMSG_RETOPTS		BIT(4)
#घोषणा IP_CMSG_PASSSEC		BIT(5)
#घोषणा IP_CMSG_ORIGDSTADDR	BIT(6)
#घोषणा IP_CMSG_CHECKSUM	BIT(7)
#घोषणा IP_CMSG_RECVFRAGSIZE	BIT(8)

/**
 * sk_to_full_sk - Access to a full socket
 * @sk: poपूर्णांकer to a socket
 *
 * SYNACK messages might be attached to request sockets.
 * Some places want to reach the listener in this हाल.
 */
अटल अंतरभूत काष्ठा sock *sk_to_full_sk(काष्ठा sock *sk)
अणु
#अगर_घोषित CONFIG_INET
	अगर (sk && sk->sk_state == TCP_NEW_SYN_RECV)
		sk = inet_reqsk(sk)->rsk_listener;
#पूर्ण_अगर
	वापस sk;
पूर्ण

/* sk_to_full_sk() variant with a स्थिर argument */
अटल अंतरभूत स्थिर काष्ठा sock *sk_स्थिर_to_full_sk(स्थिर काष्ठा sock *sk)
अणु
#अगर_घोषित CONFIG_INET
	अगर (sk && sk->sk_state == TCP_NEW_SYN_RECV)
		sk = ((स्थिर काष्ठा request_sock *)sk)->rsk_listener;
#पूर्ण_अगर
	वापस sk;
पूर्ण

अटल अंतरभूत काष्ठा sock *skb_to_full_sk(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस sk_to_full_sk(skb->sk);
पूर्ण

अटल अंतरभूत काष्ठा inet_sock *inet_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा inet_sock *)sk;
पूर्ण

अटल अंतरभूत व्योम __inet_sk_copy_descendant(काष्ठा sock *sk_to,
					     स्थिर काष्ठा sock *sk_from,
					     स्थिर पूर्णांक ancestor_size)
अणु
	स_नकल(inet_sk(sk_to) + 1, inet_sk(sk_from) + 1,
	       sk_from->sk_prot->obj_size - ancestor_size);
पूर्ण

पूर्णांक inet_sk_rebuild_header(काष्ठा sock *sk);

/**
 * inet_sk_state_load - पढ़ो sk->sk_state क्रम lockless contexts
 * @sk: socket poपूर्णांकer
 *
 * Paired with inet_sk_state_store(). Used in places we करोn't hold socket lock:
 * tcp_diag_get_info(), tcp_get_info(), tcp_poll(), get_tcp4_sock() ...
 */
अटल अंतरभूत पूर्णांक inet_sk_state_load(स्थिर काष्ठा sock *sk)
अणु
	/* state change might impact lockless पढ़ोers. */
	वापस smp_load_acquire(&sk->sk_state);
पूर्ण

/**
 * inet_sk_state_store - update sk->sk_state
 * @sk: socket poपूर्णांकer
 * @newstate: new state
 *
 * Paired with inet_sk_state_load(). Should be used in contexts where
 * state change might impact lockless पढ़ोers.
 */
व्योम inet_sk_state_store(काष्ठा sock *sk, पूर्णांक newstate);

व्योम inet_sk_set_state(काष्ठा sock *sk, पूर्णांक state);

अटल अंतरभूत अचिन्हित पूर्णांक __inet_ehashfn(स्थिर __be32 laddr,
					  स्थिर __u16 lport,
					  स्थिर __be32 faddr,
					  स्थिर __be16 fport,
					  u32 initval)
अणु
	वापस jhash_3words((__क्रमce __u32) laddr,
			    (__क्रमce __u32) faddr,
			    ((__u32) lport) << 16 | (__क्रमce __u32)fport,
			    initval);
पूर्ण

काष्ठा request_sock *inet_reqsk_alloc(स्थिर काष्ठा request_sock_ops *ops,
				      काष्ठा sock *sk_listener,
				      bool attach_listener);

अटल अंतरभूत __u8 inet_sk_flowi_flags(स्थिर काष्ठा sock *sk)
अणु
	__u8 flags = 0;

	अगर (inet_sk(sk)->transparent || inet_sk(sk)->hdrincl)
		flags |= FLOWI_FLAG_ANYSRC;
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम inet_inc_convert_csum(काष्ठा sock *sk)
अणु
	inet_sk(sk)->convert_csum++;
पूर्ण

अटल अंतरभूत व्योम inet_dec_convert_csum(काष्ठा sock *sk)
अणु
	अगर (inet_sk(sk)->convert_csum > 0)
		inet_sk(sk)->convert_csum--;
पूर्ण

अटल अंतरभूत bool inet_get_convert_csum(काष्ठा sock *sk)
अणु
	वापस !!inet_sk(sk)->convert_csum;
पूर्ण


अटल अंतरभूत bool inet_can_nonlocal_bind(काष्ठा net *net,
					  काष्ठा inet_sock *inet)
अणु
	वापस net->ipv4.sysctl_ip_nonlocal_bind ||
		inet->मुक्तbind || inet->transparent;
पूर्ण

#पूर्ण_अगर	/* _INET_SOCK_H */
