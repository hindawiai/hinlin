<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the IP module.
 *
 * Version:	@(#)ip.h	1.0.2	05/07/93
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Alan Cox, <gw4pts@gw4pts.ampr.org>
 *
 * Changes:
 *		Mike McLagan    :       Routing by source
 */
#अगर_अघोषित _IP_H
#घोषणा _IP_H

#समावेश <linux/types.h>
#समावेश <linux/ip.h>
#समावेश <linux/in.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/jhash.h>
#समावेश <linux/sockptr.h>

#समावेश <net/inet_sock.h>
#समावेश <net/route.h>
#समावेश <net/snmp.h>
#समावेश <net/flow.h>
#समावेश <net/flow_dissector.h>
#समावेश <net/netns/hash.h>

#घोषणा IPV4_MAX_PMTU		65535U		/* RFC 2675, Section 5.1 */
#घोषणा IPV4_MIN_MTU		68			/* RFC 791 */

बाह्य अचिन्हित पूर्णांक sysctl_fib_sync_mem;
बाह्य अचिन्हित पूर्णांक sysctl_fib_sync_mem_min;
बाह्य अचिन्हित पूर्णांक sysctl_fib_sync_mem_max;

काष्ठा sock;

काष्ठा inet_skb_parm अणु
	पूर्णांक			iअगर;
	काष्ठा ip_options	opt;		/* Compiled IP options		*/
	u16			flags;

#घोषणा IPSKB_FORWARDED		BIT(0)
#घोषणा IPSKB_XFRM_TUNNEL_SIZE	BIT(1)
#घोषणा IPSKB_XFRM_TRANSFORMED	BIT(2)
#घोषणा IPSKB_FRAG_COMPLETE	BIT(3)
#घोषणा IPSKB_REROUTED		BIT(4)
#घोषणा IPSKB_DOREसूचीECT	BIT(5)
#घोषणा IPSKB_FRAG_PMTU		BIT(6)
#घोषणा IPSKB_L3SLAVE		BIT(7)

	u16			frag_max_size;
पूर्ण;

अटल अंतरभूत bool ipv4_l3mdev_skb(u16 flags)
अणु
	वापस !!(flags & IPSKB_L3SLAVE);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ip_hdrlen(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस ip_hdr(skb)->ihl * 4;
पूर्ण

काष्ठा ipcm_cookie अणु
	काष्ठा sockcm_cookie	sockc;
	__be32			addr;
	पूर्णांक			oअगर;
	काष्ठा ip_options_rcu	*opt;
	__u8			ttl;
	__s16			tos;
	अक्षर			priority;
	__u16			gso_size;
पूर्ण;

अटल अंतरभूत व्योम ipcm_init(काष्ठा ipcm_cookie *ipcm)
अणु
	*ipcm = (काष्ठा ipcm_cookie) अणु .tos = -1 पूर्ण;
पूर्ण

अटल अंतरभूत व्योम ipcm_init_sk(काष्ठा ipcm_cookie *ipcm,
				स्थिर काष्ठा inet_sock *inet)
अणु
	ipcm_init(ipcm);

	ipcm->sockc.mark = inet->sk.sk_mark;
	ipcm->sockc.tsflags = inet->sk.sk_tsflags;
	ipcm->oअगर = inet->sk.sk_bound_dev_अगर;
	ipcm->addr = inet->inet_saddr;
पूर्ण

#घोषणा IPCB(skb) ((काष्ठा inet_skb_parm*)((skb)->cb))
#घोषणा PKTINFO_SKB_CB(skb) ((काष्ठा in_pktinfo *)((skb)->cb))

/* वापस enslaved device index अगर relevant */
अटल अंतरभूत पूर्णांक inet_sdअगर(स्थिर काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_NET_L3_MASTER_DEV)
	अगर (skb && ipv4_l3mdev_skb(IPCB(skb)->flags))
		वापस IPCB(skb)->iअगर;
#पूर्ण_अगर
	वापस 0;
पूर्ण

/* Special input handler क्रम packets caught by router alert option.
   They are selected only by protocol field, and then processed likely
   local ones; but only अगर someone wants them! Otherwise, router
   not running rsvpd will समाप्त RSVP.

   It is user level problem, what it will make with them.
   I have no idea, how it will masquearde or NAT them (it is joke, joke :-)),
   but receiver should be enough clever f.e. to क्रमward mtrace requests,
   sent to multicast group to reach destination designated router.
 */

काष्ठा ip_ra_chain अणु
	काष्ठा ip_ra_chain __rcu *next;
	काष्ठा sock		*sk;
	जोड़ अणु
		व्योम			(*deकाष्ठाor)(काष्ठा sock *);
		काष्ठा sock		*saved_sk;
	पूर्ण;
	काष्ठा rcu_head		rcu;
पूर्ण;

/* IP flags. */
#घोषणा IP_CE		0x8000		/* Flag: "Congestion"		*/
#घोषणा IP_DF		0x4000		/* Flag: "Don't Fragment"	*/
#घोषणा IP_MF		0x2000		/* Flag: "More Fragments"	*/
#घोषणा IP_OFFSET	0x1FFF		/* "Fragment Offset" part	*/

#घोषणा IP_FRAG_TIME	(30 * HZ)		/* fragment lअगरeसमय	*/

काष्ठा msghdr;
काष्ठा net_device;
काष्ठा packet_type;
काष्ठा rtable;
काष्ठा sockaddr;

पूर्णांक igmp_mc_init(व्योम);

/*
 *	Functions provided by ip.c
 */

पूर्णांक ip_build_and_send_pkt(काष्ठा sk_buff *skb, स्थिर काष्ठा sock *sk,
			  __be32 saddr, __be32 daddr,
			  काष्ठा ip_options_rcu *opt, u8 tos);
पूर्णांक ip_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev, काष्ठा packet_type *pt,
	   काष्ठा net_device *orig_dev);
व्योम ip_list_rcv(काष्ठा list_head *head, काष्ठा packet_type *pt,
		 काष्ठा net_device *orig_dev);
पूर्णांक ip_local_deliver(काष्ठा sk_buff *skb);
व्योम ip_protocol_deliver_rcu(काष्ठा net *net, काष्ठा sk_buff *skb, पूर्णांक proto);
पूर्णांक ip_mr_input(काष्ठा sk_buff *skb);
पूर्णांक ip_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक ip_mc_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक ip_करो_fragment(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb,
		   पूर्णांक (*output)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *));

