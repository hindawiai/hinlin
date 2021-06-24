<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_IP6_ROUTE_H
#घोषणा _NET_IP6_ROUTE_H

काष्ठा route_info अणु
	__u8			type;
	__u8			length;
	__u8			prefix_len;
#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8			reserved_h:3,
				route_pref:2,
				reserved_l:3;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8			reserved_l:3,
				route_pref:2,
				reserved_h:3;
#पूर्ण_अगर
	__be32			lअगरeसमय;
	__u8			prefix[];	/* 0,8 or 16 */
पूर्ण;

#समावेश <net/addrconf.h>
#समावेश <net/flow.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/sock.h>
#समावेश <net/lwtunnel.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/route.h>
#समावेश <net/nexthop.h>

#घोषणा RT6_LOOKUP_F_IFACE		0x00000001
#घोषणा RT6_LOOKUP_F_REACHABLE		0x00000002
#घोषणा RT6_LOOKUP_F_HAS_SADDR		0x00000004
#घोषणा RT6_LOOKUP_F_SRCPREF_TMP	0x00000008
#घोषणा RT6_LOOKUP_F_SRCPREF_PUBLIC	0x00000010
#घोषणा RT6_LOOKUP_F_SRCPREF_COA	0x00000020
#घोषणा RT6_LOOKUP_F_IGNORE_LINKSTATE	0x00000040
#घोषणा RT6_LOOKUP_F_DST_NOREF		0x00000080

/* We करो not (yet ?) support IPv6 jumbograms (RFC 2675)
 * Unlike IPv4, hdr->seg_len करोesn't include the IPv6 header
 */
#घोषणा IP6_MAX_MTU (0xFFFF + माप(काष्ठा ipv6hdr))

/*
 * rt6_srcprefs2flags() and rt6_flags2srcprefs() translate
 * between IPV6_ADDR_PREFERENCES socket option values
 *	IPV6_PREFER_SRC_TMP    = 0x1
 *	IPV6_PREFER_SRC_PUBLIC = 0x2
 *	IPV6_PREFER_SRC_COA    = 0x4
 * and above RT6_LOOKUP_F_SRCPREF_xxx flags.
 */
अटल अंतरभूत पूर्णांक rt6_srcprefs2flags(अचिन्हित पूर्णांक srcprefs)
अणु
	/* No need to biपंचांगask because srcprefs have only 3 bits. */
	वापस srcprefs << 3;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rt6_flags2srcprefs(पूर्णांक flags)
अणु
	वापस (flags >> 3) & 7;
पूर्ण

अटल अंतरभूत bool rt6_need_strict(स्थिर काष्ठा in6_addr *daddr)
अणु
	वापस ipv6_addr_type(daddr) &
		(IPV6_ADDR_MULTICAST | IPV6_ADDR_LINKLOCAL | IPV6_ADDR_LOOPBACK);
पूर्ण

/* fib entries using a nexthop object can not be coalesced पूर्णांकo
 * a multipath route
 */
अटल अंतरभूत bool rt6_qualअगरy_क्रम_ecmp(स्थिर काष्ठा fib6_info *f6i)
अणु
	/* the RTF_ADDRCONF flag filters out RA's */
	वापस !(f6i->fib6_flags & RTF_ADDRCONF) && !f6i->nh &&
		f6i->fib6_nh->fib_nh_gw_family;
पूर्ण

व्योम ip6_route_input(काष्ठा sk_buff *skb);
काष्ठा dst_entry *ip6_route_input_lookup(काष्ठा net *net,
					 काष्ठा net_device *dev,
					 काष्ठा flowi6 *fl6,
					 स्थिर काष्ठा sk_buff *skb, पूर्णांक flags);

काष्ठा dst_entry *ip6_route_output_flags_noref(काष्ठा net *net,
					       स्थिर काष्ठा sock *sk,
					       काष्ठा flowi6 *fl6, पूर्णांक flags);

काष्ठा dst_entry *ip6_route_output_flags(काष्ठा net *net, स्थिर काष्ठा sock *sk,
					 काष्ठा flowi6 *fl6, पूर्णांक flags);

