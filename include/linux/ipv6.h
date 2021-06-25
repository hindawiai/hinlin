<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _IPV6_H
#घोषणा _IPV6_H

#समावेश <uapi/linux/ipv6.h>

#घोषणा ipv6_optlen(p)  (((p)->hdrlen+1) << 3)
#घोषणा ipv6_authlen(p) (((p)->hdrlen+2) << 2)
/*
 * This काष्ठाure contains configuration options per IPv6 link.
 */
काष्ठा ipv6_devconf अणु
	__s32		क्रमwarding;
	__s32		hop_limit;
	__s32		mtu6;
	__s32		accept_ra;
	__s32		accept_redirects;
	__s32		स्वतःconf;
	__s32		dad_transmits;
	__s32		rtr_solicits;
	__s32		rtr_solicit_पूर्णांकerval;
	__s32		rtr_solicit_max_पूर्णांकerval;
	__s32		rtr_solicit_delay;
	__s32		क्रमce_mld_version;
	__s32		mldv1_unsolicited_report_पूर्णांकerval;
	__s32		mldv2_unsolicited_report_पूर्णांकerval;
	__s32		use_tempaddr;
	__s32		temp_valid_lft;
	__s32		temp_prefered_lft;
	__s32		regen_max_retry;
	__s32		max_desync_factor;
	__s32		max_addresses;
	__s32		accept_ra_defrtr;
	__u32		ra_defrtr_metric;
	__s32		accept_ra_min_hop_limit;
	__s32		accept_ra_pinfo;
	__s32		ignore_routes_with_linkकरोwn;
#अगर_घोषित CONFIG_IPV6_ROUTER_PREF
	__s32		accept_ra_rtr_pref;
	__s32		rtr_probe_पूर्णांकerval;
#अगर_घोषित CONFIG_IPV6_ROUTE_INFO
	__s32		accept_ra_rt_info_min_plen;
	__s32		accept_ra_rt_info_max_plen;
#पूर्ण_अगर
#पूर्ण_अगर
	__s32		proxy_ndp;
	__s32		accept_source_route;
	__s32		accept_ra_from_local;
#अगर_घोषित CONFIG_IPV6_OPTIMISTIC_DAD
	__s32		optimistic_dad;
	__s32		use_optimistic;
#पूर्ण_अगर
#अगर_घोषित CONFIG_IPV6_MROUTE
	__s32		mc_क्रमwarding;
#पूर्ण_अगर
	__s32		disable_ipv6;
	__s32		drop_unicast_in_l2_multicast;
	__s32		accept_dad;
	__s32		क्रमce_tllao;
	__s32           ndisc_notअगरy;
	__s32		suppress_frag_ndisc;
	__s32		accept_ra_mtu;
	__s32		drop_unsolicited_na;
	काष्ठा ipv6_stable_secret अणु
		bool initialized;
		काष्ठा in6_addr secret;
	पूर्ण stable_secret;
	__s32		use_oअगर_addrs_only;
	__s32		keep_addr_on_करोwn;
	__s32		seg6_enabled;
#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
	__s32		seg6_require_hmac;
#पूर्ण_अगर
	__u32		enhanced_dad;
	__u32		addr_gen_mode;
	__s32		disable_policy;
	__s32           ndisc_tclass;
	__s32		rpl_seg_enabled;

	काष्ठा ctl_table_header *sysctl_header;
पूर्ण;

काष्ठा ipv6_params अणु
	__s32 disable_ipv6;
	__s32 स्वतःconf;
पूर्ण;
बाह्य काष्ठा ipv6_params ipv6_शेषs;
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>

#समावेश <net/inet_sock.h>

अटल अंतरभूत काष्ठा ipv6hdr *ipv6_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा ipv6hdr *)skb_network_header(skb);
पूर्ण

अटल अंतरभूत काष्ठा ipv6hdr *inner_ipv6_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा ipv6hdr *)skb_inner_network_header(skb);
पूर्ण