काष्ठा ip_fraglist_iter अणु
	काष्ठा sk_buff	*frag;
	काष्ठा iphdr	*iph;
	पूर्णांक		offset;
	अचिन्हित पूर्णांक	hlen;
पूर्ण;

व्योम ip_fraglist_init(काष्ठा sk_buff *skb, काष्ठा iphdr *iph,
		      अचिन्हित पूर्णांक hlen, काष्ठा ip_fraglist_iter *iter);
व्योम ip_fraglist_prepare(काष्ठा sk_buff *skb, काष्ठा ip_fraglist_iter *iter);

अटल अंतरभूत काष्ठा sk_buff *ip_fraglist_next(काष्ठा ip_fraglist_iter *iter)
अणु
	काष्ठा sk_buff *skb = iter->frag;

	iter->frag = skb->next;
	skb_mark_not_on_list(skb);

	वापस skb;
पूर्ण

काष्ठा ip_frag_state अणु
	bool		DF;
	अचिन्हित पूर्णांक	hlen;
	अचिन्हित पूर्णांक	ll_rs;
	अचिन्हित पूर्णांक	mtu;
	अचिन्हित पूर्णांक	left;
	पूर्णांक		offset;
	पूर्णांक		ptr;
	__be16		not_last_frag;
पूर्ण;

व्योम ip_frag_init(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hlen, अचिन्हित पूर्णांक ll_rs,
		  अचिन्हित पूर्णांक mtu, bool DF, काष्ठा ip_frag_state *state);
काष्ठा sk_buff *ip_frag_next(काष्ठा sk_buff *skb,
			     काष्ठा ip_frag_state *state);