अटल अंतरभूत काष्ठा dst_entry *ip6_route_output(काष्ठा net *net,
						 स्थिर काष्ठा sock *sk,
						 काष्ठा flowi6 *fl6)
अणु
	वापस ip6_route_output_flags(net, sk, fl6, 0);
पूर्ण

/* Only conditionally release dst अगर flags indicates
 * !RT6_LOOKUP_F_DST_NOREF or dst is in uncached_list.
 */
अटल अंतरभूत व्योम ip6_rt_put_flags(काष्ठा rt6_info *rt, पूर्णांक flags)
अणु
	अगर (!(flags & RT6_LOOKUP_F_DST_NOREF) ||
	    !list_empty(&rt->rt6i_uncached))
		ip6_rt_put(rt);
पूर्ण

काष्ठा dst_entry *ip6_route_lookup(काष्ठा net *net, काष्ठा flowi6 *fl6,
				   स्थिर काष्ठा sk_buff *skb, पूर्णांक flags);
काष्ठा rt6_info *ip6_pol_route(काष्ठा net *net, काष्ठा fib6_table *table,
			       पूर्णांक अगरindex, काष्ठा flowi6 *fl6,
			       स्थिर काष्ठा sk_buff *skb, पूर्णांक flags);

व्योम ip6_route_init_special_entries(व्योम);
पूर्णांक ip6_route_init(व्योम);
व्योम ip6_route_cleanup(व्योम);

पूर्णांक ipv6_route_ioctl(काष्ठा net *net, अचिन्हित पूर्णांक cmd,
		काष्ठा in6_rपंचांगsg *rपंचांगsg);

पूर्णांक ip6_route_add(काष्ठा fib6_config *cfg, gfp_t gfp_flags,
		  काष्ठा netlink_ext_ack *extack);
पूर्णांक ip6_ins_rt(काष्ठा net *net, काष्ठा fib6_info *f6i);
पूर्णांक ip6_del_rt(काष्ठा net *net, काष्ठा fib6_info *f6i, bool skip_notअगरy);

व्योम rt6_flush_exceptions(काष्ठा fib6_info *f6i);
व्योम rt6_age_exceptions(काष्ठा fib6_info *f6i, काष्ठा fib6_gc_args *gc_args,
			अचिन्हित दीर्घ now);

अटल अंतरभूत पूर्णांक ip6_route_get_saddr(काष्ठा net *net, काष्ठा fib6_info *f6i,
				      स्थिर काष्ठा in6_addr *daddr,
				      अचिन्हित पूर्णांक prefs,
				      काष्ठा in6_addr *saddr)
अणु
	पूर्णांक err = 0;

	अगर (f6i && f6i->fib6_prefsrc.plen) अणु
		*saddr = f6i->fib6_prefsrc.addr;
	पूर्ण अन्यथा अणु
		काष्ठा net_device *dev = f6i ? fib6_info_nh_dev(f6i) : शून्य;

		err = ipv6_dev_get_saddr(net, dev, daddr, prefs, saddr);
	पूर्ण

	वापस err;
पूर्ण

काष्ठा rt6_info *rt6_lookup(काष्ठा net *net, स्थिर काष्ठा in6_addr *daddr,
			    स्थिर काष्ठा in6_addr *saddr, पूर्णांक oअगर,
			    स्थिर काष्ठा sk_buff *skb, पूर्णांक flags);
u32 rt6_multipath_hash(स्थिर काष्ठा net *net, स्थिर काष्ठा flowi6 *fl6,
		       स्थिर काष्ठा sk_buff *skb, काष्ठा flow_keys *hkeys);

काष्ठा dst_entry *icmp6_dst_alloc(काष्ठा net_device *dev, काष्ठा flowi6 *fl6);

व्योम fib6_क्रमce_start_gc(काष्ठा net *net);

काष्ठा fib6_info *addrconf_f6i_alloc(काष्ठा net *net, काष्ठा inet6_dev *idev,
				     स्थिर काष्ठा in6_addr *addr, bool anycast,
				     gfp_t gfp_flags);

काष्ठा rt6_info *ip6_dst_alloc(काष्ठा net *net, काष्ठा net_device *dev,
			       पूर्णांक flags);

/*
 *	support functions क्रम ND
 *
 */
