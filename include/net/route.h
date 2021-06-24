<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET  is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the IP router.
 *
 * Version:	@(#)route.h	1.0.4	05/27/93
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 * Fixes:
 *		Alan Cox	:	Reक्रमmatted. Added ip_rt_local()
 *		Alan Cox	:	Support क्रम TCP parameters.
 *		Alexey Kuznetsov:	Major changes क्रम new routing code.
 *		Mike McLagan    :	Routing by source
 *		Robert Olsson   :	Added rt_cache statistics
 */
#अगर_अघोषित _ROUTE_H
#घोषणा _ROUTE_H

#समावेश <net/dst.h>
#समावेश <net/inetpeer.h>
#समावेश <net/flow.h>
#समावेश <net/inet_sock.h>
#समावेश <net/ip_fib.h>
#समावेश <net/arp.h>
#समावेश <net/ndisc.h>
#समावेश <linux/in_route.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/route.h>
#समावेश <linux/ip.h>
#समावेश <linux/cache.h>
#समावेश <linux/security.h>

/* IPv4 datagram length is stored पूर्णांकo 16bit field (tot_len) */
#घोषणा IP_MAX_MTU	0xFFFFU

#घोषणा RTO_ONLINK	0x01

#घोषणा RT_CONN_FLAGS(sk)   (RT_TOS(inet_sk(sk)->tos) | sock_flag(sk, SOCK_LOCALROUTE))
#घोषणा RT_CONN_FLAGS_TOS(sk,tos)   (RT_TOS(tos) | sock_flag(sk, SOCK_LOCALROUTE))

काष्ठा fib_nh;
काष्ठा fib_info;
काष्ठा uncached_list;
काष्ठा rtable अणु
	काष्ठा dst_entry	dst;

	पूर्णांक			rt_genid;
	अचिन्हित पूर्णांक		rt_flags;
	__u16			rt_type;
	__u8			rt_is_input;
	__u8			rt_uses_gateway;

	पूर्णांक			rt_iअगर;

	u8			rt_gw_family;
	/* Info on neighbour */
	जोड़ अणु
		__be32		rt_gw4;
		काष्ठा in6_addr	rt_gw6;
	पूर्ण;

	/* Miscellaneous cached inक्रमmation */
	u32			rt_mtu_locked:1,
				rt_pmtu:31;

	काष्ठा list_head	rt_uncached;
	काष्ठा uncached_list	*rt_uncached_list;
पूर्ण;

अटल अंतरभूत bool rt_is_input_route(स्थिर काष्ठा rtable *rt)
अणु
	वापस rt->rt_is_input != 0;
पूर्ण

अटल अंतरभूत bool rt_is_output_route(स्थिर काष्ठा rtable *rt)
अणु
	वापस rt->rt_is_input == 0;
पूर्ण

अटल अंतरभूत __be32 rt_nexthop(स्थिर काष्ठा rtable *rt, __be32 daddr)
अणु
	अगर (rt->rt_gw_family == AF_INET)
		वापस rt->rt_gw4;
	वापस daddr;
पूर्ण

काष्ठा ip_rt_acct अणु
	__u32 	o_bytes;
	__u32 	o_packets;
	__u32 	i_bytes;
	__u32 	i_packets;
पूर्ण;

काष्ठा rt_cache_stat अणु
        अचिन्हित पूर्णांक in_slow_tot;
        अचिन्हित पूर्णांक in_slow_mc;
        अचिन्हित पूर्णांक in_no_route;
        अचिन्हित पूर्णांक in_brd;
        अचिन्हित पूर्णांक in_martian_dst;
        अचिन्हित पूर्णांक in_martian_src;
        अचिन्हित पूर्णांक out_slow_tot;
        अचिन्हित पूर्णांक out_slow_mc;
पूर्ण;

बाह्य काष्ठा ip_rt_acct __percpu *ip_rt_acct;

काष्ठा in_device;

पूर्णांक ip_rt_init(व्योम);
व्योम rt_cache_flush(काष्ठा net *net);
व्योम rt_flush_dev(काष्ठा net_device *dev);
काष्ठा rtable *ip_route_output_key_hash(काष्ठा net *net, काष्ठा flowi4 *flp,
					स्थिर काष्ठा sk_buff *skb);
काष्ठा rtable *ip_route_output_key_hash_rcu(काष्ठा net *net, काष्ठा flowi4 *flp,
					    काष्ठा fib_result *res,
					    स्थिर काष्ठा sk_buff *skb);

अटल अंतरभूत काष्ठा rtable *__ip_route_output_key(काष्ठा net *net,
						   काष्ठा flowi4 *flp)
अणु
	वापस ip_route_output_key_hash(net, flp, शून्य);
पूर्ण

काष्ठा rtable *ip_route_output_flow(काष्ठा net *, काष्ठा flowi4 *flp,
				    स्थिर काष्ठा sock *sk);
काष्ठा rtable *ip_route_output_tunnel(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev,
				      काष्ठा net *net, __be32 *saddr,
				      स्थिर काष्ठा ip_tunnel_info *info,
				      u8 protocol, bool use_cache);

काष्ठा dst_entry *ipv4_blackhole_route(काष्ठा net *net,
				       काष्ठा dst_entry *dst_orig);

अटल अंतरभूत काष्ठा rtable *ip_route_output_key(काष्ठा net *net, काष्ठा flowi4 *flp)
अणु
	वापस ip_route_output_flow(net, flp, शून्य);
पूर्ण

अटल अंतरभूत काष्ठा rtable *ip_route_output(काष्ठा net *net, __be32 daddr,
					     __be32 saddr, u8 tos, पूर्णांक oअगर)
अणु
	काष्ठा flowi4 fl4 = अणु
		.flowi4_oअगर = oअगर,
		.flowi4_tos = tos,
		.daddr = daddr,
		.saddr = saddr,
	पूर्ण;
	वापस ip_route_output_key(net, &fl4);
पूर्ण

अटल अंतरभूत काष्ठा rtable *ip_route_output_ports(काष्ठा net *net, काष्ठा flowi4 *fl4,
						   काष्ठा sock *sk,
						   __be32 daddr, __be32 saddr,
						   __be16 dport, __be16 sport,
						   __u8 proto, __u8 tos, पूर्णांक oअगर)
अणु
	flowi4_init_output(fl4, oअगर, sk ? sk->sk_mark : 0, tos,
			   RT_SCOPE_UNIVERSE, proto,
			   sk ? inet_sk_flowi_flags(sk) : 0,
			   daddr, saddr, dport, sport, sock_net_uid(net, sk));
	अगर (sk)
		security_sk_classअगरy_flow(sk, flowi4_to_flowi_common(fl4));
	वापस ip_route_output_flow(net, fl4, sk);
पूर्ण

अटल अंतरभूत काष्ठा rtable *ip_route_output_gre(काष्ठा net *net, काष्ठा flowi4 *fl4,
						 __be32 daddr, __be32 saddr,
						 __be32 gre_key, __u8 tos, पूर्णांक oअगर)
अणु
	स_रखो(fl4, 0, माप(*fl4));
	fl4->flowi4_oअगर = oअगर;
	fl4->daddr = daddr;
	fl4->saddr = saddr;
	fl4->flowi4_tos = tos;
	fl4->flowi4_proto = IPPROTO_GRE;
	fl4->fl4_gre_key = gre_key;
	वापस ip_route_output_key(net, fl4);
पूर्ण
पूर्णांक ip_mc_validate_source(काष्ठा sk_buff *skb, __be32 daddr, __be32 saddr,
			  u8 tos, काष्ठा net_device *dev,
			  काष्ठा in_device *in_dev, u32 *itag);
पूर्णांक ip_route_input_noref(काष्ठा sk_buff *skb, __be32 dst, __be32 src,
			 u8 tos, काष्ठा net_device *devin);
पूर्णांक ip_route_input_rcu(काष्ठा sk_buff *skb, __be32 dst, __be32 src,
		       u8 tos, काष्ठा net_device *devin,
		       काष्ठा fib_result *res);

पूर्णांक ip_route_use_hपूर्णांक(काष्ठा sk_buff *skb, __be32 dst, __be32 src,
		      u8 tos, काष्ठा net_device *devin,
		      स्थिर काष्ठा sk_buff *hपूर्णांक);

अटल अंतरभूत पूर्णांक ip_route_input(काष्ठा sk_buff *skb, __be32 dst, __be32 src,
				 u8 tos, काष्ठा net_device *devin)
अणु
	पूर्णांक err;

	rcu_पढ़ो_lock();
	err = ip_route_input_noref(skb, dst, src, tos, devin);
	अगर (!err) अणु
		skb_dst_क्रमce(skb);
		अगर (!skb_dst(skb))
			err = -EINVAL;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

व्योम ipv4_update_pmtu(काष्ठा sk_buff *skb, काष्ठा net *net, u32 mtu, पूर्णांक oअगर,
		      u8 protocol);
व्योम ipv4_sk_update_pmtu(काष्ठा sk_buff *skb, काष्ठा sock *sk, u32 mtu);
व्योम ipv4_redirect(काष्ठा sk_buff *skb, काष्ठा net *net, पूर्णांक oअगर, u8 protocol);
व्योम ipv4_sk_redirect(काष्ठा sk_buff *skb, काष्ठा sock *sk);
व्योम ip_rt_send_redirect(काष्ठा sk_buff *skb);

अचिन्हित पूर्णांक inet_addr_type(काष्ठा net *net, __be32 addr);
अचिन्हित पूर्णांक inet_addr_type_table(काष्ठा net *net, __be32 addr, u32 tb_id);
अचिन्हित पूर्णांक inet_dev_addr_type(काष्ठा net *net, स्थिर काष्ठा net_device *dev,
				__be32 addr);
अचिन्हित पूर्णांक inet_addr_type_dev_table(काष्ठा net *net,
				      स्थिर काष्ठा net_device *dev,
				      __be32 addr);
व्योम ip_rt_multicast_event(काष्ठा in_device *);
पूर्णांक ip_rt_ioctl(काष्ठा net *, अचिन्हित पूर्णांक cmd, काष्ठा rtentry *rt);
व्योम ip_rt_get_source(u8 *src, काष्ठा sk_buff *skb, काष्ठा rtable *rt);
काष्ठा rtable *rt_dst_alloc(काष्ठा net_device *dev,
			     अचिन्हित पूर्णांक flags, u16 type,
			     bool nopolicy, bool noxfrm);
काष्ठा rtable *rt_dst_clone(काष्ठा net_device *dev, काष्ठा rtable *rt);

काष्ठा in_अगरaddr;
व्योम fib_add_अगरaddr(काष्ठा in_अगरaddr *);
व्योम fib_del_अगरaddr(काष्ठा in_अगरaddr *, काष्ठा in_अगरaddr *);
व्योम fib_modअगरy_prefix_metric(काष्ठा in_अगरaddr *अगरa, u32 new_metric);

व्योम rt_add_uncached_list(काष्ठा rtable *rt);
व्योम rt_del_uncached_list(काष्ठा rtable *rt);

पूर्णांक fib_dump_info_fnhe(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
		       u32 table_id, काष्ठा fib_info *fi,
		       पूर्णांक *fa_index, पूर्णांक fa_start, अचिन्हित पूर्णांक flags);

अटल अंतरभूत व्योम ip_rt_put(काष्ठा rtable *rt)
अणु
	/* dst_release() accepts a शून्य parameter.
	 * We rely on dst being first काष्ठाure in काष्ठा rtable
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा rtable, dst) != 0);
	dst_release(&rt->dst);
पूर्ण

#घोषणा IPTOS_RT_MASK	(IPTOS_TOS_MASK & ~3)

बाह्य स्थिर __u8 ip_tos2prio[16];

अटल अंतरभूत अक्षर rt_tos2priority(u8 tos)
अणु
	वापस ip_tos2prio[IPTOS_TOS(tos)>>1];
पूर्ण

/* ip_route_connect() and ip_route_newports() work in tandem whilst
 * binding a socket क्रम a new outgoing connection.
 *
 * In order to use IPSEC properly, we must, in the end, have a
 * route that was looked up using all available keys including source
 * and destination ports.
 *
 * However, अगर a source port needs to be allocated (the user specअगरied
 * a wildcard source port) we need to obtain addressing inक्रमmation
 * in order to perक्रमm that allocation.
 *
 * So ip_route_connect() looks up a route using wildcarded source and
 * destination ports in the key, simply so that we can get a pair of
 * addresses to use क्रम port allocation.
 *
 * Later, once the ports are allocated, ip_route_newports() will make
 * another route lookup अगर needed to make sure we catch any IPSEC
 * rules keyed on the port inक्रमmation.
 *
 * The callers allocate the flow key on their stack, and must pass in
 * the same flowi4 object to both the ip_route_connect() and the
 * ip_route_newports() calls.
 */

अटल अंतरभूत व्योम ip_route_connect_init(काष्ठा flowi4 *fl4, __be32 dst, __be32 src,
					 u32 tos, पूर्णांक oअगर, u8 protocol,
					 __be16 sport, __be16 dport,
					 काष्ठा sock *sk)
अणु
	__u8 flow_flags = 0;

	अगर (inet_sk(sk)->transparent)
		flow_flags |= FLOWI_FLAG_ANYSRC;

	flowi4_init_output(fl4, oअगर, sk->sk_mark, tos, RT_SCOPE_UNIVERSE,
			   protocol, flow_flags, dst, src, dport, sport,
			   sk->sk_uid);
पूर्ण

अटल अंतरभूत काष्ठा rtable *ip_route_connect(काष्ठा flowi4 *fl4,
					      __be32 dst, __be32 src, u32 tos,
					      पूर्णांक oअगर, u8 protocol,
					      __be16 sport, __be16 dport,
					      काष्ठा sock *sk)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा rtable *rt;

	ip_route_connect_init(fl4, dst, src, tos, oअगर, protocol,
			      sport, dport, sk);

	अगर (!dst || !src) अणु
		rt = __ip_route_output_key(net, fl4);
		अगर (IS_ERR(rt))
			वापस rt;
		ip_rt_put(rt);
		flowi4_update_output(fl4, oअगर, tos, fl4->daddr, fl4->saddr);
	पूर्ण
	security_sk_classअगरy_flow(sk, flowi4_to_flowi_common(fl4));
	वापस ip_route_output_flow(net, fl4, sk);
पूर्ण

अटल अंतरभूत काष्ठा rtable *ip_route_newports(काष्ठा flowi4 *fl4, काष्ठा rtable *rt,
					       __be16 orig_sport, __be16 orig_dport,
					       __be16 sport, __be16 dport,
					       काष्ठा sock *sk)
अणु
	अगर (sport != orig_sport || dport != orig_dport) अणु
		fl4->fl4_dport = dport;
		fl4->fl4_sport = sport;
		ip_rt_put(rt);
		flowi4_update_output(fl4, sk->sk_bound_dev_अगर,
				     RT_CONN_FLAGS(sk), fl4->daddr,
				     fl4->saddr);
		security_sk_classअगरy_flow(sk, flowi4_to_flowi_common(fl4));
		वापस ip_route_output_flow(sock_net(sk), fl4, sk);
	पूर्ण
	वापस rt;
पूर्ण

अटल अंतरभूत पूर्णांक inet_iअगर(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा rtable *rt = skb_rtable(skb);

	अगर (rt && rt->rt_iअगर)
		वापस rt->rt_iअगर;

	वापस skb->skb_iअगर;
पूर्ण

अटल अंतरभूत पूर्णांक ip4_dst_hoplimit(स्थिर काष्ठा dst_entry *dst)
अणु
	पूर्णांक hoplimit = dst_metric_raw(dst, RTAX_HOPLIMIT);
	काष्ठा net *net = dev_net(dst->dev);

	अगर (hoplimit == 0)
		hoplimit = net->ipv4.sysctl_ip_शेष_ttl;
	वापस hoplimit;
पूर्ण

अटल अंतरभूत काष्ठा neighbour *ip_neigh_gw4(काष्ठा net_device *dev,
					     __be32 daddr)
अणु
	काष्ठा neighbour *neigh;

	neigh = __ipv4_neigh_lookup_noref(dev, daddr);
	अगर (unlikely(!neigh))
		neigh = __neigh_create(&arp_tbl, &daddr, dev, false);

	वापस neigh;
पूर्ण

अटल अंतरभूत काष्ठा neighbour *ip_neigh_क्रम_gw(काष्ठा rtable *rt,
						काष्ठा sk_buff *skb,
						bool *is_v6gw)
अणु
	काष्ठा net_device *dev = rt->dst.dev;
	काष्ठा neighbour *neigh;

	अगर (likely(rt->rt_gw_family == AF_INET)) अणु
		neigh = ip_neigh_gw4(dev, rt->rt_gw4);
	पूर्ण अन्यथा अगर (rt->rt_gw_family == AF_INET6) अणु
		neigh = ip_neigh_gw6(dev, &rt->rt_gw6);
		*is_v6gw = true;
	पूर्ण अन्यथा अणु
		neigh = ip_neigh_gw4(dev, ip_hdr(skb)->daddr);
	पूर्ण
	वापस neigh;
पूर्ण

#पूर्ण_अगर	/* _ROUTE_H */
