<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the UDP protocol.
 *
 * Version:	@(#)udp.h	1.0.2	04/28/93
 *
 * Author:	Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 */
#अगर_अघोषित _LINUX_UDP_H
#घोषणा _LINUX_UDP_H

#समावेश <net/inet_sock.h>
#समावेश <linux/skbuff.h>
#समावेश <net/netns/hash.h>
#समावेश <uapi/linux/udp.h>

अटल अंतरभूत काष्ठा udphdr *udp_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा udphdr *)skb_transport_header(skb);
पूर्ण

अटल अंतरभूत काष्ठा udphdr *inner_udp_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा udphdr *)skb_inner_transport_header(skb);
पूर्ण

#घोषणा UDP_HTABLE_SIZE_MIN		(CONFIG_BASE_SMALL ? 128 : 256)

अटल अंतरभूत u32 udp_hashfn(स्थिर काष्ठा net *net, u32 num, u32 mask)
अणु
	वापस (num + net_hash_mix(net)) & mask;
पूर्ण

काष्ठा udp_sock अणु
	/* inet_sock has to be the first member */
	काष्ठा inet_sock inet;
#घोषणा udp_port_hash		inet.sk.__sk_common.skc_u16hashes[0]
#घोषणा udp_portaddr_hash	inet.sk.__sk_common.skc_u16hashes[1]
#घोषणा udp_portaddr_node	inet.sk.__sk_common.skc_portaddr_node
	पूर्णांक		 pending;	/* Any pending frames ? */
	अचिन्हित पूर्णांक	 corkflag;	/* Cork is required */
	__u8		 encap_type;	/* Is this an Encapsulation socket? */
	अचिन्हित अक्षर	 no_check6_tx:1,/* Send zero UDP6 checksums on TX? */
			 no_check6_rx:1,/* Allow zero UDP6 checksums on RX? */
			 encap_enabled:1, /* This socket enabled encap
					   * processing; UDP tunnels and
					   * dअगरferent encapsulation layer set
					   * this
					   */
			 gro_enabled:1,	/* Request GRO aggregation */
			 accept_udp_l4:1,
			 accept_udp_fraglist:1;
	/*
	 * Following member retains the inक्रमmation to create a UDP header
	 * when the socket is uncorked.
	 */
	__u16		 len;		/* total length of pending frames */
	__u16		 gso_size;
	/*
	 * Fields specअगरic to UDP-Lite.
	 */
	__u16		 pcslen;
	__u16		 pcrlen;
/* indicator bits used by pcflag: */
#घोषणा UDPLITE_BIT      0x1  		/* set by udplite proto init function */
#घोषणा UDPLITE_SEND_CC  0x2  		/* set via udplite setsockopt         */
#घोषणा UDPLITE_RECV_CC  0x4		/* set via udplite setsocktopt        */
	__u8		 pcflag;        /* marks socket as UDP-Lite अगर > 0    */
	__u8		 unused[3];
	/*
	 * For encapsulation sockets.
	 */
	पूर्णांक (*encap_rcv)(काष्ठा sock *sk, काष्ठा sk_buff *skb);
	पूर्णांक (*encap_err_lookup)(काष्ठा sock *sk, काष्ठा sk_buff *skb);
	व्योम (*encap_destroy)(काष्ठा sock *sk);

	/* GRO functions क्रम UDP socket */
	काष्ठा sk_buff *	(*gro_receive)(काष्ठा sock *sk,
					       काष्ठा list_head *head,
					       काष्ठा sk_buff *skb);
	पूर्णांक			(*gro_complete)(काष्ठा sock *sk,
						काष्ठा sk_buff *skb,
						पूर्णांक nhoff);

	/* udp_recvmsg try to use this beक्रमe splicing sk_receive_queue */
	काष्ठा sk_buff_head	पढ़ोer_queue ____cacheline_aligned_in_smp;

	/* This field is dirtied by udp_recvmsg() */
	पूर्णांक		क्रमward_deficit;
पूर्ण;

#घोषणा UDP_MAX_SEGMENTS	(1 << 6UL)

अटल अंतरभूत काष्ठा udp_sock *udp_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा udp_sock *)sk;
पूर्ण

अटल अंतरभूत व्योम udp_set_no_check6_tx(काष्ठा sock *sk, bool val)
अणु
	udp_sk(sk)->no_check6_tx = val;
पूर्ण

अटल अंतरभूत व्योम udp_set_no_check6_rx(काष्ठा sock *sk, bool val)
अणु
	udp_sk(sk)->no_check6_rx = val;
पूर्ण

अटल अंतरभूत bool udp_get_no_check6_tx(काष्ठा sock *sk)
अणु
	वापस udp_sk(sk)->no_check6_tx;
पूर्ण

अटल अंतरभूत bool udp_get_no_check6_rx(काष्ठा sock *sk)
अणु
	वापस udp_sk(sk)->no_check6_rx;
पूर्ण

अटल अंतरभूत व्योम udp_cmsg_recv(काष्ठा msghdr *msg, काष्ठा sock *sk,
				 काष्ठा sk_buff *skb)
अणु
	पूर्णांक gso_size;

	अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4) अणु
		gso_size = skb_shinfo(skb)->gso_size;
		put_cmsg(msg, SOL_UDP, UDP_GRO, माप(gso_size), &gso_size);
	पूर्ण
पूर्ण

अटल अंतरभूत bool udp_unexpected_gso(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अगर (!skb_is_gso(skb))
		वापस false;

	अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4 && !udp_sk(sk)->accept_udp_l4)
		वापस true;

	अगर (skb_shinfo(skb)->gso_type & SKB_GSO_FRAGLIST && !udp_sk(sk)->accept_udp_fraglist)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत व्योम udp_allow_gso(काष्ठा sock *sk)
अणु
	udp_sk(sk)->accept_udp_l4 = 1;
	udp_sk(sk)->accept_udp_fraglist = 1;
पूर्ण

#घोषणा udp_portaddr_क्रम_each_entry(__sk, list) \
	hlist_क्रम_each_entry(__sk, list, __sk_common.skc_portaddr_node)

#घोषणा udp_portaddr_क्रम_each_entry_rcu(__sk, list) \
	hlist_क्रम_each_entry_rcu(__sk, list, __sk_common.skc_portaddr_node)

#घोषणा IS_UDPLITE(__sk) (__sk->sk_protocol == IPPROTO_UDPLITE)

#पूर्ण_अगर	/* _LINUX_UDP_H */