व्योम ip_send_check(काष्ठा iphdr *ip);
पूर्णांक __ip_local_out(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक ip_local_out(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);

पूर्णांक __ip_queue_xmit(काष्ठा sock *sk, काष्ठा sk_buff *skb, काष्ठा flowi *fl,
		    __u8 tos);
व्योम ip_init(व्योम);
पूर्णांक ip_append_data(काष्ठा sock *sk, काष्ठा flowi4 *fl4,
		   पूर्णांक getfrag(व्योम *from, अक्षर *to, पूर्णांक offset, पूर्णांक len,
			       पूर्णांक odd, काष्ठा sk_buff *skb),
		   व्योम *from, पूर्णांक len, पूर्णांक protolen,
		   काष्ठा ipcm_cookie *ipc,
		   काष्ठा rtable **rt,
		   अचिन्हित पूर्णांक flags);
पूर्णांक ip_generic_getfrag(व्योम *from, अक्षर *to, पूर्णांक offset, पूर्णांक len, पूर्णांक odd,
		       काष्ठा sk_buff *skb);
sमाप_प्रकार ip_append_page(काष्ठा sock *sk, काष्ठा flowi4 *fl4, काष्ठा page *page,
		       पूर्णांक offset, माप_प्रकार size, पूर्णांक flags);
काष्ठा sk_buff *__ip_make_skb(काष्ठा sock *sk, काष्ठा flowi4 *fl4,
			      काष्ठा sk_buff_head *queue,
			      काष्ठा inet_cork *cork);
पूर्णांक ip_send_skb(काष्ठा net *net, काष्ठा sk_buff *skb);
पूर्णांक ip_push_pending_frames(काष्ठा sock *sk, काष्ठा flowi4 *fl4);
व्योम ip_flush_pending_frames(काष्ठा sock *sk);
काष्ठा sk_buff *ip_make_skb(काष्ठा sock *sk, काष्ठा flowi4 *fl4,
			    पूर्णांक getfrag(व्योम *from, अक्षर *to, पूर्णांक offset,
					पूर्णांक len, पूर्णांक odd, काष्ठा sk_buff *skb),
			    व्योम *from, पूर्णांक length, पूर्णांक transhdrlen,
			    काष्ठा ipcm_cookie *ipc, काष्ठा rtable **rtp,
			    काष्ठा inet_cork *cork, अचिन्हित पूर्णांक flags);

पूर्णांक ip_queue_xmit(काष्ठा sock *sk, काष्ठा sk_buff *skb, काष्ठा flowi *fl);

अटल अंतरभूत काष्ठा sk_buff *ip_finish_skb(काष्ठा sock *sk, काष्ठा flowi4 *fl4)
अणु
	वापस __ip_make_skb(sk, fl4, &sk->sk_ग_लिखो_queue, &inet_sk(sk)->cork.base);
पूर्ण

अटल अंतरभूत __u8 get_rttos(काष्ठा ipcm_cookie* ipc, काष्ठा inet_sock *inet)
अणु
	वापस (ipc->tos != -1) ? RT_TOS(ipc->tos) : RT_TOS(inet->tos);
पूर्ण

अटल अंतरभूत __u8 get_rtconn_flags(काष्ठा ipcm_cookie* ipc, काष्ठा sock* sk)
अणु
	वापस (ipc->tos != -1) ? RT_CONN_FLAGS_TOS(sk, ipc->tos) : RT_CONN_FLAGS(sk);
पूर्ण

/* datagram.c */
पूर्णांक __ip4_datagram_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len);
पूर्णांक ip4_datagram_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len);

व्योम ip4_datagram_release_cb(काष्ठा sock *sk);

काष्ठा ip_reply_arg अणु
	काष्ठा kvec iov[1];
	पूर्णांक	    flags;
	__wsum 	    csum;
	पूर्णांक	    csumoffset; /* u16 offset of csum in iov[0].iov_base */
				/* -1 अगर not needed */
	पूर्णांक	    bound_dev_अगर;
	u8  	    tos;
	kuid_t	    uid;
पूर्ण;

#घोषणा IP_REPLY_ARG_NOSRCCHECK 1

अटल अंतरभूत __u8 ip_reply_arg_flowi_flags(स्थिर काष्ठा ip_reply_arg *arg)
अणु
	वापस (arg->flags & IP_REPLY_ARG_NOSRCCHECK) ? FLOWI_FLAG_ANYSRC : 0;
पूर्ण

व्योम ip_send_unicast_reply(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			   स्थिर काष्ठा ip_options *sopt,
			   __be32 daddr, __be32 saddr,
			   स्थिर काष्ठा ip_reply_arg *arg,
			   अचिन्हित पूर्णांक len, u64 transmit_समय);

#घोषणा IP_INC_STATS(net, field)	SNMP_INC_STATS64((net)->mib.ip_statistics, field)
#घोषणा __IP_INC_STATS(net, field)	__SNMP_INC_STATS64((net)->mib.ip_statistics, field)
#घोषणा IP_ADD_STATS(net, field, val)	SNMP_ADD_STATS64((net)->mib.ip_statistics, field, val)
#घोषणा __IP_ADD_STATS(net, field, val) __SNMP_ADD_STATS64((net)->mib.ip_statistics, field, val)
#घोषणा IP_UPD_PO_STATS(net, field, val) SNMP_UPD_PO_STATS64((net)->mib.ip_statistics, field, val)
#घोषणा __IP_UPD_PO_STATS(net, field, val) __SNMP_UPD_PO_STATS64((net)->mib.ip_statistics, field, val)
#घोषणा NET_INC_STATS(net, field)	SNMP_INC_STATS((net)->mib.net_statistics, field)
#घोषणा __NET_INC_STATS(net, field)	__SNMP_INC_STATS((net)->mib.net_statistics, field)
#घोषणा NET_ADD_STATS(net, field, adnd)	SNMP_ADD_STATS((net)->mib.net_statistics, field, adnd)
#घोषणा __NET_ADD_STATS(net, field, adnd) __SNMP_ADD_STATS((net)->mib.net_statistics, field, adnd)