अटल अंतरभूत काष्ठा ipv6hdr *ipipv6_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा ipv6hdr *)skb_transport_header(skb);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ipv6_transport_len(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस ntohs(ipv6_hdr(skb)->payload_len) + माप(काष्ठा ipv6hdr) -
	       skb_network_header_len(skb);
पूर्ण

/* 
   This काष्ठाure contains results of exthdrs parsing
   as offsets from skb->nh.
 */

काष्ठा inet6_skb_parm अणु
	पूर्णांक			iअगर;
	__be16			ra;
	__u16			dst0;
	__u16			srcrt;
	__u16			dst1;
	__u16			lastopt;
	__u16			nhoff;
	__u16			flags;
#अगर defined(CONFIG_IPV6_MIP6) || defined(CONFIG_IPV6_MIP6_MODULE)
	__u16			dsthao;
#पूर्ण_अगर
	__u16			frag_max_size;

#घोषणा IP6SKB_XFRM_TRANSFORMED	1
#घोषणा IP6SKB_FORWARDED	2
#घोषणा IP6SKB_REROUTED		4
#घोषणा IP6SKB_ROUTERALERT	8
#घोषणा IP6SKB_FRAGMENTED      16
#घोषणा IP6SKB_HOPBYHOP        32
#घोषणा IP6SKB_L3SLAVE         64
#घोषणा IP6SKB_JUMBOGRAM      128
पूर्ण;

#अगर defined(CONFIG_NET_L3_MASTER_DEV)
अटल अंतरभूत bool ipv6_l3mdev_skb(__u16 flags)
अणु
	वापस flags & IP6SKB_L3SLAVE;
पूर्ण
#अन्यथा
अटल अंतरभूत bool ipv6_l3mdev_skb(__u16 flags)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#घोषणा IP6CB(skb)	((काष्ठा inet6_skb_parm*)((skb)->cb))
#घोषणा IP6CBMTU(skb)	((काष्ठा ip6_mtuinfo *)((skb)->cb))

अटल अंतरभूत पूर्णांक inet6_iअगर(स्थिर काष्ठा sk_buff *skb)
अणु
	bool l3_slave = ipv6_l3mdev_skb(IP6CB(skb)->flags);

	वापस l3_slave ? skb->skb_iअगर : IP6CB(skb)->iअगर;
पूर्ण

अटल अंतरभूत bool inet6_is_jumbogram(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस !!(IP6CB(skb)->flags & IP6SKB_JUMBOGRAM);
पूर्ण

/* can not be used in TCP layer after tcp_v6_fill_cb */
अटल अंतरभूत पूर्णांक inet6_sdअगर(स्थिर काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_NET_L3_MASTER_DEV)
	अगर (skb && ipv6_l3mdev_skb(IP6CB(skb)->flags))
		वापस IP6CB(skb)->iअगर;
#पूर्ण_अगर
	वापस 0;
पूर्ण

काष्ठा tcp6_request_sock अणु
	काष्ठा tcp_request_sock	  tcp6rsk_tcp;
पूर्ण;

काष्ठा ipv6_mc_socklist;
काष्ठा ipv6_ac_socklist;
काष्ठा ipv6_fl_socklist;

काष्ठा inet6_cork अणु
	काष्ठा ipv6_txoptions *opt;
	u8 hop_limit;
	u8 tclass;
पूर्ण;

/**
 * काष्ठा ipv6_pinfo - ipv6 निजी area
 *
 * In the काष्ठा sock hierarchy (tcp6_sock, upd6_sock, etc)
 * this _must_ be the last member, so that inet6_sk_generic
 * is able to calculate its offset from the base काष्ठा sock
 * by using the काष्ठा proto->slab_obj_size member. -acme
 */
काष्ठा ipv6_pinfo अणु
	काष्ठा in6_addr 	saddr;
	काष्ठा in6_pktinfo	sticky_pktinfo;
	स्थिर काष्ठा in6_addr		*daddr_cache;
#अगर_घोषित CONFIG_IPV6_SUBTREES
	स्थिर काष्ठा in6_addr		*saddr_cache;
#पूर्ण_अगर

	__be32			flow_label;
	__u32			frag_size;

	/*
	 * Packed in 16bits.
	 * Omit one shअगरt by putting the चिन्हित field at MSB.
	 */
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__s16			hop_limit:9;
	__u16			__unused_1:7;
#अन्यथा
	__u16			__unused_1:7;
	__s16			hop_limit:9;
#पूर्ण_अगर

#अगर defined(__BIG_ENDIAN_BITFIELD)
	/* Packed in 16bits. */
	__s16			mcast_hops:9;
	__u16			__unused_2:6,
				mc_loop:1;
#अन्यथा
	__u16			mc_loop:1,
				__unused_2:6;
	__s16			mcast_hops:9;
#पूर्ण_अगर
	पूर्णांक			ucast_oअगर;
	पूर्णांक			mcast_oअगर;

	/* pktoption flags */
	जोड़ अणु
		काष्ठा अणु
			__u16	srcrt:1,
				osrcrt:1,
			        rxinfo:1,
			        rxoinfo:1,
				rxhlim:1,
				rxohlim:1,
				hopopts:1,
				ohopopts:1,
				dstopts:1,
				odstopts:1,
                                rxflow:1,
				rxtclass:1,
				rxpmtu:1,
				rxorigdstaddr:1,
				recvfragsize:1;
				/* 1 bits hole */
		पूर्ण bits;
		__u16		all;
	पूर्ण rxopt;

	/* sockopt flags */
	__u16			recverr:1,
	                        sndflow:1,
				repflow:1,
				pmtudisc:3,
				padding:1,	/* 1 bit hole */
				srcprefs:3,	/* 001: prefer temporary address
						 * 010: prefer खुला address
						 * 100: prefer care-of address
						 */
				करोntfrag:1,
				स्वतःflowlabel:1,
				स्वतःflowlabel_set:1,
				mc_all:1,
				recverr_rfc4884:1,
				rtalert_isolate:1;
	__u8			min_hopcount;
	__u8			tclass;
	__be32			rcv_flowinfo;

	__u32			dst_cookie;
	__u32			rx_dst_cookie;

	काष्ठा ipv6_mc_socklist	__rcu *ipv6_mc_list;
	काष्ठा ipv6_ac_socklist	*ipv6_ac_list;
	काष्ठा ipv6_fl_socklist __rcu *ipv6_fl_list;

	काष्ठा ipv6_txoptions __rcu	*opt;
	काष्ठा sk_buff		*pktoptions;
	काष्ठा sk_buff		*rxpmtu;
	काष्ठा inet6_cork	cork;
पूर्ण;

/* WARNING: करोn't change the layout of the members in अणुraw,udp,tcpपूर्ण6_sock! */
काष्ठा raw6_sock अणु
	/* inet_sock has to be the first member of raw6_sock */
	काष्ठा inet_sock	inet;
	__u32			checksum;	/* perक्रमm checksum */
	__u32			offset;		/* checksum offset  */
	काष्ठा icmp6_filter	filter;
	__u32			ip6mr_table;
	/* ipv6_pinfo has to be the last member of raw6_sock, see inet6_sk_generic */
	काष्ठा ipv6_pinfo	inet6;
पूर्ण;

काष्ठा udp6_sock अणु
	काष्ठा udp_sock	  udp;
	/* ipv6_pinfo has to be the last member of udp6_sock, see inet6_sk_generic */
	काष्ठा ipv6_pinfo inet6;
पूर्ण;

काष्ठा tcp6_sock अणु
	काष्ठा tcp_sock	  tcp;
	/* ipv6_pinfo has to be the last member of tcp6_sock, see inet6_sk_generic */
	काष्ठा ipv6_pinfo inet6;
पूर्ण;

बाह्य पूर्णांक inet6_sk_rebuild_header(काष्ठा sock *sk);

काष्ठा tcp6_समयरुको_sock अणु
	काष्ठा tcp_समयरुको_sock   tcp6tw_tcp;
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6)
bool ipv6_mod_enabled(व्योम);

अटल अंतरभूत काष्ठा ipv6_pinfo *inet6_sk(स्थिर काष्ठा sock *__sk)
अणु
	वापस sk_fullsock(__sk) ? inet_sk(__sk)->pinet6 : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा raw6_sock *raw6_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा raw6_sock *)sk;