काष्ठा fib6_info *rt6_get_dflt_router(काष्ठा net *net,
				     स्थिर काष्ठा in6_addr *addr,
				     काष्ठा net_device *dev);
काष्ठा fib6_info *rt6_add_dflt_router(काष्ठा net *net,
				     स्थिर काष्ठा in6_addr *gwaddr,
				     काष्ठा net_device *dev, अचिन्हित पूर्णांक pref,
				     u32 defrtr_usr_metric);

व्योम rt6_purge_dflt_routers(काष्ठा net *net);

पूर्णांक rt6_route_rcv(काष्ठा net_device *dev, u8 *opt, पूर्णांक len,
		  स्थिर काष्ठा in6_addr *gwaddr);

व्योम ip6_update_pmtu(काष्ठा sk_buff *skb, काष्ठा net *net, __be32 mtu, पूर्णांक oअगर,
		     u32 mark, kuid_t uid);
व्योम ip6_sk_update_pmtu(काष्ठा sk_buff *skb, काष्ठा sock *sk, __be32 mtu);
व्योम ip6_redirect(काष्ठा sk_buff *skb, काष्ठा net *net, पूर्णांक oअगर, u32 mark,
		  kuid_t uid);
व्योम ip6_redirect_no_header(काष्ठा sk_buff *skb, काष्ठा net *net, पूर्णांक oअगर);
व्योम ip6_sk_redirect(काष्ठा sk_buff *skb, काष्ठा sock *sk);

काष्ठा netlink_callback;

काष्ठा rt6_rtnl_dump_arg अणु
	काष्ठा sk_buff *skb;
	काष्ठा netlink_callback *cb;
	काष्ठा net *net;
	काष्ठा fib_dump_filter filter;
पूर्ण;

पूर्णांक rt6_dump_route(काष्ठा fib6_info *f6i, व्योम *p_arg, अचिन्हित पूर्णांक skip);
व्योम rt6_mtu_change(काष्ठा net_device *dev, अचिन्हित पूर्णांक mtu);
व्योम rt6_हटाओ_prefsrc(काष्ठा inet6_अगरaddr *अगरp);
व्योम rt6_clean_tohost(काष्ठा net *net, काष्ठा in6_addr *gateway);
व्योम rt6_sync_up(काष्ठा net_device *dev, अचिन्हित अक्षर nh_flags);
व्योम rt6_disable_ip(काष्ठा net_device *dev, अचिन्हित दीर्घ event);
व्योम rt6_sync_करोwn_dev(काष्ठा net_device *dev, अचिन्हित दीर्घ event);
व्योम rt6_multipath_rebalance(काष्ठा fib6_info *f6i);

व्योम rt6_uncached_list_add(काष्ठा rt6_info *rt);
व्योम rt6_uncached_list_del(काष्ठा rt6_info *rt);

अटल अंतरभूत स्थिर काष्ठा rt6_info *skb_rt6_info(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा dst_entry *dst = skb_dst(skb);
	स्थिर काष्ठा rt6_info *rt6 = शून्य;

	अगर (dst)
		rt6 = container_of(dst, काष्ठा rt6_info, dst);

	वापस rt6;
पूर्ण

/*
 *	Store a destination cache entry in a socket
 */
अटल अंतरभूत व्योम ip6_dst_store(काष्ठा sock *sk, काष्ठा dst_entry *dst,
				 स्थिर काष्ठा in6_addr *daddr,
				 स्थिर काष्ठा in6_addr *saddr)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);

	np->dst_cookie = rt6_get_cookie((काष्ठा rt6_info *)dst);
	sk_setup_caps(sk, dst);
	np->daddr_cache = daddr;
#अगर_घोषित CONFIG_IPV6_SUBTREES
	np->saddr_cache = saddr;
#पूर्ण_अगर
पूर्ण

व्योम ip6_sk_dst_store_flow(काष्ठा sock *sk, काष्ठा dst_entry *dst,
			   स्थिर काष्ठा flowi6 *fl6);