u64 snmp_get_cpu_field(व्योम __percpu *mib, पूर्णांक cpu, पूर्णांक offct);
अचिन्हित दीर्घ snmp_fold_field(व्योम __percpu *mib, पूर्णांक offt);
#अगर BITS_PER_LONG==32
u64 snmp_get_cpu_field64(व्योम __percpu *mib, पूर्णांक cpu, पूर्णांक offct,
			 माप_प्रकार syncp_offset);
u64 snmp_fold_field64(व्योम __percpu *mib, पूर्णांक offt, माप_प्रकार sync_off);
#अन्यथा
अटल अंतरभूत u64  snmp_get_cpu_field64(व्योम __percpu *mib, पूर्णांक cpu, पूर्णांक offct,
					माप_प्रकार syncp_offset)
अणु
	वापस snmp_get_cpu_field(mib, cpu, offct);

पूर्ण

अटल अंतरभूत u64 snmp_fold_field64(व्योम __percpu *mib, पूर्णांक offt, माप_प्रकार syncp_off)
अणु
	वापस snmp_fold_field(mib, offt);
पूर्ण
#पूर्ण_अगर

#घोषणा snmp_get_cpu_field64_batch(buff64, stats_list, mib_statistic, offset) \
अणु \
	पूर्णांक i, c; \
	क्रम_each_possible_cpu(c) अणु \
		क्रम (i = 0; stats_list[i].name; i++) \
			buff64[i] += snmp_get_cpu_field64( \
					mib_statistic, \
					c, stats_list[i].entry, \
					offset); \
	पूर्ण \
पूर्ण

#घोषणा snmp_get_cpu_field_batch(buff, stats_list, mib_statistic) \
अणु \
	पूर्णांक i, c; \
	क्रम_each_possible_cpu(c) अणु \
		क्रम (i = 0; stats_list[i].name; i++) \
			buff[i] += snmp_get_cpu_field( \
						mib_statistic, \
						c, stats_list[i].entry); \
	पूर्ण \
पूर्ण

व्योम inet_get_local_port_range(काष्ठा net *net, पूर्णांक *low, पूर्णांक *high);

#अगर_घोषित CONFIG_SYSCTL
अटल अंतरभूत bool inet_is_local_reserved_port(काष्ठा net *net, अचिन्हित लघु port)
अणु
	अगर (!net->ipv4.sysctl_local_reserved_ports)
		वापस false;
	वापस test_bit(port, net->ipv4.sysctl_local_reserved_ports);
पूर्ण

अटल अंतरभूत bool sysctl_dev_name_is_allowed(स्थिर अक्षर *name)
अणु
	वापस म_भेद(name, "default") != 0  && म_भेद(name, "all") != 0;
पूर्ण

अटल अंतरभूत bool inet_port_requires_bind_service(काष्ठा net *net, अचिन्हित लघु port)
अणु
	वापस port < net->ipv4.sysctl_ip_prot_sock;
पूर्ण

#अन्यथा
अटल अंतरभूत bool inet_is_local_reserved_port(काष्ठा net *net, अचिन्हित लघु port)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool inet_port_requires_bind_service(काष्ठा net *net, अचिन्हित लघु port)
अणु
	वापस port < PROT_SOCK;
पूर्ण
#पूर्ण_अगर

__be32 inet_current_बारtamp(व्योम);

/* From inetpeer.c */
बाह्य पूर्णांक inet_peer_threshold;
बाह्य पूर्णांक inet_peer_mपूर्णांकtl;
बाह्य पूर्णांक inet_peer_maxttl;

व्योम ipfrag_init(व्योम);

व्योम ip_अटल_sysctl_init(व्योम);

#घोषणा IP4_REPLY_MARK(net, mark) \
	((net)->ipv4.sysctl_fwmark_reflect ? (mark) : 0)