पूर्ण

#घोषणा __ipv6_only_sock(sk)	(sk->sk_ipv6only)
#घोषणा ipv6_only_sock(sk)	(__ipv6_only_sock(sk))
#घोषणा ipv6_sk_rxinfo(sk)	((sk)->sk_family == PF_INET6 && \
				 inet6_sk(sk)->rxopt.bits.rxinfo)

अटल अंतरभूत स्थिर काष्ठा in6_addr *inet6_rcv_saddr(स्थिर काष्ठा sock *sk)
अणु
	अगर (sk->sk_family == AF_INET6)
		वापस &sk->sk_v6_rcv_saddr;
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक inet_v6_ipv6only(स्थिर काष्ठा sock *sk)
अणु
	/* ipv6only field is at same position क्रम समयरुको and other sockets */
	वापस ipv6_only_sock(sk);
पूर्ण
#अन्यथा
#घोषणा __ipv6_only_sock(sk)	0
#घोषणा ipv6_only_sock(sk)	0
#घोषणा ipv6_sk_rxinfo(sk)	0

अटल अंतरभूत bool ipv6_mod_enabled(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा ipv6_pinfo * inet6_sk(स्थिर काष्ठा sock *__sk)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा inet6_request_sock *
			inet6_rsk(स्थिर काष्ठा request_sock *rsk)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा raw6_sock *raw6_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस शून्य;
पूर्ण

#घोषणा inet6_rcv_saddr(__sk)	शून्य
#घोषणा tcp_twsk_ipv6only(__sk)		0
#घोषणा inet_v6_ipv6only(__sk)		0
#पूर्ण_अगर /* IS_ENABLED(CONFIG_IPV6) */
#पूर्ण_अगर /* _IPV6_H */