अटल अंतरभूत bool ipv6_unicast_destination(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा rt6_info *rt = (काष्ठा rt6_info *) skb_dst(skb);

	वापस rt->rt6i_flags & RTF_LOCAL;
पूर्ण

अटल अंतरभूत bool ipv6_anycast_destination(स्थिर काष्ठा dst_entry *dst,
					    स्थिर काष्ठा in6_addr *daddr)
अणु
	काष्ठा rt6_info *rt = (काष्ठा rt6_info *)dst;

	वापस rt->rt6i_flags & RTF_ANYCAST ||
		(rt->rt6i_dst.plen < 127 &&
		 !(rt->rt6i_flags & (RTF_GATEWAY | RTF_NONEXTHOP)) &&
		 ipv6_addr_equal(&rt->rt6i_dst.addr, daddr));
पूर्ण

पूर्णांक ip6_fragment(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb,
		 पूर्णांक (*output)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *));

अटल अंतरभूत पूर्णांक ip6_skb_dst_mtu(काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6_pinfo *np = skb->sk && !dev_recursion_level() ?
				inet6_sk(skb->sk) : शून्य;

	वापस (np && np->pmtudisc >= IPV6_PMTUDISC_PROBE) ?
	       skb_dst(skb)->dev->mtu : dst_mtu(skb_dst(skb));
पूर्ण

अटल अंतरभूत bool ip6_sk_accept_pmtu(स्थिर काष्ठा sock *sk)
अणु
	वापस inet6_sk(sk)->pmtudisc != IPV6_PMTUDISC_INTERFACE &&
	       inet6_sk(sk)->pmtudisc != IPV6_PMTUDISC_OMIT;
पूर्ण

अटल अंतरभूत bool ip6_sk_ignore_df(स्थिर काष्ठा sock *sk)
अणु
	वापस inet6_sk(sk)->pmtudisc < IPV6_PMTUDISC_DO ||
	       inet6_sk(sk)->pmtudisc == IPV6_PMTUDISC_OMIT;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा in6_addr *rt6_nexthop(स्थिर काष्ठा rt6_info *rt,
						 स्थिर काष्ठा in6_addr *daddr)
अणु
	अगर (rt->rt6i_flags & RTF_GATEWAY)
		वापस &rt->rt6i_gateway;
	अन्यथा अगर (unlikely(rt->rt6i_flags & RTF_CACHE))
		वापस &rt->rt6i_dst.addr;
	अन्यथा
		वापस daddr;
पूर्ण

अटल अंतरभूत bool rt6_duplicate_nexthop(काष्ठा fib6_info *a, काष्ठा fib6_info *b)
अणु
	काष्ठा fib6_nh *nha, *nhb;

	अगर (a->nh || b->nh)
		वापस nexthop_cmp(a->nh, b->nh);

	nha = a->fib6_nh;
	nhb = b->fib6_nh;
	वापस nha->fib_nh_dev == nhb->fib_nh_dev &&
	       ipv6_addr_equal(&nha->fib_nh_gw6, &nhb->fib_nh_gw6) &&
	       !lwtunnel_cmp_encap(nha->fib_nh_lws, nhb->fib_nh_lws);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ip6_dst_mtu_क्रमward(स्थिर काष्ठा dst_entry *dst)
अणु
	काष्ठा inet6_dev *idev;
	अचिन्हित पूर्णांक mtu;

	अगर (dst_metric_locked(dst, RTAX_MTU)) अणु
		mtu = dst_metric_raw(dst, RTAX_MTU);
		अगर (mtu)
			वापस mtu;
	पूर्ण

	mtu = IPV6_MIN_MTU;
	rcu_पढ़ो_lock();
	idev = __in6_dev_get(dst->dev);
	अगर (idev)
		mtu = idev->cnf.mtu6;
	rcu_पढ़ो_unlock();

	वापस mtu;
पूर्ण

u32 ip6_mtu_from_fib6(स्थिर काष्ठा fib6_result *res,
		      स्थिर काष्ठा in6_addr *daddr,
		      स्थिर काष्ठा in6_addr *saddr);

काष्ठा neighbour *ip6_neigh_lookup(स्थिर काष्ठा in6_addr *gw,
				   काष्ठा net_device *dev, काष्ठा sk_buff *skb,
				   स्थिर व्योम *daddr);
#पूर्ण_अगर