अटल अंतरभूत bool ip_is_fragment(स्थिर काष्ठा iphdr *iph)
अणु
	वापस (iph->frag_off & htons(IP_MF | IP_OFFSET)) != 0;
पूर्ण

#अगर_घोषित CONFIG_INET
#समावेश <net/dst.h>

/* The function in 2.2 was invalid, producing wrong result क्रम
 * check=0xFEFF. It was noticed by Arthur Skawina _year_ ago. --ANK(000625) */
अटल अंतरभूत
पूर्णांक ip_decrease_ttl(काष्ठा iphdr *iph)
अणु
	u32 check = (__क्रमce u32)iph->check;
	check += (__क्रमce u32)htons(0x0100);
	iph->check = (__क्रमce __sum16)(check + (check>=0xFFFF));
	वापस --iph->ttl;
पूर्ण

अटल अंतरभूत पूर्णांक ip_mtu_locked(स्थिर काष्ठा dst_entry *dst)
अणु
	स्थिर काष्ठा rtable *rt = (स्थिर काष्ठा rtable *)dst;

	वापस rt->rt_mtu_locked || dst_metric_locked(dst, RTAX_MTU);
पूर्ण

अटल अंतरभूत
पूर्णांक ip_करोnt_fragment(स्थिर काष्ठा sock *sk, स्थिर काष्ठा dst_entry *dst)
अणु
	u8 pmtudisc = READ_ONCE(inet_sk(sk)->pmtudisc);

	वापस  pmtudisc == IP_PMTUDISC_DO ||
		(pmtudisc == IP_PMTUDISC_WANT &&
		 !ip_mtu_locked(dst));
पूर्ण

अटल अंतरभूत bool ip_sk_accept_pmtu(स्थिर काष्ठा sock *sk)
अणु
	वापस inet_sk(sk)->pmtudisc != IP_PMTUDISC_INTERFACE &&
	       inet_sk(sk)->pmtudisc != IP_PMTUDISC_OMIT;
पूर्ण

अटल अंतरभूत bool ip_sk_use_pmtu(स्थिर काष्ठा sock *sk)
अणु
	वापस inet_sk(sk)->pmtudisc < IP_PMTUDISC_PROBE;
पूर्ण

अटल अंतरभूत bool ip_sk_ignore_df(स्थिर काष्ठा sock *sk)
अणु
	वापस inet_sk(sk)->pmtudisc < IP_PMTUDISC_DO ||
	       inet_sk(sk)->pmtudisc == IP_PMTUDISC_OMIT;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ip_dst_mtu_maybe_क्रमward(स्थिर काष्ठा dst_entry *dst,
						    bool क्रमwarding)
अणु
	काष्ठा net *net = dev_net(dst->dev);
	अचिन्हित पूर्णांक mtu;

	अगर (net->ipv4.sysctl_ip_fwd_use_pmtu ||
	    ip_mtu_locked(dst) ||
	    !क्रमwarding)
		वापस dst_mtu(dst);

	/* 'forwarding = true' हाल should always honour route mtu */
	mtu = dst_metric_raw(dst, RTAX_MTU);
	अगर (mtu)
		वापस mtu;

	वापस min(READ_ONCE(dst->dev->mtu), IP_MAX_MTU);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ip_skb_dst_mtu(काष्ठा sock *sk,
					  स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (!sk || !sk_fullsock(sk) || ip_sk_use_pmtu(sk)) अणु
		bool क्रमwarding = IPCB(skb)->flags & IPSKB_FORWARDED;

		वापस ip_dst_mtu_maybe_क्रमward(skb_dst(skb), क्रमwarding);
	पूर्ण

	वापस min(READ_ONCE(skb_dst(skb)->dev->mtu), IP_MAX_MTU);
पूर्ण

काष्ठा dst_metrics *ip_fib_metrics_init(काष्ठा net *net, काष्ठा nlattr *fc_mx,
					पूर्णांक fc_mx_len,
					काष्ठा netlink_ext_ack *extack);
अटल अंतरभूत व्योम ip_fib_metrics_put(काष्ठा dst_metrics *fib_metrics)
अणु
	अगर (fib_metrics != &dst_शेष_metrics &&
	    refcount_dec_and_test(&fib_metrics->refcnt))
		kमुक्त(fib_metrics);
पूर्ण

/* ipv4 and ipv6 both use refcounted metrics अगर it is not the शेष */
अटल अंतरभूत
व्योम ip_dst_init_metrics(काष्ठा dst_entry *dst, काष्ठा dst_metrics *fib_metrics)
अणु
	dst_init_metrics(dst, fib_metrics->metrics, true);

	अगर (fib_metrics != &dst_शेष_metrics) अणु
		dst->_metrics |= DST_METRICS_REFCOUNTED;
		refcount_inc(&fib_metrics->refcnt);
	पूर्ण
पूर्ण

अटल अंतरभूत
व्योम ip_dst_metrics_put(काष्ठा dst_entry *dst)
अणु
	काष्ठा dst_metrics *p = (काष्ठा dst_metrics *)DST_METRICS_PTR(dst);

	अगर (p != &dst_शेष_metrics && refcount_dec_and_test(&p->refcnt))
		kमुक्त(p);
पूर्ण

u32 ip_idents_reserve(u32 hash, पूर्णांक segs);
व्योम __ip_select_ident(काष्ठा net *net, काष्ठा iphdr *iph, पूर्णांक segs);

अटल अंतरभूत व्योम ip_select_ident_segs(काष्ठा net *net, काष्ठा sk_buff *skb,
					काष्ठा sock *sk, पूर्णांक segs)
अणु
	काष्ठा iphdr *iph = ip_hdr(skb);

	अगर ((iph->frag_off & htons(IP_DF)) && !skb->ignore_df) अणु
		/* This is only to work around buggy Winकरोws95/2000
		 * VJ compression implementations.  If the ID field
		 * करोes not change, they drop every other packet in
		 * a TCP stream using header compression.
		 */
		अगर (sk && inet_sk(sk)->inet_daddr) अणु
			iph->id = htons(inet_sk(sk)->inet_id);
			inet_sk(sk)->inet_id += segs;
		पूर्ण अन्यथा अणु
			iph->id = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		__ip_select_ident(net, iph, segs);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ip_select_ident(काष्ठा net *net, काष्ठा sk_buff *skb,
				   काष्ठा sock *sk)
अणु
	ip_select_ident_segs(net, skb, sk, 1);
पूर्ण

अटल अंतरभूत __wsum inet_compute_pseuकरो(काष्ठा sk_buff *skb, पूर्णांक proto)
अणु
	वापस csum_tcpudp_nofold(ip_hdr(skb)->saddr, ip_hdr(skb)->daddr,
				  skb->len, proto, 0);
पूर्ण

/* copy IPv4 saddr & daddr to flow_keys, possibly using 64bit load/store
 * Equivalent to :	flow->v4addrs.src = iph->saddr;
 *			flow->v4addrs.dst = iph->daddr;
 */
अटल अंतरभूत व्योम iph_to_flow_copy_v4addrs(काष्ठा flow_keys *flow,
					    स्थिर काष्ठा iphdr *iph)
अणु
	BUILD_BUG_ON(दुरत्व(typeof(flow->addrs), v4addrs.dst) !=
		     दुरत्व(typeof(flow->addrs), v4addrs.src) +
			      माप(flow->addrs.v4addrs.src));
	स_नकल(&flow->addrs.v4addrs, &iph->saddr, माप(flow->addrs.v4addrs));
	flow->control.addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
पूर्ण

अटल अंतरभूत __wsum inet_gro_compute_pseuकरो(काष्ठा sk_buff *skb, पूर्णांक proto)
अणु
	स्थिर काष्ठा iphdr *iph = skb_gro_network_header(skb);

	वापस csum_tcpudp_nofold(iph->saddr, iph->daddr,
				  skb_gro_len(skb), proto, 0);
पूर्ण

/*
 *	Map a multicast IP onto multicast MAC क्रम type ethernet.
 */

अटल अंतरभूत व्योम ip_eth_mc_map(__be32 naddr, अक्षर *buf)
अणु
	__u32 addr=ntohl(naddr);
	buf[0]=0x01;
	buf[1]=0x00;
	buf[2]=0x5e;
	buf[5]=addr&0xFF;
	addr>>=8;
	buf[4]=addr&0xFF;
	addr>>=8;
	buf[3]=addr&0x7F;
पूर्ण

/*
 *	Map a multicast IP onto multicast MAC क्रम type IP-over-InfiniBand.
 *	Leave P_Key as 0 to be filled in by driver.
 */

अटल अंतरभूत व्योम ip_ib_mc_map(__be32 naddr, स्थिर अचिन्हित अक्षर *broadcast, अक्षर *buf)
अणु
	__u32 addr;
	अचिन्हित अक्षर scope = broadcast[5] & 0xF;

	buf[0]  = 0;		/* Reserved */
	buf[1]  = 0xff;		/* Multicast QPN */
	buf[2]  = 0xff;
	buf[3]  = 0xff;
	addr    = ntohl(naddr);
	buf[4]  = 0xff;
	buf[5]  = 0x10 | scope;	/* scope from broadcast address */
	buf[6]  = 0x40;		/* IPv4 signature */
	buf[7]  = 0x1b;
	buf[8]  = broadcast[8];		/* P_Key */
	buf[9]  = broadcast[9];
	buf[10] = 0;
	buf[11] = 0;
	buf[12] = 0;
	buf[13] = 0;
	buf[14] = 0;
	buf[15] = 0;
	buf[19] = addr & 0xff;
	addr  >>= 8;
	buf[18] = addr & 0xff;
	addr  >>= 8;
	buf[17] = addr & 0xff;
	addr  >>= 8;
	buf[16] = addr & 0x0f;
पूर्ण

अटल अंतरभूत व्योम ip_ipgre_mc_map(__be32 naddr, स्थिर अचिन्हित अक्षर *broadcast, अक्षर *buf)
अणु
	अगर ((broadcast[0] | broadcast[1] | broadcast[2] | broadcast[3]) != 0)
		स_नकल(buf, broadcast, 4);
	अन्यथा
		स_नकल(buf, &naddr, माप(naddr));
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <linux/ipv6.h>
#पूर्ण_अगर

अटल __अंतरभूत__ व्योम inet_reset_saddr(काष्ठा sock *sk)
अणु
	inet_sk(sk)->inet_rcv_saddr = inet_sk(sk)->inet_saddr = 0;
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (sk->sk_family == PF_INET6) अणु
		काष्ठा ipv6_pinfo *np = inet6_sk(sk);

		स_रखो(&np->saddr, 0, माप(np->saddr));
		स_रखो(&sk->sk_v6_rcv_saddr, 0, माप(sk->sk_v6_rcv_saddr));
	पूर्ण
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर

अटल अंतरभूत अचिन्हित पूर्णांक ipv4_addr_hash(__be32 ip)
अणु
	वापस (__क्रमce अचिन्हित पूर्णांक) ip;
पूर्ण

अटल अंतरभूत u32 ipv4_portaddr_hash(स्थिर काष्ठा net *net,
				     __be32 saddr,
				     अचिन्हित पूर्णांक port)
अणु
	वापस jhash_1word((__क्रमce u32)saddr, net_hash_mix(net)) ^ port;
पूर्ण

bool ip_call_ra_chain(काष्ठा sk_buff *skb);

/*
 *	Functions provided by ip_fragment.c
 */

क्रमागत ip_defrag_users अणु
	IP_DEFRAG_LOCAL_DELIVER,
	IP_DEFRAG_CALL_RA_CHAIN,
	IP_DEFRAG_CONNTRACK_IN,
	__IP_DEFRAG_CONNTRACK_IN_END	= IP_DEFRAG_CONNTRACK_IN + अच_लघु_उच्च,
	IP_DEFRAG_CONNTRACK_OUT,
	__IP_DEFRAG_CONNTRACK_OUT_END	= IP_DEFRAG_CONNTRACK_OUT + अच_लघु_उच्च,
	IP_DEFRAG_CONNTRACK_BRIDGE_IN,
	__IP_DEFRAG_CONNTRACK_BRIDGE_IN = IP_DEFRAG_CONNTRACK_BRIDGE_IN + अच_लघु_उच्च,
	IP_DEFRAG_VS_IN,
	IP_DEFRAG_VS_OUT,
	IP_DEFRAG_VS_FWD,
	IP_DEFRAG_AF_PACKET,
	IP_DEFRAG_MACVLAN,
पूर्ण;

/* Return true अगर the value of 'user' is between 'lower_bond'
 * and 'upper_bond' inclusively.
 */
अटल अंतरभूत bool ip_defrag_user_in_between(u32 user,
					     क्रमागत ip_defrag_users lower_bond,
					     क्रमागत ip_defrag_users upper_bond)
अणु
	वापस user >= lower_bond && user <= upper_bond;
पूर्ण

पूर्णांक ip_defrag(काष्ठा net *net, काष्ठा sk_buff *skb, u32 user);
#अगर_घोषित CONFIG_INET
काष्ठा sk_buff *ip_check_defrag(काष्ठा net *net, काष्ठा sk_buff *skb, u32 user);
#अन्यथा
अटल अंतरभूत काष्ठा sk_buff *ip_check_defrag(काष्ठा net *net, काष्ठा sk_buff *skb, u32 user)
अणु
	वापस skb;
पूर्ण
#पूर्ण_अगर

/*
 *	Functions provided by ip_क्रमward.c
 */

पूर्णांक ip_क्रमward(काष्ठा sk_buff *skb);

/*
 *	Functions provided by ip_options.c
 */

व्योम ip_options_build(काष्ठा sk_buff *skb, काष्ठा ip_options *opt,
		      __be32 daddr, काष्ठा rtable *rt, पूर्णांक is_frag);

पूर्णांक __ip_options_echo(काष्ठा net *net, काष्ठा ip_options *करोpt,
		      काष्ठा sk_buff *skb, स्थिर काष्ठा ip_options *sopt);
अटल अंतरभूत पूर्णांक ip_options_echo(काष्ठा net *net, काष्ठा ip_options *करोpt,
				  काष्ठा sk_buff *skb)
अणु
	वापस __ip_options_echo(net, करोpt, skb, &IPCB(skb)->opt);
पूर्ण

व्योम ip_options_fragment(काष्ठा sk_buff *skb);
पूर्णांक __ip_options_compile(काष्ठा net *net, काष्ठा ip_options *opt,
			 काष्ठा sk_buff *skb, __be32 *info);
पूर्णांक ip_options_compile(काष्ठा net *net, काष्ठा ip_options *opt,
		       काष्ठा sk_buff *skb);
पूर्णांक ip_options_get(काष्ठा net *net, काष्ठा ip_options_rcu **optp,
		   sockptr_t data, पूर्णांक optlen);
व्योम ip_options_unकरो(काष्ठा ip_options *opt);
व्योम ip_क्रमward_options(काष्ठा sk_buff *skb);
पूर्णांक ip_options_rcv_srr(काष्ठा sk_buff *skb, काष्ठा net_device *dev);

/*
 *	Functions provided by ip_sockglue.c
 */

व्योम ipv4_pktinfo_prepare(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb);
व्योम ip_cmsg_recv_offset(काष्ठा msghdr *msg, काष्ठा sock *sk,
			 काष्ठा sk_buff *skb, पूर्णांक tlen, पूर्णांक offset);
पूर्णांक ip_cmsg_send(काष्ठा sock *sk, काष्ठा msghdr *msg,
		 काष्ठा ipcm_cookie *ipc, bool allow_ipv6);
पूर्णांक ip_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname, sockptr_t optval,
		  अचिन्हित पूर्णांक optlen);
पूर्णांक ip_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname, अक्षर __user *optval,
		  पूर्णांक __user *optlen);
पूर्णांक ip_ra_control(काष्ठा sock *sk, अचिन्हित अक्षर on,
		  व्योम (*deकाष्ठाor)(काष्ठा sock *));

पूर्णांक ip_recv_error(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक len, पूर्णांक *addr_len);
व्योम ip_icmp_error(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक err, __be16 port,
		   u32 info, u8 *payload);
व्योम ip_local_error(काष्ठा sock *sk, पूर्णांक err, __be32 daddr, __be16 dport,
		    u32 info);

अटल अंतरभूत व्योम ip_cmsg_recv(काष्ठा msghdr *msg, काष्ठा sk_buff *skb)
अणु
	ip_cmsg_recv_offset(msg, skb->sk, skb, 0, 0);
पूर्ण

bool icmp_global_allow(व्योम);
बाह्य पूर्णांक sysctl_icmp_msgs_per_sec;
बाह्य पूर्णांक sysctl_icmp_msgs_burst;

#अगर_घोषित CONFIG_PROC_FS
पूर्णांक ip_misc_proc_init(व्योम);
#पूर्ण_अगर

पूर्णांक rपंचांग_getroute_parse_ip_proto(काष्ठा nlattr *attr, u8 *ip_proto, u8 family,
				काष्ठा netlink_ext_ack *extack);

अटल अंतरभूत bool inetdev_valid_mtu(अचिन्हित पूर्णांक mtu)
अणु
	वापस likely(mtu >= IPV4_MIN_MTU);
पूर्ण

व्योम ip_sock_set_मुक्तbind(काष्ठा sock *sk);
पूर्णांक ip_sock_set_mtu_discover(काष्ठा sock *sk, पूर्णांक val);
व्योम ip_sock_set_pktinfo(काष्ठा sock *sk);
व्योम ip_sock_set_recverr(काष्ठा sock *sk);
व्योम ip_sock_set_tos(काष्ठा sock *sk, पूर्णांक val);

#पूर्ण_अगर	/* _IP_H */
