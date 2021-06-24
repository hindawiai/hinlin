<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Linux INET6 implementation
 *	FIB front-end.
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 */

/*	Changes:
 *
 *	YOSHIFUJI Hideaki @USAGI
 *		reworked शेष router selection.
 *		- respect outgoing पूर्णांकerface
 *		- select from (probably) reachable routers (i.e.
 *		routers in REACHABLE, STALE, DELAY or PROBE states).
 *		- always select the same router अगर it is (probably)
 *		reachable.  otherwise, round-robin the list.
 *	Ville Nuorvala
 *		Fixed routing subtrees.
 */

#घोषणा pr_fmt(fmt) "IPv6: " fmt

#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/बार.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/route.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/in6.h>
#समावेश <linux/mroute6.h>
#समावेश <linux/init.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/slab.h>
#समावेश <linux/jhash.h>
#समावेश <net/net_namespace.h>
#समावेश <net/snmp.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/ip6_route.h>
#समावेश <net/ndisc.h>
#समावेश <net/addrconf.h>
#समावेश <net/tcp.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/dst.h>
#समावेश <net/dst_metadata.h>
#समावेश <net/xfrm.h>
#समावेश <net/netevent.h>
#समावेश <net/netlink.h>
#समावेश <net/rtnh.h>
#समावेश <net/lwtunnel.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/l3mdev.h>
#समावेश <net/ip.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/btf_ids.h>

#अगर_घोषित CONFIG_SYSCTL
#समावेश <linux/sysctl.h>
#पूर्ण_अगर

अटल पूर्णांक ip6_rt_type_to_error(u8 fib6_type);

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/fib6.h>
EXPORT_TRACEPOINT_SYMBOL_GPL(fib6_table_lookup);
#अघोषित CREATE_TRACE_POINTS

क्रमागत rt6_nud_state अणु
	RT6_NUD_FAIL_HARD = -3,
	RT6_NUD_FAIL_PROBE = -2,
	RT6_NUD_FAIL_DO_RR = -1,
	RT6_NUD_SUCCEED = 1
पूर्ण;

INसूचीECT_CALLABLE_SCOPE
काष्ठा dst_entry	*ip6_dst_check(काष्ठा dst_entry *dst, u32 cookie);
अटल अचिन्हित पूर्णांक	 ip6_शेष_advmss(स्थिर काष्ठा dst_entry *dst);
INसूचीECT_CALLABLE_SCOPE
अचिन्हित पूर्णांक		ip6_mtu(स्थिर काष्ठा dst_entry *dst);
अटल काष्ठा dst_entry *ip6_negative_advice(काष्ठा dst_entry *);
अटल व्योम		ip6_dst_destroy(काष्ठा dst_entry *);
अटल व्योम		ip6_dst_अगरकरोwn(काष्ठा dst_entry *,
				       काष्ठा net_device *dev, पूर्णांक how);
अटल पूर्णांक		 ip6_dst_gc(काष्ठा dst_ops *ops);

अटल पूर्णांक		ip6_pkt_discard(काष्ठा sk_buff *skb);
अटल पूर्णांक		ip6_pkt_discard_out(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
अटल पूर्णांक		ip6_pkt_prohibit(काष्ठा sk_buff *skb);
अटल पूर्णांक		ip6_pkt_prohibit_out(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
अटल व्योम		ip6_link_failure(काष्ठा sk_buff *skb);
अटल व्योम		ip6_rt_update_pmtu(काष्ठा dst_entry *dst, काष्ठा sock *sk,
					   काष्ठा sk_buff *skb, u32 mtu,
					   bool confirm_neigh);
अटल व्योम		rt6_करो_redirect(काष्ठा dst_entry *dst, काष्ठा sock *sk,
					काष्ठा sk_buff *skb);
अटल पूर्णांक rt6_score_route(स्थिर काष्ठा fib6_nh *nh, u32 fib6_flags, पूर्णांक oअगर,
			   पूर्णांक strict);
अटल माप_प्रकार rt6_nlmsg_size(काष्ठा fib6_info *f6i);
अटल पूर्णांक rt6_fill_node(काष्ठा net *net, काष्ठा sk_buff *skb,
			 काष्ठा fib6_info *rt, काष्ठा dst_entry *dst,
			 काष्ठा in6_addr *dest, काष्ठा in6_addr *src,
			 पूर्णांक iअगर, पूर्णांक type, u32 portid, u32 seq,
			 अचिन्हित पूर्णांक flags);
अटल काष्ठा rt6_info *rt6_find_cached_rt(स्थिर काष्ठा fib6_result *res,
					   स्थिर काष्ठा in6_addr *daddr,
					   स्थिर काष्ठा in6_addr *saddr);

#अगर_घोषित CONFIG_IPV6_ROUTE_INFO
अटल काष्ठा fib6_info *rt6_add_route_info(काष्ठा net *net,
					   स्थिर काष्ठा in6_addr *prefix, पूर्णांक prefixlen,
					   स्थिर काष्ठा in6_addr *gwaddr,
					   काष्ठा net_device *dev,
					   अचिन्हित पूर्णांक pref);
अटल काष्ठा fib6_info *rt6_get_route_info(काष्ठा net *net,
					   स्थिर काष्ठा in6_addr *prefix, पूर्णांक prefixlen,
					   स्थिर काष्ठा in6_addr *gwaddr,
					   काष्ठा net_device *dev);
#पूर्ण_अगर

काष्ठा uncached_list अणु
	spinlock_t		lock;
	काष्ठा list_head	head;
पूर्ण;

अटल DEFINE_PER_CPU_ALIGNED(काष्ठा uncached_list, rt6_uncached_list);

व्योम rt6_uncached_list_add(काष्ठा rt6_info *rt)
अणु
	काष्ठा uncached_list *ul = raw_cpu_ptr(&rt6_uncached_list);

	rt->rt6i_uncached_list = ul;

	spin_lock_bh(&ul->lock);
	list_add_tail(&rt->rt6i_uncached, &ul->head);
	spin_unlock_bh(&ul->lock);
पूर्ण

व्योम rt6_uncached_list_del(काष्ठा rt6_info *rt)
अणु
	अगर (!list_empty(&rt->rt6i_uncached)) अणु
		काष्ठा uncached_list *ul = rt->rt6i_uncached_list;
		काष्ठा net *net = dev_net(rt->dst.dev);

		spin_lock_bh(&ul->lock);
		list_del(&rt->rt6i_uncached);
		atomic_dec(&net->ipv6.rt6_stats->fib_rt_uncache);
		spin_unlock_bh(&ul->lock);
	पूर्ण
पूर्ण

अटल व्योम rt6_uncached_list_flush_dev(काष्ठा net *net, काष्ठा net_device *dev)
अणु
	काष्ठा net_device *loopback_dev = net->loopback_dev;
	पूर्णांक cpu;

	अगर (dev == loopback_dev)
		वापस;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा uncached_list *ul = per_cpu_ptr(&rt6_uncached_list, cpu);
		काष्ठा rt6_info *rt;

		spin_lock_bh(&ul->lock);
		list_क्रम_each_entry(rt, &ul->head, rt6i_uncached) अणु
			काष्ठा inet6_dev *rt_idev = rt->rt6i_idev;
			काष्ठा net_device *rt_dev = rt->dst.dev;

			अगर (rt_idev->dev == dev) अणु
				rt->rt6i_idev = in6_dev_get(loopback_dev);
				in6_dev_put(rt_idev);
			पूर्ण

			अगर (rt_dev == dev) अणु
				rt->dst.dev = blackhole_netdev;
				dev_hold(rt->dst.dev);
				dev_put(rt_dev);
			पूर्ण
		पूर्ण
		spin_unlock_bh(&ul->lock);
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर व्योम *choose_neigh_daddr(स्थिर काष्ठा in6_addr *p,
					     काष्ठा sk_buff *skb,
					     स्थिर व्योम *daddr)
अणु
	अगर (!ipv6_addr_any(p))
		वापस (स्थिर व्योम *) p;
	अन्यथा अगर (skb)
		वापस &ipv6_hdr(skb)->daddr;
	वापस daddr;
पूर्ण

काष्ठा neighbour *ip6_neigh_lookup(स्थिर काष्ठा in6_addr *gw,
				   काष्ठा net_device *dev,
				   काष्ठा sk_buff *skb,
				   स्थिर व्योम *daddr)
अणु
	काष्ठा neighbour *n;

	daddr = choose_neigh_daddr(gw, skb, daddr);
	n = __ipv6_neigh_lookup(dev, daddr);
	अगर (n)
		वापस n;

	n = neigh_create(&nd_tbl, daddr, dev);
	वापस IS_ERR(n) ? शून्य : n;
पूर्ण

अटल काष्ठा neighbour *ip6_dst_neigh_lookup(स्थिर काष्ठा dst_entry *dst,
					      काष्ठा sk_buff *skb,
					      स्थिर व्योम *daddr)
अणु
	स्थिर काष्ठा rt6_info *rt = container_of(dst, काष्ठा rt6_info, dst);

	वापस ip6_neigh_lookup(rt6_nexthop(rt, &in6addr_any),
				dst->dev, skb, daddr);
पूर्ण

अटल व्योम ip6_confirm_neigh(स्थिर काष्ठा dst_entry *dst, स्थिर व्योम *daddr)
अणु
	काष्ठा net_device *dev = dst->dev;
	काष्ठा rt6_info *rt = (काष्ठा rt6_info *)dst;

	daddr = choose_neigh_daddr(rt6_nexthop(rt, &in6addr_any), शून्य, daddr);
	अगर (!daddr)
		वापस;
	अगर (dev->flags & (IFF_NOARP | IFF_LOOPBACK))
		वापस;
	अगर (ipv6_addr_is_multicast((स्थिर काष्ठा in6_addr *)daddr))
		वापस;
	__ipv6_confirm_neigh(dev, daddr);
पूर्ण

अटल काष्ठा dst_ops ip6_dst_ops_ढाँचा = अणु
	.family			=	AF_INET6,
	.gc			=	ip6_dst_gc,
	.gc_thresh		=	1024,
	.check			=	ip6_dst_check,
	.शेष_advmss		=	ip6_शेष_advmss,
	.mtu			=	ip6_mtu,
	.cow_metrics		=	dst_cow_metrics_generic,
	.destroy		=	ip6_dst_destroy,
	.अगरकरोwn			=	ip6_dst_अगरकरोwn,
	.negative_advice	=	ip6_negative_advice,
	.link_failure		=	ip6_link_failure,
	.update_pmtu		=	ip6_rt_update_pmtu,
	.redirect		=	rt6_करो_redirect,
	.local_out		=	__ip6_local_out,
	.neigh_lookup		=	ip6_dst_neigh_lookup,
	.confirm_neigh		=	ip6_confirm_neigh,
पूर्ण;

अटल काष्ठा dst_ops ip6_dst_blackhole_ops = अणु
	.family			= AF_INET6,
	.शेष_advmss		= ip6_शेष_advmss,
	.neigh_lookup		= ip6_dst_neigh_lookup,
	.check			= ip6_dst_check,
	.destroy		= ip6_dst_destroy,
	.cow_metrics		= dst_cow_metrics_generic,
	.update_pmtu		= dst_blackhole_update_pmtu,
	.redirect		= dst_blackhole_redirect,
	.mtu			= dst_blackhole_mtu,
पूर्ण;

अटल स्थिर u32 ip6_ढाँचा_metrics[RTAX_MAX] = अणु
	[RTAX_HOPLIMIT - 1] = 0,
पूर्ण;

अटल स्थिर काष्ठा fib6_info fib6_null_entry_ढाँचा = अणु
	.fib6_flags	= (RTF_REJECT | RTF_NONEXTHOP),
	.fib6_protocol  = RTPROT_KERNEL,
	.fib6_metric	= ~(u32)0,
	.fib6_ref	= REFCOUNT_INIT(1),
	.fib6_type	= RTN_UNREACHABLE,
	.fib6_metrics	= (काष्ठा dst_metrics *)&dst_शेष_metrics,
पूर्ण;

अटल स्थिर काष्ठा rt6_info ip6_null_entry_ढाँचा = अणु
	.dst = अणु
		.__refcnt	= ATOMIC_INIT(1),
		.__use		= 1,
		.obsolete	= DST_OBSOLETE_FORCE_CHK,
		.error		= -ENETUNREACH,
		.input		= ip6_pkt_discard,
		.output		= ip6_pkt_discard_out,
	पूर्ण,
	.rt6i_flags	= (RTF_REJECT | RTF_NONEXTHOP),
पूर्ण;

#अगर_घोषित CONFIG_IPV6_MULTIPLE_TABLES

अटल स्थिर काष्ठा rt6_info ip6_prohibit_entry_ढाँचा = अणु
	.dst = अणु
		.__refcnt	= ATOMIC_INIT(1),
		.__use		= 1,
		.obsolete	= DST_OBSOLETE_FORCE_CHK,
		.error		= -EACCES,
		.input		= ip6_pkt_prohibit,
		.output		= ip6_pkt_prohibit_out,
	पूर्ण,
	.rt6i_flags	= (RTF_REJECT | RTF_NONEXTHOP),
पूर्ण;

अटल स्थिर काष्ठा rt6_info ip6_blk_hole_entry_ढाँचा = अणु
	.dst = अणु
		.__refcnt	= ATOMIC_INIT(1),
		.__use		= 1,
		.obsolete	= DST_OBSOLETE_FORCE_CHK,
		.error		= -EINVAL,
		.input		= dst_discard,
		.output		= dst_discard_out,
	पूर्ण,
	.rt6i_flags	= (RTF_REJECT | RTF_NONEXTHOP),
पूर्ण;

#पूर्ण_अगर

अटल व्योम rt6_info_init(काष्ठा rt6_info *rt)
अणु
	काष्ठा dst_entry *dst = &rt->dst;

	स_रखो(dst + 1, 0, माप(*rt) - माप(*dst));
	INIT_LIST_HEAD(&rt->rt6i_uncached);
पूर्ण

/* allocate dst with ip6_dst_ops */
काष्ठा rt6_info *ip6_dst_alloc(काष्ठा net *net, काष्ठा net_device *dev,
			       पूर्णांक flags)
अणु
	काष्ठा rt6_info *rt = dst_alloc(&net->ipv6.ip6_dst_ops, dev,
					1, DST_OBSOLETE_FORCE_CHK, flags);

	अगर (rt) अणु
		rt6_info_init(rt);
		atomic_inc(&net->ipv6.rt6_stats->fib_rt_alloc);
	पूर्ण

	वापस rt;
पूर्ण
EXPORT_SYMBOL(ip6_dst_alloc);

अटल व्योम ip6_dst_destroy(काष्ठा dst_entry *dst)
अणु
	काष्ठा rt6_info *rt = (काष्ठा rt6_info *)dst;
	काष्ठा fib6_info *from;
	काष्ठा inet6_dev *idev;

	ip_dst_metrics_put(dst);
	rt6_uncached_list_del(rt);

	idev = rt->rt6i_idev;
	अगर (idev) अणु
		rt->rt6i_idev = शून्य;
		in6_dev_put(idev);
	पूर्ण

	from = xchg((__क्रमce काष्ठा fib6_info **)&rt->from, शून्य);
	fib6_info_release(from);
पूर्ण

अटल व्योम ip6_dst_अगरकरोwn(काष्ठा dst_entry *dst, काष्ठा net_device *dev,
			   पूर्णांक how)
अणु
	काष्ठा rt6_info *rt = (काष्ठा rt6_info *)dst;
	काष्ठा inet6_dev *idev = rt->rt6i_idev;
	काष्ठा net_device *loopback_dev =
		dev_net(dev)->loopback_dev;

	अगर (idev && idev->dev != loopback_dev) अणु
		काष्ठा inet6_dev *loopback_idev = in6_dev_get(loopback_dev);
		अगर (loopback_idev) अणु
			rt->rt6i_idev = loopback_idev;
			in6_dev_put(idev);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool __rt6_check_expired(स्थिर काष्ठा rt6_info *rt)
अणु
	अगर (rt->rt6i_flags & RTF_EXPIRES)
		वापस समय_after(jअगरfies, rt->dst.expires);
	अन्यथा
		वापस false;
पूर्ण

अटल bool rt6_check_expired(स्थिर काष्ठा rt6_info *rt)
अणु
	काष्ठा fib6_info *from;

	from = rcu_dereference(rt->from);

	अगर (rt->rt6i_flags & RTF_EXPIRES) अणु
		अगर (समय_after(jअगरfies, rt->dst.expires))
			वापस true;
	पूर्ण अन्यथा अगर (from) अणु
		वापस rt->dst.obsolete != DST_OBSOLETE_FORCE_CHK ||
			fib6_check_expired(from);
	पूर्ण
	वापस false;
पूर्ण

व्योम fib6_select_path(स्थिर काष्ठा net *net, काष्ठा fib6_result *res,
		      काष्ठा flowi6 *fl6, पूर्णांक oअगर, bool have_oअगर_match,
		      स्थिर काष्ठा sk_buff *skb, पूर्णांक strict)
अणु
	काष्ठा fib6_info *sibling, *next_sibling;
	काष्ठा fib6_info *match = res->f6i;

	अगर (!match->nh && (!match->fib6_nsiblings || have_oअगर_match))
		जाओ out;

	अगर (match->nh && have_oअगर_match && res->nh)
		वापस;

	/* We might have alपढ़ोy computed the hash क्रम ICMPv6 errors. In such
	 * हाल it will always be non-zero. Otherwise now is the समय to करो it.
	 */
	अगर (!fl6->mp_hash &&
	    (!match->nh || nexthop_is_multipath(match->nh)))
		fl6->mp_hash = rt6_multipath_hash(net, fl6, skb, शून्य);

	अगर (unlikely(match->nh)) अणु
		nexthop_path_fib6_result(res, fl6->mp_hash);
		वापस;
	पूर्ण

	अगर (fl6->mp_hash <= atomic_पढ़ो(&match->fib6_nh->fib_nh_upper_bound))
		जाओ out;

	list_क्रम_each_entry_safe(sibling, next_sibling, &match->fib6_siblings,
				 fib6_siblings) अणु
		स्थिर काष्ठा fib6_nh *nh = sibling->fib6_nh;
		पूर्णांक nh_upper_bound;

		nh_upper_bound = atomic_पढ़ो(&nh->fib_nh_upper_bound);
		अगर (fl6->mp_hash > nh_upper_bound)
			जारी;
		अगर (rt6_score_route(nh, sibling->fib6_flags, oअगर, strict) < 0)
			अवरोध;
		match = sibling;
		अवरोध;
	पूर्ण

out:
	res->f6i = match;
	res->nh = match->fib6_nh;
पूर्ण

/*
 *	Route lookup. rcu_पढ़ो_lock() should be held.
 */

अटल bool __rt6_device_match(काष्ठा net *net, स्थिर काष्ठा fib6_nh *nh,
			       स्थिर काष्ठा in6_addr *saddr, पूर्णांक oअगर, पूर्णांक flags)
अणु
	स्थिर काष्ठा net_device *dev;

	अगर (nh->fib_nh_flags & RTNH_F_DEAD)
		वापस false;

	dev = nh->fib_nh_dev;
	अगर (oअगर) अणु
		अगर (dev->अगरindex == oअगर)
			वापस true;
	पूर्ण अन्यथा अणु
		अगर (ipv6_chk_addr(net, saddr, dev,
				  flags & RT6_LOOKUP_F_IFACE))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

काष्ठा fib6_nh_dm_arg अणु
	काष्ठा net		*net;
	स्थिर काष्ठा in6_addr	*saddr;
	पूर्णांक			oअगर;
	पूर्णांक			flags;
	काष्ठा fib6_nh		*nh;
पूर्ण;

अटल पूर्णांक __rt6_nh_dev_match(काष्ठा fib6_nh *nh, व्योम *_arg)
अणु
	काष्ठा fib6_nh_dm_arg *arg = _arg;

	arg->nh = nh;
	वापस __rt6_device_match(arg->net, nh, arg->saddr, arg->oअगर,
				  arg->flags);
पूर्ण

/* वापसs fib6_nh from nexthop or शून्य */
अटल काष्ठा fib6_nh *rt6_nh_dev_match(काष्ठा net *net, काष्ठा nexthop *nh,
					काष्ठा fib6_result *res,
					स्थिर काष्ठा in6_addr *saddr,
					पूर्णांक oअगर, पूर्णांक flags)
अणु
	काष्ठा fib6_nh_dm_arg arg = अणु
		.net   = net,
		.saddr = saddr,
		.oअगर   = oअगर,
		.flags = flags,
	पूर्ण;

	अगर (nexthop_is_blackhole(nh))
		वापस शून्य;

	अगर (nexthop_क्रम_each_fib6_nh(nh, __rt6_nh_dev_match, &arg))
		वापस arg.nh;

	वापस शून्य;
पूर्ण

अटल व्योम rt6_device_match(काष्ठा net *net, काष्ठा fib6_result *res,
			     स्थिर काष्ठा in6_addr *saddr, पूर्णांक oअगर, पूर्णांक flags)
अणु
	काष्ठा fib6_info *f6i = res->f6i;
	काष्ठा fib6_info *spf6i;
	काष्ठा fib6_nh *nh;

	अगर (!oअगर && ipv6_addr_any(saddr)) अणु
		अगर (unlikely(f6i->nh)) अणु
			nh = nexthop_fib6_nh(f6i->nh);
			अगर (nexthop_is_blackhole(f6i->nh))
				जाओ out_blackhole;
		पूर्ण अन्यथा अणु
			nh = f6i->fib6_nh;
		पूर्ण
		अगर (!(nh->fib_nh_flags & RTNH_F_DEAD))
			जाओ out;
	पूर्ण

	क्रम (spf6i = f6i; spf6i; spf6i = rcu_dereference(spf6i->fib6_next)) अणु
		bool matched = false;

		अगर (unlikely(spf6i->nh)) अणु
			nh = rt6_nh_dev_match(net, spf6i->nh, res, saddr,
					      oअगर, flags);
			अगर (nh)
				matched = true;
		पूर्ण अन्यथा अणु
			nh = spf6i->fib6_nh;
			अगर (__rt6_device_match(net, nh, saddr, oअगर, flags))
				matched = true;
		पूर्ण
		अगर (matched) अणु
			res->f6i = spf6i;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (oअगर && flags & RT6_LOOKUP_F_IFACE) अणु
		res->f6i = net->ipv6.fib6_null_entry;
		nh = res->f6i->fib6_nh;
		जाओ out;
	पूर्ण

	अगर (unlikely(f6i->nh)) अणु
		nh = nexthop_fib6_nh(f6i->nh);
		अगर (nexthop_is_blackhole(f6i->nh))
			जाओ out_blackhole;
	पूर्ण अन्यथा अणु
		nh = f6i->fib6_nh;
	पूर्ण

	अगर (nh->fib_nh_flags & RTNH_F_DEAD) अणु
		res->f6i = net->ipv6.fib6_null_entry;
		nh = res->f6i->fib6_nh;
	पूर्ण
out:
	res->nh = nh;
	res->fib6_type = res->f6i->fib6_type;
	res->fib6_flags = res->f6i->fib6_flags;
	वापस;

out_blackhole:
	res->fib6_flags |= RTF_REJECT;
	res->fib6_type = RTN_BLACKHOLE;
	res->nh = nh;
पूर्ण

#अगर_घोषित CONFIG_IPV6_ROUTER_PREF
काष्ठा __rt6_probe_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा in6_addr target;
	काष्ठा net_device *dev;
पूर्ण;

अटल व्योम rt6_probe_deferred(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा in6_addr mcaddr;
	काष्ठा __rt6_probe_work *work =
		container_of(w, काष्ठा __rt6_probe_work, work);

	addrconf_addr_solict_mult(&work->target, &mcaddr);
	ndisc_send_ns(work->dev, &work->target, &mcaddr, शून्य, 0);
	dev_put(work->dev);
	kमुक्त(work);
पूर्ण

अटल व्योम rt6_probe(काष्ठा fib6_nh *fib6_nh)
अणु
	काष्ठा __rt6_probe_work *work = शून्य;
	स्थिर काष्ठा in6_addr *nh_gw;
	अचिन्हित दीर्घ last_probe;
	काष्ठा neighbour *neigh;
	काष्ठा net_device *dev;
	काष्ठा inet6_dev *idev;

	/*
	 * Okay, this करोes not seem to be appropriate
	 * क्रम now, however, we need to check अगर it
	 * is really so; aka Router Reachability Probing.
	 *
	 * Router Reachability Probe MUST be rate-limited
	 * to no more than one per minute.
	 */
	अगर (!fib6_nh->fib_nh_gw_family)
		वापस;

	nh_gw = &fib6_nh->fib_nh_gw6;
	dev = fib6_nh->fib_nh_dev;
	rcu_पढ़ो_lock_bh();
	last_probe = READ_ONCE(fib6_nh->last_probe);
	idev = __in6_dev_get(dev);
	neigh = __ipv6_neigh_lookup_noref(dev, nh_gw);
	अगर (neigh) अणु
		अगर (neigh->nud_state & NUD_VALID)
			जाओ out;

		ग_लिखो_lock(&neigh->lock);
		अगर (!(neigh->nud_state & NUD_VALID) &&
		    समय_after(jअगरfies,
			       neigh->updated + idev->cnf.rtr_probe_पूर्णांकerval)) अणु
			work = kदो_स्मृति(माप(*work), GFP_ATOMIC);
			अगर (work)
				__neigh_set_probe_once(neigh);
		पूर्ण
		ग_लिखो_unlock(&neigh->lock);
	पूर्ण अन्यथा अगर (समय_after(jअगरfies, last_probe +
				       idev->cnf.rtr_probe_पूर्णांकerval)) अणु
		work = kदो_स्मृति(माप(*work), GFP_ATOMIC);
	पूर्ण

	अगर (!work || cmpxchg(&fib6_nh->last_probe,
			     last_probe, jअगरfies) != last_probe) अणु
		kमुक्त(work);
	पूर्ण अन्यथा अणु
		INIT_WORK(&work->work, rt6_probe_deferred);
		work->target = *nh_gw;
		dev_hold(dev);
		work->dev = dev;
		schedule_work(&work->work);
	पूर्ण

out:
	rcu_पढ़ो_unlock_bh();
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम rt6_probe(काष्ठा fib6_nh *fib6_nh)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * Default Router Selection (RFC 2461 6.3.6)
 */
अटल क्रमागत rt6_nud_state rt6_check_neigh(स्थिर काष्ठा fib6_nh *fib6_nh)
अणु
	क्रमागत rt6_nud_state ret = RT6_NUD_FAIL_HARD;
	काष्ठा neighbour *neigh;

	rcu_पढ़ो_lock_bh();
	neigh = __ipv6_neigh_lookup_noref(fib6_nh->fib_nh_dev,
					  &fib6_nh->fib_nh_gw6);
	अगर (neigh) अणु
		पढ़ो_lock(&neigh->lock);
		अगर (neigh->nud_state & NUD_VALID)
			ret = RT6_NUD_SUCCEED;
#अगर_घोषित CONFIG_IPV6_ROUTER_PREF
		अन्यथा अगर (!(neigh->nud_state & NUD_FAILED))
			ret = RT6_NUD_SUCCEED;
		अन्यथा
			ret = RT6_NUD_FAIL_PROBE;
#पूर्ण_अगर
		पढ़ो_unlock(&neigh->lock);
	पूर्ण अन्यथा अणु
		ret = IS_ENABLED(CONFIG_IPV6_ROUTER_PREF) ?
		      RT6_NUD_SUCCEED : RT6_NUD_FAIL_DO_RR;
	पूर्ण
	rcu_पढ़ो_unlock_bh();

	वापस ret;
पूर्ण

अटल पूर्णांक rt6_score_route(स्थिर काष्ठा fib6_nh *nh, u32 fib6_flags, पूर्णांक oअगर,
			   पूर्णांक strict)
अणु
	पूर्णांक m = 0;

	अगर (!oअगर || nh->fib_nh_dev->अगरindex == oअगर)
		m = 2;

	अगर (!m && (strict & RT6_LOOKUP_F_IFACE))
		वापस RT6_NUD_FAIL_HARD;
#अगर_घोषित CONFIG_IPV6_ROUTER_PREF
	m |= IPV6_DECODE_PREF(IPV6_EXTRACT_PREF(fib6_flags)) << 2;
#पूर्ण_अगर
	अगर ((strict & RT6_LOOKUP_F_REACHABLE) &&
	    !(fib6_flags & RTF_NONEXTHOP) && nh->fib_nh_gw_family) अणु
		पूर्णांक n = rt6_check_neigh(nh);
		अगर (n < 0)
			वापस n;
	पूर्ण
	वापस m;
पूर्ण

अटल bool find_match(काष्ठा fib6_nh *nh, u32 fib6_flags,
		       पूर्णांक oअगर, पूर्णांक strict, पूर्णांक *mpri, bool *करो_rr)
अणु
	bool match_करो_rr = false;
	bool rc = false;
	पूर्णांक m;

	अगर (nh->fib_nh_flags & RTNH_F_DEAD)
		जाओ out;

	अगर (ip6_ignore_linkकरोwn(nh->fib_nh_dev) &&
	    nh->fib_nh_flags & RTNH_F_LINKDOWN &&
	    !(strict & RT6_LOOKUP_F_IGNORE_LINKSTATE))
		जाओ out;

	m = rt6_score_route(nh, fib6_flags, oअगर, strict);
	अगर (m == RT6_NUD_FAIL_DO_RR) अणु
		match_करो_rr = true;
		m = 0; /* lowest valid score */
	पूर्ण अन्यथा अगर (m == RT6_NUD_FAIL_HARD) अणु
		जाओ out;
	पूर्ण

	अगर (strict & RT6_LOOKUP_F_REACHABLE)
		rt6_probe(nh);

	/* note that m can be RT6_NUD_FAIL_PROBE at this poपूर्णांक */
	अगर (m > *mpri) अणु
		*करो_rr = match_करो_rr;
		*mpri = m;
		rc = true;
	पूर्ण
out:
	वापस rc;
पूर्ण

काष्ठा fib6_nh_frl_arg अणु
	u32		flags;
	पूर्णांक		oअगर;
	पूर्णांक		strict;
	पूर्णांक		*mpri;
	bool		*करो_rr;
	काष्ठा fib6_nh	*nh;
पूर्ण;

अटल पूर्णांक rt6_nh_find_match(काष्ठा fib6_nh *nh, व्योम *_arg)
अणु
	काष्ठा fib6_nh_frl_arg *arg = _arg;

	arg->nh = nh;
	वापस find_match(nh, arg->flags, arg->oअगर, arg->strict,
			  arg->mpri, arg->करो_rr);
पूर्ण

अटल व्योम __find_rr_leaf(काष्ठा fib6_info *f6i_start,
			   काष्ठा fib6_info *nomatch, u32 metric,
			   काष्ठा fib6_result *res, काष्ठा fib6_info **cont,
			   पूर्णांक oअगर, पूर्णांक strict, bool *करो_rr, पूर्णांक *mpri)
अणु
	काष्ठा fib6_info *f6i;

	क्रम (f6i = f6i_start;
	     f6i && f6i != nomatch;
	     f6i = rcu_dereference(f6i->fib6_next)) अणु
		bool matched = false;
		काष्ठा fib6_nh *nh;

		अगर (cont && f6i->fib6_metric != metric) अणु
			*cont = f6i;
			वापस;
		पूर्ण

		अगर (fib6_check_expired(f6i))
			जारी;

		अगर (unlikely(f6i->nh)) अणु
			काष्ठा fib6_nh_frl_arg arg = अणु
				.flags  = f6i->fib6_flags,
				.oअगर    = oअगर,
				.strict = strict,
				.mpri   = mpri,
				.करो_rr  = करो_rr
			पूर्ण;

			अगर (nexthop_is_blackhole(f6i->nh)) अणु
				res->fib6_flags = RTF_REJECT;
				res->fib6_type = RTN_BLACKHOLE;
				res->f6i = f6i;
				res->nh = nexthop_fib6_nh(f6i->nh);
				वापस;
			पूर्ण
			अगर (nexthop_क्रम_each_fib6_nh(f6i->nh, rt6_nh_find_match,
						     &arg)) अणु
				matched = true;
				nh = arg.nh;
			पूर्ण
		पूर्ण अन्यथा अणु
			nh = f6i->fib6_nh;
			अगर (find_match(nh, f6i->fib6_flags, oअगर, strict,
				       mpri, करो_rr))
				matched = true;
		पूर्ण
		अगर (matched) अणु
			res->f6i = f6i;
			res->nh = nh;
			res->fib6_flags = f6i->fib6_flags;
			res->fib6_type = f6i->fib6_type;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम find_rr_leaf(काष्ठा fib6_node *fn, काष्ठा fib6_info *leaf,
			 काष्ठा fib6_info *rr_head, पूर्णांक oअगर, पूर्णांक strict,
			 bool *करो_rr, काष्ठा fib6_result *res)
अणु
	u32 metric = rr_head->fib6_metric;
	काष्ठा fib6_info *cont = शून्य;
	पूर्णांक mpri = -1;

	__find_rr_leaf(rr_head, शून्य, metric, res, &cont,
		       oअगर, strict, करो_rr, &mpri);

	__find_rr_leaf(leaf, rr_head, metric, res, &cont,
		       oअगर, strict, करो_rr, &mpri);

	अगर (res->f6i || !cont)
		वापस;

	__find_rr_leaf(cont, शून्य, metric, res, शून्य,
		       oअगर, strict, करो_rr, &mpri);
पूर्ण

अटल व्योम rt6_select(काष्ठा net *net, काष्ठा fib6_node *fn, पूर्णांक oअगर,
		       काष्ठा fib6_result *res, पूर्णांक strict)
अणु
	काष्ठा fib6_info *leaf = rcu_dereference(fn->leaf);
	काष्ठा fib6_info *rt0;
	bool करो_rr = false;
	पूर्णांक key_plen;

	/* make sure this function or its helpers sets f6i */
	res->f6i = शून्य;

	अगर (!leaf || leaf == net->ipv6.fib6_null_entry)
		जाओ out;

	rt0 = rcu_dereference(fn->rr_ptr);
	अगर (!rt0)
		rt0 = leaf;

	/* Double check to make sure fn is not an पूर्णांकermediate node
	 * and fn->leaf करोes not poपूर्णांकs to its child's leaf
	 * (This might happen अगर all routes under fn are deleted from
	 * the tree and fib6_repair_tree() is called on the node.)
	 */
	key_plen = rt0->fib6_dst.plen;
#अगर_घोषित CONFIG_IPV6_SUBTREES
	अगर (rt0->fib6_src.plen)
		key_plen = rt0->fib6_src.plen;
#पूर्ण_अगर
	अगर (fn->fn_bit != key_plen)
		जाओ out;

	find_rr_leaf(fn, leaf, rt0, oअगर, strict, &करो_rr, res);
	अगर (करो_rr) अणु
		काष्ठा fib6_info *next = rcu_dereference(rt0->fib6_next);

		/* no entries matched; करो round-robin */
		अगर (!next || next->fib6_metric != rt0->fib6_metric)
			next = leaf;

		अगर (next != rt0) अणु
			spin_lock_bh(&leaf->fib6_table->tb6_lock);
			/* make sure next is not being deleted from the tree */
			अगर (next->fib6_node)
				rcu_assign_poपूर्णांकer(fn->rr_ptr, next);
			spin_unlock_bh(&leaf->fib6_table->tb6_lock);
		पूर्ण
	पूर्ण

out:
	अगर (!res->f6i) अणु
		res->f6i = net->ipv6.fib6_null_entry;
		res->nh = res->f6i->fib6_nh;
		res->fib6_flags = res->f6i->fib6_flags;
		res->fib6_type = res->f6i->fib6_type;
	पूर्ण
पूर्ण

अटल bool rt6_is_gw_or_nonexthop(स्थिर काष्ठा fib6_result *res)
अणु
	वापस (res->f6i->fib6_flags & RTF_NONEXTHOP) ||
	       res->nh->fib_nh_gw_family;
पूर्ण

#अगर_घोषित CONFIG_IPV6_ROUTE_INFO
पूर्णांक rt6_route_rcv(काष्ठा net_device *dev, u8 *opt, पूर्णांक len,
		  स्थिर काष्ठा in6_addr *gwaddr)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा route_info *rinfo = (काष्ठा route_info *) opt;
	काष्ठा in6_addr prefix_buf, *prefix;
	अचिन्हित पूर्णांक pref;
	अचिन्हित दीर्घ lअगरeसमय;
	काष्ठा fib6_info *rt;

	अगर (len < माप(काष्ठा route_info)) अणु
		वापस -EINVAL;
	पूर्ण

	/* Sanity check क्रम prefix_len and length */
	अगर (rinfo->length > 3) अणु
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (rinfo->prefix_len > 128) अणु
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (rinfo->prefix_len > 64) अणु
		अगर (rinfo->length < 2) अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (rinfo->prefix_len > 0) अणु
		अगर (rinfo->length < 1) अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	pref = rinfo->route_pref;
	अगर (pref == ICMPV6_ROUTER_PREF_INVALID)
		वापस -EINVAL;

	lअगरeसमय = addrconf_समयout_fixup(ntohl(rinfo->lअगरeसमय), HZ);

	अगर (rinfo->length == 3)
		prefix = (काष्ठा in6_addr *)rinfo->prefix;
	अन्यथा अणु
		/* this function is safe */
		ipv6_addr_prefix(&prefix_buf,
				 (काष्ठा in6_addr *)rinfo->prefix,
				 rinfo->prefix_len);
		prefix = &prefix_buf;
	पूर्ण

	अगर (rinfo->prefix_len == 0)
		rt = rt6_get_dflt_router(net, gwaddr, dev);
	अन्यथा
		rt = rt6_get_route_info(net, prefix, rinfo->prefix_len,
					gwaddr, dev);

	अगर (rt && !lअगरeसमय) अणु
		ip6_del_rt(net, rt, false);
		rt = शून्य;
	पूर्ण

	अगर (!rt && lअगरeसमय)
		rt = rt6_add_route_info(net, prefix, rinfo->prefix_len, gwaddr,
					dev, pref);
	अन्यथा अगर (rt)
		rt->fib6_flags = RTF_ROUTEINFO |
				 (rt->fib6_flags & ~RTF_PREF_MASK) | RTF_PREF(pref);

	अगर (rt) अणु
		अगर (!addrconf_finite_समयout(lअगरeसमय))
			fib6_clean_expires(rt);
		अन्यथा
			fib6_set_expires(rt, jअगरfies + HZ * lअगरeसमय);

		fib6_info_release(rt);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 *	Misc support functions
 */

/* called with rcu_lock held */
अटल काष्ठा net_device *ip6_rt_get_dev_rcu(स्थिर काष्ठा fib6_result *res)
अणु
	काष्ठा net_device *dev = res->nh->fib_nh_dev;

	अगर (res->fib6_flags & (RTF_LOCAL | RTF_ANYCAST)) अणु
		/* क्रम copies of local routes, dst->dev needs to be the
		 * device अगर it is a master device, the master device अगर
		 * device is enslaved, and the loopback as the शेष
		 */
		अगर (netअगर_is_l3_slave(dev) &&
		    !rt6_need_strict(&res->f6i->fib6_dst.addr))
			dev = l3mdev_master_dev_rcu(dev);
		अन्यथा अगर (!netअगर_is_l3_master(dev))
			dev = dev_net(dev)->loopback_dev;
		/* last हाल is netअगर_is_l3_master(dev) is true in which
		 * हाल we want dev वापसed to be dev
		 */
	पूर्ण

	वापस dev;
पूर्ण

अटल स्थिर पूर्णांक fib6_prop[RTN_MAX + 1] = अणु
	[RTN_UNSPEC]	= 0,
	[RTN_UNICAST]	= 0,
	[RTN_LOCAL]	= 0,
	[RTN_BROADCAST]	= 0,
	[RTN_ANYCAST]	= 0,
	[RTN_MULTICAST]	= 0,
	[RTN_BLACKHOLE]	= -EINVAL,
	[RTN_UNREACHABLE] = -EHOSTUNREACH,
	[RTN_PROHIBIT]	= -EACCES,
	[RTN_THROW]	= -EAGAIN,
	[RTN_NAT]	= -EINVAL,
	[RTN_XRESOLVE]	= -EINVAL,
पूर्ण;

अटल पूर्णांक ip6_rt_type_to_error(u8 fib6_type)
अणु
	वापस fib6_prop[fib6_type];
पूर्ण

अटल अचिन्हित लघु fib6_info_dst_flags(काष्ठा fib6_info *rt)
अणु
	अचिन्हित लघु flags = 0;

	अगर (rt->dst_nocount)
		flags |= DST_NOCOUNT;
	अगर (rt->dst_nopolicy)
		flags |= DST_NOPOLICY;

	वापस flags;
पूर्ण

अटल व्योम ip6_rt_init_dst_reject(काष्ठा rt6_info *rt, u8 fib6_type)
अणु
	rt->dst.error = ip6_rt_type_to_error(fib6_type);

	चयन (fib6_type) अणु
	हाल RTN_BLACKHOLE:
		rt->dst.output = dst_discard_out;
		rt->dst.input = dst_discard;
		अवरोध;
	हाल RTN_PROHIBIT:
		rt->dst.output = ip6_pkt_prohibit_out;
		rt->dst.input = ip6_pkt_prohibit;
		अवरोध;
	हाल RTN_THROW:
	हाल RTN_UNREACHABLE:
	शेष:
		rt->dst.output = ip6_pkt_discard_out;
		rt->dst.input = ip6_pkt_discard;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ip6_rt_init_dst(काष्ठा rt6_info *rt, स्थिर काष्ठा fib6_result *res)
अणु
	काष्ठा fib6_info *f6i = res->f6i;

	अगर (res->fib6_flags & RTF_REJECT) अणु
		ip6_rt_init_dst_reject(rt, res->fib6_type);
		वापस;
	पूर्ण

	rt->dst.error = 0;
	rt->dst.output = ip6_output;

	अगर (res->fib6_type == RTN_LOCAL || res->fib6_type == RTN_ANYCAST) अणु
		rt->dst.input = ip6_input;
	पूर्ण अन्यथा अगर (ipv6_addr_type(&f6i->fib6_dst.addr) & IPV6_ADDR_MULTICAST) अणु
		rt->dst.input = ip6_mc_input;
	पूर्ण अन्यथा अणु
		rt->dst.input = ip6_क्रमward;
	पूर्ण

	अगर (res->nh->fib_nh_lws) अणु
		rt->dst.lwtstate = lwtstate_get(res->nh->fib_nh_lws);
		lwtunnel_set_redirect(&rt->dst);
	पूर्ण

	rt->dst.lastuse = jअगरfies;
पूर्ण

/* Caller must alपढ़ोy hold reference to @from */
अटल व्योम rt6_set_from(काष्ठा rt6_info *rt, काष्ठा fib6_info *from)
अणु
	rt->rt6i_flags &= ~RTF_EXPIRES;
	rcu_assign_poपूर्णांकer(rt->from, from);
	ip_dst_init_metrics(&rt->dst, from->fib6_metrics);
पूर्ण

/* Caller must alपढ़ोy hold reference to f6i in result */
अटल व्योम ip6_rt_copy_init(काष्ठा rt6_info *rt, स्थिर काष्ठा fib6_result *res)
अणु
	स्थिर काष्ठा fib6_nh *nh = res->nh;
	स्थिर काष्ठा net_device *dev = nh->fib_nh_dev;
	काष्ठा fib6_info *f6i = res->f6i;

	ip6_rt_init_dst(rt, res);

	rt->rt6i_dst = f6i->fib6_dst;
	rt->rt6i_idev = dev ? in6_dev_get(dev) : शून्य;
	rt->rt6i_flags = res->fib6_flags;
	अगर (nh->fib_nh_gw_family) अणु
		rt->rt6i_gateway = nh->fib_nh_gw6;
		rt->rt6i_flags |= RTF_GATEWAY;
	पूर्ण
	rt6_set_from(rt, f6i);
#अगर_घोषित CONFIG_IPV6_SUBTREES
	rt->rt6i_src = f6i->fib6_src;
#पूर्ण_अगर
पूर्ण

अटल काष्ठा fib6_node* fib6_backtrack(काष्ठा fib6_node *fn,
					काष्ठा in6_addr *saddr)
अणु
	काष्ठा fib6_node *pn, *sn;
	जबतक (1) अणु
		अगर (fn->fn_flags & RTN_TL_ROOT)
			वापस शून्य;
		pn = rcu_dereference(fn->parent);
		sn = FIB6_SUBTREE(pn);
		अगर (sn && sn != fn)
			fn = fib6_node_lookup(sn, शून्य, saddr);
		अन्यथा
			fn = pn;
		अगर (fn->fn_flags & RTN_RTINFO)
			वापस fn;
	पूर्ण
पूर्ण

अटल bool ip6_hold_safe(काष्ठा net *net, काष्ठा rt6_info **prt)
अणु
	काष्ठा rt6_info *rt = *prt;

	अगर (dst_hold_safe(&rt->dst))
		वापस true;
	अगर (net) अणु
		rt = net->ipv6.ip6_null_entry;
		dst_hold(&rt->dst);
	पूर्ण अन्यथा अणु
		rt = शून्य;
	पूर्ण
	*prt = rt;
	वापस false;
पूर्ण

/* called with rcu_lock held */
अटल काष्ठा rt6_info *ip6_create_rt_rcu(स्थिर काष्ठा fib6_result *res)
अणु
	काष्ठा net_device *dev = res->nh->fib_nh_dev;
	काष्ठा fib6_info *f6i = res->f6i;
	अचिन्हित लघु flags;
	काष्ठा rt6_info *nrt;

	अगर (!fib6_info_hold_safe(f6i))
		जाओ fallback;

	flags = fib6_info_dst_flags(f6i);
	nrt = ip6_dst_alloc(dev_net(dev), dev, flags);
	अगर (!nrt) अणु
		fib6_info_release(f6i);
		जाओ fallback;
	पूर्ण

	ip6_rt_copy_init(nrt, res);
	वापस nrt;

fallback:
	nrt = dev_net(dev)->ipv6.ip6_null_entry;
	dst_hold(&nrt->dst);
	वापस nrt;
पूर्ण

INसूचीECT_CALLABLE_SCOPE काष्ठा rt6_info *ip6_pol_route_lookup(काष्ठा net *net,
					     काष्ठा fib6_table *table,
					     काष्ठा flowi6 *fl6,
					     स्थिर काष्ठा sk_buff *skb,
					     पूर्णांक flags)
अणु
	काष्ठा fib6_result res = अणुपूर्ण;
	काष्ठा fib6_node *fn;
	काष्ठा rt6_info *rt;

	अगर (fl6->flowi6_flags & FLOWI_FLAG_SKIP_NH_OIF)
		flags &= ~RT6_LOOKUP_F_IFACE;

	rcu_पढ़ो_lock();
	fn = fib6_node_lookup(&table->tb6_root, &fl6->daddr, &fl6->saddr);
restart:
	res.f6i = rcu_dereference(fn->leaf);
	अगर (!res.f6i)
		res.f6i = net->ipv6.fib6_null_entry;
	अन्यथा
		rt6_device_match(net, &res, &fl6->saddr, fl6->flowi6_oअगर,
				 flags);

	अगर (res.f6i == net->ipv6.fib6_null_entry) अणु
		fn = fib6_backtrack(fn, &fl6->saddr);
		अगर (fn)
			जाओ restart;

		rt = net->ipv6.ip6_null_entry;
		dst_hold(&rt->dst);
		जाओ out;
	पूर्ण अन्यथा अगर (res.fib6_flags & RTF_REJECT) अणु
		जाओ करो_create;
	पूर्ण

	fib6_select_path(net, &res, fl6, fl6->flowi6_oअगर,
			 fl6->flowi6_oअगर != 0, skb, flags);

	/* Search through exception table */
	rt = rt6_find_cached_rt(&res, &fl6->daddr, &fl6->saddr);
	अगर (rt) अणु
		अगर (ip6_hold_safe(net, &rt))
			dst_use_noref(&rt->dst, jअगरfies);
	पूर्ण अन्यथा अणु
करो_create:
		rt = ip6_create_rt_rcu(&res);
	पूर्ण

out:
	trace_fib6_table_lookup(net, &res, table, fl6);

	rcu_पढ़ो_unlock();

	वापस rt;
पूर्ण

काष्ठा dst_entry *ip6_route_lookup(काष्ठा net *net, काष्ठा flowi6 *fl6,
				   स्थिर काष्ठा sk_buff *skb, पूर्णांक flags)
अणु
	वापस fib6_rule_lookup(net, fl6, skb, flags, ip6_pol_route_lookup);
पूर्ण
EXPORT_SYMBOL_GPL(ip6_route_lookup);

काष्ठा rt6_info *rt6_lookup(काष्ठा net *net, स्थिर काष्ठा in6_addr *daddr,
			    स्थिर काष्ठा in6_addr *saddr, पूर्णांक oअगर,
			    स्थिर काष्ठा sk_buff *skb, पूर्णांक strict)
अणु
	काष्ठा flowi6 fl6 = अणु
		.flowi6_oअगर = oअगर,
		.daddr = *daddr,
	पूर्ण;
	काष्ठा dst_entry *dst;
	पूर्णांक flags = strict ? RT6_LOOKUP_F_IFACE : 0;

	अगर (saddr) अणु
		स_नकल(&fl6.saddr, saddr, माप(*saddr));
		flags |= RT6_LOOKUP_F_HAS_SADDR;
	पूर्ण

	dst = fib6_rule_lookup(net, &fl6, skb, flags, ip6_pol_route_lookup);
	अगर (dst->error == 0)
		वापस (काष्ठा rt6_info *) dst;

	dst_release(dst);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(rt6_lookup);

/* ip6_ins_rt is called with FREE table->tb6_lock.
 * It takes new route entry, the addition fails by any reason the
 * route is released.
 * Caller must hold dst beक्रमe calling it.
 */

अटल पूर्णांक __ip6_ins_rt(काष्ठा fib6_info *rt, काष्ठा nl_info *info,
			काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;
	काष्ठा fib6_table *table;

	table = rt->fib6_table;
	spin_lock_bh(&table->tb6_lock);
	err = fib6_add(&table->tb6_root, rt, info, extack);
	spin_unlock_bh(&table->tb6_lock);

	वापस err;
पूर्ण

पूर्णांक ip6_ins_rt(काष्ठा net *net, काष्ठा fib6_info *rt)
अणु
	काष्ठा nl_info info = अणु	.nl_net = net, पूर्ण;

	वापस __ip6_ins_rt(rt, &info, शून्य);
पूर्ण

अटल काष्ठा rt6_info *ip6_rt_cache_alloc(स्थिर काष्ठा fib6_result *res,
					   स्थिर काष्ठा in6_addr *daddr,
					   स्थिर काष्ठा in6_addr *saddr)
अणु
	काष्ठा fib6_info *f6i = res->f6i;
	काष्ठा net_device *dev;
	काष्ठा rt6_info *rt;

	/*
	 *	Clone the route.
	 */

	अगर (!fib6_info_hold_safe(f6i))
		वापस शून्य;

	dev = ip6_rt_get_dev_rcu(res);
	rt = ip6_dst_alloc(dev_net(dev), dev, 0);
	अगर (!rt) अणु
		fib6_info_release(f6i);
		वापस शून्य;
	पूर्ण

	ip6_rt_copy_init(rt, res);
	rt->rt6i_flags |= RTF_CACHE;
	rt->rt6i_dst.addr = *daddr;
	rt->rt6i_dst.plen = 128;

	अगर (!rt6_is_gw_or_nonexthop(res)) अणु
		अगर (f6i->fib6_dst.plen != 128 &&
		    ipv6_addr_equal(&f6i->fib6_dst.addr, daddr))
			rt->rt6i_flags |= RTF_ANYCAST;
#अगर_घोषित CONFIG_IPV6_SUBTREES
		अगर (rt->rt6i_src.plen && saddr) अणु
			rt->rt6i_src.addr = *saddr;
			rt->rt6i_src.plen = 128;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	वापस rt;
पूर्ण

अटल काष्ठा rt6_info *ip6_rt_pcpu_alloc(स्थिर काष्ठा fib6_result *res)
अणु
	काष्ठा fib6_info *f6i = res->f6i;
	अचिन्हित लघु flags = fib6_info_dst_flags(f6i);
	काष्ठा net_device *dev;
	काष्ठा rt6_info *pcpu_rt;

	अगर (!fib6_info_hold_safe(f6i))
		वापस शून्य;

	rcu_पढ़ो_lock();
	dev = ip6_rt_get_dev_rcu(res);
	pcpu_rt = ip6_dst_alloc(dev_net(dev), dev, flags | DST_NOCOUNT);
	rcu_पढ़ो_unlock();
	अगर (!pcpu_rt) अणु
		fib6_info_release(f6i);
		वापस शून्य;
	पूर्ण
	ip6_rt_copy_init(pcpu_rt, res);
	pcpu_rt->rt6i_flags |= RTF_PCPU;

	अगर (f6i->nh)
		pcpu_rt->sernum = rt_genid_ipv6(dev_net(dev));

	वापस pcpu_rt;
पूर्ण

अटल bool rt6_is_valid(स्थिर काष्ठा rt6_info *rt6)
अणु
	वापस rt6->sernum == rt_genid_ipv6(dev_net(rt6->dst.dev));
पूर्ण

/* It should be called with rcu_पढ़ो_lock() acquired */
अटल काष्ठा rt6_info *rt6_get_pcpu_route(स्थिर काष्ठा fib6_result *res)
अणु
	काष्ठा rt6_info *pcpu_rt;

	pcpu_rt = this_cpu_पढ़ो(*res->nh->rt6i_pcpu);

	अगर (pcpu_rt && pcpu_rt->sernum && !rt6_is_valid(pcpu_rt)) अणु
		काष्ठा rt6_info *prev, **p;

		p = this_cpu_ptr(res->nh->rt6i_pcpu);
		prev = xchg(p, शून्य);
		अगर (prev) अणु
			dst_dev_put(&prev->dst);
			dst_release(&prev->dst);
		पूर्ण

		pcpu_rt = शून्य;
	पूर्ण

	वापस pcpu_rt;
पूर्ण

अटल काष्ठा rt6_info *rt6_make_pcpu_route(काष्ठा net *net,
					    स्थिर काष्ठा fib6_result *res)
अणु
	काष्ठा rt6_info *pcpu_rt, *prev, **p;

	pcpu_rt = ip6_rt_pcpu_alloc(res);
	अगर (!pcpu_rt)
		वापस शून्य;

	p = this_cpu_ptr(res->nh->rt6i_pcpu);
	prev = cmpxchg(p, शून्य, pcpu_rt);
	BUG_ON(prev);

	अगर (res->f6i->fib6_destroying) अणु
		काष्ठा fib6_info *from;

		from = xchg((__क्रमce काष्ठा fib6_info **)&pcpu_rt->from, शून्य);
		fib6_info_release(from);
	पूर्ण

	वापस pcpu_rt;
पूर्ण

/* exception hash table implementation
 */
अटल DEFINE_SPINLOCK(rt6_exception_lock);

/* Remove rt6_ex from hash table and मुक्त the memory
 * Caller must hold rt6_exception_lock
 */
अटल व्योम rt6_हटाओ_exception(काष्ठा rt6_exception_bucket *bucket,
				 काष्ठा rt6_exception *rt6_ex)
अणु
	काष्ठा fib6_info *from;
	काष्ठा net *net;

	अगर (!bucket || !rt6_ex)
		वापस;

	net = dev_net(rt6_ex->rt6i->dst.dev);
	net->ipv6.rt6_stats->fib_rt_cache--;

	/* purge completely the exception to allow releasing the held resources:
	 * some [sk] cache may keep the dst around क्रम unlimited समय
	 */
	from = xchg((__क्रमce काष्ठा fib6_info **)&rt6_ex->rt6i->from, शून्य);
	fib6_info_release(from);
	dst_dev_put(&rt6_ex->rt6i->dst);

	hlist_del_rcu(&rt6_ex->hlist);
	dst_release(&rt6_ex->rt6i->dst);
	kमुक्त_rcu(rt6_ex, rcu);
	WARN_ON_ONCE(!bucket->depth);
	bucket->depth--;
पूर्ण

/* Remove oldest rt6_ex in bucket and मुक्त the memory
 * Caller must hold rt6_exception_lock
 */
अटल व्योम rt6_exception_हटाओ_oldest(काष्ठा rt6_exception_bucket *bucket)
अणु
	काष्ठा rt6_exception *rt6_ex, *oldest = शून्य;

	अगर (!bucket)
		वापस;

	hlist_क्रम_each_entry(rt6_ex, &bucket->chain, hlist) अणु
		अगर (!oldest || समय_beक्रमe(rt6_ex->stamp, oldest->stamp))
			oldest = rt6_ex;
	पूर्ण
	rt6_हटाओ_exception(bucket, oldest);
पूर्ण

अटल u32 rt6_exception_hash(स्थिर काष्ठा in6_addr *dst,
			      स्थिर काष्ठा in6_addr *src)
अणु
	अटल u32 seed __पढ़ो_mostly;
	u32 val;

	net_get_अक्रमom_once(&seed, माप(seed));
	val = jhash2((स्थिर u32 *)dst, माप(*dst)/माप(u32), seed);

#अगर_घोषित CONFIG_IPV6_SUBTREES
	अगर (src)
		val = jhash2((स्थिर u32 *)src, माप(*src)/माप(u32), val);
#पूर्ण_अगर
	वापस hash_32(val, FIB6_EXCEPTION_BUCKET_SIZE_SHIFT);
पूर्ण

/* Helper function to find the cached rt in the hash table
 * and update bucket poपूर्णांकer to poपूर्णांक to the bucket क्रम this
 * (daddr, saddr) pair
 * Caller must hold rt6_exception_lock
 */
अटल काष्ठा rt6_exception *
__rt6_find_exception_spinlock(काष्ठा rt6_exception_bucket **bucket,
			      स्थिर काष्ठा in6_addr *daddr,
			      स्थिर काष्ठा in6_addr *saddr)
अणु
	काष्ठा rt6_exception *rt6_ex;
	u32 hval;

	अगर (!(*bucket) || !daddr)
		वापस शून्य;

	hval = rt6_exception_hash(daddr, saddr);
	*bucket += hval;

	hlist_क्रम_each_entry(rt6_ex, &(*bucket)->chain, hlist) अणु
		काष्ठा rt6_info *rt6 = rt6_ex->rt6i;
		bool matched = ipv6_addr_equal(daddr, &rt6->rt6i_dst.addr);

#अगर_घोषित CONFIG_IPV6_SUBTREES
		अगर (matched && saddr)
			matched = ipv6_addr_equal(saddr, &rt6->rt6i_src.addr);
#पूर्ण_अगर
		अगर (matched)
			वापस rt6_ex;
	पूर्ण
	वापस शून्य;
पूर्ण

/* Helper function to find the cached rt in the hash table
 * and update bucket poपूर्णांकer to poपूर्णांक to the bucket क्रम this
 * (daddr, saddr) pair
 * Caller must hold rcu_पढ़ो_lock()
 */
अटल काष्ठा rt6_exception *
__rt6_find_exception_rcu(काष्ठा rt6_exception_bucket **bucket,
			 स्थिर काष्ठा in6_addr *daddr,
			 स्थिर काष्ठा in6_addr *saddr)
अणु
	काष्ठा rt6_exception *rt6_ex;
	u32 hval;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());

	अगर (!(*bucket) || !daddr)
		वापस शून्य;

	hval = rt6_exception_hash(daddr, saddr);
	*bucket += hval;

	hlist_क्रम_each_entry_rcu(rt6_ex, &(*bucket)->chain, hlist) अणु
		काष्ठा rt6_info *rt6 = rt6_ex->rt6i;
		bool matched = ipv6_addr_equal(daddr, &rt6->rt6i_dst.addr);

#अगर_घोषित CONFIG_IPV6_SUBTREES
		अगर (matched && saddr)
			matched = ipv6_addr_equal(saddr, &rt6->rt6i_src.addr);
#पूर्ण_अगर
		अगर (matched)
			वापस rt6_ex;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक fib6_mtu(स्थिर काष्ठा fib6_result *res)
अणु
	स्थिर काष्ठा fib6_nh *nh = res->nh;
	अचिन्हित पूर्णांक mtu;

	अगर (res->f6i->fib6_pmtu) अणु
		mtu = res->f6i->fib6_pmtu;
	पूर्ण अन्यथा अणु
		काष्ठा net_device *dev = nh->fib_nh_dev;
		काष्ठा inet6_dev *idev;

		rcu_पढ़ो_lock();
		idev = __in6_dev_get(dev);
		mtu = idev->cnf.mtu6;
		rcu_पढ़ो_unlock();
	पूर्ण

	mtu = min_t(अचिन्हित पूर्णांक, mtu, IP6_MAX_MTU);

	वापस mtu - lwtunnel_headroom(nh->fib_nh_lws, mtu);
पूर्ण

#घोषणा FIB6_EXCEPTION_BUCKET_FLUSHED  0x1UL

/* used when the flushed bit is not relevant, only access to the bucket
 * (ie., all bucket users except rt6_insert_exception);
 *
 * called under rcu lock; someबार called with rt6_exception_lock held
 */
अटल
काष्ठा rt6_exception_bucket *fib6_nh_get_excptn_bucket(स्थिर काष्ठा fib6_nh *nh,
						       spinlock_t *lock)
अणु
	काष्ठा rt6_exception_bucket *bucket;

	अगर (lock)
		bucket = rcu_dereference_रक्षित(nh->rt6i_exception_bucket,
						   lockdep_is_held(lock));
	अन्यथा
		bucket = rcu_dereference(nh->rt6i_exception_bucket);

	/* हटाओ bucket flushed bit अगर set */
	अगर (bucket) अणु
		अचिन्हित दीर्घ p = (अचिन्हित दीर्घ)bucket;

		p &= ~FIB6_EXCEPTION_BUCKET_FLUSHED;
		bucket = (काष्ठा rt6_exception_bucket *)p;
	पूर्ण

	वापस bucket;
पूर्ण

अटल bool fib6_nh_excptn_bucket_flushed(काष्ठा rt6_exception_bucket *bucket)
अणु
	अचिन्हित दीर्घ p = (अचिन्हित दीर्घ)bucket;

	वापस !!(p & FIB6_EXCEPTION_BUCKET_FLUSHED);
पूर्ण

/* called with rt6_exception_lock held */
अटल व्योम fib6_nh_excptn_bucket_set_flushed(काष्ठा fib6_nh *nh,
					      spinlock_t *lock)
अणु
	काष्ठा rt6_exception_bucket *bucket;
	अचिन्हित दीर्घ p;

	bucket = rcu_dereference_रक्षित(nh->rt6i_exception_bucket,
					   lockdep_is_held(lock));

	p = (अचिन्हित दीर्घ)bucket;
	p |= FIB6_EXCEPTION_BUCKET_FLUSHED;
	bucket = (काष्ठा rt6_exception_bucket *)p;
	rcu_assign_poपूर्णांकer(nh->rt6i_exception_bucket, bucket);
पूर्ण

अटल पूर्णांक rt6_insert_exception(काष्ठा rt6_info *nrt,
				स्थिर काष्ठा fib6_result *res)
अणु
	काष्ठा net *net = dev_net(nrt->dst.dev);
	काष्ठा rt6_exception_bucket *bucket;
	काष्ठा fib6_info *f6i = res->f6i;
	काष्ठा in6_addr *src_key = शून्य;
	काष्ठा rt6_exception *rt6_ex;
	काष्ठा fib6_nh *nh = res->nh;
	पूर्णांक err = 0;

	spin_lock_bh(&rt6_exception_lock);

	bucket = rcu_dereference_रक्षित(nh->rt6i_exception_bucket,
					  lockdep_is_held(&rt6_exception_lock));
	अगर (!bucket) अणु
		bucket = kसुस्मृति(FIB6_EXCEPTION_BUCKET_SIZE, माप(*bucket),
				 GFP_ATOMIC);
		अगर (!bucket) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		rcu_assign_poपूर्णांकer(nh->rt6i_exception_bucket, bucket);
	पूर्ण अन्यथा अगर (fib6_nh_excptn_bucket_flushed(bucket)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

#अगर_घोषित CONFIG_IPV6_SUBTREES
	/* fib6_src.plen != 0 indicates f6i is in subtree
	 * and exception table is indexed by a hash of
	 * both fib6_dst and fib6_src.
	 * Otherwise, the exception table is indexed by
	 * a hash of only fib6_dst.
	 */
	अगर (f6i->fib6_src.plen)
		src_key = &nrt->rt6i_src.addr;
#पूर्ण_अगर
	/* rt6_mtu_change() might lower mtu on f6i.
	 * Only insert this exception route अगर its mtu
	 * is less than f6i's mtu value.
	 */
	अगर (dst_metric_raw(&nrt->dst, RTAX_MTU) >= fib6_mtu(res)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	rt6_ex = __rt6_find_exception_spinlock(&bucket, &nrt->rt6i_dst.addr,
					       src_key);
	अगर (rt6_ex)
		rt6_हटाओ_exception(bucket, rt6_ex);

	rt6_ex = kzalloc(माप(*rt6_ex), GFP_ATOMIC);
	अगर (!rt6_ex) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	rt6_ex->rt6i = nrt;
	rt6_ex->stamp = jअगरfies;
	hlist_add_head_rcu(&rt6_ex->hlist, &bucket->chain);
	bucket->depth++;
	net->ipv6.rt6_stats->fib_rt_cache++;

	अगर (bucket->depth > FIB6_MAX_DEPTH)
		rt6_exception_हटाओ_oldest(bucket);

out:
	spin_unlock_bh(&rt6_exception_lock);

	/* Update fn->fn_sernum to invalidate all cached dst */
	अगर (!err) अणु
		spin_lock_bh(&f6i->fib6_table->tb6_lock);
		fib6_update_sernum(net, f6i);
		spin_unlock_bh(&f6i->fib6_table->tb6_lock);
		fib6_क्रमce_start_gc(net);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम fib6_nh_flush_exceptions(काष्ठा fib6_nh *nh, काष्ठा fib6_info *from)
अणु
	काष्ठा rt6_exception_bucket *bucket;
	काष्ठा rt6_exception *rt6_ex;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i;

	spin_lock_bh(&rt6_exception_lock);

	bucket = fib6_nh_get_excptn_bucket(nh, &rt6_exception_lock);
	अगर (!bucket)
		जाओ out;

	/* Prevent rt6_insert_exception() to recreate the bucket list */
	अगर (!from)
		fib6_nh_excptn_bucket_set_flushed(nh, &rt6_exception_lock);

	क्रम (i = 0; i < FIB6_EXCEPTION_BUCKET_SIZE; i++) अणु
		hlist_क्रम_each_entry_safe(rt6_ex, पंचांगp, &bucket->chain, hlist) अणु
			अगर (!from ||
			    rcu_access_poपूर्णांकer(rt6_ex->rt6i->from) == from)
				rt6_हटाओ_exception(bucket, rt6_ex);
		पूर्ण
		WARN_ON_ONCE(!from && bucket->depth);
		bucket++;
	पूर्ण
out:
	spin_unlock_bh(&rt6_exception_lock);
पूर्ण

अटल पूर्णांक rt6_nh_flush_exceptions(काष्ठा fib6_nh *nh, व्योम *arg)
अणु
	काष्ठा fib6_info *f6i = arg;

	fib6_nh_flush_exceptions(nh, f6i);

	वापस 0;
पूर्ण

व्योम rt6_flush_exceptions(काष्ठा fib6_info *f6i)
अणु
	अगर (f6i->nh)
		nexthop_क्रम_each_fib6_nh(f6i->nh, rt6_nh_flush_exceptions,
					 f6i);
	अन्यथा
		fib6_nh_flush_exceptions(f6i->fib6_nh, f6i);
पूर्ण

/* Find cached rt in the hash table inside passed in rt
 * Caller has to hold rcu_पढ़ो_lock()
 */
अटल काष्ठा rt6_info *rt6_find_cached_rt(स्थिर काष्ठा fib6_result *res,
					   स्थिर काष्ठा in6_addr *daddr,
					   स्थिर काष्ठा in6_addr *saddr)
अणु
	स्थिर काष्ठा in6_addr *src_key = शून्य;
	काष्ठा rt6_exception_bucket *bucket;
	काष्ठा rt6_exception *rt6_ex;
	काष्ठा rt6_info *ret = शून्य;

#अगर_घोषित CONFIG_IPV6_SUBTREES
	/* fib6i_src.plen != 0 indicates f6i is in subtree
	 * and exception table is indexed by a hash of
	 * both fib6_dst and fib6_src.
	 * However, the src addr used to create the hash
	 * might not be exactly the passed in saddr which
	 * is a /128 addr from the flow.
	 * So we need to use f6i->fib6_src to reकरो lookup
	 * अगर the passed in saddr करोes not find anything.
	 * (See the logic in ip6_rt_cache_alloc() on how
	 * rt->rt6i_src is updated.)
	 */
	अगर (res->f6i->fib6_src.plen)
		src_key = saddr;
find_ex:
#पूर्ण_अगर
	bucket = fib6_nh_get_excptn_bucket(res->nh, शून्य);
	rt6_ex = __rt6_find_exception_rcu(&bucket, daddr, src_key);

	अगर (rt6_ex && !rt6_check_expired(rt6_ex->rt6i))
		ret = rt6_ex->rt6i;

#अगर_घोषित CONFIG_IPV6_SUBTREES
	/* Use fib6_src as src_key and reकरो lookup */
	अगर (!ret && src_key && src_key != &res->f6i->fib6_src.addr) अणु
		src_key = &res->f6i->fib6_src.addr;
		जाओ find_ex;
	पूर्ण
#पूर्ण_अगर

	वापस ret;
पूर्ण

/* Remove the passed in cached rt from the hash table that contains it */
अटल पूर्णांक fib6_nh_हटाओ_exception(स्थिर काष्ठा fib6_nh *nh, पूर्णांक plen,
				    स्थिर काष्ठा rt6_info *rt)
अणु
	स्थिर काष्ठा in6_addr *src_key = शून्य;
	काष्ठा rt6_exception_bucket *bucket;
	काष्ठा rt6_exception *rt6_ex;
	पूर्णांक err;

	अगर (!rcu_access_poपूर्णांकer(nh->rt6i_exception_bucket))
		वापस -ENOENT;

	spin_lock_bh(&rt6_exception_lock);
	bucket = fib6_nh_get_excptn_bucket(nh, &rt6_exception_lock);

#अगर_घोषित CONFIG_IPV6_SUBTREES
	/* rt6i_src.plen != 0 indicates 'from' is in subtree
	 * and exception table is indexed by a hash of
	 * both rt6i_dst and rt6i_src.
	 * Otherwise, the exception table is indexed by
	 * a hash of only rt6i_dst.
	 */
	अगर (plen)
		src_key = &rt->rt6i_src.addr;
#पूर्ण_अगर
	rt6_ex = __rt6_find_exception_spinlock(&bucket,
					       &rt->rt6i_dst.addr,
					       src_key);
	अगर (rt6_ex) अणु
		rt6_हटाओ_exception(bucket, rt6_ex);
		err = 0;
	पूर्ण अन्यथा अणु
		err = -ENOENT;
	पूर्ण

	spin_unlock_bh(&rt6_exception_lock);
	वापस err;
पूर्ण

काष्ठा fib6_nh_excptn_arg अणु
	काष्ठा rt6_info	*rt;
	पूर्णांक		plen;
पूर्ण;

अटल पूर्णांक rt6_nh_हटाओ_exception_rt(काष्ठा fib6_nh *nh, व्योम *_arg)
अणु
	काष्ठा fib6_nh_excptn_arg *arg = _arg;
	पूर्णांक err;

	err = fib6_nh_हटाओ_exception(nh, arg->plen, arg->rt);
	अगर (err == 0)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक rt6_हटाओ_exception_rt(काष्ठा rt6_info *rt)
अणु
	काष्ठा fib6_info *from;

	from = rcu_dereference(rt->from);
	अगर (!from || !(rt->rt6i_flags & RTF_CACHE))
		वापस -EINVAL;

	अगर (from->nh) अणु
		काष्ठा fib6_nh_excptn_arg arg = अणु
			.rt = rt,
			.plen = from->fib6_src.plen
		पूर्ण;
		पूर्णांक rc;

		/* rc = 1 means an entry was found */
		rc = nexthop_क्रम_each_fib6_nh(from->nh,
					      rt6_nh_हटाओ_exception_rt,
					      &arg);
		वापस rc ? 0 : -ENOENT;
	पूर्ण

	वापस fib6_nh_हटाओ_exception(from->fib6_nh,
					from->fib6_src.plen, rt);
पूर्ण

/* Find rt6_ex which contains the passed in rt cache and
 * refresh its stamp
 */
अटल व्योम fib6_nh_update_exception(स्थिर काष्ठा fib6_nh *nh, पूर्णांक plen,
				     स्थिर काष्ठा rt6_info *rt)
अणु
	स्थिर काष्ठा in6_addr *src_key = शून्य;
	काष्ठा rt6_exception_bucket *bucket;
	काष्ठा rt6_exception *rt6_ex;

	bucket = fib6_nh_get_excptn_bucket(nh, शून्य);
#अगर_घोषित CONFIG_IPV6_SUBTREES
	/* rt6i_src.plen != 0 indicates 'from' is in subtree
	 * and exception table is indexed by a hash of
	 * both rt6i_dst and rt6i_src.
	 * Otherwise, the exception table is indexed by
	 * a hash of only rt6i_dst.
	 */
	अगर (plen)
		src_key = &rt->rt6i_src.addr;
#पूर्ण_अगर
	rt6_ex = __rt6_find_exception_rcu(&bucket, &rt->rt6i_dst.addr, src_key);
	अगर (rt6_ex)
		rt6_ex->stamp = jअगरfies;
पूर्ण

काष्ठा fib6_nh_match_arg अणु
	स्थिर काष्ठा net_device *dev;
	स्थिर काष्ठा in6_addr	*gw;
	काष्ठा fib6_nh		*match;
पूर्ण;

/* determine अगर fib6_nh has given device and gateway */
अटल पूर्णांक fib6_nh_find_match(काष्ठा fib6_nh *nh, व्योम *_arg)
अणु
	काष्ठा fib6_nh_match_arg *arg = _arg;

	अगर (arg->dev != nh->fib_nh_dev ||
	    (arg->gw && !nh->fib_nh_gw_family) ||
	    (!arg->gw && nh->fib_nh_gw_family) ||
	    (arg->gw && !ipv6_addr_equal(arg->gw, &nh->fib_nh_gw6)))
		वापस 0;

	arg->match = nh;

	/* found a match, अवरोध the loop */
	वापस 1;
पूर्ण

अटल व्योम rt6_update_exception_stamp_rt(काष्ठा rt6_info *rt)
अणु
	काष्ठा fib6_info *from;
	काष्ठा fib6_nh *fib6_nh;

	rcu_पढ़ो_lock();

	from = rcu_dereference(rt->from);
	अगर (!from || !(rt->rt6i_flags & RTF_CACHE))
		जाओ unlock;

	अगर (from->nh) अणु
		काष्ठा fib6_nh_match_arg arg = अणु
			.dev = rt->dst.dev,
			.gw = &rt->rt6i_gateway,
		पूर्ण;

		nexthop_क्रम_each_fib6_nh(from->nh, fib6_nh_find_match, &arg);

		अगर (!arg.match)
			जाओ unlock;
		fib6_nh = arg.match;
	पूर्ण अन्यथा अणु
		fib6_nh = from->fib6_nh;
	पूर्ण
	fib6_nh_update_exception(fib6_nh, from->fib6_src.plen, rt);
unlock:
	rcu_पढ़ो_unlock();
पूर्ण

अटल bool rt6_mtu_change_route_allowed(काष्ठा inet6_dev *idev,
					 काष्ठा rt6_info *rt, पूर्णांक mtu)
अणु
	/* If the new MTU is lower than the route PMTU, this new MTU will be the
	 * lowest MTU in the path: always allow updating the route PMTU to
	 * reflect PMTU decreases.
	 *
	 * If the new MTU is higher, and the route PMTU is equal to the local
	 * MTU, this means the old MTU is the lowest in the path, so allow
	 * updating it: अगर other nodes now have lower MTUs, PMTU discovery will
	 * handle this.
	 */

	अगर (dst_mtu(&rt->dst) >= mtu)
		वापस true;

	अगर (dst_mtu(&rt->dst) == idev->cnf.mtu6)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम rt6_exceptions_update_pmtu(काष्ठा inet6_dev *idev,
				       स्थिर काष्ठा fib6_nh *nh, पूर्णांक mtu)
अणु
	काष्ठा rt6_exception_bucket *bucket;
	काष्ठा rt6_exception *rt6_ex;
	पूर्णांक i;

	bucket = fib6_nh_get_excptn_bucket(nh, &rt6_exception_lock);
	अगर (!bucket)
		वापस;

	क्रम (i = 0; i < FIB6_EXCEPTION_BUCKET_SIZE; i++) अणु
		hlist_क्रम_each_entry(rt6_ex, &bucket->chain, hlist) अणु
			काष्ठा rt6_info *entry = rt6_ex->rt6i;

			/* For RTF_CACHE with rt6i_pmtu == 0 (i.e. a redirected
			 * route), the metrics of its rt->from have alपढ़ोy
			 * been updated.
			 */
			अगर (dst_metric_raw(&entry->dst, RTAX_MTU) &&
			    rt6_mtu_change_route_allowed(idev, entry, mtu))
				dst_metric_set(&entry->dst, RTAX_MTU, mtu);
		पूर्ण
		bucket++;
	पूर्ण
पूर्ण

#घोषणा RTF_CACHE_GATEWAY	(RTF_GATEWAY | RTF_CACHE)

अटल व्योम fib6_nh_exceptions_clean_tohost(स्थिर काष्ठा fib6_nh *nh,
					    स्थिर काष्ठा in6_addr *gateway)
अणु
	काष्ठा rt6_exception_bucket *bucket;
	काष्ठा rt6_exception *rt6_ex;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i;

	अगर (!rcu_access_poपूर्णांकer(nh->rt6i_exception_bucket))
		वापस;

	spin_lock_bh(&rt6_exception_lock);
	bucket = fib6_nh_get_excptn_bucket(nh, &rt6_exception_lock);
	अगर (bucket) अणु
		क्रम (i = 0; i < FIB6_EXCEPTION_BUCKET_SIZE; i++) अणु
			hlist_क्रम_each_entry_safe(rt6_ex, पंचांगp,
						  &bucket->chain, hlist) अणु
				काष्ठा rt6_info *entry = rt6_ex->rt6i;

				अगर ((entry->rt6i_flags & RTF_CACHE_GATEWAY) ==
				    RTF_CACHE_GATEWAY &&
				    ipv6_addr_equal(gateway,
						    &entry->rt6i_gateway)) अणु
					rt6_हटाओ_exception(bucket, rt6_ex);
				पूर्ण
			पूर्ण
			bucket++;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&rt6_exception_lock);
पूर्ण

अटल व्योम rt6_age_examine_exception(काष्ठा rt6_exception_bucket *bucket,
				      काष्ठा rt6_exception *rt6_ex,
				      काष्ठा fib6_gc_args *gc_args,
				      अचिन्हित दीर्घ now)
अणु
	काष्ठा rt6_info *rt = rt6_ex->rt6i;

	/* we are pruning and obsoleting aged-out and non gateway exceptions
	 * even अगर others have still references to them, so that on next
	 * dst_check() such references can be dropped.
	 * EXPIRES exceptions - e.g. pmtu-generated ones are pruned when
	 * expired, independently from their aging, as per RFC 8201 section 4
	 */
	अगर (!(rt->rt6i_flags & RTF_EXPIRES)) अणु
		अगर (समय_after_eq(now, rt->dst.lastuse + gc_args->समयout)) अणु
			RT6_TRACE("aging clone %p\n", rt);
			rt6_हटाओ_exception(bucket, rt6_ex);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (समय_after(jअगरfies, rt->dst.expires)) अणु
		RT6_TRACE("purging expired route %p\n", rt);
		rt6_हटाओ_exception(bucket, rt6_ex);
		वापस;
	पूर्ण

	अगर (rt->rt6i_flags & RTF_GATEWAY) अणु
		काष्ठा neighbour *neigh;

		neigh = __ipv6_neigh_lookup_noref(rt->dst.dev, &rt->rt6i_gateway);

		अगर (!(neigh && (neigh->flags & NTF_ROUTER))) अणु
			RT6_TRACE("purging route %p via non-router but gateway\n",
				  rt);
			rt6_हटाओ_exception(bucket, rt6_ex);
			वापस;
		पूर्ण
	पूर्ण

	gc_args->more++;
पूर्ण

अटल व्योम fib6_nh_age_exceptions(स्थिर काष्ठा fib6_nh *nh,
				   काष्ठा fib6_gc_args *gc_args,
				   अचिन्हित दीर्घ now)
अणु
	काष्ठा rt6_exception_bucket *bucket;
	काष्ठा rt6_exception *rt6_ex;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i;

	अगर (!rcu_access_poपूर्णांकer(nh->rt6i_exception_bucket))
		वापस;

	rcu_पढ़ो_lock_bh();
	spin_lock(&rt6_exception_lock);
	bucket = fib6_nh_get_excptn_bucket(nh, &rt6_exception_lock);
	अगर (bucket) अणु
		क्रम (i = 0; i < FIB6_EXCEPTION_BUCKET_SIZE; i++) अणु
			hlist_क्रम_each_entry_safe(rt6_ex, पंचांगp,
						  &bucket->chain, hlist) अणु
				rt6_age_examine_exception(bucket, rt6_ex,
							  gc_args, now);
			पूर्ण
			bucket++;
		पूर्ण
	पूर्ण
	spin_unlock(&rt6_exception_lock);
	rcu_पढ़ो_unlock_bh();
पूर्ण

काष्ठा fib6_nh_age_excptn_arg अणु
	काष्ठा fib6_gc_args	*gc_args;
	अचिन्हित दीर्घ		now;
पूर्ण;

अटल पूर्णांक rt6_nh_age_exceptions(काष्ठा fib6_nh *nh, व्योम *_arg)
अणु
	काष्ठा fib6_nh_age_excptn_arg *arg = _arg;

	fib6_nh_age_exceptions(nh, arg->gc_args, arg->now);
	वापस 0;
पूर्ण

व्योम rt6_age_exceptions(काष्ठा fib6_info *f6i,
			काष्ठा fib6_gc_args *gc_args,
			अचिन्हित दीर्घ now)
अणु
	अगर (f6i->nh) अणु
		काष्ठा fib6_nh_age_excptn_arg arg = अणु
			.gc_args = gc_args,
			.now = now
		पूर्ण;

		nexthop_क्रम_each_fib6_nh(f6i->nh, rt6_nh_age_exceptions,
					 &arg);
	पूर्ण अन्यथा अणु
		fib6_nh_age_exceptions(f6i->fib6_nh, gc_args, now);
	पूर्ण
पूर्ण

/* must be called with rcu lock held */
पूर्णांक fib6_table_lookup(काष्ठा net *net, काष्ठा fib6_table *table, पूर्णांक oअगर,
		      काष्ठा flowi6 *fl6, काष्ठा fib6_result *res, पूर्णांक strict)
अणु
	काष्ठा fib6_node *fn, *saved_fn;

	fn = fib6_node_lookup(&table->tb6_root, &fl6->daddr, &fl6->saddr);
	saved_fn = fn;

	अगर (fl6->flowi6_flags & FLOWI_FLAG_SKIP_NH_OIF)
		oअगर = 0;

reकरो_rt6_select:
	rt6_select(net, fn, oअगर, res, strict);
	अगर (res->f6i == net->ipv6.fib6_null_entry) अणु
		fn = fib6_backtrack(fn, &fl6->saddr);
		अगर (fn)
			जाओ reकरो_rt6_select;
		अन्यथा अगर (strict & RT6_LOOKUP_F_REACHABLE) अणु
			/* also consider unreachable route */
			strict &= ~RT6_LOOKUP_F_REACHABLE;
			fn = saved_fn;
			जाओ reकरो_rt6_select;
		पूर्ण
	पूर्ण

	trace_fib6_table_lookup(net, res, table, fl6);

	वापस 0;
पूर्ण

काष्ठा rt6_info *ip6_pol_route(काष्ठा net *net, काष्ठा fib6_table *table,
			       पूर्णांक oअगर, काष्ठा flowi6 *fl6,
			       स्थिर काष्ठा sk_buff *skb, पूर्णांक flags)
अणु
	काष्ठा fib6_result res = अणुपूर्ण;
	काष्ठा rt6_info *rt = शून्य;
	पूर्णांक strict = 0;

	WARN_ON_ONCE((flags & RT6_LOOKUP_F_DST_NOREF) &&
		     !rcu_पढ़ो_lock_held());

	strict |= flags & RT6_LOOKUP_F_IFACE;
	strict |= flags & RT6_LOOKUP_F_IGNORE_LINKSTATE;
	अगर (net->ipv6.devconf_all->क्रमwarding == 0)
		strict |= RT6_LOOKUP_F_REACHABLE;

	rcu_पढ़ो_lock();

	fib6_table_lookup(net, table, oअगर, fl6, &res, strict);
	अगर (res.f6i == net->ipv6.fib6_null_entry)
		जाओ out;

	fib6_select_path(net, &res, fl6, oअगर, false, skb, strict);

	/*Search through exception table */
	rt = rt6_find_cached_rt(&res, &fl6->daddr, &fl6->saddr);
	अगर (rt) अणु
		जाओ out;
	पूर्ण अन्यथा अगर (unlikely((fl6->flowi6_flags & FLOWI_FLAG_KNOWN_NH) &&
			    !res.nh->fib_nh_gw_family)) अणु
		/* Create a RTF_CACHE clone which will not be
		 * owned by the fib6 tree.  It is क्रम the special हाल where
		 * the daddr in the skb during the neighbor look-up is dअगरferent
		 * from the fl6->daddr used to look-up route here.
		 */
		rt = ip6_rt_cache_alloc(&res, &fl6->daddr, शून्य);

		अगर (rt) अणु
			/* 1 refcnt is taken during ip6_rt_cache_alloc().
			 * As rt6_uncached_list_add() करोes not consume refcnt,
			 * this refcnt is always वापसed to the caller even
			 * अगर caller sets RT6_LOOKUP_F_DST_NOREF flag.
			 */
			rt6_uncached_list_add(rt);
			atomic_inc(&net->ipv6.rt6_stats->fib_rt_uncache);
			rcu_पढ़ो_unlock();

			वापस rt;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Get a percpu copy */
		local_bh_disable();
		rt = rt6_get_pcpu_route(&res);

		अगर (!rt)
			rt = rt6_make_pcpu_route(net, &res);

		local_bh_enable();
	पूर्ण
out:
	अगर (!rt)
		rt = net->ipv6.ip6_null_entry;
	अगर (!(flags & RT6_LOOKUP_F_DST_NOREF))
		ip6_hold_safe(net, &rt);
	rcu_पढ़ो_unlock();

	वापस rt;
पूर्ण
EXPORT_SYMBOL_GPL(ip6_pol_route);

INसूचीECT_CALLABLE_SCOPE काष्ठा rt6_info *ip6_pol_route_input(काष्ठा net *net,
					    काष्ठा fib6_table *table,
					    काष्ठा flowi6 *fl6,
					    स्थिर काष्ठा sk_buff *skb,
					    पूर्णांक flags)
अणु
	वापस ip6_pol_route(net, table, fl6->flowi6_iअगर, fl6, skb, flags);
पूर्ण

काष्ठा dst_entry *ip6_route_input_lookup(काष्ठा net *net,
					 काष्ठा net_device *dev,
					 काष्ठा flowi6 *fl6,
					 स्थिर काष्ठा sk_buff *skb,
					 पूर्णांक flags)
अणु
	अगर (rt6_need_strict(&fl6->daddr) && dev->type != ARPHRD_PIMREG)
		flags |= RT6_LOOKUP_F_IFACE;

	वापस fib6_rule_lookup(net, fl6, skb, flags, ip6_pol_route_input);
पूर्ण
EXPORT_SYMBOL_GPL(ip6_route_input_lookup);

अटल व्योम ip6_multipath_l3_keys(स्थिर काष्ठा sk_buff *skb,
				  काष्ठा flow_keys *keys,
				  काष्ठा flow_keys *flkeys)
अणु
	स्थिर काष्ठा ipv6hdr *outer_iph = ipv6_hdr(skb);
	स्थिर काष्ठा ipv6hdr *key_iph = outer_iph;
	काष्ठा flow_keys *_flkeys = flkeys;
	स्थिर काष्ठा ipv6hdr *inner_iph;
	स्थिर काष्ठा icmp6hdr *icmph;
	काष्ठा ipv6hdr _inner_iph;
	काष्ठा icmp6hdr _icmph;

	अगर (likely(outer_iph->nexthdr != IPPROTO_ICMPV6))
		जाओ out;

	icmph = skb_header_poपूर्णांकer(skb, skb_transport_offset(skb),
				   माप(_icmph), &_icmph);
	अगर (!icmph)
		जाओ out;

	अगर (!icmpv6_is_err(icmph->icmp6_type))
		जाओ out;

	inner_iph = skb_header_poपूर्णांकer(skb,
				       skb_transport_offset(skb) + माप(*icmph),
				       माप(_inner_iph), &_inner_iph);
	अगर (!inner_iph)
		जाओ out;

	key_iph = inner_iph;
	_flkeys = शून्य;
out:
	अगर (_flkeys) अणु
		keys->addrs.v6addrs.src = _flkeys->addrs.v6addrs.src;
		keys->addrs.v6addrs.dst = _flkeys->addrs.v6addrs.dst;
		keys->tags.flow_label = _flkeys->tags.flow_label;
		keys->basic.ip_proto = _flkeys->basic.ip_proto;
	पूर्ण अन्यथा अणु
		keys->addrs.v6addrs.src = key_iph->saddr;
		keys->addrs.v6addrs.dst = key_iph->daddr;
		keys->tags.flow_label = ip6_flowlabel(key_iph);
		keys->basic.ip_proto = key_iph->nexthdr;
	पूर्ण
पूर्ण

/* अगर skb is set it will be used and fl6 can be शून्य */
u32 rt6_multipath_hash(स्थिर काष्ठा net *net, स्थिर काष्ठा flowi6 *fl6,
		       स्थिर काष्ठा sk_buff *skb, काष्ठा flow_keys *flkeys)
अणु
	काष्ठा flow_keys hash_keys;
	u32 mhash;

	चयन (ip6_multipath_hash_policy(net)) अणु
	हाल 0:
		स_रखो(&hash_keys, 0, माप(hash_keys));
		hash_keys.control.addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
		अगर (skb) अणु
			ip6_multipath_l3_keys(skb, &hash_keys, flkeys);
		पूर्ण अन्यथा अणु
			hash_keys.addrs.v6addrs.src = fl6->saddr;
			hash_keys.addrs.v6addrs.dst = fl6->daddr;
			hash_keys.tags.flow_label = (__क्रमce u32)flowi6_get_flowlabel(fl6);
			hash_keys.basic.ip_proto = fl6->flowi6_proto;
		पूर्ण
		अवरोध;
	हाल 1:
		अगर (skb) अणु
			अचिन्हित पूर्णांक flag = FLOW_DISSECTOR_F_STOP_AT_ENCAP;
			काष्ठा flow_keys keys;

			/* लघु-circuit अगर we alपढ़ोy have L4 hash present */
			अगर (skb->l4_hash)
				वापस skb_get_hash_raw(skb) >> 1;

			स_रखो(&hash_keys, 0, माप(hash_keys));

			अगर (!flkeys) अणु
				skb_flow_dissect_flow_keys(skb, &keys, flag);
				flkeys = &keys;
			पूर्ण
			hash_keys.control.addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
			hash_keys.addrs.v6addrs.src = flkeys->addrs.v6addrs.src;
			hash_keys.addrs.v6addrs.dst = flkeys->addrs.v6addrs.dst;
			hash_keys.ports.src = flkeys->ports.src;
			hash_keys.ports.dst = flkeys->ports.dst;
			hash_keys.basic.ip_proto = flkeys->basic.ip_proto;
		पूर्ण अन्यथा अणु
			स_रखो(&hash_keys, 0, माप(hash_keys));
			hash_keys.control.addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
			hash_keys.addrs.v6addrs.src = fl6->saddr;
			hash_keys.addrs.v6addrs.dst = fl6->daddr;
			hash_keys.ports.src = fl6->fl6_sport;
			hash_keys.ports.dst = fl6->fl6_dport;
			hash_keys.basic.ip_proto = fl6->flowi6_proto;
		पूर्ण
		अवरोध;
	हाल 2:
		स_रखो(&hash_keys, 0, माप(hash_keys));
		hash_keys.control.addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
		अगर (skb) अणु
			काष्ठा flow_keys keys;

			अगर (!flkeys) अणु
				skb_flow_dissect_flow_keys(skb, &keys, 0);
				flkeys = &keys;
			पूर्ण

			/* Inner can be v4 or v6 */
			अगर (flkeys->control.addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) अणु
				hash_keys.control.addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
				hash_keys.addrs.v4addrs.src = flkeys->addrs.v4addrs.src;
				hash_keys.addrs.v4addrs.dst = flkeys->addrs.v4addrs.dst;
			पूर्ण अन्यथा अगर (flkeys->control.addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS) अणु
				hash_keys.control.addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
				hash_keys.addrs.v6addrs.src = flkeys->addrs.v6addrs.src;
				hash_keys.addrs.v6addrs.dst = flkeys->addrs.v6addrs.dst;
				hash_keys.tags.flow_label = flkeys->tags.flow_label;
				hash_keys.basic.ip_proto = flkeys->basic.ip_proto;
			पूर्ण अन्यथा अणु
				/* Same as हाल 0 */
				hash_keys.control.addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
				ip6_multipath_l3_keys(skb, &hash_keys, flkeys);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Same as हाल 0 */
			hash_keys.control.addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
			hash_keys.addrs.v6addrs.src = fl6->saddr;
			hash_keys.addrs.v6addrs.dst = fl6->daddr;
			hash_keys.tags.flow_label = (__क्रमce u32)flowi6_get_flowlabel(fl6);
			hash_keys.basic.ip_proto = fl6->flowi6_proto;
		पूर्ण
		अवरोध;
	पूर्ण
	mhash = flow_hash_from_keys(&hash_keys);

	वापस mhash >> 1;
पूर्ण

/* Called with rcu held */
व्योम ip6_route_input(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	काष्ठा net *net = dev_net(skb->dev);
	पूर्णांक flags = RT6_LOOKUP_F_HAS_SADDR | RT6_LOOKUP_F_DST_NOREF;
	काष्ठा ip_tunnel_info *tun_info;
	काष्ठा flowi6 fl6 = अणु
		.flowi6_iअगर = skb->dev->अगरindex,
		.daddr = iph->daddr,
		.saddr = iph->saddr,
		.flowlabel = ip6_flowinfo(iph),
		.flowi6_mark = skb->mark,
		.flowi6_proto = iph->nexthdr,
	पूर्ण;
	काष्ठा flow_keys *flkeys = शून्य, _flkeys;

	tun_info = skb_tunnel_info(skb);
	अगर (tun_info && !(tun_info->mode & IP_TUNNEL_INFO_TX))
		fl6.flowi6_tun_key.tun_id = tun_info->key.tun_id;

	अगर (fib6_rules_early_flow_dissect(net, skb, &fl6, &_flkeys))
		flkeys = &_flkeys;

	अगर (unlikely(fl6.flowi6_proto == IPPROTO_ICMPV6))
		fl6.mp_hash = rt6_multipath_hash(net, &fl6, skb, flkeys);
	skb_dst_drop(skb);
	skb_dst_set_noref(skb, ip6_route_input_lookup(net, skb->dev,
						      &fl6, skb, flags));
पूर्ण

INसूचीECT_CALLABLE_SCOPE काष्ठा rt6_info *ip6_pol_route_output(काष्ठा net *net,
					     काष्ठा fib6_table *table,
					     काष्ठा flowi6 *fl6,
					     स्थिर काष्ठा sk_buff *skb,
					     पूर्णांक flags)
अणु
	वापस ip6_pol_route(net, table, fl6->flowi6_oअगर, fl6, skb, flags);
पूर्ण

काष्ठा dst_entry *ip6_route_output_flags_noref(काष्ठा net *net,
					       स्थिर काष्ठा sock *sk,
					       काष्ठा flowi6 *fl6, पूर्णांक flags)
अणु
	bool any_src;

	अगर (ipv6_addr_type(&fl6->daddr) &
	    (IPV6_ADDR_MULTICAST | IPV6_ADDR_LINKLOCAL)) अणु
		काष्ठा dst_entry *dst;

		/* This function करोes not take refcnt on the dst */
		dst = l3mdev_link_scope_lookup(net, fl6);
		अगर (dst)
			वापस dst;
	पूर्ण

	fl6->flowi6_iअगर = LOOPBACK_IFINDEX;

	flags |= RT6_LOOKUP_F_DST_NOREF;
	any_src = ipv6_addr_any(&fl6->saddr);
	अगर ((sk && sk->sk_bound_dev_अगर) || rt6_need_strict(&fl6->daddr) ||
	    (fl6->flowi6_oअगर && any_src))
		flags |= RT6_LOOKUP_F_IFACE;

	अगर (!any_src)
		flags |= RT6_LOOKUP_F_HAS_SADDR;
	अन्यथा अगर (sk)
		flags |= rt6_srcprefs2flags(inet6_sk(sk)->srcprefs);

	वापस fib6_rule_lookup(net, fl6, शून्य, flags, ip6_pol_route_output);
पूर्ण
EXPORT_SYMBOL_GPL(ip6_route_output_flags_noref);

काष्ठा dst_entry *ip6_route_output_flags(काष्ठा net *net,
					 स्थिर काष्ठा sock *sk,
					 काष्ठा flowi6 *fl6,
					 पूर्णांक flags)
अणु
	काष्ठा dst_entry *dst;
	काष्ठा rt6_info *rt6;

	rcu_पढ़ो_lock();
	dst = ip6_route_output_flags_noref(net, sk, fl6, flags);
	rt6 = (काष्ठा rt6_info *)dst;
	/* For dst cached in uncached_list, refcnt is alपढ़ोy taken. */
	अगर (list_empty(&rt6->rt6i_uncached) && !dst_hold_safe(dst)) अणु
		dst = &net->ipv6.ip6_null_entry->dst;
		dst_hold(dst);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस dst;
पूर्ण
EXPORT_SYMBOL_GPL(ip6_route_output_flags);

काष्ठा dst_entry *ip6_blackhole_route(काष्ठा net *net, काष्ठा dst_entry *dst_orig)
अणु
	काष्ठा rt6_info *rt, *ort = (काष्ठा rt6_info *) dst_orig;
	काष्ठा net_device *loopback_dev = net->loopback_dev;
	काष्ठा dst_entry *new = शून्य;

	rt = dst_alloc(&ip6_dst_blackhole_ops, loopback_dev, 1,
		       DST_OBSOLETE_DEAD, 0);
	अगर (rt) अणु
		rt6_info_init(rt);
		atomic_inc(&net->ipv6.rt6_stats->fib_rt_alloc);

		new = &rt->dst;
		new->__use = 1;
		new->input = dst_discard;
		new->output = dst_discard_out;

		dst_copy_metrics(new, &ort->dst);

		rt->rt6i_idev = in6_dev_get(loopback_dev);
		rt->rt6i_gateway = ort->rt6i_gateway;
		rt->rt6i_flags = ort->rt6i_flags & ~RTF_PCPU;

		स_नकल(&rt->rt6i_dst, &ort->rt6i_dst, माप(काष्ठा rt6key));
#अगर_घोषित CONFIG_IPV6_SUBTREES
		स_नकल(&rt->rt6i_src, &ort->rt6i_src, माप(काष्ठा rt6key));
#पूर्ण_अगर
	पूर्ण

	dst_release(dst_orig);
	वापस new ? new : ERR_PTR(-ENOMEM);
पूर्ण

/*
 *	Destination cache support functions
 */

अटल bool fib6_check(काष्ठा fib6_info *f6i, u32 cookie)
अणु
	u32 rt_cookie = 0;

	अगर (!fib6_get_cookie_safe(f6i, &rt_cookie) || rt_cookie != cookie)
		वापस false;

	अगर (fib6_check_expired(f6i))
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा dst_entry *rt6_check(काष्ठा rt6_info *rt,
				   काष्ठा fib6_info *from,
				   u32 cookie)
अणु
	u32 rt_cookie = 0;

	अगर (!from || !fib6_get_cookie_safe(from, &rt_cookie) ||
	    rt_cookie != cookie)
		वापस शून्य;

	अगर (rt6_check_expired(rt))
		वापस शून्य;

	वापस &rt->dst;
पूर्ण

अटल काष्ठा dst_entry *rt6_dst_from_check(काष्ठा rt6_info *rt,
					    काष्ठा fib6_info *from,
					    u32 cookie)
अणु
	अगर (!__rt6_check_expired(rt) &&
	    rt->dst.obsolete == DST_OBSOLETE_FORCE_CHK &&
	    fib6_check(from, cookie))
		वापस &rt->dst;
	अन्यथा
		वापस शून्य;
पूर्ण

INसूचीECT_CALLABLE_SCOPE काष्ठा dst_entry *ip6_dst_check(काष्ठा dst_entry *dst,
							u32 cookie)
अणु
	काष्ठा dst_entry *dst_ret;
	काष्ठा fib6_info *from;
	काष्ठा rt6_info *rt;

	rt = container_of(dst, काष्ठा rt6_info, dst);

	अगर (rt->sernum)
		वापस rt6_is_valid(rt) ? dst : शून्य;

	rcu_पढ़ो_lock();

	/* All IPV6 dsts are created with ->obsolete set to the value
	 * DST_OBSOLETE_FORCE_CHK which क्रमces validation calls करोwn
	 * पूर्णांकo this function always.
	 */

	from = rcu_dereference(rt->from);

	अगर (from && (rt->rt6i_flags & RTF_PCPU ||
	    unlikely(!list_empty(&rt->rt6i_uncached))))
		dst_ret = rt6_dst_from_check(rt, from, cookie);
	अन्यथा
		dst_ret = rt6_check(rt, from, cookie);

	rcu_पढ़ो_unlock();

	वापस dst_ret;
पूर्ण
EXPORT_INसूचीECT_CALLABLE(ip6_dst_check);

अटल काष्ठा dst_entry *ip6_negative_advice(काष्ठा dst_entry *dst)
अणु
	काष्ठा rt6_info *rt = (काष्ठा rt6_info *) dst;

	अगर (rt) अणु
		अगर (rt->rt6i_flags & RTF_CACHE) अणु
			rcu_पढ़ो_lock();
			अगर (rt6_check_expired(rt)) अणु
				rt6_हटाओ_exception_rt(rt);
				dst = शून्य;
			पूर्ण
			rcu_पढ़ो_unlock();
		पूर्ण अन्यथा अणु
			dst_release(dst);
			dst = शून्य;
		पूर्ण
	पूर्ण
	वापस dst;
पूर्ण

अटल व्योम ip6_link_failure(काष्ठा sk_buff *skb)
अणु
	काष्ठा rt6_info *rt;

	icmpv6_send(skb, ICMPV6_DEST_UNREACH, ICMPV6_ADDR_UNREACH, 0);

	rt = (काष्ठा rt6_info *) skb_dst(skb);
	अगर (rt) अणु
		rcu_पढ़ो_lock();
		अगर (rt->rt6i_flags & RTF_CACHE) अणु
			rt6_हटाओ_exception_rt(rt);
		पूर्ण अन्यथा अणु
			काष्ठा fib6_info *from;
			काष्ठा fib6_node *fn;

			from = rcu_dereference(rt->from);
			अगर (from) अणु
				fn = rcu_dereference(from->fib6_node);
				अगर (fn && (rt->rt6i_flags & RTF_DEFAULT))
					fn->fn_sernum = -1;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

अटल व्योम rt6_update_expires(काष्ठा rt6_info *rt0, पूर्णांक समयout)
अणु
	अगर (!(rt0->rt6i_flags & RTF_EXPIRES)) अणु
		काष्ठा fib6_info *from;

		rcu_पढ़ो_lock();
		from = rcu_dereference(rt0->from);
		अगर (from)
			rt0->dst.expires = from->expires;
		rcu_पढ़ो_unlock();
	पूर्ण

	dst_set_expires(&rt0->dst, समयout);
	rt0->rt6i_flags |= RTF_EXPIRES;
पूर्ण

अटल व्योम rt6_करो_update_pmtu(काष्ठा rt6_info *rt, u32 mtu)
अणु
	काष्ठा net *net = dev_net(rt->dst.dev);

	dst_metric_set(&rt->dst, RTAX_MTU, mtu);
	rt->rt6i_flags |= RTF_MODIFIED;
	rt6_update_expires(rt, net->ipv6.sysctl.ip6_rt_mtu_expires);
पूर्ण

अटल bool rt6_cache_allowed_क्रम_pmtu(स्थिर काष्ठा rt6_info *rt)
अणु
	वापस !(rt->rt6i_flags & RTF_CACHE) &&
		(rt->rt6i_flags & RTF_PCPU || rcu_access_poपूर्णांकer(rt->from));
पूर्ण

अटल व्योम __ip6_rt_update_pmtu(काष्ठा dst_entry *dst, स्थिर काष्ठा sock *sk,
				 स्थिर काष्ठा ipv6hdr *iph, u32 mtu,
				 bool confirm_neigh)
अणु
	स्थिर काष्ठा in6_addr *daddr, *saddr;
	काष्ठा rt6_info *rt6 = (काष्ठा rt6_info *)dst;

	/* Note: करो *NOT* check dst_metric_locked(dst, RTAX_MTU)
	 * IPv6 pmtu discovery isn't optional, so 'mtu lock' cannot disable it.
	 * [see also comment in rt6_mtu_change_route()]
	 */

	अगर (iph) अणु
		daddr = &iph->daddr;
		saddr = &iph->saddr;
	पूर्ण अन्यथा अगर (sk) अणु
		daddr = &sk->sk_v6_daddr;
		saddr = &inet6_sk(sk)->saddr;
	पूर्ण अन्यथा अणु
		daddr = शून्य;
		saddr = शून्य;
	पूर्ण

	अगर (confirm_neigh)
		dst_confirm_neigh(dst, daddr);

	अगर (mtu < IPV6_MIN_MTU)
		वापस;
	अगर (mtu >= dst_mtu(dst))
		वापस;

	अगर (!rt6_cache_allowed_क्रम_pmtu(rt6)) अणु
		rt6_करो_update_pmtu(rt6, mtu);
		/* update rt6_ex->stamp क्रम cache */
		अगर (rt6->rt6i_flags & RTF_CACHE)
			rt6_update_exception_stamp_rt(rt6);
	पूर्ण अन्यथा अगर (daddr) अणु
		काष्ठा fib6_result res = अणुपूर्ण;
		काष्ठा rt6_info *nrt6;

		rcu_पढ़ो_lock();
		res.f6i = rcu_dereference(rt6->from);
		अगर (!res.f6i)
			जाओ out_unlock;

		res.fib6_flags = res.f6i->fib6_flags;
		res.fib6_type = res.f6i->fib6_type;

		अगर (res.f6i->nh) अणु
			काष्ठा fib6_nh_match_arg arg = अणु
				.dev = dst->dev,
				.gw = &rt6->rt6i_gateway,
			पूर्ण;

			nexthop_क्रम_each_fib6_nh(res.f6i->nh,
						 fib6_nh_find_match, &arg);

			/* fib6_info uses a nexthop that करोes not have fib6_nh
			 * using the dst->dev + gw. Should be impossible.
			 */
			अगर (!arg.match)
				जाओ out_unlock;

			res.nh = arg.match;
		पूर्ण अन्यथा अणु
			res.nh = res.f6i->fib6_nh;
		पूर्ण

		nrt6 = ip6_rt_cache_alloc(&res, daddr, saddr);
		अगर (nrt6) अणु
			rt6_करो_update_pmtu(nrt6, mtu);
			अगर (rt6_insert_exception(nrt6, &res))
				dst_release_immediate(&nrt6->dst);
		पूर्ण
out_unlock:
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

अटल व्योम ip6_rt_update_pmtu(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			       काष्ठा sk_buff *skb, u32 mtu,
			       bool confirm_neigh)
अणु
	__ip6_rt_update_pmtu(dst, sk, skb ? ipv6_hdr(skb) : शून्य, mtu,
			     confirm_neigh);
पूर्ण

व्योम ip6_update_pmtu(काष्ठा sk_buff *skb, काष्ठा net *net, __be32 mtu,
		     पूर्णांक oअगर, u32 mark, kuid_t uid)
अणु
	स्थिर काष्ठा ipv6hdr *iph = (काष्ठा ipv6hdr *) skb->data;
	काष्ठा dst_entry *dst;
	काष्ठा flowi6 fl6 = अणु
		.flowi6_oअगर = oअगर,
		.flowi6_mark = mark ? mark : IP6_REPLY_MARK(net, skb->mark),
		.daddr = iph->daddr,
		.saddr = iph->saddr,
		.flowlabel = ip6_flowinfo(iph),
		.flowi6_uid = uid,
	पूर्ण;

	dst = ip6_route_output(net, शून्य, &fl6);
	अगर (!dst->error)
		__ip6_rt_update_pmtu(dst, शून्य, iph, ntohl(mtu), true);
	dst_release(dst);
पूर्ण
EXPORT_SYMBOL_GPL(ip6_update_pmtu);

व्योम ip6_sk_update_pmtu(काष्ठा sk_buff *skb, काष्ठा sock *sk, __be32 mtu)
अणु
	पूर्णांक oअगर = sk->sk_bound_dev_अगर;
	काष्ठा dst_entry *dst;

	अगर (!oअगर && skb->dev)
		oअगर = l3mdev_master_अगरindex(skb->dev);

	ip6_update_pmtu(skb, sock_net(sk), mtu, oअगर, sk->sk_mark, sk->sk_uid);

	dst = __sk_dst_get(sk);
	अगर (!dst || !dst->obsolete ||
	    dst->ops->check(dst, inet6_sk(sk)->dst_cookie))
		वापस;

	bh_lock_sock(sk);
	अगर (!sock_owned_by_user(sk) && !ipv6_addr_v4mapped(&sk->sk_v6_daddr))
		ip6_datagram_dst_update(sk, false);
	bh_unlock_sock(sk);
पूर्ण
EXPORT_SYMBOL_GPL(ip6_sk_update_pmtu);

व्योम ip6_sk_dst_store_flow(काष्ठा sock *sk, काष्ठा dst_entry *dst,
			   स्थिर काष्ठा flowi6 *fl6)
अणु
#अगर_घोषित CONFIG_IPV6_SUBTREES
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
#पूर्ण_अगर

	ip6_dst_store(sk, dst,
		      ipv6_addr_equal(&fl6->daddr, &sk->sk_v6_daddr) ?
		      &sk->sk_v6_daddr : शून्य,
#अगर_घोषित CONFIG_IPV6_SUBTREES
		      ipv6_addr_equal(&fl6->saddr, &np->saddr) ?
		      &np->saddr :
#पूर्ण_अगर
		      शून्य);
पूर्ण

अटल bool ip6_redirect_nh_match(स्थिर काष्ठा fib6_result *res,
				  काष्ठा flowi6 *fl6,
				  स्थिर काष्ठा in6_addr *gw,
				  काष्ठा rt6_info **ret)
अणु
	स्थिर काष्ठा fib6_nh *nh = res->nh;

	अगर (nh->fib_nh_flags & RTNH_F_DEAD || !nh->fib_nh_gw_family ||
	    fl6->flowi6_oअगर != nh->fib_nh_dev->अगरindex)
		वापस false;

	/* rt_cache's gateway might be different from its 'parent'
	 * in the हाल of an ip redirect.
	 * So we keep searching in the exception table अगर the gateway
	 * is dअगरferent.
	 */
	अगर (!ipv6_addr_equal(gw, &nh->fib_nh_gw6)) अणु
		काष्ठा rt6_info *rt_cache;

		rt_cache = rt6_find_cached_rt(res, &fl6->daddr, &fl6->saddr);
		अगर (rt_cache &&
		    ipv6_addr_equal(gw, &rt_cache->rt6i_gateway)) अणु
			*ret = rt_cache;
			वापस true;
		पूर्ण
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

काष्ठा fib6_nh_rd_arg अणु
	काष्ठा fib6_result	*res;
	काष्ठा flowi6		*fl6;
	स्थिर काष्ठा in6_addr	*gw;
	काष्ठा rt6_info		**ret;
पूर्ण;

अटल पूर्णांक fib6_nh_redirect_match(काष्ठा fib6_nh *nh, व्योम *_arg)
अणु
	काष्ठा fib6_nh_rd_arg *arg = _arg;

	arg->res->nh = nh;
	वापस ip6_redirect_nh_match(arg->res, arg->fl6, arg->gw, arg->ret);
पूर्ण

/* Handle redirects */
काष्ठा ip6rd_flowi अणु
	काष्ठा flowi6 fl6;
	काष्ठा in6_addr gateway;
पूर्ण;

INसूचीECT_CALLABLE_SCOPE काष्ठा rt6_info *__ip6_route_redirect(काष्ठा net *net,
					     काष्ठा fib6_table *table,
					     काष्ठा flowi6 *fl6,
					     स्थिर काष्ठा sk_buff *skb,
					     पूर्णांक flags)
अणु
	काष्ठा ip6rd_flowi *rdfl = (काष्ठा ip6rd_flowi *)fl6;
	काष्ठा rt6_info *ret = शून्य;
	काष्ठा fib6_result res = अणुपूर्ण;
	काष्ठा fib6_nh_rd_arg arg = अणु
		.res = &res,
		.fl6 = fl6,
		.gw  = &rdfl->gateway,
		.ret = &ret
	पूर्ण;
	काष्ठा fib6_info *rt;
	काष्ठा fib6_node *fn;

	/* l3mdev_update_flow overrides oअगर अगर the device is enslaved; in
	 * this हाल we must match on the real ingress device, so reset it
	 */
	अगर (fl6->flowi6_flags & FLOWI_FLAG_SKIP_NH_OIF)
		fl6->flowi6_oअगर = skb->dev->अगरindex;

	/* Get the "current" route क्रम this destination and
	 * check अगर the redirect has come from appropriate router.
	 *
	 * RFC 4861 specअगरies that redirects should only be
	 * accepted अगर they come from the nexthop to the target.
	 * Due to the way the routes are chosen, this notion
	 * is a bit fuzzy and one might need to check all possible
	 * routes.
	 */

	rcu_पढ़ो_lock();
	fn = fib6_node_lookup(&table->tb6_root, &fl6->daddr, &fl6->saddr);
restart:
	क्रम_each_fib6_node_rt_rcu(fn) अणु
		res.f6i = rt;
		अगर (fib6_check_expired(rt))
			जारी;
		अगर (rt->fib6_flags & RTF_REJECT)
			अवरोध;
		अगर (unlikely(rt->nh)) अणु
			अगर (nexthop_is_blackhole(rt->nh))
				जारी;
			/* on match, res->nh is filled in and potentially ret */
			अगर (nexthop_क्रम_each_fib6_nh(rt->nh,
						     fib6_nh_redirect_match,
						     &arg))
				जाओ out;
		पूर्ण अन्यथा अणु
			res.nh = rt->fib6_nh;
			अगर (ip6_redirect_nh_match(&res, fl6, &rdfl->gateway,
						  &ret))
				जाओ out;
		पूर्ण
	पूर्ण

	अगर (!rt)
		rt = net->ipv6.fib6_null_entry;
	अन्यथा अगर (rt->fib6_flags & RTF_REJECT) अणु
		ret = net->ipv6.ip6_null_entry;
		जाओ out;
	पूर्ण

	अगर (rt == net->ipv6.fib6_null_entry) अणु
		fn = fib6_backtrack(fn, &fl6->saddr);
		अगर (fn)
			जाओ restart;
	पूर्ण

	res.f6i = rt;
	res.nh = rt->fib6_nh;
out:
	अगर (ret) अणु
		ip6_hold_safe(net, &ret);
	पूर्ण अन्यथा अणु
		res.fib6_flags = res.f6i->fib6_flags;
		res.fib6_type = res.f6i->fib6_type;
		ret = ip6_create_rt_rcu(&res);
	पूर्ण

	rcu_पढ़ो_unlock();

	trace_fib6_table_lookup(net, &res, table, fl6);
	वापस ret;
पूर्ण;

अटल काष्ठा dst_entry *ip6_route_redirect(काष्ठा net *net,
					    स्थिर काष्ठा flowi6 *fl6,
					    स्थिर काष्ठा sk_buff *skb,
					    स्थिर काष्ठा in6_addr *gateway)
अणु
	पूर्णांक flags = RT6_LOOKUP_F_HAS_SADDR;
	काष्ठा ip6rd_flowi rdfl;

	rdfl.fl6 = *fl6;
	rdfl.gateway = *gateway;

	वापस fib6_rule_lookup(net, &rdfl.fl6, skb,
				flags, __ip6_route_redirect);
पूर्ण

व्योम ip6_redirect(काष्ठा sk_buff *skb, काष्ठा net *net, पूर्णांक oअगर, u32 mark,
		  kuid_t uid)
अणु
	स्थिर काष्ठा ipv6hdr *iph = (काष्ठा ipv6hdr *) skb->data;
	काष्ठा dst_entry *dst;
	काष्ठा flowi6 fl6 = अणु
		.flowi6_iअगर = LOOPBACK_IFINDEX,
		.flowi6_oअगर = oअगर,
		.flowi6_mark = mark,
		.daddr = iph->daddr,
		.saddr = iph->saddr,
		.flowlabel = ip6_flowinfo(iph),
		.flowi6_uid = uid,
	पूर्ण;

	dst = ip6_route_redirect(net, &fl6, skb, &ipv6_hdr(skb)->saddr);
	rt6_करो_redirect(dst, शून्य, skb);
	dst_release(dst);
पूर्ण
EXPORT_SYMBOL_GPL(ip6_redirect);

व्योम ip6_redirect_no_header(काष्ठा sk_buff *skb, काष्ठा net *net, पूर्णांक oअगर)
अणु
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	स्थिर काष्ठा rd_msg *msg = (काष्ठा rd_msg *)icmp6_hdr(skb);
	काष्ठा dst_entry *dst;
	काष्ठा flowi6 fl6 = अणु
		.flowi6_iअगर = LOOPBACK_IFINDEX,
		.flowi6_oअगर = oअगर,
		.daddr = msg->dest,
		.saddr = iph->daddr,
		.flowi6_uid = sock_net_uid(net, शून्य),
	पूर्ण;

	dst = ip6_route_redirect(net, &fl6, skb, &iph->saddr);
	rt6_करो_redirect(dst, शून्य, skb);
	dst_release(dst);
पूर्ण

व्योम ip6_sk_redirect(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	ip6_redirect(skb, sock_net(sk), sk->sk_bound_dev_अगर, sk->sk_mark,
		     sk->sk_uid);
पूर्ण
EXPORT_SYMBOL_GPL(ip6_sk_redirect);

अटल अचिन्हित पूर्णांक ip6_शेष_advmss(स्थिर काष्ठा dst_entry *dst)
अणु
	काष्ठा net_device *dev = dst->dev;
	अचिन्हित पूर्णांक mtu = dst_mtu(dst);
	काष्ठा net *net = dev_net(dev);

	mtu -= माप(काष्ठा ipv6hdr) + माप(काष्ठा tcphdr);

	अगर (mtu < net->ipv6.sysctl.ip6_rt_min_advmss)
		mtu = net->ipv6.sysctl.ip6_rt_min_advmss;

	/*
	 * Maximal non-jumbo IPv6 payload is IPV6_MAXPLEN and
	 * corresponding MSS is IPV6_MAXPLEN - tcp_header_size.
	 * IPV6_MAXPLEN is also valid and means: "any MSS,
	 * rely only on pmtu discovery"
	 */
	अगर (mtu > IPV6_MAXPLEN - माप(काष्ठा tcphdr))
		mtu = IPV6_MAXPLEN;
	वापस mtu;
पूर्ण

INसूचीECT_CALLABLE_SCOPE अचिन्हित पूर्णांक ip6_mtu(स्थिर काष्ठा dst_entry *dst)
अणु
	काष्ठा inet6_dev *idev;
	अचिन्हित पूर्णांक mtu;

	mtu = dst_metric_raw(dst, RTAX_MTU);
	अगर (mtu)
		जाओ out;

	mtu = IPV6_MIN_MTU;

	rcu_पढ़ो_lock();
	idev = __in6_dev_get(dst->dev);
	अगर (idev)
		mtu = idev->cnf.mtu6;
	rcu_पढ़ो_unlock();

out:
	mtu = min_t(अचिन्हित पूर्णांक, mtu, IP6_MAX_MTU);

	वापस mtu - lwtunnel_headroom(dst->lwtstate, mtu);
पूर्ण
EXPORT_INसूचीECT_CALLABLE(ip6_mtu);

/* MTU selection:
 * 1. mtu on route is locked - use it
 * 2. mtu from nexthop exception
 * 3. mtu from egress device
 *
 * based on ip6_dst_mtu_क्रमward and exception logic of
 * rt6_find_cached_rt; called with rcu_पढ़ो_lock
 */
u32 ip6_mtu_from_fib6(स्थिर काष्ठा fib6_result *res,
		      स्थिर काष्ठा in6_addr *daddr,
		      स्थिर काष्ठा in6_addr *saddr)
अणु
	स्थिर काष्ठा fib6_nh *nh = res->nh;
	काष्ठा fib6_info *f6i = res->f6i;
	काष्ठा inet6_dev *idev;
	काष्ठा rt6_info *rt;
	u32 mtu = 0;

	अगर (unlikely(fib6_metric_locked(f6i, RTAX_MTU))) अणु
		mtu = f6i->fib6_pmtu;
		अगर (mtu)
			जाओ out;
	पूर्ण

	rt = rt6_find_cached_rt(res, daddr, saddr);
	अगर (unlikely(rt)) अणु
		mtu = dst_metric_raw(&rt->dst, RTAX_MTU);
	पूर्ण अन्यथा अणु
		काष्ठा net_device *dev = nh->fib_nh_dev;

		mtu = IPV6_MIN_MTU;
		idev = __in6_dev_get(dev);
		अगर (idev && idev->cnf.mtu6 > mtu)
			mtu = idev->cnf.mtu6;
	पूर्ण

	mtu = min_t(अचिन्हित पूर्णांक, mtu, IP6_MAX_MTU);
out:
	वापस mtu - lwtunnel_headroom(nh->fib_nh_lws, mtu);
पूर्ण

काष्ठा dst_entry *icmp6_dst_alloc(काष्ठा net_device *dev,
				  काष्ठा flowi6 *fl6)
अणु
	काष्ठा dst_entry *dst;
	काष्ठा rt6_info *rt;
	काष्ठा inet6_dev *idev = in6_dev_get(dev);
	काष्ठा net *net = dev_net(dev);

	अगर (unlikely(!idev))
		वापस ERR_PTR(-ENODEV);

	rt = ip6_dst_alloc(net, dev, 0);
	अगर (unlikely(!rt)) अणु
		in6_dev_put(idev);
		dst = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	rt->dst.input = ip6_input;
	rt->dst.output  = ip6_output;
	rt->rt6i_gateway  = fl6->daddr;
	rt->rt6i_dst.addr = fl6->daddr;
	rt->rt6i_dst.plen = 128;
	rt->rt6i_idev     = idev;
	dst_metric_set(&rt->dst, RTAX_HOPLIMIT, 0);

	/* Add this dst पूर्णांकo uncached_list so that rt6_disable_ip() can
	 * करो proper release of the net_device
	 */
	rt6_uncached_list_add(rt);
	atomic_inc(&net->ipv6.rt6_stats->fib_rt_uncache);

	dst = xfrm_lookup(net, &rt->dst, flowi6_to_flowi(fl6), शून्य, 0);

out:
	वापस dst;
पूर्ण

अटल पूर्णांक ip6_dst_gc(काष्ठा dst_ops *ops)
अणु
	काष्ठा net *net = container_of(ops, काष्ठा net, ipv6.ip6_dst_ops);
	पूर्णांक rt_min_पूर्णांकerval = net->ipv6.sysctl.ip6_rt_gc_min_पूर्णांकerval;
	पूर्णांक rt_max_size = net->ipv6.sysctl.ip6_rt_max_size;
	पूर्णांक rt_elasticity = net->ipv6.sysctl.ip6_rt_gc_elasticity;
	पूर्णांक rt_gc_समयout = net->ipv6.sysctl.ip6_rt_gc_समयout;
	अचिन्हित दीर्घ rt_last_gc = net->ipv6.ip6_rt_last_gc;
	पूर्णांक entries;

	entries = dst_entries_get_fast(ops);
	अगर (entries > rt_max_size)
		entries = dst_entries_get_slow(ops);

	अगर (समय_after(rt_last_gc + rt_min_पूर्णांकerval, jअगरfies) &&
	    entries <= rt_max_size)
		जाओ out;

	net->ipv6.ip6_rt_gc_expire++;
	fib6_run_gc(net->ipv6.ip6_rt_gc_expire, net, true);
	entries = dst_entries_get_slow(ops);
	अगर (entries < ops->gc_thresh)
		net->ipv6.ip6_rt_gc_expire = rt_gc_समयout>>1;
out:
	net->ipv6.ip6_rt_gc_expire -= net->ipv6.ip6_rt_gc_expire>>rt_elasticity;
	वापस entries > rt_max_size;
पूर्ण

अटल पूर्णांक ip6_nh_lookup_table(काष्ठा net *net, काष्ठा fib6_config *cfg,
			       स्थिर काष्ठा in6_addr *gw_addr, u32 tbid,
			       पूर्णांक flags, काष्ठा fib6_result *res)
अणु
	काष्ठा flowi6 fl6 = अणु
		.flowi6_oअगर = cfg->fc_अगरindex,
		.daddr = *gw_addr,
		.saddr = cfg->fc_prefsrc,
	पूर्ण;
	काष्ठा fib6_table *table;
	पूर्णांक err;

	table = fib6_get_table(net, tbid);
	अगर (!table)
		वापस -EINVAL;

	अगर (!ipv6_addr_any(&cfg->fc_prefsrc))
		flags |= RT6_LOOKUP_F_HAS_SADDR;

	flags |= RT6_LOOKUP_F_IGNORE_LINKSTATE;

	err = fib6_table_lookup(net, table, cfg->fc_अगरindex, &fl6, res, flags);
	अगर (!err && res->f6i != net->ipv6.fib6_null_entry)
		fib6_select_path(net, res, &fl6, cfg->fc_अगरindex,
				 cfg->fc_अगरindex != 0, शून्य, flags);

	वापस err;
पूर्ण

अटल पूर्णांक ip6_route_check_nh_onlink(काष्ठा net *net,
				     काष्ठा fib6_config *cfg,
				     स्थिर काष्ठा net_device *dev,
				     काष्ठा netlink_ext_ack *extack)
अणु
	u32 tbid = l3mdev_fib_table_rcu(dev) ? : RT_TABLE_MAIN;
	स्थिर काष्ठा in6_addr *gw_addr = &cfg->fc_gateway;
	काष्ठा fib6_result res = अणुपूर्ण;
	पूर्णांक err;

	err = ip6_nh_lookup_table(net, cfg, gw_addr, tbid, 0, &res);
	अगर (!err && !(res.fib6_flags & RTF_REJECT) &&
	    /* ignore match अगर it is the शेष route */
	    !ipv6_addr_any(&res.f6i->fib6_dst.addr) &&
	    (res.fib6_type != RTN_UNICAST || dev != res.nh->fib_nh_dev)) अणु
		NL_SET_ERR_MSG(extack,
			       "Nexthop has invalid gateway or device mismatch");
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ip6_route_check_nh(काष्ठा net *net,
			      काष्ठा fib6_config *cfg,
			      काष्ठा net_device **_dev,
			      काष्ठा inet6_dev **idev)
अणु
	स्थिर काष्ठा in6_addr *gw_addr = &cfg->fc_gateway;
	काष्ठा net_device *dev = _dev ? *_dev : शून्य;
	पूर्णांक flags = RT6_LOOKUP_F_IFACE;
	काष्ठा fib6_result res = अणुपूर्ण;
	पूर्णांक err = -EHOSTUNREACH;

	अगर (cfg->fc_table) अणु
		err = ip6_nh_lookup_table(net, cfg, gw_addr,
					  cfg->fc_table, flags, &res);
		/* gw_addr can not require a gateway or resolve to a reject
		 * route. If a device is given, it must match the result.
		 */
		अगर (err || res.fib6_flags & RTF_REJECT ||
		    res.nh->fib_nh_gw_family ||
		    (dev && dev != res.nh->fib_nh_dev))
			err = -EHOSTUNREACH;
	पूर्ण

	अगर (err < 0) अणु
		काष्ठा flowi6 fl6 = अणु
			.flowi6_oअगर = cfg->fc_अगरindex,
			.daddr = *gw_addr,
		पूर्ण;

		err = fib6_lookup(net, cfg->fc_अगरindex, &fl6, &res, flags);
		अगर (err || res.fib6_flags & RTF_REJECT ||
		    res.nh->fib_nh_gw_family)
			err = -EHOSTUNREACH;

		अगर (err)
			वापस err;

		fib6_select_path(net, &res, &fl6, cfg->fc_अगरindex,
				 cfg->fc_अगरindex != 0, शून्य, flags);
	पूर्ण

	err = 0;
	अगर (dev) अणु
		अगर (dev != res.nh->fib_nh_dev)
			err = -EHOSTUNREACH;
	पूर्ण अन्यथा अणु
		*_dev = dev = res.nh->fib_nh_dev;
		dev_hold(dev);
		*idev = in6_dev_get(dev);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ip6_validate_gw(काष्ठा net *net, काष्ठा fib6_config *cfg,
			   काष्ठा net_device **_dev, काष्ठा inet6_dev **idev,
			   काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा in6_addr *gw_addr = &cfg->fc_gateway;
	पूर्णांक gwa_type = ipv6_addr_type(gw_addr);
	bool skip_dev = gwa_type & IPV6_ADDR_LINKLOCAL ? false : true;
	स्थिर काष्ठा net_device *dev = *_dev;
	bool need_addr_check = !dev;
	पूर्णांक err = -EINVAL;

	/* अगर gw_addr is local we will fail to detect this in हाल
	 * address is still TENTATIVE (DAD in progress). rt6_lookup()
	 * will वापस alपढ़ोy-added prefix route via पूर्णांकerface that
	 * prefix route was asचिन्हित to, which might be non-loopback.
	 */
	अगर (dev &&
	    ipv6_chk_addr_and_flags(net, gw_addr, dev, skip_dev, 0, 0)) अणु
		NL_SET_ERR_MSG(extack, "Gateway can not be a local address");
		जाओ out;
	पूर्ण

	अगर (gwa_type != (IPV6_ADDR_LINKLOCAL | IPV6_ADDR_UNICAST)) अणु
		/* IPv6 strictly inhibits using not link-local
		 * addresses as nexthop address.
		 * Otherwise, router will not able to send redirects.
		 * It is very good, but in some (rare!) circumstances
		 * (SIT, PtP, NBMA NOARP links) it is handy to allow
		 * some exceptions. --ANK
		 * We allow IPv4-mapped nexthops to support RFC4798-type
		 * addressing
		 */
		अगर (!(gwa_type & (IPV6_ADDR_UNICAST | IPV6_ADDR_MAPPED))) अणु
			NL_SET_ERR_MSG(extack, "Invalid gateway address");
			जाओ out;
		पूर्ण

		rcu_पढ़ो_lock();

		अगर (cfg->fc_flags & RTNH_F_ONLINK)
			err = ip6_route_check_nh_onlink(net, cfg, dev, extack);
		अन्यथा
			err = ip6_route_check_nh(net, cfg, _dev, idev);

		rcu_पढ़ो_unlock();

		अगर (err)
			जाओ out;
	पूर्ण

	/* reload in हाल device was changed */
	dev = *_dev;

	err = -EINVAL;
	अगर (!dev) अणु
		NL_SET_ERR_MSG(extack, "Egress device not specified");
		जाओ out;
	पूर्ण अन्यथा अगर (dev->flags & IFF_LOOPBACK) अणु
		NL_SET_ERR_MSG(extack,
			       "Egress device can not be loopback device for this route");
		जाओ out;
	पूर्ण

	/* अगर we did not check gw_addr above, करो so now that the
	 * egress device has been resolved.
	 */
	अगर (need_addr_check &&
	    ipv6_chk_addr_and_flags(net, gw_addr, dev, skip_dev, 0, 0)) अणु
		NL_SET_ERR_MSG(extack, "Gateway can not be a local address");
		जाओ out;
	पूर्ण

	err = 0;
out:
	वापस err;
पूर्ण

अटल bool fib6_is_reject(u32 flags, काष्ठा net_device *dev, पूर्णांक addr_type)
अणु
	अगर ((flags & RTF_REJECT) ||
	    (dev && (dev->flags & IFF_LOOPBACK) &&
	     !(addr_type & IPV6_ADDR_LOOPBACK) &&
	     !(flags & (RTF_ANYCAST | RTF_LOCAL))))
		वापस true;

	वापस false;
पूर्ण

पूर्णांक fib6_nh_init(काष्ठा net *net, काष्ठा fib6_nh *fib6_nh,
		 काष्ठा fib6_config *cfg, gfp_t gfp_flags,
		 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev = शून्य;
	काष्ठा inet6_dev *idev = शून्य;
	पूर्णांक addr_type;
	पूर्णांक err;

	fib6_nh->fib_nh_family = AF_INET6;
#अगर_घोषित CONFIG_IPV6_ROUTER_PREF
	fib6_nh->last_probe = jअगरfies;
#पूर्ण_अगर
	अगर (cfg->fc_is_fdb) अणु
		fib6_nh->fib_nh_gw6 = cfg->fc_gateway;
		fib6_nh->fib_nh_gw_family = AF_INET6;
		वापस 0;
	पूर्ण

	err = -ENODEV;
	अगर (cfg->fc_अगरindex) अणु
		dev = dev_get_by_index(net, cfg->fc_अगरindex);
		अगर (!dev)
			जाओ out;
		idev = in6_dev_get(dev);
		अगर (!idev)
			जाओ out;
	पूर्ण

	अगर (cfg->fc_flags & RTNH_F_ONLINK) अणु
		अगर (!dev) अणु
			NL_SET_ERR_MSG(extack,
				       "Nexthop device required for onlink");
			जाओ out;
		पूर्ण

		अगर (!(dev->flags & IFF_UP)) अणु
			NL_SET_ERR_MSG(extack, "Nexthop device is not up");
			err = -ENETDOWN;
			जाओ out;
		पूर्ण

		fib6_nh->fib_nh_flags |= RTNH_F_ONLINK;
	पूर्ण

	fib6_nh->fib_nh_weight = 1;

	/* We cannot add true routes via loopback here,
	 * they would result in kernel looping; promote them to reject routes
	 */
	addr_type = ipv6_addr_type(&cfg->fc_dst);
	अगर (fib6_is_reject(cfg->fc_flags, dev, addr_type)) अणु
		/* hold loopback dev/idev अगर we haven't करोne so. */
		अगर (dev != net->loopback_dev) अणु
			अगर (dev) अणु
				dev_put(dev);
				in6_dev_put(idev);
			पूर्ण
			dev = net->loopback_dev;
			dev_hold(dev);
			idev = in6_dev_get(dev);
			अगर (!idev) अणु
				err = -ENODEV;
				जाओ out;
			पूर्ण
		पूर्ण
		जाओ pcpu_alloc;
	पूर्ण

	अगर (cfg->fc_flags & RTF_GATEWAY) अणु
		err = ip6_validate_gw(net, cfg, &dev, &idev, extack);
		अगर (err)
			जाओ out;

		fib6_nh->fib_nh_gw6 = cfg->fc_gateway;
		fib6_nh->fib_nh_gw_family = AF_INET6;
	पूर्ण

	err = -ENODEV;
	अगर (!dev)
		जाओ out;

	अगर (idev->cnf.disable_ipv6) अणु
		NL_SET_ERR_MSG(extack, "IPv6 is disabled on nexthop device");
		err = -EACCES;
		जाओ out;
	पूर्ण

	अगर (!(dev->flags & IFF_UP) && !cfg->fc_ignore_dev_करोwn) अणु
		NL_SET_ERR_MSG(extack, "Nexthop device is not up");
		err = -ENETDOWN;
		जाओ out;
	पूर्ण

	अगर (!(cfg->fc_flags & (RTF_LOCAL | RTF_ANYCAST)) &&
	    !netअगर_carrier_ok(dev))
		fib6_nh->fib_nh_flags |= RTNH_F_LINKDOWN;

	err = fib_nh_common_init(net, &fib6_nh->nh_common, cfg->fc_encap,
				 cfg->fc_encap_type, cfg, gfp_flags, extack);
	अगर (err)
		जाओ out;

pcpu_alloc:
	fib6_nh->rt6i_pcpu = alloc_percpu_gfp(काष्ठा rt6_info *, gfp_flags);
	अगर (!fib6_nh->rt6i_pcpu) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	fib6_nh->fib_nh_dev = dev;
	fib6_nh->fib_nh_oअगर = dev->अगरindex;
	err = 0;
out:
	अगर (idev)
		in6_dev_put(idev);

	अगर (err) अणु
		lwtstate_put(fib6_nh->fib_nh_lws);
		fib6_nh->fib_nh_lws = शून्य;
		अगर (dev)
			dev_put(dev);
	पूर्ण

	वापस err;
पूर्ण

व्योम fib6_nh_release(काष्ठा fib6_nh *fib6_nh)
अणु
	काष्ठा rt6_exception_bucket *bucket;

	rcu_पढ़ो_lock();

	fib6_nh_flush_exceptions(fib6_nh, शून्य);
	bucket = fib6_nh_get_excptn_bucket(fib6_nh, शून्य);
	अगर (bucket) अणु
		rcu_assign_poपूर्णांकer(fib6_nh->rt6i_exception_bucket, शून्य);
		kमुक्त(bucket);
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (fib6_nh->rt6i_pcpu) अणु
		पूर्णांक cpu;

		क्रम_each_possible_cpu(cpu) अणु
			काष्ठा rt6_info **ppcpu_rt;
			काष्ठा rt6_info *pcpu_rt;

			ppcpu_rt = per_cpu_ptr(fib6_nh->rt6i_pcpu, cpu);
			pcpu_rt = *ppcpu_rt;
			अगर (pcpu_rt) अणु
				dst_dev_put(&pcpu_rt->dst);
				dst_release(&pcpu_rt->dst);
				*ppcpu_rt = शून्य;
			पूर्ण
		पूर्ण

		मुक्त_percpu(fib6_nh->rt6i_pcpu);
	पूर्ण

	fib_nh_common_release(&fib6_nh->nh_common);
पूर्ण

अटल काष्ठा fib6_info *ip6_route_info_create(काष्ठा fib6_config *cfg,
					      gfp_t gfp_flags,
					      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = cfg->fc_nlinfo.nl_net;
	काष्ठा fib6_info *rt = शून्य;
	काष्ठा nexthop *nh = शून्य;
	काष्ठा fib6_table *table;
	काष्ठा fib6_nh *fib6_nh;
	पूर्णांक err = -EINVAL;
	पूर्णांक addr_type;

	/* RTF_PCPU is an पूर्णांकernal flag; can not be set by userspace */
	अगर (cfg->fc_flags & RTF_PCPU) अणु
		NL_SET_ERR_MSG(extack, "Userspace can not set RTF_PCPU");
		जाओ out;
	पूर्ण

	/* RTF_CACHE is an पूर्णांकernal flag; can not be set by userspace */
	अगर (cfg->fc_flags & RTF_CACHE) अणु
		NL_SET_ERR_MSG(extack, "Userspace can not set RTF_CACHE");
		जाओ out;
	पूर्ण

	अगर (cfg->fc_type > RTN_MAX) अणु
		NL_SET_ERR_MSG(extack, "Invalid route type");
		जाओ out;
	पूर्ण

	अगर (cfg->fc_dst_len > 128) अणु
		NL_SET_ERR_MSG(extack, "Invalid prefix length");
		जाओ out;
	पूर्ण
	अगर (cfg->fc_src_len > 128) अणु
		NL_SET_ERR_MSG(extack, "Invalid source address length");
		जाओ out;
	पूर्ण
#अगर_अघोषित CONFIG_IPV6_SUBTREES
	अगर (cfg->fc_src_len) अणु
		NL_SET_ERR_MSG(extack,
			       "Specifying source address requires IPV6_SUBTREES to be enabled");
		जाओ out;
	पूर्ण
#पूर्ण_अगर
	अगर (cfg->fc_nh_id) अणु
		nh = nexthop_find_by_id(net, cfg->fc_nh_id);
		अगर (!nh) अणु
			NL_SET_ERR_MSG(extack, "Nexthop id does not exist");
			जाओ out;
		पूर्ण
		err = fib6_check_nexthop(nh, cfg, extack);
		अगर (err)
			जाओ out;
	पूर्ण

	err = -ENOBUFS;
	अगर (cfg->fc_nlinfo.nlh &&
	    !(cfg->fc_nlinfo.nlh->nlmsg_flags & NLM_F_CREATE)) अणु
		table = fib6_get_table(net, cfg->fc_table);
		अगर (!table) अणु
			pr_warn("NLM_F_CREATE should be specified when creating new route\n");
			table = fib6_new_table(net, cfg->fc_table);
		पूर्ण
	पूर्ण अन्यथा अणु
		table = fib6_new_table(net, cfg->fc_table);
	पूर्ण

	अगर (!table)
		जाओ out;

	err = -ENOMEM;
	rt = fib6_info_alloc(gfp_flags, !nh);
	अगर (!rt)
		जाओ out;

	rt->fib6_metrics = ip_fib_metrics_init(net, cfg->fc_mx, cfg->fc_mx_len,
					       extack);
	अगर (IS_ERR(rt->fib6_metrics)) अणु
		err = PTR_ERR(rt->fib6_metrics);
		/* Do not leave garbage there. */
		rt->fib6_metrics = (काष्ठा dst_metrics *)&dst_शेष_metrics;
		जाओ out;
	पूर्ण

	अगर (cfg->fc_flags & RTF_ADDRCONF)
		rt->dst_nocount = true;

	अगर (cfg->fc_flags & RTF_EXPIRES)
		fib6_set_expires(rt, jअगरfies +
				घड़ी_प्रकार_to_jअगरfies(cfg->fc_expires));
	अन्यथा
		fib6_clean_expires(rt);

	अगर (cfg->fc_protocol == RTPROT_UNSPEC)
		cfg->fc_protocol = RTPROT_BOOT;
	rt->fib6_protocol = cfg->fc_protocol;

	rt->fib6_table = table;
	rt->fib6_metric = cfg->fc_metric;
	rt->fib6_type = cfg->fc_type ? : RTN_UNICAST;
	rt->fib6_flags = cfg->fc_flags & ~RTF_GATEWAY;

	ipv6_addr_prefix(&rt->fib6_dst.addr, &cfg->fc_dst, cfg->fc_dst_len);
	rt->fib6_dst.plen = cfg->fc_dst_len;

#अगर_घोषित CONFIG_IPV6_SUBTREES
	ipv6_addr_prefix(&rt->fib6_src.addr, &cfg->fc_src, cfg->fc_src_len);
	rt->fib6_src.plen = cfg->fc_src_len;
#पूर्ण_अगर
	अगर (nh) अणु
		अगर (rt->fib6_src.plen) अणु
			NL_SET_ERR_MSG(extack, "Nexthops can not be used with source routing");
			जाओ out_मुक्त;
		पूर्ण
		अगर (!nexthop_get(nh)) अणु
			NL_SET_ERR_MSG(extack, "Nexthop has been deleted");
			जाओ out_मुक्त;
		पूर्ण
		rt->nh = nh;
		fib6_nh = nexthop_fib6_nh(rt->nh);
	पूर्ण अन्यथा अणु
		err = fib6_nh_init(net, rt->fib6_nh, cfg, gfp_flags, extack);
		अगर (err)
			जाओ out;

		fib6_nh = rt->fib6_nh;

		/* We cannot add true routes via loopback here, they would
		 * result in kernel looping; promote them to reject routes
		 */
		addr_type = ipv6_addr_type(&cfg->fc_dst);
		अगर (fib6_is_reject(cfg->fc_flags, rt->fib6_nh->fib_nh_dev,
				   addr_type))
			rt->fib6_flags = RTF_REJECT | RTF_NONEXTHOP;
	पूर्ण

	अगर (!ipv6_addr_any(&cfg->fc_prefsrc)) अणु
		काष्ठा net_device *dev = fib6_nh->fib_nh_dev;

		अगर (!ipv6_chk_addr(net, &cfg->fc_prefsrc, dev, 0)) अणु
			NL_SET_ERR_MSG(extack, "Invalid source address");
			err = -EINVAL;
			जाओ out;
		पूर्ण
		rt->fib6_prefsrc.addr = cfg->fc_prefsrc;
		rt->fib6_prefsrc.plen = 128;
	पूर्ण अन्यथा
		rt->fib6_prefsrc.plen = 0;

	वापस rt;
out:
	fib6_info_release(rt);
	वापस ERR_PTR(err);
out_मुक्त:
	ip_fib_metrics_put(rt->fib6_metrics);
	kमुक्त(rt);
	वापस ERR_PTR(err);
पूर्ण

पूर्णांक ip6_route_add(काष्ठा fib6_config *cfg, gfp_t gfp_flags,
		  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib6_info *rt;
	पूर्णांक err;

	rt = ip6_route_info_create(cfg, gfp_flags, extack);
	अगर (IS_ERR(rt))
		वापस PTR_ERR(rt);

	err = __ip6_ins_rt(rt, &cfg->fc_nlinfo, extack);
	fib6_info_release(rt);

	वापस err;
पूर्ण

अटल पूर्णांक __ip6_del_rt(काष्ठा fib6_info *rt, काष्ठा nl_info *info)
अणु
	काष्ठा net *net = info->nl_net;
	काष्ठा fib6_table *table;
	पूर्णांक err;

	अगर (rt == net->ipv6.fib6_null_entry) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	table = rt->fib6_table;
	spin_lock_bh(&table->tb6_lock);
	err = fib6_del(rt, info);
	spin_unlock_bh(&table->tb6_lock);

out:
	fib6_info_release(rt);
	वापस err;
पूर्ण

पूर्णांक ip6_del_rt(काष्ठा net *net, काष्ठा fib6_info *rt, bool skip_notअगरy)
अणु
	काष्ठा nl_info info = अणु
		.nl_net = net,
		.skip_notअगरy = skip_notअगरy
	पूर्ण;

	वापस __ip6_del_rt(rt, &info);
पूर्ण

अटल पूर्णांक __ip6_del_rt_siblings(काष्ठा fib6_info *rt, काष्ठा fib6_config *cfg)
अणु
	काष्ठा nl_info *info = &cfg->fc_nlinfo;
	काष्ठा net *net = info->nl_net;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा fib6_table *table;
	पूर्णांक err = -ENOENT;

	अगर (rt == net->ipv6.fib6_null_entry)
		जाओ out_put;
	table = rt->fib6_table;
	spin_lock_bh(&table->tb6_lock);

	अगर (rt->fib6_nsiblings && cfg->fc_delete_all_nh) अणु
		काष्ठा fib6_info *sibling, *next_sibling;
		काष्ठा fib6_node *fn;

		/* prefer to send a single notअगरication with all hops */
		skb = nlmsg_new(rt6_nlmsg_size(rt), gfp_any());
		अगर (skb) अणु
			u32 seq = info->nlh ? info->nlh->nlmsg_seq : 0;

			अगर (rt6_fill_node(net, skb, rt, शून्य,
					  शून्य, शून्य, 0, RTM_DELROUTE,
					  info->portid, seq, 0) < 0) अणु
				kमुक्त_skb(skb);
				skb = शून्य;
			पूर्ण अन्यथा
				info->skip_notअगरy = 1;
		पूर्ण

		/* 'rt' poपूर्णांकs to the first sibling route. If it is not the
		 * leaf, then we करो not need to send a notअगरication. Otherwise,
		 * we need to check अगर the last sibling has a next route or not
		 * and emit a replace or delete notअगरication, respectively.
		 */
		info->skip_notअगरy_kernel = 1;
		fn = rcu_dereference_रक्षित(rt->fib6_node,
					    lockdep_is_held(&table->tb6_lock));
		अगर (rcu_access_poपूर्णांकer(fn->leaf) == rt) अणु
			काष्ठा fib6_info *last_sibling, *replace_rt;

			last_sibling = list_last_entry(&rt->fib6_siblings,
						       काष्ठा fib6_info,
						       fib6_siblings);
			replace_rt = rcu_dereference_रक्षित(
					    last_sibling->fib6_next,
					    lockdep_is_held(&table->tb6_lock));
			अगर (replace_rt)
				call_fib6_entry_notअगरiers_replace(net,
								  replace_rt);
			अन्यथा
				call_fib6_multipath_entry_notअगरiers(net,
						       FIB_EVENT_ENTRY_DEL,
						       rt, rt->fib6_nsiblings,
						       शून्य);
		पूर्ण
		list_क्रम_each_entry_safe(sibling, next_sibling,
					 &rt->fib6_siblings,
					 fib6_siblings) अणु
			err = fib6_del(sibling, info);
			अगर (err)
				जाओ out_unlock;
		पूर्ण
	पूर्ण

	err = fib6_del(rt, info);
out_unlock:
	spin_unlock_bh(&table->tb6_lock);
out_put:
	fib6_info_release(rt);

	अगर (skb) अणु
		rtnl_notअगरy(skb, net, info->portid, RTNLGRP_IPV6_ROUTE,
			    info->nlh, gfp_any());
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __ip6_del_cached_rt(काष्ठा rt6_info *rt, काष्ठा fib6_config *cfg)
अणु
	पूर्णांक rc = -ESRCH;

	अगर (cfg->fc_अगरindex && rt->dst.dev->अगरindex != cfg->fc_अगरindex)
		जाओ out;

	अगर (cfg->fc_flags & RTF_GATEWAY &&
	    !ipv6_addr_equal(&cfg->fc_gateway, &rt->rt6i_gateway))
		जाओ out;

	rc = rt6_हटाओ_exception_rt(rt);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक ip6_del_cached_rt(काष्ठा fib6_config *cfg, काष्ठा fib6_info *rt,
			     काष्ठा fib6_nh *nh)
अणु
	काष्ठा fib6_result res = अणु
		.f6i = rt,
		.nh = nh,
	पूर्ण;
	काष्ठा rt6_info *rt_cache;

	rt_cache = rt6_find_cached_rt(&res, &cfg->fc_dst, &cfg->fc_src);
	अगर (rt_cache)
		वापस __ip6_del_cached_rt(rt_cache, cfg);

	वापस 0;
पूर्ण

काष्ठा fib6_nh_del_cached_rt_arg अणु
	काष्ठा fib6_config *cfg;
	काष्ठा fib6_info *f6i;
पूर्ण;

अटल पूर्णांक fib6_nh_del_cached_rt(काष्ठा fib6_nh *nh, व्योम *_arg)
अणु
	काष्ठा fib6_nh_del_cached_rt_arg *arg = _arg;
	पूर्णांक rc;

	rc = ip6_del_cached_rt(arg->cfg, arg->f6i, nh);
	वापस rc != -ESRCH ? rc : 0;
पूर्ण

अटल पूर्णांक ip6_del_cached_rt_nh(काष्ठा fib6_config *cfg, काष्ठा fib6_info *f6i)
अणु
	काष्ठा fib6_nh_del_cached_rt_arg arg = अणु
		.cfg = cfg,
		.f6i = f6i
	पूर्ण;

	वापस nexthop_क्रम_each_fib6_nh(f6i->nh, fib6_nh_del_cached_rt, &arg);
पूर्ण

अटल पूर्णांक ip6_route_del(काष्ठा fib6_config *cfg,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib6_table *table;
	काष्ठा fib6_info *rt;
	काष्ठा fib6_node *fn;
	पूर्णांक err = -ESRCH;

	table = fib6_get_table(cfg->fc_nlinfo.nl_net, cfg->fc_table);
	अगर (!table) अणु
		NL_SET_ERR_MSG(extack, "FIB table does not exist");
		वापस err;
	पूर्ण

	rcu_पढ़ो_lock();

	fn = fib6_locate(&table->tb6_root,
			 &cfg->fc_dst, cfg->fc_dst_len,
			 &cfg->fc_src, cfg->fc_src_len,
			 !(cfg->fc_flags & RTF_CACHE));

	अगर (fn) अणु
		क्रम_each_fib6_node_rt_rcu(fn) अणु
			काष्ठा fib6_nh *nh;

			अगर (rt->nh && cfg->fc_nh_id &&
			    rt->nh->id != cfg->fc_nh_id)
				जारी;

			अगर (cfg->fc_flags & RTF_CACHE) अणु
				पूर्णांक rc = 0;

				अगर (rt->nh) अणु
					rc = ip6_del_cached_rt_nh(cfg, rt);
				पूर्ण अन्यथा अगर (cfg->fc_nh_id) अणु
					जारी;
				पूर्ण अन्यथा अणु
					nh = rt->fib6_nh;
					rc = ip6_del_cached_rt(cfg, rt, nh);
				पूर्ण
				अगर (rc != -ESRCH) अणु
					rcu_पढ़ो_unlock();
					वापस rc;
				पूर्ण
				जारी;
			पूर्ण

			अगर (cfg->fc_metric && cfg->fc_metric != rt->fib6_metric)
				जारी;
			अगर (cfg->fc_protocol &&
			    cfg->fc_protocol != rt->fib6_protocol)
				जारी;

			अगर (rt->nh) अणु
				अगर (!fib6_info_hold_safe(rt))
					जारी;
				rcu_पढ़ो_unlock();

				वापस __ip6_del_rt(rt, &cfg->fc_nlinfo);
			पूर्ण
			अगर (cfg->fc_nh_id)
				जारी;

			nh = rt->fib6_nh;
			अगर (cfg->fc_अगरindex &&
			    (!nh->fib_nh_dev ||
			     nh->fib_nh_dev->अगरindex != cfg->fc_अगरindex))
				जारी;
			अगर (cfg->fc_flags & RTF_GATEWAY &&
			    !ipv6_addr_equal(&cfg->fc_gateway, &nh->fib_nh_gw6))
				जारी;
			अगर (!fib6_info_hold_safe(rt))
				जारी;
			rcu_पढ़ो_unlock();

			/* अगर gateway was specअगरied only delete the one hop */
			अगर (cfg->fc_flags & RTF_GATEWAY)
				वापस __ip6_del_rt(rt, &cfg->fc_nlinfo);

			वापस __ip6_del_rt_siblings(rt, cfg);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

अटल व्योम rt6_करो_redirect(काष्ठा dst_entry *dst, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा netevent_redirect netevent;
	काष्ठा rt6_info *rt, *nrt = शून्य;
	काष्ठा fib6_result res = अणुपूर्ण;
	काष्ठा ndisc_options nकरोpts;
	काष्ठा inet6_dev *in6_dev;
	काष्ठा neighbour *neigh;
	काष्ठा rd_msg *msg;
	पूर्णांक optlen, on_link;
	u8 *lladdr;

	optlen = skb_tail_poपूर्णांकer(skb) - skb_transport_header(skb);
	optlen -= माप(*msg);

	अगर (optlen < 0) अणु
		net_dbg_ratelimited("rt6_do_redirect: packet too short\n");
		वापस;
	पूर्ण

	msg = (काष्ठा rd_msg *)icmp6_hdr(skb);

	अगर (ipv6_addr_is_multicast(&msg->dest)) अणु
		net_dbg_ratelimited("rt6_do_redirect: destination address is multicast\n");
		वापस;
	पूर्ण

	on_link = 0;
	अगर (ipv6_addr_equal(&msg->dest, &msg->target)) अणु
		on_link = 1;
	पूर्ण अन्यथा अगर (ipv6_addr_type(&msg->target) !=
		   (IPV6_ADDR_UNICAST|IPV6_ADDR_LINKLOCAL)) अणु
		net_dbg_ratelimited("rt6_do_redirect: target address is not link-local unicast\n");
		वापस;
	पूर्ण

	in6_dev = __in6_dev_get(skb->dev);
	अगर (!in6_dev)
		वापस;
	अगर (in6_dev->cnf.क्रमwarding || !in6_dev->cnf.accept_redirects)
		वापस;

	/* RFC2461 8.1:
	 *	The IP source address of the Redirect MUST be the same as the current
	 *	first-hop router क्रम the specअगरied ICMP Destination Address.
	 */

	अगर (!ndisc_parse_options(skb->dev, msg->opt, optlen, &nकरोpts)) अणु
		net_dbg_ratelimited("rt6_redirect: invalid ND options\n");
		वापस;
	पूर्ण

	lladdr = शून्य;
	अगर (nकरोpts.nd_opts_tgt_lladdr) अणु
		lladdr = ndisc_opt_addr_data(nकरोpts.nd_opts_tgt_lladdr,
					     skb->dev);
		अगर (!lladdr) अणु
			net_dbg_ratelimited("rt6_redirect: invalid link-layer address length\n");
			वापस;
		पूर्ण
	पूर्ण

	rt = (काष्ठा rt6_info *) dst;
	अगर (rt->rt6i_flags & RTF_REJECT) अणु
		net_dbg_ratelimited("rt6_redirect: source isn't a valid nexthop for redirect target\n");
		वापस;
	पूर्ण

	/* Redirect received -> path was valid.
	 * Look, redirects are sent only in response to data packets,
	 * so that this nexthop apparently is reachable. --ANK
	 */
	dst_confirm_neigh(&rt->dst, &ipv6_hdr(skb)->saddr);

	neigh = __neigh_lookup(&nd_tbl, &msg->target, skb->dev, 1);
	अगर (!neigh)
		वापस;

	/*
	 *	We have finally decided to accept it.
	 */

	ndisc_update(skb->dev, neigh, lladdr, NUD_STALE,
		     NEIGH_UPDATE_F_WEAK_OVERRIDE|
		     NEIGH_UPDATE_F_OVERRIDE|
		     (on_link ? 0 : (NEIGH_UPDATE_F_OVERRIDE_ISROUTER|
				     NEIGH_UPDATE_F_ISROUTER)),
		     NDISC_REसूचीECT, &nकरोpts);

	rcu_पढ़ो_lock();
	res.f6i = rcu_dereference(rt->from);
	अगर (!res.f6i)
		जाओ out;

	अगर (res.f6i->nh) अणु
		काष्ठा fib6_nh_match_arg arg = अणु
			.dev = dst->dev,
			.gw = &rt->rt6i_gateway,
		पूर्ण;

		nexthop_क्रम_each_fib6_nh(res.f6i->nh,
					 fib6_nh_find_match, &arg);

		/* fib6_info uses a nexthop that करोes not have fib6_nh
		 * using the dst->dev. Should be impossible
		 */
		अगर (!arg.match)
			जाओ out;
		res.nh = arg.match;
	पूर्ण अन्यथा अणु
		res.nh = res.f6i->fib6_nh;
	पूर्ण

	res.fib6_flags = res.f6i->fib6_flags;
	res.fib6_type = res.f6i->fib6_type;
	nrt = ip6_rt_cache_alloc(&res, &msg->dest, शून्य);
	अगर (!nrt)
		जाओ out;

	nrt->rt6i_flags = RTF_GATEWAY|RTF_UP|RTF_DYNAMIC|RTF_CACHE;
	अगर (on_link)
		nrt->rt6i_flags &= ~RTF_GATEWAY;

	nrt->rt6i_gateway = *(काष्ठा in6_addr *)neigh->primary_key;

	/* rt6_insert_exception() will take care of duplicated exceptions */
	अगर (rt6_insert_exception(nrt, &res)) अणु
		dst_release_immediate(&nrt->dst);
		जाओ out;
	पूर्ण

	netevent.old = &rt->dst;
	netevent.new = &nrt->dst;
	netevent.daddr = &msg->dest;
	netevent.neigh = neigh;
	call_netevent_notअगरiers(NETEVENT_REसूचीECT, &netevent);

out:
	rcu_पढ़ो_unlock();
	neigh_release(neigh);
पूर्ण

#अगर_घोषित CONFIG_IPV6_ROUTE_INFO
अटल काष्ठा fib6_info *rt6_get_route_info(काष्ठा net *net,
					   स्थिर काष्ठा in6_addr *prefix, पूर्णांक prefixlen,
					   स्थिर काष्ठा in6_addr *gwaddr,
					   काष्ठा net_device *dev)
अणु
	u32 tb_id = l3mdev_fib_table(dev) ? : RT6_TABLE_INFO;
	पूर्णांक अगरindex = dev->अगरindex;
	काष्ठा fib6_node *fn;
	काष्ठा fib6_info *rt = शून्य;
	काष्ठा fib6_table *table;

	table = fib6_get_table(net, tb_id);
	अगर (!table)
		वापस शून्य;

	rcu_पढ़ो_lock();
	fn = fib6_locate(&table->tb6_root, prefix, prefixlen, शून्य, 0, true);
	अगर (!fn)
		जाओ out;

	क्रम_each_fib6_node_rt_rcu(fn) अणु
		/* these routes करो not use nexthops */
		अगर (rt->nh)
			जारी;
		अगर (rt->fib6_nh->fib_nh_dev->अगरindex != अगरindex)
			जारी;
		अगर (!(rt->fib6_flags & RTF_ROUTEINFO) ||
		    !rt->fib6_nh->fib_nh_gw_family)
			जारी;
		अगर (!ipv6_addr_equal(&rt->fib6_nh->fib_nh_gw6, gwaddr))
			जारी;
		अगर (!fib6_info_hold_safe(rt))
			जारी;
		अवरोध;
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस rt;
पूर्ण

अटल काष्ठा fib6_info *rt6_add_route_info(काष्ठा net *net,
					   स्थिर काष्ठा in6_addr *prefix, पूर्णांक prefixlen,
					   स्थिर काष्ठा in6_addr *gwaddr,
					   काष्ठा net_device *dev,
					   अचिन्हित पूर्णांक pref)
अणु
	काष्ठा fib6_config cfg = अणु
		.fc_metric	= IP6_RT_PRIO_USER,
		.fc_अगरindex	= dev->अगरindex,
		.fc_dst_len	= prefixlen,
		.fc_flags	= RTF_GATEWAY | RTF_ADDRCONF | RTF_ROUTEINFO |
				  RTF_UP | RTF_PREF(pref),
		.fc_protocol = RTPROT_RA,
		.fc_type = RTN_UNICAST,
		.fc_nlinfo.portid = 0,
		.fc_nlinfo.nlh = शून्य,
		.fc_nlinfo.nl_net = net,
	पूर्ण;

	cfg.fc_table = l3mdev_fib_table(dev) ? : RT6_TABLE_INFO;
	cfg.fc_dst = *prefix;
	cfg.fc_gateway = *gwaddr;

	/* We should treat it as a शेष route अगर prefix length is 0. */
	अगर (!prefixlen)
		cfg.fc_flags |= RTF_DEFAULT;

	ip6_route_add(&cfg, GFP_ATOMIC, शून्य);

	वापस rt6_get_route_info(net, prefix, prefixlen, gwaddr, dev);
पूर्ण
#पूर्ण_अगर

काष्ठा fib6_info *rt6_get_dflt_router(काष्ठा net *net,
				     स्थिर काष्ठा in6_addr *addr,
				     काष्ठा net_device *dev)
अणु
	u32 tb_id = l3mdev_fib_table(dev) ? : RT6_TABLE_DFLT;
	काष्ठा fib6_info *rt;
	काष्ठा fib6_table *table;

	table = fib6_get_table(net, tb_id);
	अगर (!table)
		वापस शून्य;

	rcu_पढ़ो_lock();
	क्रम_each_fib6_node_rt_rcu(&table->tb6_root) अणु
		काष्ठा fib6_nh *nh;

		/* RA routes करो not use nexthops */
		अगर (rt->nh)
			जारी;

		nh = rt->fib6_nh;
		अगर (dev == nh->fib_nh_dev &&
		    ((rt->fib6_flags & (RTF_ADDRCONF | RTF_DEFAULT)) == (RTF_ADDRCONF | RTF_DEFAULT)) &&
		    ipv6_addr_equal(&nh->fib_nh_gw6, addr))
			अवरोध;
	पूर्ण
	अगर (rt && !fib6_info_hold_safe(rt))
		rt = शून्य;
	rcu_पढ़ो_unlock();
	वापस rt;
पूर्ण

काष्ठा fib6_info *rt6_add_dflt_router(काष्ठा net *net,
				     स्थिर काष्ठा in6_addr *gwaddr,
				     काष्ठा net_device *dev,
				     अचिन्हित पूर्णांक pref,
				     u32 defrtr_usr_metric)
अणु
	काष्ठा fib6_config cfg = अणु
		.fc_table	= l3mdev_fib_table(dev) ? : RT6_TABLE_DFLT,
		.fc_metric	= defrtr_usr_metric,
		.fc_अगरindex	= dev->अगरindex,
		.fc_flags	= RTF_GATEWAY | RTF_ADDRCONF | RTF_DEFAULT |
				  RTF_UP | RTF_EXPIRES | RTF_PREF(pref),
		.fc_protocol = RTPROT_RA,
		.fc_type = RTN_UNICAST,
		.fc_nlinfo.portid = 0,
		.fc_nlinfo.nlh = शून्य,
		.fc_nlinfo.nl_net = net,
	पूर्ण;

	cfg.fc_gateway = *gwaddr;

	अगर (!ip6_route_add(&cfg, GFP_ATOMIC, शून्य)) अणु
		काष्ठा fib6_table *table;

		table = fib6_get_table(dev_net(dev), cfg.fc_table);
		अगर (table)
			table->flags |= RT6_TABLE_HAS_DFLT_ROUTER;
	पूर्ण

	वापस rt6_get_dflt_router(net, gwaddr, dev);
पूर्ण

अटल व्योम __rt6_purge_dflt_routers(काष्ठा net *net,
				     काष्ठा fib6_table *table)
अणु
	काष्ठा fib6_info *rt;

restart:
	rcu_पढ़ो_lock();
	क्रम_each_fib6_node_rt_rcu(&table->tb6_root) अणु
		काष्ठा net_device *dev = fib6_info_nh_dev(rt);
		काष्ठा inet6_dev *idev = dev ? __in6_dev_get(dev) : शून्य;

		अगर (rt->fib6_flags & (RTF_DEFAULT | RTF_ADDRCONF) &&
		    (!idev || idev->cnf.accept_ra != 2) &&
		    fib6_info_hold_safe(rt)) अणु
			rcu_पढ़ो_unlock();
			ip6_del_rt(net, rt, false);
			जाओ restart;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	table->flags &= ~RT6_TABLE_HAS_DFLT_ROUTER;
पूर्ण

व्योम rt6_purge_dflt_routers(काष्ठा net *net)
अणु
	काष्ठा fib6_table *table;
	काष्ठा hlist_head *head;
	अचिन्हित पूर्णांक h;

	rcu_पढ़ो_lock();

	क्रम (h = 0; h < FIB6_TABLE_HASHSZ; h++) अणु
		head = &net->ipv6.fib_table_hash[h];
		hlist_क्रम_each_entry_rcu(table, head, tb6_hlist) अणु
			अगर (table->flags & RT6_TABLE_HAS_DFLT_ROUTER)
				__rt6_purge_dflt_routers(net, table);
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम rपंचांगsg_to_fib6_config(काष्ठा net *net,
				 काष्ठा in6_rपंचांगsg *rपंचांगsg,
				 काष्ठा fib6_config *cfg)
अणु
	*cfg = (काष्ठा fib6_config)अणु
		.fc_table = l3mdev_fib_table_by_index(net, rपंचांगsg->rपंचांगsg_अगरindex) ?
			 : RT6_TABLE_MAIN,
		.fc_अगरindex = rपंचांगsg->rपंचांगsg_अगरindex,
		.fc_metric = rपंचांगsg->rपंचांगsg_metric ? : IP6_RT_PRIO_USER,
		.fc_expires = rपंचांगsg->rपंचांगsg_info,
		.fc_dst_len = rपंचांगsg->rपंचांगsg_dst_len,
		.fc_src_len = rपंचांगsg->rपंचांगsg_src_len,
		.fc_flags = rपंचांगsg->rपंचांगsg_flags,
		.fc_type = rपंचांगsg->rपंचांगsg_type,

		.fc_nlinfo.nl_net = net,

		.fc_dst = rपंचांगsg->rपंचांगsg_dst,
		.fc_src = rपंचांगsg->rपंचांगsg_src,
		.fc_gateway = rपंचांगsg->rपंचांगsg_gateway,
	पूर्ण;
पूर्ण

पूर्णांक ipv6_route_ioctl(काष्ठा net *net, अचिन्हित पूर्णांक cmd, काष्ठा in6_rपंचांगsg *rपंचांगsg)
अणु
	काष्ठा fib6_config cfg;
	पूर्णांक err;

	अगर (cmd != SIOCADDRT && cmd != SIOCDELRT)
		वापस -EINVAL;
	अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	rपंचांगsg_to_fib6_config(net, rपंचांगsg, &cfg);

	rtnl_lock();
	चयन (cmd) अणु
	हाल SIOCADDRT:
		err = ip6_route_add(&cfg, GFP_KERNEL, शून्य);
		अवरोध;
	हाल SIOCDELRT:
		err = ip6_route_del(&cfg, शून्य);
		अवरोध;
	पूर्ण
	rtnl_unlock();
	वापस err;
पूर्ण

/*
 *	Drop the packet on the न्यूनमान
 */

अटल पूर्णांक ip6_pkt_drop(काष्ठा sk_buff *skb, u8 code, पूर्णांक ipstats_mib_noroutes)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा net *net = dev_net(dst->dev);
	काष्ठा inet6_dev *idev;
	पूर्णांक type;

	अगर (netअगर_is_l3_master(skb->dev) &&
	    dst->dev == net->loopback_dev)
		idev = __in6_dev_get_safely(dev_get_by_index_rcu(net, IP6CB(skb)->iअगर));
	अन्यथा
		idev = ip6_dst_idev(dst);

	चयन (ipstats_mib_noroutes) अणु
	हाल IPSTATS_MIB_INNOROUTES:
		type = ipv6_addr_type(&ipv6_hdr(skb)->daddr);
		अगर (type == IPV6_ADDR_ANY) अणु
			IP6_INC_STATS(net, idev, IPSTATS_MIB_INADDRERRORS);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल IPSTATS_MIB_OUTNOROUTES:
		IP6_INC_STATS(net, idev, ipstats_mib_noroutes);
		अवरोध;
	पूर्ण

	/* Start over by dropping the dst क्रम l3mdev हाल */
	अगर (netअगर_is_l3_master(skb->dev))
		skb_dst_drop(skb);

	icmpv6_send(skb, ICMPV6_DEST_UNREACH, code, 0);
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक ip6_pkt_discard(काष्ठा sk_buff *skb)
अणु
	वापस ip6_pkt_drop(skb, ICMPV6_NOROUTE, IPSTATS_MIB_INNOROUTES);
पूर्ण

अटल पूर्णांक ip6_pkt_discard_out(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	skb->dev = skb_dst(skb)->dev;
	वापस ip6_pkt_drop(skb, ICMPV6_NOROUTE, IPSTATS_MIB_OUTNOROUTES);
पूर्ण

अटल पूर्णांक ip6_pkt_prohibit(काष्ठा sk_buff *skb)
अणु
	वापस ip6_pkt_drop(skb, ICMPV6_ADM_PROHIBITED, IPSTATS_MIB_INNOROUTES);
पूर्ण

अटल पूर्णांक ip6_pkt_prohibit_out(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	skb->dev = skb_dst(skb)->dev;
	वापस ip6_pkt_drop(skb, ICMPV6_ADM_PROHIBITED, IPSTATS_MIB_OUTNOROUTES);
पूर्ण

/*
 *	Allocate a dst क्रम local (unicast / anycast) address.
 */

काष्ठा fib6_info *addrconf_f6i_alloc(काष्ठा net *net,
				     काष्ठा inet6_dev *idev,
				     स्थिर काष्ठा in6_addr *addr,
				     bool anycast, gfp_t gfp_flags)
अणु
	काष्ठा fib6_config cfg = अणु
		.fc_table = l3mdev_fib_table(idev->dev) ? : RT6_TABLE_LOCAL,
		.fc_अगरindex = idev->dev->अगरindex,
		.fc_flags = RTF_UP | RTF_NONEXTHOP,
		.fc_dst = *addr,
		.fc_dst_len = 128,
		.fc_protocol = RTPROT_KERNEL,
		.fc_nlinfo.nl_net = net,
		.fc_ignore_dev_करोwn = true,
	पूर्ण;
	काष्ठा fib6_info *f6i;

	अगर (anycast) अणु
		cfg.fc_type = RTN_ANYCAST;
		cfg.fc_flags |= RTF_ANYCAST;
	पूर्ण अन्यथा अणु
		cfg.fc_type = RTN_LOCAL;
		cfg.fc_flags |= RTF_LOCAL;
	पूर्ण

	f6i = ip6_route_info_create(&cfg, gfp_flags, शून्य);
	अगर (!IS_ERR(f6i))
		f6i->dst_nocount = true;
	वापस f6i;
पूर्ण

/* हटाओ deleted ip from prefsrc entries */
काष्ठा arg_dev_net_ip अणु
	काष्ठा net_device *dev;
	काष्ठा net *net;
	काष्ठा in6_addr *addr;
पूर्ण;

अटल पूर्णांक fib6_हटाओ_prefsrc(काष्ठा fib6_info *rt, व्योम *arg)
अणु
	काष्ठा net_device *dev = ((काष्ठा arg_dev_net_ip *)arg)->dev;
	काष्ठा net *net = ((काष्ठा arg_dev_net_ip *)arg)->net;
	काष्ठा in6_addr *addr = ((काष्ठा arg_dev_net_ip *)arg)->addr;

	अगर (!rt->nh &&
	    ((व्योम *)rt->fib6_nh->fib_nh_dev == dev || !dev) &&
	    rt != net->ipv6.fib6_null_entry &&
	    ipv6_addr_equal(addr, &rt->fib6_prefsrc.addr)) अणु
		spin_lock_bh(&rt6_exception_lock);
		/* हटाओ prefsrc entry */
		rt->fib6_prefsrc.plen = 0;
		spin_unlock_bh(&rt6_exception_lock);
	पूर्ण
	वापस 0;
पूर्ण

व्योम rt6_हटाओ_prefsrc(काष्ठा inet6_अगरaddr *अगरp)
अणु
	काष्ठा net *net = dev_net(अगरp->idev->dev);
	काष्ठा arg_dev_net_ip adni = अणु
		.dev = अगरp->idev->dev,
		.net = net,
		.addr = &अगरp->addr,
	पूर्ण;
	fib6_clean_all(net, fib6_हटाओ_prefsrc, &adni);
पूर्ण

#घोषणा RTF_RA_ROUTER		(RTF_ADDRCONF | RTF_DEFAULT)

/* Remove routers and update dst entries when gateway turn पूर्णांकo host. */
अटल पूर्णांक fib6_clean_tohost(काष्ठा fib6_info *rt, व्योम *arg)
अणु
	काष्ठा in6_addr *gateway = (काष्ठा in6_addr *)arg;
	काष्ठा fib6_nh *nh;

	/* RA routes करो not use nexthops */
	अगर (rt->nh)
		वापस 0;

	nh = rt->fib6_nh;
	अगर (((rt->fib6_flags & RTF_RA_ROUTER) == RTF_RA_ROUTER) &&
	    nh->fib_nh_gw_family && ipv6_addr_equal(gateway, &nh->fib_nh_gw6))
		वापस -1;

	/* Further clean up cached routes in exception table.
	 * This is needed because cached route may have a dअगरferent
	 * gateway than its 'parent' in the हाल of an ip redirect.
	 */
	fib6_nh_exceptions_clean_tohost(nh, gateway);

	वापस 0;
पूर्ण

व्योम rt6_clean_tohost(काष्ठा net *net, काष्ठा in6_addr *gateway)
अणु
	fib6_clean_all(net, fib6_clean_tohost, gateway);
पूर्ण

काष्ठा arg_netdev_event अणु
	स्थिर काष्ठा net_device *dev;
	जोड़ अणु
		अचिन्हित अक्षर nh_flags;
		अचिन्हित दीर्घ event;
	पूर्ण;
पूर्ण;

अटल काष्ठा fib6_info *rt6_multipath_first_sibling(स्थिर काष्ठा fib6_info *rt)
अणु
	काष्ठा fib6_info *iter;
	काष्ठा fib6_node *fn;

	fn = rcu_dereference_रक्षित(rt->fib6_node,
			lockdep_is_held(&rt->fib6_table->tb6_lock));
	iter = rcu_dereference_रक्षित(fn->leaf,
			lockdep_is_held(&rt->fib6_table->tb6_lock));
	जबतक (iter) अणु
		अगर (iter->fib6_metric == rt->fib6_metric &&
		    rt6_qualअगरy_क्रम_ecmp(iter))
			वापस iter;
		iter = rcu_dereference_रक्षित(iter->fib6_next,
				lockdep_is_held(&rt->fib6_table->tb6_lock));
	पूर्ण

	वापस शून्य;
पूर्ण

/* only called क्रम fib entries with builtin fib6_nh */
अटल bool rt6_is_dead(स्थिर काष्ठा fib6_info *rt)
अणु
	अगर (rt->fib6_nh->fib_nh_flags & RTNH_F_DEAD ||
	    (rt->fib6_nh->fib_nh_flags & RTNH_F_LINKDOWN &&
	     ip6_ignore_linkकरोwn(rt->fib6_nh->fib_nh_dev)))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक rt6_multipath_total_weight(स्थिर काष्ठा fib6_info *rt)
अणु
	काष्ठा fib6_info *iter;
	पूर्णांक total = 0;

	अगर (!rt6_is_dead(rt))
		total += rt->fib6_nh->fib_nh_weight;

	list_क्रम_each_entry(iter, &rt->fib6_siblings, fib6_siblings) अणु
		अगर (!rt6_is_dead(iter))
			total += iter->fib6_nh->fib_nh_weight;
	पूर्ण

	वापस total;
पूर्ण

अटल व्योम rt6_upper_bound_set(काष्ठा fib6_info *rt, पूर्णांक *weight, पूर्णांक total)
अणु
	पूर्णांक upper_bound = -1;

	अगर (!rt6_is_dead(rt)) अणु
		*weight += rt->fib6_nh->fib_nh_weight;
		upper_bound = DIV_ROUND_CLOSEST_ULL((u64) (*weight) << 31,
						    total) - 1;
	पूर्ण
	atomic_set(&rt->fib6_nh->fib_nh_upper_bound, upper_bound);
पूर्ण

अटल व्योम rt6_multipath_upper_bound_set(काष्ठा fib6_info *rt, पूर्णांक total)
अणु
	काष्ठा fib6_info *iter;
	पूर्णांक weight = 0;

	rt6_upper_bound_set(rt, &weight, total);

	list_क्रम_each_entry(iter, &rt->fib6_siblings, fib6_siblings)
		rt6_upper_bound_set(iter, &weight, total);
पूर्ण

व्योम rt6_multipath_rebalance(काष्ठा fib6_info *rt)
अणु
	काष्ठा fib6_info *first;
	पूर्णांक total;

	/* In हाल the entire multipath route was marked क्रम flushing,
	 * then there is no need to rebalance upon the removal of every
	 * sibling route.
	 */
	अगर (!rt->fib6_nsiblings || rt->should_flush)
		वापस;

	/* During lookup routes are evaluated in order, so we need to
	 * make sure upper bounds are asचिन्हित from the first sibling
	 * onwards.
	 */
	first = rt6_multipath_first_sibling(rt);
	अगर (WARN_ON_ONCE(!first))
		वापस;

	total = rt6_multipath_total_weight(first);
	rt6_multipath_upper_bound_set(first, total);
पूर्ण

अटल पूर्णांक fib6_अगरup(काष्ठा fib6_info *rt, व्योम *p_arg)
अणु
	स्थिर काष्ठा arg_netdev_event *arg = p_arg;
	काष्ठा net *net = dev_net(arg->dev);

	अगर (rt != net->ipv6.fib6_null_entry && !rt->nh &&
	    rt->fib6_nh->fib_nh_dev == arg->dev) अणु
		rt->fib6_nh->fib_nh_flags &= ~arg->nh_flags;
		fib6_update_sernum_upto_root(net, rt);
		rt6_multipath_rebalance(rt);
	पूर्ण

	वापस 0;
पूर्ण

व्योम rt6_sync_up(काष्ठा net_device *dev, अचिन्हित अक्षर nh_flags)
अणु
	काष्ठा arg_netdev_event arg = अणु
		.dev = dev,
		अणु
			.nh_flags = nh_flags,
		पूर्ण,
	पूर्ण;

	अगर (nh_flags & RTNH_F_DEAD && netअगर_carrier_ok(dev))
		arg.nh_flags |= RTNH_F_LINKDOWN;

	fib6_clean_all(dev_net(dev), fib6_अगरup, &arg);
पूर्ण

/* only called क्रम fib entries with अंतरभूत fib6_nh */
अटल bool rt6_multipath_uses_dev(स्थिर काष्ठा fib6_info *rt,
				   स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा fib6_info *iter;

	अगर (rt->fib6_nh->fib_nh_dev == dev)
		वापस true;
	list_क्रम_each_entry(iter, &rt->fib6_siblings, fib6_siblings)
		अगर (iter->fib6_nh->fib_nh_dev == dev)
			वापस true;

	वापस false;
पूर्ण

अटल व्योम rt6_multipath_flush(काष्ठा fib6_info *rt)
अणु
	काष्ठा fib6_info *iter;

	rt->should_flush = 1;
	list_क्रम_each_entry(iter, &rt->fib6_siblings, fib6_siblings)
		iter->should_flush = 1;
पूर्ण

अटल अचिन्हित पूर्णांक rt6_multipath_dead_count(स्थिर काष्ठा fib6_info *rt,
					     स्थिर काष्ठा net_device *करोwn_dev)
अणु
	काष्ठा fib6_info *iter;
	अचिन्हित पूर्णांक dead = 0;

	अगर (rt->fib6_nh->fib_nh_dev == करोwn_dev ||
	    rt->fib6_nh->fib_nh_flags & RTNH_F_DEAD)
		dead++;
	list_क्रम_each_entry(iter, &rt->fib6_siblings, fib6_siblings)
		अगर (iter->fib6_nh->fib_nh_dev == करोwn_dev ||
		    iter->fib6_nh->fib_nh_flags & RTNH_F_DEAD)
			dead++;

	वापस dead;
पूर्ण

अटल व्योम rt6_multipath_nh_flags_set(काष्ठा fib6_info *rt,
				       स्थिर काष्ठा net_device *dev,
				       अचिन्हित अक्षर nh_flags)
अणु
	काष्ठा fib6_info *iter;

	अगर (rt->fib6_nh->fib_nh_dev == dev)
		rt->fib6_nh->fib_nh_flags |= nh_flags;
	list_क्रम_each_entry(iter, &rt->fib6_siblings, fib6_siblings)
		अगर (iter->fib6_nh->fib_nh_dev == dev)
			iter->fib6_nh->fib_nh_flags |= nh_flags;
पूर्ण

/* called with ग_लिखो lock held क्रम table with rt */
अटल पूर्णांक fib6_अगरकरोwn(काष्ठा fib6_info *rt, व्योम *p_arg)
अणु
	स्थिर काष्ठा arg_netdev_event *arg = p_arg;
	स्थिर काष्ठा net_device *dev = arg->dev;
	काष्ठा net *net = dev_net(dev);

	अगर (rt == net->ipv6.fib6_null_entry || rt->nh)
		वापस 0;

	चयन (arg->event) अणु
	हाल NETDEV_UNREGISTER:
		वापस rt->fib6_nh->fib_nh_dev == dev ? -1 : 0;
	हाल NETDEV_DOWN:
		अगर (rt->should_flush)
			वापस -1;
		अगर (!rt->fib6_nsiblings)
			वापस rt->fib6_nh->fib_nh_dev == dev ? -1 : 0;
		अगर (rt6_multipath_uses_dev(rt, dev)) अणु
			अचिन्हित पूर्णांक count;

			count = rt6_multipath_dead_count(rt, dev);
			अगर (rt->fib6_nsiblings + 1 == count) अणु
				rt6_multipath_flush(rt);
				वापस -1;
			पूर्ण
			rt6_multipath_nh_flags_set(rt, dev, RTNH_F_DEAD |
						   RTNH_F_LINKDOWN);
			fib6_update_sernum(net, rt);
			rt6_multipath_rebalance(rt);
		पूर्ण
		वापस -2;
	हाल NETDEV_CHANGE:
		अगर (rt->fib6_nh->fib_nh_dev != dev ||
		    rt->fib6_flags & (RTF_LOCAL | RTF_ANYCAST))
			अवरोध;
		rt->fib6_nh->fib_nh_flags |= RTNH_F_LINKDOWN;
		rt6_multipath_rebalance(rt);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

व्योम rt6_sync_करोwn_dev(काष्ठा net_device *dev, अचिन्हित दीर्घ event)
अणु
	काष्ठा arg_netdev_event arg = अणु
		.dev = dev,
		अणु
			.event = event,
		पूर्ण,
	पूर्ण;
	काष्ठा net *net = dev_net(dev);

	अगर (net->ipv6.sysctl.skip_notअगरy_on_dev_करोwn)
		fib6_clean_all_skip_notअगरy(net, fib6_अगरकरोwn, &arg);
	अन्यथा
		fib6_clean_all(net, fib6_अगरकरोwn, &arg);
पूर्ण

व्योम rt6_disable_ip(काष्ठा net_device *dev, अचिन्हित दीर्घ event)
अणु
	rt6_sync_करोwn_dev(dev, event);
	rt6_uncached_list_flush_dev(dev_net(dev), dev);
	neigh_अगरकरोwn(&nd_tbl, dev);
पूर्ण

काष्ठा rt6_mtu_change_arg अणु
	काष्ठा net_device *dev;
	अचिन्हित पूर्णांक mtu;
	काष्ठा fib6_info *f6i;
पूर्ण;

अटल पूर्णांक fib6_nh_mtu_change(काष्ठा fib6_nh *nh, व्योम *_arg)
अणु
	काष्ठा rt6_mtu_change_arg *arg = (काष्ठा rt6_mtu_change_arg *)_arg;
	काष्ठा fib6_info *f6i = arg->f6i;

	/* For administrative MTU increase, there is no way to discover
	 * IPv6 PMTU increase, so PMTU increase should be updated here.
	 * Since RFC 1981 करोesn't include administrative MTU increase
	 * update PMTU increase is a MUST. (i.e. jumbo frame)
	 */
	अगर (nh->fib_nh_dev == arg->dev) अणु
		काष्ठा inet6_dev *idev = __in6_dev_get(arg->dev);
		u32 mtu = f6i->fib6_pmtu;

		अगर (mtu >= arg->mtu ||
		    (mtu < arg->mtu && mtu == idev->cnf.mtu6))
			fib6_metric_set(f6i, RTAX_MTU, arg->mtu);

		spin_lock_bh(&rt6_exception_lock);
		rt6_exceptions_update_pmtu(idev, nh, arg->mtu);
		spin_unlock_bh(&rt6_exception_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt6_mtu_change_route(काष्ठा fib6_info *f6i, व्योम *p_arg)
अणु
	काष्ठा rt6_mtu_change_arg *arg = (काष्ठा rt6_mtu_change_arg *) p_arg;
	काष्ठा inet6_dev *idev;

	/* In IPv6 pmtu discovery is not optional,
	   so that RTAX_MTU lock cannot disable it.
	   We still use this lock to block changes
	   caused by addrconf/ndisc.
	*/

	idev = __in6_dev_get(arg->dev);
	अगर (!idev)
		वापस 0;

	अगर (fib6_metric_locked(f6i, RTAX_MTU))
		वापस 0;

	arg->f6i = f6i;
	अगर (f6i->nh) अणु
		/* fib6_nh_mtu_change only वापसs 0, so this is safe */
		वापस nexthop_क्रम_each_fib6_nh(f6i->nh, fib6_nh_mtu_change,
						arg);
	पूर्ण

	वापस fib6_nh_mtu_change(f6i->fib6_nh, arg);
पूर्ण

व्योम rt6_mtu_change(काष्ठा net_device *dev, अचिन्हित पूर्णांक mtu)
अणु
	काष्ठा rt6_mtu_change_arg arg = अणु
		.dev = dev,
		.mtu = mtu,
	पूर्ण;

	fib6_clean_all(dev_net(dev), rt6_mtu_change_route, &arg);
पूर्ण

अटल स्थिर काष्ठा nla_policy rपंचांग_ipv6_policy[RTA_MAX+1] = अणु
	[RTA_UNSPEC]		= अणु .strict_start_type = RTA_DPORT + 1 पूर्ण,
	[RTA_GATEWAY]           = अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[RTA_PREFSRC]		= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[RTA_OIF]               = अणु .type = NLA_U32 पूर्ण,
	[RTA_IIF]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_PRIORITY]          = अणु .type = NLA_U32 पूर्ण,
	[RTA_METRICS]           = अणु .type = NLA_NESTED पूर्ण,
	[RTA_MULTIPATH]		= अणु .len = माप(काष्ठा rtnexthop) पूर्ण,
	[RTA_PREF]              = अणु .type = NLA_U8 पूर्ण,
	[RTA_ENCAP_TYPE]	= अणु .type = NLA_U16 पूर्ण,
	[RTA_ENCAP]		= अणु .type = NLA_NESTED पूर्ण,
	[RTA_EXPIRES]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_UID]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_MARK]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_TABLE]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_IP_PROTO]		= अणु .type = NLA_U8 पूर्ण,
	[RTA_SPORT]		= अणु .type = NLA_U16 पूर्ण,
	[RTA_DPORT]		= अणु .type = NLA_U16 पूर्ण,
	[RTA_NH_ID]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक rपंचांग_to_fib6_config(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			      काष्ठा fib6_config *cfg,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rपंचांगsg *rपंचांग;
	काष्ठा nlattr *tb[RTA_MAX+1];
	अचिन्हित पूर्णांक pref;
	पूर्णांक err;

	err = nlmsg_parse_deprecated(nlh, माप(*rपंचांग), tb, RTA_MAX,
				     rपंचांग_ipv6_policy, extack);
	अगर (err < 0)
		जाओ errout;

	err = -EINVAL;
	rपंचांग = nlmsg_data(nlh);

	*cfg = (काष्ठा fib6_config)अणु
		.fc_table = rपंचांग->rपंचांग_table,
		.fc_dst_len = rपंचांग->rपंचांग_dst_len,
		.fc_src_len = rपंचांग->rपंचांग_src_len,
		.fc_flags = RTF_UP,
		.fc_protocol = rपंचांग->rपंचांग_protocol,
		.fc_type = rपंचांग->rपंचांग_type,

		.fc_nlinfo.portid = NETLINK_CB(skb).portid,
		.fc_nlinfo.nlh = nlh,
		.fc_nlinfo.nl_net = sock_net(skb->sk),
	पूर्ण;

	अगर (rपंचांग->rपंचांग_type == RTN_UNREACHABLE ||
	    rपंचांग->rपंचांग_type == RTN_BLACKHOLE ||
	    rपंचांग->rपंचांग_type == RTN_PROHIBIT ||
	    rपंचांग->rपंचांग_type == RTN_THROW)
		cfg->fc_flags |= RTF_REJECT;

	अगर (rपंचांग->rपंचांग_type == RTN_LOCAL)
		cfg->fc_flags |= RTF_LOCAL;

	अगर (rपंचांग->rपंचांग_flags & RTM_F_CLONED)
		cfg->fc_flags |= RTF_CACHE;

	cfg->fc_flags |= (rपंचांग->rपंचांग_flags & RTNH_F_ONLINK);

	अगर (tb[RTA_NH_ID]) अणु
		अगर (tb[RTA_GATEWAY]   || tb[RTA_OIF] ||
		    tb[RTA_MULTIPATH] || tb[RTA_ENCAP]) अणु
			NL_SET_ERR_MSG(extack,
				       "Nexthop specification and nexthop id are mutually exclusive");
			जाओ errout;
		पूर्ण
		cfg->fc_nh_id = nla_get_u32(tb[RTA_NH_ID]);
	पूर्ण

	अगर (tb[RTA_GATEWAY]) अणु
		cfg->fc_gateway = nla_get_in6_addr(tb[RTA_GATEWAY]);
		cfg->fc_flags |= RTF_GATEWAY;
	पूर्ण
	अगर (tb[RTA_VIA]) अणु
		NL_SET_ERR_MSG(extack, "IPv6 does not support RTA_VIA attribute");
		जाओ errout;
	पूर्ण

	अगर (tb[RTA_DST]) अणु
		पूर्णांक plen = (rपंचांग->rपंचांग_dst_len + 7) >> 3;

		अगर (nla_len(tb[RTA_DST]) < plen)
			जाओ errout;

		nla_स_नकल(&cfg->fc_dst, tb[RTA_DST], plen);
	पूर्ण

	अगर (tb[RTA_SRC]) अणु
		पूर्णांक plen = (rपंचांग->rपंचांग_src_len + 7) >> 3;

		अगर (nla_len(tb[RTA_SRC]) < plen)
			जाओ errout;

		nla_स_नकल(&cfg->fc_src, tb[RTA_SRC], plen);
	पूर्ण

	अगर (tb[RTA_PREFSRC])
		cfg->fc_prefsrc = nla_get_in6_addr(tb[RTA_PREFSRC]);

	अगर (tb[RTA_OIF])
		cfg->fc_अगरindex = nla_get_u32(tb[RTA_OIF]);

	अगर (tb[RTA_PRIORITY])
		cfg->fc_metric = nla_get_u32(tb[RTA_PRIORITY]);

	अगर (tb[RTA_METRICS]) अणु
		cfg->fc_mx = nla_data(tb[RTA_METRICS]);
		cfg->fc_mx_len = nla_len(tb[RTA_METRICS]);
	पूर्ण

	अगर (tb[RTA_TABLE])
		cfg->fc_table = nla_get_u32(tb[RTA_TABLE]);

	अगर (tb[RTA_MULTIPATH]) अणु
		cfg->fc_mp = nla_data(tb[RTA_MULTIPATH]);
		cfg->fc_mp_len = nla_len(tb[RTA_MULTIPATH]);

		err = lwtunnel_valid_encap_type_attr(cfg->fc_mp,
						     cfg->fc_mp_len, extack);
		अगर (err < 0)
			जाओ errout;
	पूर्ण

	अगर (tb[RTA_PREF]) अणु
		pref = nla_get_u8(tb[RTA_PREF]);
		अगर (pref != ICMPV6_ROUTER_PREF_LOW &&
		    pref != ICMPV6_ROUTER_PREF_HIGH)
			pref = ICMPV6_ROUTER_PREF_MEDIUM;
		cfg->fc_flags |= RTF_PREF(pref);
	पूर्ण

	अगर (tb[RTA_ENCAP])
		cfg->fc_encap = tb[RTA_ENCAP];

	अगर (tb[RTA_ENCAP_TYPE]) अणु
		cfg->fc_encap_type = nla_get_u16(tb[RTA_ENCAP_TYPE]);

		err = lwtunnel_valid_encap_type(cfg->fc_encap_type, extack);
		अगर (err < 0)
			जाओ errout;
	पूर्ण

	अगर (tb[RTA_EXPIRES]) अणु
		अचिन्हित दीर्घ समयout = addrconf_समयout_fixup(nla_get_u32(tb[RTA_EXPIRES]), HZ);

		अगर (addrconf_finite_समयout(समयout)) अणु
			cfg->fc_expires = jअगरfies_to_घड़ी_प्रकार(समयout * HZ);
			cfg->fc_flags |= RTF_EXPIRES;
		पूर्ण
	पूर्ण

	err = 0;
errout:
	वापस err;
पूर्ण

काष्ठा rt6_nh अणु
	काष्ठा fib6_info *fib6_info;
	काष्ठा fib6_config r_cfg;
	काष्ठा list_head next;
पूर्ण;

अटल पूर्णांक ip6_route_info_append(काष्ठा net *net,
				 काष्ठा list_head *rt6_nh_list,
				 काष्ठा fib6_info *rt,
				 काष्ठा fib6_config *r_cfg)
अणु
	काष्ठा rt6_nh *nh;
	पूर्णांक err = -EEXIST;

	list_क्रम_each_entry(nh, rt6_nh_list, next) अणु
		/* check अगर fib6_info alपढ़ोy exists */
		अगर (rt6_duplicate_nexthop(nh->fib6_info, rt))
			वापस err;
	पूर्ण

	nh = kzalloc(माप(*nh), GFP_KERNEL);
	अगर (!nh)
		वापस -ENOMEM;
	nh->fib6_info = rt;
	स_नकल(&nh->r_cfg, r_cfg, माप(*r_cfg));
	list_add_tail(&nh->next, rt6_nh_list);

	वापस 0;
पूर्ण

अटल व्योम ip6_route_mpath_notअगरy(काष्ठा fib6_info *rt,
				   काष्ठा fib6_info *rt_last,
				   काष्ठा nl_info *info,
				   __u16 nlflags)
अणु
	/* अगर this is an APPEND route, then rt poपूर्णांकs to the first route
	 * inserted and rt_last poपूर्णांकs to last route inserted. Userspace
	 * wants a consistent dump of the route which starts at the first
	 * nexthop. Since sibling routes are always added at the end of
	 * the list, find the first sibling of the last route appended
	 */
	अगर ((nlflags & NLM_F_APPEND) && rt_last && rt_last->fib6_nsiblings) अणु
		rt = list_first_entry(&rt_last->fib6_siblings,
				      काष्ठा fib6_info,
				      fib6_siblings);
	पूर्ण

	अगर (rt)
		inet6_rt_notअगरy(RTM_NEWROUTE, rt, info, nlflags);
पूर्ण

अटल bool ip6_route_mpath_should_notअगरy(स्थिर काष्ठा fib6_info *rt)
अणु
	bool rt_can_ecmp = rt6_qualअगरy_क्रम_ecmp(rt);
	bool should_notअगरy = false;
	काष्ठा fib6_info *leaf;
	काष्ठा fib6_node *fn;

	rcu_पढ़ो_lock();
	fn = rcu_dereference(rt->fib6_node);
	अगर (!fn)
		जाओ out;

	leaf = rcu_dereference(fn->leaf);
	अगर (!leaf)
		जाओ out;

	अगर (rt == leaf ||
	    (rt_can_ecmp && rt->fib6_metric == leaf->fib6_metric &&
	     rt6_qualअगरy_क्रम_ecmp(leaf)))
		should_notअगरy = true;
out:
	rcu_पढ़ो_unlock();

	वापस should_notअगरy;
पूर्ण

अटल पूर्णांक ip6_route_multipath_add(काष्ठा fib6_config *cfg,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib6_info *rt_notअगर = शून्य, *rt_last = शून्य;
	काष्ठा nl_info *info = &cfg->fc_nlinfo;
	काष्ठा fib6_config r_cfg;
	काष्ठा rtnexthop *rtnh;
	काष्ठा fib6_info *rt;
	काष्ठा rt6_nh *err_nh;
	काष्ठा rt6_nh *nh, *nh_safe;
	__u16 nlflags;
	पूर्णांक reमुख्यing;
	पूर्णांक attrlen;
	पूर्णांक err = 1;
	पूर्णांक nhn = 0;
	पूर्णांक replace = (cfg->fc_nlinfo.nlh &&
		       (cfg->fc_nlinfo.nlh->nlmsg_flags & NLM_F_REPLACE));
	LIST_HEAD(rt6_nh_list);

	nlflags = replace ? NLM_F_REPLACE : NLM_F_CREATE;
	अगर (info->nlh && info->nlh->nlmsg_flags & NLM_F_APPEND)
		nlflags |= NLM_F_APPEND;

	reमुख्यing = cfg->fc_mp_len;
	rtnh = (काष्ठा rtnexthop *)cfg->fc_mp;

	/* Parse a Multipath Entry and build a list (rt6_nh_list) of
	 * fib6_info काष्ठाs per nexthop
	 */
	जबतक (rtnh_ok(rtnh, reमुख्यing)) अणु
		स_नकल(&r_cfg, cfg, माप(*cfg));
		अगर (rtnh->rtnh_अगरindex)
			r_cfg.fc_अगरindex = rtnh->rtnh_अगरindex;

		attrlen = rtnh_attrlen(rtnh);
		अगर (attrlen > 0) अणु
			काष्ठा nlattr *nla, *attrs = rtnh_attrs(rtnh);

			nla = nla_find(attrs, attrlen, RTA_GATEWAY);
			अगर (nla) अणु
				r_cfg.fc_gateway = nla_get_in6_addr(nla);
				r_cfg.fc_flags |= RTF_GATEWAY;
			पूर्ण
			r_cfg.fc_encap = nla_find(attrs, attrlen, RTA_ENCAP);
			nla = nla_find(attrs, attrlen, RTA_ENCAP_TYPE);
			अगर (nla)
				r_cfg.fc_encap_type = nla_get_u16(nla);
		पूर्ण

		r_cfg.fc_flags |= (rtnh->rtnh_flags & RTNH_F_ONLINK);
		rt = ip6_route_info_create(&r_cfg, GFP_KERNEL, extack);
		अगर (IS_ERR(rt)) अणु
			err = PTR_ERR(rt);
			rt = शून्य;
			जाओ cleanup;
		पूर्ण
		अगर (!rt6_qualअगरy_क्रम_ecmp(rt)) अणु
			err = -EINVAL;
			NL_SET_ERR_MSG(extack,
				       "Device only routes can not be added for IPv6 using the multipath API.");
			fib6_info_release(rt);
			जाओ cleanup;
		पूर्ण

		rt->fib6_nh->fib_nh_weight = rtnh->rtnh_hops + 1;

		err = ip6_route_info_append(info->nl_net, &rt6_nh_list,
					    rt, &r_cfg);
		अगर (err) अणु
			fib6_info_release(rt);
			जाओ cleanup;
		पूर्ण

		rtnh = rtnh_next(rtnh, &reमुख्यing);
	पूर्ण

	अगर (list_empty(&rt6_nh_list)) अणु
		NL_SET_ERR_MSG(extack,
			       "Invalid nexthop configuration - no valid nexthops");
		वापस -EINVAL;
	पूर्ण

	/* क्रम add and replace send one notअगरication with all nexthops.
	 * Skip the notअगरication in fib6_add_rt2node and send one with
	 * the full route when करोne
	 */
	info->skip_notअगरy = 1;

	/* For add and replace, send one notअगरication with all nexthops. For
	 * append, send one notअगरication with all appended nexthops.
	 */
	info->skip_notअगरy_kernel = 1;

	err_nh = शून्य;
	list_क्रम_each_entry(nh, &rt6_nh_list, next) अणु
		err = __ip6_ins_rt(nh->fib6_info, info, extack);
		fib6_info_release(nh->fib6_info);

		अगर (!err) अणु
			/* save reference to last route successfully inserted */
			rt_last = nh->fib6_info;

			/* save reference to first route क्रम notअगरication */
			अगर (!rt_notअगर)
				rt_notअगर = nh->fib6_info;
		पूर्ण

		/* nh->fib6_info is used or मुक्तd at this poपूर्णांक, reset to शून्य*/
		nh->fib6_info = शून्य;
		अगर (err) अणु
			अगर (replace && nhn)
				NL_SET_ERR_MSG_MOD(extack,
						   "multipath route replace failed (check consistency of installed routes)");
			err_nh = nh;
			जाओ add_errout;
		पूर्ण

		/* Because each route is added like a single route we हटाओ
		 * these flags after the first nexthop: अगर there is a collision,
		 * we have alपढ़ोy failed to add the first nexthop:
		 * fib6_add_rt2node() has rejected it; when replacing, old
		 * nexthops have been replaced by first new, the rest should
		 * be added to it.
		 */
		अगर (cfg->fc_nlinfo.nlh) अणु
			cfg->fc_nlinfo.nlh->nlmsg_flags &= ~(NLM_F_EXCL |
							     NLM_F_REPLACE);
			cfg->fc_nlinfo.nlh->nlmsg_flags |= NLM_F_CREATE;
		पूर्ण
		nhn++;
	पूर्ण

	/* An in-kernel notअगरication should only be sent in हाल the new
	 * multipath route is added as the first route in the node, or अगर
	 * it was appended to it. We pass 'rt_notif' since it is the first
	 * sibling and might allow us to skip some checks in the replace हाल.
	 */
	अगर (ip6_route_mpath_should_notअगरy(rt_notअगर)) अणु
		क्रमागत fib_event_type fib_event;

		अगर (rt_notअगर->fib6_nsiblings != nhn - 1)
			fib_event = FIB_EVENT_ENTRY_APPEND;
		अन्यथा
			fib_event = FIB_EVENT_ENTRY_REPLACE;

		err = call_fib6_multipath_entry_notअगरiers(info->nl_net,
							  fib_event, rt_notअगर,
							  nhn - 1, extack);
		अगर (err) अणु
			/* Delete all the siblings that were just added */
			err_nh = शून्य;
			जाओ add_errout;
		पूर्ण
	पूर्ण

	/* success ... tell user about new route */
	ip6_route_mpath_notअगरy(rt_notअगर, rt_last, info, nlflags);
	जाओ cleanup;

add_errout:
	/* send notअगरication क्रम routes that were added so that
	 * the delete notअगरications sent by ip6_route_del are
	 * coherent
	 */
	अगर (rt_notअगर)
		ip6_route_mpath_notअगरy(rt_notअगर, rt_last, info, nlflags);

	/* Delete routes that were alपढ़ोy added */
	list_क्रम_each_entry(nh, &rt6_nh_list, next) अणु
		अगर (err_nh == nh)
			अवरोध;
		ip6_route_del(&nh->r_cfg, extack);
	पूर्ण

cleanup:
	list_क्रम_each_entry_safe(nh, nh_safe, &rt6_nh_list, next) अणु
		अगर (nh->fib6_info)
			fib6_info_release(nh->fib6_info);
		list_del(&nh->next);
		kमुक्त(nh);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ip6_route_multipath_del(काष्ठा fib6_config *cfg,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib6_config r_cfg;
	काष्ठा rtnexthop *rtnh;
	पूर्णांक last_err = 0;
	पूर्णांक reमुख्यing;
	पूर्णांक attrlen;
	पूर्णांक err;

	reमुख्यing = cfg->fc_mp_len;
	rtnh = (काष्ठा rtnexthop *)cfg->fc_mp;

	/* Parse a Multipath Entry */
	जबतक (rtnh_ok(rtnh, reमुख्यing)) अणु
		स_नकल(&r_cfg, cfg, माप(*cfg));
		अगर (rtnh->rtnh_अगरindex)
			r_cfg.fc_अगरindex = rtnh->rtnh_अगरindex;

		attrlen = rtnh_attrlen(rtnh);
		अगर (attrlen > 0) अणु
			काष्ठा nlattr *nla, *attrs = rtnh_attrs(rtnh);

			nla = nla_find(attrs, attrlen, RTA_GATEWAY);
			अगर (nla) अणु
				nla_स_नकल(&r_cfg.fc_gateway, nla, 16);
				r_cfg.fc_flags |= RTF_GATEWAY;
			पूर्ण
		पूर्ण
		err = ip6_route_del(&r_cfg, extack);
		अगर (err)
			last_err = err;

		rtnh = rtnh_next(rtnh, &reमुख्यing);
	पूर्ण

	वापस last_err;
पूर्ण

अटल पूर्णांक inet6_rपंचांग_delroute(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib6_config cfg;
	पूर्णांक err;

	err = rपंचांग_to_fib6_config(skb, nlh, &cfg, extack);
	अगर (err < 0)
		वापस err;

	अगर (cfg.fc_nh_id &&
	    !nexthop_find_by_id(sock_net(skb->sk), cfg.fc_nh_id)) अणु
		NL_SET_ERR_MSG(extack, "Nexthop id does not exist");
		वापस -EINVAL;
	पूर्ण

	अगर (cfg.fc_mp)
		वापस ip6_route_multipath_del(&cfg, extack);
	अन्यथा अणु
		cfg.fc_delete_all_nh = 1;
		वापस ip6_route_del(&cfg, extack);
	पूर्ण
पूर्ण

अटल पूर्णांक inet6_rपंचांग_newroute(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib6_config cfg;
	पूर्णांक err;

	err = rपंचांग_to_fib6_config(skb, nlh, &cfg, extack);
	अगर (err < 0)
		वापस err;

	अगर (cfg.fc_metric == 0)
		cfg.fc_metric = IP6_RT_PRIO_USER;

	अगर (cfg.fc_mp)
		वापस ip6_route_multipath_add(&cfg, extack);
	अन्यथा
		वापस ip6_route_add(&cfg, GFP_KERNEL, extack);
पूर्ण

/* add the overhead of this fib6_nh to nexthop_len */
अटल पूर्णांक rt6_nh_nlmsg_size(काष्ठा fib6_nh *nh, व्योम *arg)
अणु
	पूर्णांक *nexthop_len = arg;

	*nexthop_len += nla_total_size(0)	 /* RTA_MULTIPATH */
		     + NLA_ALIGN(माप(काष्ठा rtnexthop))
		     + nla_total_size(16); /* RTA_GATEWAY */

	अगर (nh->fib_nh_lws) अणु
		/* RTA_ENCAP_TYPE */
		*nexthop_len += lwtunnel_get_encap_size(nh->fib_nh_lws);
		/* RTA_ENCAP */
		*nexthop_len += nla_total_size(2);
	पूर्ण

	वापस 0;
पूर्ण

अटल माप_प्रकार rt6_nlmsg_size(काष्ठा fib6_info *f6i)
अणु
	पूर्णांक nexthop_len;

	अगर (f6i->nh) अणु
		nexthop_len = nla_total_size(4); /* RTA_NH_ID */
		nexthop_क्रम_each_fib6_nh(f6i->nh, rt6_nh_nlmsg_size,
					 &nexthop_len);
	पूर्ण अन्यथा अणु
		काष्ठा fib6_nh *nh = f6i->fib6_nh;

		nexthop_len = 0;
		अगर (f6i->fib6_nsiblings) अणु
			nexthop_len = nla_total_size(0)	 /* RTA_MULTIPATH */
				    + NLA_ALIGN(माप(काष्ठा rtnexthop))
				    + nla_total_size(16) /* RTA_GATEWAY */
				    + lwtunnel_get_encap_size(nh->fib_nh_lws);

			nexthop_len *= f6i->fib6_nsiblings;
		पूर्ण
		nexthop_len += lwtunnel_get_encap_size(nh->fib_nh_lws);
	पूर्ण

	वापस NLMSG_ALIGN(माप(काष्ठा rपंचांगsg))
	       + nla_total_size(16) /* RTA_SRC */
	       + nla_total_size(16) /* RTA_DST */
	       + nla_total_size(16) /* RTA_GATEWAY */
	       + nla_total_size(16) /* RTA_PREFSRC */
	       + nla_total_size(4) /* RTA_TABLE */
	       + nla_total_size(4) /* RTA_IIF */
	       + nla_total_size(4) /* RTA_OIF */
	       + nla_total_size(4) /* RTA_PRIORITY */
	       + RTAX_MAX * nla_total_size(4) /* RTA_METRICS */
	       + nla_total_size(माप(काष्ठा rta_cacheinfo))
	       + nla_total_size(TCP_CA_NAME_MAX) /* RTAX_CC_ALGO */
	       + nla_total_size(1) /* RTA_PREF */
	       + nexthop_len;
पूर्ण

अटल पूर्णांक rt6_fill_node_nexthop(काष्ठा sk_buff *skb, काष्ठा nexthop *nh,
				 अचिन्हित अक्षर *flags)
अणु
	अगर (nexthop_is_multipath(nh)) अणु
		काष्ठा nlattr *mp;

		mp = nla_nest_start_noflag(skb, RTA_MULTIPATH);
		अगर (!mp)
			जाओ nla_put_failure;

		अगर (nexthop_mpath_fill_node(skb, nh, AF_INET6))
			जाओ nla_put_failure;

		nla_nest_end(skb, mp);
	पूर्ण अन्यथा अणु
		काष्ठा fib6_nh *fib6_nh;

		fib6_nh = nexthop_fib6_nh(nh);
		अगर (fib_nexthop_info(skb, &fib6_nh->nh_common, AF_INET6,
				     flags, false) < 0)
			जाओ nla_put_failure;
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक rt6_fill_node(काष्ठा net *net, काष्ठा sk_buff *skb,
			 काष्ठा fib6_info *rt, काष्ठा dst_entry *dst,
			 काष्ठा in6_addr *dest, काष्ठा in6_addr *src,
			 पूर्णांक iअगर, पूर्णांक type, u32 portid, u32 seq,
			 अचिन्हित पूर्णांक flags)
अणु
	काष्ठा rt6_info *rt6 = (काष्ठा rt6_info *)dst;
	काष्ठा rt6key *rt6_dst, *rt6_src;
	u32 *pmetrics, table, rt6_flags;
	अचिन्हित अक्षर nh_flags = 0;
	काष्ठा nlmsghdr *nlh;
	काष्ठा rपंचांगsg *rपंचांग;
	दीर्घ expires = 0;

	nlh = nlmsg_put(skb, portid, seq, type, माप(*rपंचांग), flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	अगर (rt6) अणु
		rt6_dst = &rt6->rt6i_dst;
		rt6_src = &rt6->rt6i_src;
		rt6_flags = rt6->rt6i_flags;
	पूर्ण अन्यथा अणु
		rt6_dst = &rt->fib6_dst;
		rt6_src = &rt->fib6_src;
		rt6_flags = rt->fib6_flags;
	पूर्ण

	rपंचांग = nlmsg_data(nlh);
	rपंचांग->rपंचांग_family = AF_INET6;
	rपंचांग->rपंचांग_dst_len = rt6_dst->plen;
	rपंचांग->rपंचांग_src_len = rt6_src->plen;
	rपंचांग->rपंचांग_tos = 0;
	अगर (rt->fib6_table)
		table = rt->fib6_table->tb6_id;
	अन्यथा
		table = RT6_TABLE_UNSPEC;
	rपंचांग->rपंचांग_table = table < 256 ? table : RT_TABLE_COMPAT;
	अगर (nla_put_u32(skb, RTA_TABLE, table))
		जाओ nla_put_failure;

	rपंचांग->rपंचांग_type = rt->fib6_type;
	rपंचांग->rपंचांग_flags = 0;
	rपंचांग->rपंचांग_scope = RT_SCOPE_UNIVERSE;
	rपंचांग->rपंचांग_protocol = rt->fib6_protocol;

	अगर (rt6_flags & RTF_CACHE)
		rपंचांग->rपंचांग_flags |= RTM_F_CLONED;

	अगर (dest) अणु
		अगर (nla_put_in6_addr(skb, RTA_DST, dest))
			जाओ nla_put_failure;
		rपंचांग->rपंचांग_dst_len = 128;
	पूर्ण अन्यथा अगर (rपंचांग->rपंचांग_dst_len)
		अगर (nla_put_in6_addr(skb, RTA_DST, &rt6_dst->addr))
			जाओ nla_put_failure;
#अगर_घोषित CONFIG_IPV6_SUBTREES
	अगर (src) अणु
		अगर (nla_put_in6_addr(skb, RTA_SRC, src))
			जाओ nla_put_failure;
		rपंचांग->rपंचांग_src_len = 128;
	पूर्ण अन्यथा अगर (rपंचांग->rपंचांग_src_len &&
		   nla_put_in6_addr(skb, RTA_SRC, &rt6_src->addr))
		जाओ nla_put_failure;
#पूर्ण_अगर
	अगर (iअगर) अणु
#अगर_घोषित CONFIG_IPV6_MROUTE
		अगर (ipv6_addr_is_multicast(&rt6_dst->addr)) अणु
			पूर्णांक err = ip6mr_get_route(net, skb, rपंचांग, portid);

			अगर (err == 0)
				वापस 0;
			अगर (err < 0)
				जाओ nla_put_failure;
		पूर्ण अन्यथा
#पूर्ण_अगर
			अगर (nla_put_u32(skb, RTA_IIF, iअगर))
				जाओ nla_put_failure;
	पूर्ण अन्यथा अगर (dest) अणु
		काष्ठा in6_addr saddr_buf;
		अगर (ip6_route_get_saddr(net, rt, dest, 0, &saddr_buf) == 0 &&
		    nla_put_in6_addr(skb, RTA_PREFSRC, &saddr_buf))
			जाओ nla_put_failure;
	पूर्ण

	अगर (rt->fib6_prefsrc.plen) अणु
		काष्ठा in6_addr saddr_buf;
		saddr_buf = rt->fib6_prefsrc.addr;
		अगर (nla_put_in6_addr(skb, RTA_PREFSRC, &saddr_buf))
			जाओ nla_put_failure;
	पूर्ण

	pmetrics = dst ? dst_metrics_ptr(dst) : rt->fib6_metrics->metrics;
	अगर (rtnetlink_put_metrics(skb, pmetrics) < 0)
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, RTA_PRIORITY, rt->fib6_metric))
		जाओ nla_put_failure;

	/* For multipath routes, walk the siblings list and add
	 * each as a nexthop within RTA_MULTIPATH.
	 */
	अगर (rt6) अणु
		अगर (rt6_flags & RTF_GATEWAY &&
		    nla_put_in6_addr(skb, RTA_GATEWAY, &rt6->rt6i_gateway))
			जाओ nla_put_failure;

		अगर (dst->dev && nla_put_u32(skb, RTA_OIF, dst->dev->अगरindex))
			जाओ nla_put_failure;

		अगर (dst->lwtstate &&
		    lwtunnel_fill_encap(skb, dst->lwtstate, RTA_ENCAP, RTA_ENCAP_TYPE) < 0)
			जाओ nla_put_failure;
	पूर्ण अन्यथा अगर (rt->fib6_nsiblings) अणु
		काष्ठा fib6_info *sibling, *next_sibling;
		काष्ठा nlattr *mp;

		mp = nla_nest_start_noflag(skb, RTA_MULTIPATH);
		अगर (!mp)
			जाओ nla_put_failure;

		अगर (fib_add_nexthop(skb, &rt->fib6_nh->nh_common,
				    rt->fib6_nh->fib_nh_weight, AF_INET6) < 0)
			जाओ nla_put_failure;

		list_क्रम_each_entry_safe(sibling, next_sibling,
					 &rt->fib6_siblings, fib6_siblings) अणु
			अगर (fib_add_nexthop(skb, &sibling->fib6_nh->nh_common,
					    sibling->fib6_nh->fib_nh_weight,
					    AF_INET6) < 0)
				जाओ nla_put_failure;
		पूर्ण

		nla_nest_end(skb, mp);
	पूर्ण अन्यथा अगर (rt->nh) अणु
		अगर (nla_put_u32(skb, RTA_NH_ID, rt->nh->id))
			जाओ nla_put_failure;

		अगर (nexthop_is_blackhole(rt->nh))
			rपंचांग->rपंचांग_type = RTN_BLACKHOLE;

		अगर (net->ipv4.sysctl_nexthop_compat_mode &&
		    rt6_fill_node_nexthop(skb, rt->nh, &nh_flags) < 0)
			जाओ nla_put_failure;

		rपंचांग->rपंचांग_flags |= nh_flags;
	पूर्ण अन्यथा अणु
		अगर (fib_nexthop_info(skb, &rt->fib6_nh->nh_common, AF_INET6,
				     &nh_flags, false) < 0)
			जाओ nla_put_failure;

		rपंचांग->rपंचांग_flags |= nh_flags;
	पूर्ण

	अगर (rt6_flags & RTF_EXPIRES) अणु
		expires = dst ? dst->expires : rt->expires;
		expires -= jअगरfies;
	पूर्ण

	अगर (!dst) अणु
		अगर (rt->offload)
			rपंचांग->rपंचांग_flags |= RTM_F_OFFLOAD;
		अगर (rt->trap)
			rपंचांग->rपंचांग_flags |= RTM_F_TRAP;
		अगर (rt->offload_failed)
			rपंचांग->rपंचांग_flags |= RTM_F_OFFLOAD_FAILED;
	पूर्ण

	अगर (rtnl_put_cacheinfo(skb, dst, 0, expires, dst ? dst->error : 0) < 0)
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, RTA_PREF, IPV6_EXTRACT_PREF(rt6_flags)))
		जाओ nla_put_failure;


	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fib6_info_nh_uses_dev(काष्ठा fib6_nh *nh, व्योम *arg)
अणु
	स्थिर काष्ठा net_device *dev = arg;

	अगर (nh->fib_nh_dev == dev)
		वापस 1;

	वापस 0;
पूर्ण

अटल bool fib6_info_uses_dev(स्थिर काष्ठा fib6_info *f6i,
			       स्थिर काष्ठा net_device *dev)
अणु
	अगर (f6i->nh) अणु
		काष्ठा net_device *_dev = (काष्ठा net_device *)dev;

		वापस !!nexthop_क्रम_each_fib6_nh(f6i->nh,
						  fib6_info_nh_uses_dev,
						  _dev);
	पूर्ण

	अगर (f6i->fib6_nh->fib_nh_dev == dev)
		वापस true;

	अगर (f6i->fib6_nsiblings) अणु
		काष्ठा fib6_info *sibling, *next_sibling;

		list_क्रम_each_entry_safe(sibling, next_sibling,
					 &f6i->fib6_siblings, fib6_siblings) अणु
			अगर (sibling->fib6_nh->fib_nh_dev == dev)
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

काष्ठा fib6_nh_exception_dump_walker अणु
	काष्ठा rt6_rtnl_dump_arg *dump;
	काष्ठा fib6_info *rt;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक skip;
	अचिन्हित पूर्णांक count;
पूर्ण;

अटल पूर्णांक rt6_nh_dump_exceptions(काष्ठा fib6_nh *nh, व्योम *arg)
अणु
	काष्ठा fib6_nh_exception_dump_walker *w = arg;
	काष्ठा rt6_rtnl_dump_arg *dump = w->dump;
	काष्ठा rt6_exception_bucket *bucket;
	काष्ठा rt6_exception *rt6_ex;
	पूर्णांक i, err;

	bucket = fib6_nh_get_excptn_bucket(nh, शून्य);
	अगर (!bucket)
		वापस 0;

	क्रम (i = 0; i < FIB6_EXCEPTION_BUCKET_SIZE; i++) अणु
		hlist_क्रम_each_entry(rt6_ex, &bucket->chain, hlist) अणु
			अगर (w->skip) अणु
				w->skip--;
				जारी;
			पूर्ण

			/* Expiration of entries करोesn't bump sernum, insertion
			 * करोes. Removal is triggered by insertion, so we can
			 * rely on the fact that अगर entries change between two
			 * partial dumps, this node is scanned again completely,
			 * see rt6_insert_exception() and fib6_dump_table().
			 *
			 * Count expired entries we go through as handled
			 * entries that we'll skip next समय, in हाल of partial
			 * node dump. Otherwise, अगर entries expire meanजबतक,
			 * we'll skip the wrong amount.
			 */
			अगर (rt6_check_expired(rt6_ex->rt6i)) अणु
				w->count++;
				जारी;
			पूर्ण

			err = rt6_fill_node(dump->net, dump->skb, w->rt,
					    &rt6_ex->rt6i->dst, शून्य, शून्य, 0,
					    RTM_NEWROUTE,
					    NETLINK_CB(dump->cb->skb).portid,
					    dump->cb->nlh->nlmsg_seq, w->flags);
			अगर (err)
				वापस err;

			w->count++;
		पूर्ण
		bucket++;
	पूर्ण

	वापस 0;
पूर्ण

/* Return -1 अगर करोne with node, number of handled routes on partial dump */
पूर्णांक rt6_dump_route(काष्ठा fib6_info *rt, व्योम *p_arg, अचिन्हित पूर्णांक skip)
अणु
	काष्ठा rt6_rtnl_dump_arg *arg = (काष्ठा rt6_rtnl_dump_arg *) p_arg;
	काष्ठा fib_dump_filter *filter = &arg->filter;
	अचिन्हित पूर्णांक flags = NLM_F_MULTI;
	काष्ठा net *net = arg->net;
	पूर्णांक count = 0;

	अगर (rt == net->ipv6.fib6_null_entry)
		वापस -1;

	अगर ((filter->flags & RTM_F_PREFIX) &&
	    !(rt->fib6_flags & RTF_PREFIX_RT)) अणु
		/* success since this is not a prefix route */
		वापस -1;
	पूर्ण
	अगर (filter->filter_set &&
	    ((filter->rt_type  && rt->fib6_type != filter->rt_type) ||
	     (filter->dev      && !fib6_info_uses_dev(rt, filter->dev)) ||
	     (filter->protocol && rt->fib6_protocol != filter->protocol))) अणु
		वापस -1;
	पूर्ण

	अगर (filter->filter_set ||
	    !filter->dump_routes || !filter->dump_exceptions) अणु
		flags |= NLM_F_DUMP_FILTERED;
	पूर्ण

	अगर (filter->dump_routes) अणु
		अगर (skip) अणु
			skip--;
		पूर्ण अन्यथा अणु
			अगर (rt6_fill_node(net, arg->skb, rt, शून्य, शून्य, शून्य,
					  0, RTM_NEWROUTE,
					  NETLINK_CB(arg->cb->skb).portid,
					  arg->cb->nlh->nlmsg_seq, flags)) अणु
				वापस 0;
			पूर्ण
			count++;
		पूर्ण
	पूर्ण

	अगर (filter->dump_exceptions) अणु
		काष्ठा fib6_nh_exception_dump_walker w = अणु .dump = arg,
							   .rt = rt,
							   .flags = flags,
							   .skip = skip,
							   .count = 0 पूर्ण;
		पूर्णांक err;

		rcu_पढ़ो_lock();
		अगर (rt->nh) अणु
			err = nexthop_क्रम_each_fib6_nh(rt->nh,
						       rt6_nh_dump_exceptions,
						       &w);
		पूर्ण अन्यथा अणु
			err = rt6_nh_dump_exceptions(rt->fib6_nh, &w);
		पूर्ण
		rcu_पढ़ो_unlock();

		अगर (err)
			वापस count += w.count;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक inet6_rपंचांग_valid_getroute_req(काष्ठा sk_buff *skb,
					स्थिर काष्ठा nlmsghdr *nlh,
					काष्ठा nlattr **tb,
					काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rपंचांगsg *rपंचांग;
	पूर्णांक i, err;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*rपंचांग))) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Invalid header for get route request");
		वापस -EINVAL;
	पूर्ण

	अगर (!netlink_strict_get_check(skb))
		वापस nlmsg_parse_deprecated(nlh, माप(*rपंचांग), tb, RTA_MAX,
					      rपंचांग_ipv6_policy, extack);

	rपंचांग = nlmsg_data(nlh);
	अगर ((rपंचांग->rपंचांग_src_len && rपंचांग->rपंचांग_src_len != 128) ||
	    (rपंचांग->rपंचांग_dst_len && rपंचांग->rपंचांग_dst_len != 128) ||
	    rपंचांग->rपंचांग_table || rपंचांग->rपंचांग_protocol || rपंचांग->rपंचांग_scope ||
	    rपंचांग->rपंचांग_type) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid values in header for get route request");
		वापस -EINVAL;
	पूर्ण
	अगर (rपंचांग->rपंचांग_flags & ~RTM_F_FIB_MATCH) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Invalid flags for get route request");
		वापस -EINVAL;
	पूर्ण

	err = nlmsg_parse_deprecated_strict(nlh, माप(*rपंचांग), tb, RTA_MAX,
					    rपंचांग_ipv6_policy, extack);
	अगर (err)
		वापस err;

	अगर ((tb[RTA_SRC] && !rपंचांग->rपंचांग_src_len) ||
	    (tb[RTA_DST] && !rपंचांग->rपंचांग_dst_len)) अणु
		NL_SET_ERR_MSG_MOD(extack, "rtm_src_len and rtm_dst_len must be 128 for IPv6");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i <= RTA_MAX; i++) अणु
		अगर (!tb[i])
			जारी;

		चयन (i) अणु
		हाल RTA_SRC:
		हाल RTA_DST:
		हाल RTA_IIF:
		हाल RTA_OIF:
		हाल RTA_MARK:
		हाल RTA_UID:
		हाल RTA_SPORT:
		हाल RTA_DPORT:
		हाल RTA_IP_PROTO:
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_MOD(extack, "Unsupported attribute in get route request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inet6_rपंचांग_getroute(काष्ठा sk_buff *in_skb, काष्ठा nlmsghdr *nlh,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा nlattr *tb[RTA_MAX+1];
	पूर्णांक err, iअगर = 0, oअगर = 0;
	काष्ठा fib6_info *from;
	काष्ठा dst_entry *dst;
	काष्ठा rt6_info *rt;
	काष्ठा sk_buff *skb;
	काष्ठा rपंचांगsg *rपंचांग;
	काष्ठा flowi6 fl6 = अणुपूर्ण;
	bool fibmatch;

	err = inet6_rपंचांग_valid_getroute_req(in_skb, nlh, tb, extack);
	अगर (err < 0)
		जाओ errout;

	err = -EINVAL;
	rपंचांग = nlmsg_data(nlh);
	fl6.flowlabel = ip6_make_flowinfo(rपंचांग->rपंचांग_tos, 0);
	fibmatch = !!(rपंचांग->rपंचांग_flags & RTM_F_FIB_MATCH);

	अगर (tb[RTA_SRC]) अणु
		अगर (nla_len(tb[RTA_SRC]) < माप(काष्ठा in6_addr))
			जाओ errout;

		fl6.saddr = *(काष्ठा in6_addr *)nla_data(tb[RTA_SRC]);
	पूर्ण

	अगर (tb[RTA_DST]) अणु
		अगर (nla_len(tb[RTA_DST]) < माप(काष्ठा in6_addr))
			जाओ errout;

		fl6.daddr = *(काष्ठा in6_addr *)nla_data(tb[RTA_DST]);
	पूर्ण

	अगर (tb[RTA_IIF])
		iअगर = nla_get_u32(tb[RTA_IIF]);

	अगर (tb[RTA_OIF])
		oअगर = nla_get_u32(tb[RTA_OIF]);

	अगर (tb[RTA_MARK])
		fl6.flowi6_mark = nla_get_u32(tb[RTA_MARK]);

	अगर (tb[RTA_UID])
		fl6.flowi6_uid = make_kuid(current_user_ns(),
					   nla_get_u32(tb[RTA_UID]));
	अन्यथा
		fl6.flowi6_uid = iअगर ? INVALID_UID : current_uid();

	अगर (tb[RTA_SPORT])
		fl6.fl6_sport = nla_get_be16(tb[RTA_SPORT]);

	अगर (tb[RTA_DPORT])
		fl6.fl6_dport = nla_get_be16(tb[RTA_DPORT]);

	अगर (tb[RTA_IP_PROTO]) अणु
		err = rपंचांग_getroute_parse_ip_proto(tb[RTA_IP_PROTO],
						  &fl6.flowi6_proto, AF_INET6,
						  extack);
		अगर (err)
			जाओ errout;
	पूर्ण

	अगर (iअगर) अणु
		काष्ठा net_device *dev;
		पूर्णांक flags = 0;

		rcu_पढ़ो_lock();

		dev = dev_get_by_index_rcu(net, iअगर);
		अगर (!dev) अणु
			rcu_पढ़ो_unlock();
			err = -ENODEV;
			जाओ errout;
		पूर्ण

		fl6.flowi6_iअगर = iअगर;

		अगर (!ipv6_addr_any(&fl6.saddr))
			flags |= RT6_LOOKUP_F_HAS_SADDR;

		dst = ip6_route_input_lookup(net, dev, &fl6, शून्य, flags);

		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अणु
		fl6.flowi6_oअगर = oअगर;

		dst = ip6_route_output(net, शून्य, &fl6);
	पूर्ण


	rt = container_of(dst, काष्ठा rt6_info, dst);
	अगर (rt->dst.error) अणु
		err = rt->dst.error;
		ip6_rt_put(rt);
		जाओ errout;
	पूर्ण

	अगर (rt == net->ipv6.ip6_null_entry) अणु
		err = rt->dst.error;
		ip6_rt_put(rt);
		जाओ errout;
	पूर्ण

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb) अणु
		ip6_rt_put(rt);
		err = -ENOBUFS;
		जाओ errout;
	पूर्ण

	skb_dst_set(skb, &rt->dst);

	rcu_पढ़ो_lock();
	from = rcu_dereference(rt->from);
	अगर (from) अणु
		अगर (fibmatch)
			err = rt6_fill_node(net, skb, from, शून्य, शून्य, शून्य,
					    iअगर, RTM_NEWROUTE,
					    NETLINK_CB(in_skb).portid,
					    nlh->nlmsg_seq, 0);
		अन्यथा
			err = rt6_fill_node(net, skb, from, dst, &fl6.daddr,
					    &fl6.saddr, iअगर, RTM_NEWROUTE,
					    NETLINK_CB(in_skb).portid,
					    nlh->nlmsg_seq, 0);
	पूर्ण अन्यथा अणु
		err = -ENETUNREACH;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण

	err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);
errout:
	वापस err;
पूर्ण

व्योम inet6_rt_notअगरy(पूर्णांक event, काष्ठा fib6_info *rt, काष्ठा nl_info *info,
		     अचिन्हित पूर्णांक nlm_flags)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा net *net = info->nl_net;
	u32 seq;
	पूर्णांक err;

	err = -ENOBUFS;
	seq = info->nlh ? info->nlh->nlmsg_seq : 0;

	skb = nlmsg_new(rt6_nlmsg_size(rt), gfp_any());
	अगर (!skb)
		जाओ errout;

	err = rt6_fill_node(net, skb, rt, शून्य, शून्य, शून्य, 0,
			    event, info->portid, seq, nlm_flags);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in rt6_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	rtnl_notअगरy(skb, net, info->portid, RTNLGRP_IPV6_ROUTE,
		    info->nlh, gfp_any());
	वापस;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_IPV6_ROUTE, err);
पूर्ण

व्योम fib6_rt_update(काष्ठा net *net, काष्ठा fib6_info *rt,
		    काष्ठा nl_info *info)
अणु
	u32 seq = info->nlh ? info->nlh->nlmsg_seq : 0;
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(rt6_nlmsg_size(rt), gfp_any());
	अगर (!skb)
		जाओ errout;

	err = rt6_fill_node(net, skb, rt, शून्य, शून्य, शून्य, 0,
			    RTM_NEWROUTE, info->portid, seq, NLM_F_REPLACE);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in rt6_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	rtnl_notअगरy(skb, net, info->portid, RTNLGRP_IPV6_ROUTE,
		    info->nlh, gfp_any());
	वापस;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_IPV6_ROUTE, err);
पूर्ण

व्योम fib6_info_hw_flags_set(काष्ठा net *net, काष्ठा fib6_info *f6i,
			    bool offload, bool trap, bool offload_failed)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	अगर (f6i->offload == offload && f6i->trap == trap &&
	    f6i->offload_failed == offload_failed)
		वापस;

	f6i->offload = offload;
	f6i->trap = trap;

	/* 2 means send notअगरications only अगर offload_failed was changed. */
	अगर (net->ipv6.sysctl.fib_notअगरy_on_flag_change == 2 &&
	    f6i->offload_failed == offload_failed)
		वापस;

	f6i->offload_failed = offload_failed;

	अगर (!rcu_access_poपूर्णांकer(f6i->fib6_node))
		/* The route was हटाओd from the tree, करो not send
		 * notअगरication.
		 */
		वापस;

	अगर (!net->ipv6.sysctl.fib_notअगरy_on_flag_change)
		वापस;

	skb = nlmsg_new(rt6_nlmsg_size(f6i), GFP_KERNEL);
	अगर (!skb) अणु
		err = -ENOBUFS;
		जाओ errout;
	पूर्ण

	err = rt6_fill_node(net, skb, f6i, शून्य, शून्य, शून्य, 0, RTM_NEWROUTE, 0,
			    0, 0);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in rt6_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण

	rtnl_notअगरy(skb, net, 0, RTNLGRP_IPV6_ROUTE, शून्य, GFP_KERNEL);
	वापस;

errout:
	rtnl_set_sk_err(net, RTNLGRP_IPV6_ROUTE, err);
पूर्ण
EXPORT_SYMBOL(fib6_info_hw_flags_set);

अटल पूर्णांक ip6_route_dev_notअगरy(काष्ठा notअगरier_block *this,
				अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा net *net = dev_net(dev);

	अगर (!(dev->flags & IFF_LOOPBACK))
		वापस NOTIFY_OK;

	अगर (event == NETDEV_REGISTER) अणु
		net->ipv6.fib6_null_entry->fib6_nh->fib_nh_dev = dev;
		net->ipv6.ip6_null_entry->dst.dev = dev;
		net->ipv6.ip6_null_entry->rt6i_idev = in6_dev_get(dev);
#अगर_घोषित CONFIG_IPV6_MULTIPLE_TABLES
		net->ipv6.ip6_prohibit_entry->dst.dev = dev;
		net->ipv6.ip6_prohibit_entry->rt6i_idev = in6_dev_get(dev);
		net->ipv6.ip6_blk_hole_entry->dst.dev = dev;
		net->ipv6.ip6_blk_hole_entry->rt6i_idev = in6_dev_get(dev);
#पूर्ण_अगर
	 पूर्ण अन्यथा अगर (event == NETDEV_UNREGISTER &&
		    dev->reg_state != NETREG_UNREGISTERED) अणु
		/* NETDEV_UNREGISTER could be fired क्रम multiple बार by
		 * netdev_रुको_allrefs(). Make sure we only call this once.
		 */
		in6_dev_put_clear(&net->ipv6.ip6_null_entry->rt6i_idev);
#अगर_घोषित CONFIG_IPV6_MULTIPLE_TABLES
		in6_dev_put_clear(&net->ipv6.ip6_prohibit_entry->rt6i_idev);
		in6_dev_put_clear(&net->ipv6.ip6_blk_hole_entry->rt6i_idev);
#पूर्ण_अगर
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

/*
 *	/proc
 */

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक rt6_stats_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा net *net = (काष्ठा net *)seq->निजी;
	seq_म_लिखो(seq, "%04x %04x %04x %04x %04x %04x %04x\n",
		   net->ipv6.rt6_stats->fib_nodes,
		   net->ipv6.rt6_stats->fib_route_nodes,
		   atomic_पढ़ो(&net->ipv6.rt6_stats->fib_rt_alloc),
		   net->ipv6.rt6_stats->fib_rt_entries,
		   net->ipv6.rt6_stats->fib_rt_cache,
		   dst_entries_get_slow(&net->ipv6.ip6_dst_ops),
		   net->ipv6.rt6_stats->fib_discarded_routes);

	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_PROC_FS */

#अगर_घोषित CONFIG_SYSCTL

अटल पूर्णांक ipv6_sysctl_rtcache_flush(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
			      व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा net *net;
	पूर्णांक delay;
	पूर्णांक ret;
	अगर (!ग_लिखो)
		वापस -EINVAL;

	net = (काष्ठा net *)ctl->extra1;
	delay = net->ipv6.sysctl.flush_delay;
	ret = proc_करोपूर्णांकvec(ctl, ग_लिखो, buffer, lenp, ppos);
	अगर (ret)
		वापस ret;

	fib6_run_gc(delay <= 0 ? 0 : (अचिन्हित दीर्घ)delay, net, delay > 0);
	वापस 0;
पूर्ण

अटल काष्ठा ctl_table ipv6_route_table_ढाँचा[] = अणु
	अणु
		.procname	=	"flush",
		.data		=	&init_net.ipv6.sysctl.flush_delay,
		.maxlen		=	माप(पूर्णांक),
		.mode		=	0200,
		.proc_handler	=	ipv6_sysctl_rtcache_flush
	पूर्ण,
	अणु
		.procname	=	"gc_thresh",
		.data		=	&ip6_dst_ops_ढाँचा.gc_thresh,
		.maxlen		=	माप(पूर्णांक),
		.mode		=	0644,
		.proc_handler	=	proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	=	"max_size",
		.data		=	&init_net.ipv6.sysctl.ip6_rt_max_size,
		.maxlen		=	माप(पूर्णांक),
		.mode		=	0644,
		.proc_handler	=	proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	=	"gc_min_interval",
		.data		=	&init_net.ipv6.sysctl.ip6_rt_gc_min_पूर्णांकerval,
		.maxlen		=	माप(पूर्णांक),
		.mode		=	0644,
		.proc_handler	=	proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	=	"gc_timeout",
		.data		=	&init_net.ipv6.sysctl.ip6_rt_gc_समयout,
		.maxlen		=	माप(पूर्णांक),
		.mode		=	0644,
		.proc_handler	=	proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	=	"gc_interval",
		.data		=	&init_net.ipv6.sysctl.ip6_rt_gc_पूर्णांकerval,
		.maxlen		=	माप(पूर्णांक),
		.mode		=	0644,
		.proc_handler	=	proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	=	"gc_elasticity",
		.data		=	&init_net.ipv6.sysctl.ip6_rt_gc_elasticity,
		.maxlen		=	माप(पूर्णांक),
		.mode		=	0644,
		.proc_handler	=	proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	=	"mtu_expires",
		.data		=	&init_net.ipv6.sysctl.ip6_rt_mtu_expires,
		.maxlen		=	माप(पूर्णांक),
		.mode		=	0644,
		.proc_handler	=	proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	=	"min_adv_mss",
		.data		=	&init_net.ipv6.sysctl.ip6_rt_min_advmss,
		.maxlen		=	माप(पूर्णांक),
		.mode		=	0644,
		.proc_handler	=	proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	=	"gc_min_interval_ms",
		.data		=	&init_net.ipv6.sysctl.ip6_rt_gc_min_पूर्णांकerval,
		.maxlen		=	माप(पूर्णांक),
		.mode		=	0644,
		.proc_handler	=	proc_करोपूर्णांकvec_ms_jअगरfies,
	पूर्ण,
	अणु
		.procname	=	"skip_notify_on_dev_down",
		.data		=	&init_net.ipv6.sysctl.skip_notअगरy_on_dev_करोwn,
		.maxlen		=	माप(पूर्णांक),
		.mode		=	0644,
		.proc_handler	=	proc_करोपूर्णांकvec_minmax,
		.extra1		=	SYSCTL_ZERO,
		.extra2		=	SYSCTL_ONE,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

काष्ठा ctl_table * __net_init ipv6_route_sysctl_init(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;

	table = kmemdup(ipv6_route_table_ढाँचा,
			माप(ipv6_route_table_ढाँचा),
			GFP_KERNEL);

	अगर (table) अणु
		table[0].data = &net->ipv6.sysctl.flush_delay;
		table[0].extra1 = net;
		table[1].data = &net->ipv6.ip6_dst_ops.gc_thresh;
		table[2].data = &net->ipv6.sysctl.ip6_rt_max_size;
		table[3].data = &net->ipv6.sysctl.ip6_rt_gc_min_पूर्णांकerval;
		table[4].data = &net->ipv6.sysctl.ip6_rt_gc_समयout;
		table[5].data = &net->ipv6.sysctl.ip6_rt_gc_पूर्णांकerval;
		table[6].data = &net->ipv6.sysctl.ip6_rt_gc_elasticity;
		table[7].data = &net->ipv6.sysctl.ip6_rt_mtu_expires;
		table[8].data = &net->ipv6.sysctl.ip6_rt_min_advmss;
		table[9].data = &net->ipv6.sysctl.ip6_rt_gc_min_पूर्णांकerval;
		table[10].data = &net->ipv6.sysctl.skip_notअगरy_on_dev_करोwn;

		/* Don't export sysctls to unprivileged users */
		अगर (net->user_ns != &init_user_ns)
			table[0].procname = शून्य;
	पूर्ण

	वापस table;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __net_init ip6_route_net_init(काष्ठा net *net)
अणु
	पूर्णांक ret = -ENOMEM;

	स_नकल(&net->ipv6.ip6_dst_ops, &ip6_dst_ops_ढाँचा,
	       माप(net->ipv6.ip6_dst_ops));

	अगर (dst_entries_init(&net->ipv6.ip6_dst_ops) < 0)
		जाओ out_ip6_dst_ops;

	net->ipv6.fib6_null_entry = fib6_info_alloc(GFP_KERNEL, true);
	अगर (!net->ipv6.fib6_null_entry)
		जाओ out_ip6_dst_entries;
	स_नकल(net->ipv6.fib6_null_entry, &fib6_null_entry_ढाँचा,
	       माप(*net->ipv6.fib6_null_entry));

	net->ipv6.ip6_null_entry = kmemdup(&ip6_null_entry_ढाँचा,
					   माप(*net->ipv6.ip6_null_entry),
					   GFP_KERNEL);
	अगर (!net->ipv6.ip6_null_entry)
		जाओ out_fib6_null_entry;
	net->ipv6.ip6_null_entry->dst.ops = &net->ipv6.ip6_dst_ops;
	dst_init_metrics(&net->ipv6.ip6_null_entry->dst,
			 ip6_ढाँचा_metrics, true);
	INIT_LIST_HEAD(&net->ipv6.ip6_null_entry->rt6i_uncached);

#अगर_घोषित CONFIG_IPV6_MULTIPLE_TABLES
	net->ipv6.fib6_has_custom_rules = false;
	net->ipv6.ip6_prohibit_entry = kmemdup(&ip6_prohibit_entry_ढाँचा,
					       माप(*net->ipv6.ip6_prohibit_entry),
					       GFP_KERNEL);
	अगर (!net->ipv6.ip6_prohibit_entry)
		जाओ out_ip6_null_entry;
	net->ipv6.ip6_prohibit_entry->dst.ops = &net->ipv6.ip6_dst_ops;
	dst_init_metrics(&net->ipv6.ip6_prohibit_entry->dst,
			 ip6_ढाँचा_metrics, true);
	INIT_LIST_HEAD(&net->ipv6.ip6_prohibit_entry->rt6i_uncached);

	net->ipv6.ip6_blk_hole_entry = kmemdup(&ip6_blk_hole_entry_ढाँचा,
					       माप(*net->ipv6.ip6_blk_hole_entry),
					       GFP_KERNEL);
	अगर (!net->ipv6.ip6_blk_hole_entry)
		जाओ out_ip6_prohibit_entry;
	net->ipv6.ip6_blk_hole_entry->dst.ops = &net->ipv6.ip6_dst_ops;
	dst_init_metrics(&net->ipv6.ip6_blk_hole_entry->dst,
			 ip6_ढाँचा_metrics, true);
	INIT_LIST_HEAD(&net->ipv6.ip6_blk_hole_entry->rt6i_uncached);
#अगर_घोषित CONFIG_IPV6_SUBTREES
	net->ipv6.fib6_routes_require_src = 0;
#पूर्ण_अगर
#पूर्ण_अगर

	net->ipv6.sysctl.flush_delay = 0;
	net->ipv6.sysctl.ip6_rt_max_size = 4096;
	net->ipv6.sysctl.ip6_rt_gc_min_पूर्णांकerval = HZ / 2;
	net->ipv6.sysctl.ip6_rt_gc_समयout = 60*HZ;
	net->ipv6.sysctl.ip6_rt_gc_पूर्णांकerval = 30*HZ;
	net->ipv6.sysctl.ip6_rt_gc_elasticity = 9;
	net->ipv6.sysctl.ip6_rt_mtu_expires = 10*60*HZ;
	net->ipv6.sysctl.ip6_rt_min_advmss = IPV6_MIN_MTU - 20 - 40;
	net->ipv6.sysctl.skip_notअगरy_on_dev_करोwn = 0;

	net->ipv6.ip6_rt_gc_expire = 30*HZ;

	ret = 0;
out:
	वापस ret;

#अगर_घोषित CONFIG_IPV6_MULTIPLE_TABLES
out_ip6_prohibit_entry:
	kमुक्त(net->ipv6.ip6_prohibit_entry);
out_ip6_null_entry:
	kमुक्त(net->ipv6.ip6_null_entry);
#पूर्ण_अगर
out_fib6_null_entry:
	kमुक्त(net->ipv6.fib6_null_entry);
out_ip6_dst_entries:
	dst_entries_destroy(&net->ipv6.ip6_dst_ops);
out_ip6_dst_ops:
	जाओ out;
पूर्ण

अटल व्योम __net_निकास ip6_route_net_निकास(काष्ठा net *net)
अणु
	kमुक्त(net->ipv6.fib6_null_entry);
	kमुक्त(net->ipv6.ip6_null_entry);
#अगर_घोषित CONFIG_IPV6_MULTIPLE_TABLES
	kमुक्त(net->ipv6.ip6_prohibit_entry);
	kमुक्त(net->ipv6.ip6_blk_hole_entry);
#पूर्ण_अगर
	dst_entries_destroy(&net->ipv6.ip6_dst_ops);
पूर्ण

अटल पूर्णांक __net_init ip6_route_net_init_late(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_PROC_FS
	proc_create_net("ipv6_route", 0, net->proc_net, &ipv6_route_seq_ops,
			माप(काष्ठा ipv6_route_iter));
	proc_create_net_single("rt6_stats", 0444, net->proc_net,
			rt6_stats_seq_show, शून्य);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम __net_निकास ip6_route_net_निकास_late(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_PROC_FS
	हटाओ_proc_entry("ipv6_route", net->proc_net);
	हटाओ_proc_entry("rt6_stats", net->proc_net);
#पूर्ण_अगर
पूर्ण

अटल काष्ठा pernet_operations ip6_route_net_ops = अणु
	.init = ip6_route_net_init,
	.निकास = ip6_route_net_निकास,
पूर्ण;

अटल पूर्णांक __net_init ipv6_inetpeer_init(काष्ठा net *net)
अणु
	काष्ठा inet_peer_base *bp = kदो_स्मृति(माप(*bp), GFP_KERNEL);

	अगर (!bp)
		वापस -ENOMEM;
	inet_peer_base_init(bp);
	net->ipv6.peers = bp;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास ipv6_inetpeer_निकास(काष्ठा net *net)
अणु
	काष्ठा inet_peer_base *bp = net->ipv6.peers;

	net->ipv6.peers = शून्य;
	inetpeer_invalidate_tree(bp);
	kमुक्त(bp);
पूर्ण

अटल काष्ठा pernet_operations ipv6_inetpeer_ops = अणु
	.init	=	ipv6_inetpeer_init,
	.निकास	=	ipv6_inetpeer_निकास,
पूर्ण;

अटल काष्ठा pernet_operations ip6_route_net_late_ops = अणु
	.init = ip6_route_net_init_late,
	.निकास = ip6_route_net_निकास_late,
पूर्ण;

अटल काष्ठा notअगरier_block ip6_route_dev_notअगरier = अणु
	.notअगरier_call = ip6_route_dev_notअगरy,
	.priority = ADDRCONF_NOTIFY_PRIORITY - 10,
पूर्ण;

व्योम __init ip6_route_init_special_entries(व्योम)
अणु
	/* Registering of the loopback is करोne beक्रमe this portion of code,
	 * the loopback reference in rt6_info will not be taken, करो it
	 * manually क्रम init_net */
	init_net.ipv6.fib6_null_entry->fib6_nh->fib_nh_dev = init_net.loopback_dev;
	init_net.ipv6.ip6_null_entry->dst.dev = init_net.loopback_dev;
	init_net.ipv6.ip6_null_entry->rt6i_idev = in6_dev_get(init_net.loopback_dev);
  #अगर_घोषित CONFIG_IPV6_MULTIPLE_TABLES
	init_net.ipv6.ip6_prohibit_entry->dst.dev = init_net.loopback_dev;
	init_net.ipv6.ip6_prohibit_entry->rt6i_idev = in6_dev_get(init_net.loopback_dev);
	init_net.ipv6.ip6_blk_hole_entry->dst.dev = init_net.loopback_dev;
	init_net.ipv6.ip6_blk_hole_entry->rt6i_idev = in6_dev_get(init_net.loopback_dev);
  #पूर्ण_अगर
पूर्ण

#अगर IS_BUILTIN(CONFIG_IPV6)
#अगर defined(CONFIG_BPF_SYSCALL) && defined(CONFIG_PROC_FS)
DEFINE_BPF_ITER_FUNC(ipv6_route, काष्ठा bpf_iter_meta *meta, काष्ठा fib6_info *rt)

BTF_ID_LIST(btf_fib6_info_id)
BTF_ID(काष्ठा, fib6_info)

अटल स्थिर काष्ठा bpf_iter_seq_info ipv6_route_seq_info = अणु
	.seq_ops		= &ipv6_route_seq_ops,
	.init_seq_निजी	= bpf_iter_init_seq_net,
	.fini_seq_निजी	= bpf_iter_fini_seq_net,
	.seq_priv_size		= माप(काष्ठा ipv6_route_iter),
पूर्ण;

अटल काष्ठा bpf_iter_reg ipv6_route_reg_info = अणु
	.target			= "ipv6_route",
	.ctx_arg_info_size	= 1,
	.ctx_arg_info		= अणु
		अणु दुरत्व(काष्ठा bpf_iter__ipv6_route, rt),
		  PTR_TO_BTF_ID_OR_शून्य पूर्ण,
	पूर्ण,
	.seq_info		= &ipv6_route_seq_info,
पूर्ण;

अटल पूर्णांक __init bpf_iter_रेजिस्टर(व्योम)
अणु
	ipv6_route_reg_info.ctx_arg_info[0].btf_id = *btf_fib6_info_id;
	वापस bpf_iter_reg_target(&ipv6_route_reg_info);
पूर्ण

अटल व्योम bpf_iter_unरेजिस्टर(व्योम)
अणु
	bpf_iter_unreg_target(&ipv6_route_reg_info);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

पूर्णांक __init ip6_route_init(व्योम)
अणु
	पूर्णांक ret;
	पूर्णांक cpu;

	ret = -ENOMEM;
	ip6_dst_ops_ढाँचा.kmem_cachep =
		kmem_cache_create("ip6_dst_cache", माप(काष्ठा rt6_info), 0,
				  SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!ip6_dst_ops_ढाँचा.kmem_cachep)
		जाओ out;

	ret = dst_entries_init(&ip6_dst_blackhole_ops);
	अगर (ret)
		जाओ out_kmem_cache;

	ret = रेजिस्टर_pernet_subsys(&ipv6_inetpeer_ops);
	अगर (ret)
		जाओ out_dst_entries;

	ret = रेजिस्टर_pernet_subsys(&ip6_route_net_ops);
	अगर (ret)
		जाओ out_रेजिस्टर_inetpeer;

	ip6_dst_blackhole_ops.kmem_cachep = ip6_dst_ops_ढाँचा.kmem_cachep;

	ret = fib6_init();
	अगर (ret)
		जाओ out_रेजिस्टर_subsys;

	ret = xfrm6_init();
	अगर (ret)
		जाओ out_fib6_init;

	ret = fib6_rules_init();
	अगर (ret)
		जाओ xfrm6_init;

	ret = रेजिस्टर_pernet_subsys(&ip6_route_net_late_ops);
	अगर (ret)
		जाओ fib6_rules_init;

	ret = rtnl_रेजिस्टर_module(THIS_MODULE, PF_INET6, RTM_NEWROUTE,
				   inet6_rपंचांग_newroute, शून्य, 0);
	अगर (ret < 0)
		जाओ out_रेजिस्टर_late_subsys;

	ret = rtnl_रेजिस्टर_module(THIS_MODULE, PF_INET6, RTM_DELROUTE,
				   inet6_rपंचांग_delroute, शून्य, 0);
	अगर (ret < 0)
		जाओ out_रेजिस्टर_late_subsys;

	ret = rtnl_रेजिस्टर_module(THIS_MODULE, PF_INET6, RTM_GETROUTE,
				   inet6_rपंचांग_getroute, शून्य,
				   RTNL_FLAG_DOIT_UNLOCKED);
	अगर (ret < 0)
		जाओ out_रेजिस्टर_late_subsys;

	ret = रेजिस्टर_netdevice_notअगरier(&ip6_route_dev_notअगरier);
	अगर (ret)
		जाओ out_रेजिस्टर_late_subsys;

#अगर IS_BUILTIN(CONFIG_IPV6)
#अगर defined(CONFIG_BPF_SYSCALL) && defined(CONFIG_PROC_FS)
	ret = bpf_iter_रेजिस्टर();
	अगर (ret)
		जाओ out_रेजिस्टर_late_subsys;
#पूर्ण_अगर
#पूर्ण_अगर

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा uncached_list *ul = per_cpu_ptr(&rt6_uncached_list, cpu);

		INIT_LIST_HEAD(&ul->head);
		spin_lock_init(&ul->lock);
	पूर्ण

out:
	वापस ret;

out_रेजिस्टर_late_subsys:
	rtnl_unरेजिस्टर_all(PF_INET6);
	unरेजिस्टर_pernet_subsys(&ip6_route_net_late_ops);
fib6_rules_init:
	fib6_rules_cleanup();
xfrm6_init:
	xfrm6_fini();
out_fib6_init:
	fib6_gc_cleanup();
out_रेजिस्टर_subsys:
	unरेजिस्टर_pernet_subsys(&ip6_route_net_ops);
out_रेजिस्टर_inetpeer:
	unरेजिस्टर_pernet_subsys(&ipv6_inetpeer_ops);
out_dst_entries:
	dst_entries_destroy(&ip6_dst_blackhole_ops);
out_kmem_cache:
	kmem_cache_destroy(ip6_dst_ops_ढाँचा.kmem_cachep);
	जाओ out;
पूर्ण

व्योम ip6_route_cleanup(व्योम)
अणु
#अगर IS_BUILTIN(CONFIG_IPV6)
#अगर defined(CONFIG_BPF_SYSCALL) && defined(CONFIG_PROC_FS)
	bpf_iter_unरेजिस्टर();
#पूर्ण_अगर
#पूर्ण_अगर
	unरेजिस्टर_netdevice_notअगरier(&ip6_route_dev_notअगरier);
	unरेजिस्टर_pernet_subsys(&ip6_route_net_late_ops);
	fib6_rules_cleanup();
	xfrm6_fini();
	fib6_gc_cleanup();
	unरेजिस्टर_pernet_subsys(&ipv6_inetpeer_ops);
	unरेजिस्टर_pernet_subsys(&ip6_route_net_ops);
	dst_entries_destroy(&ip6_dst_blackhole_ops);
	kmem_cache_destroy(ip6_dst_ops_ढाँचा.kmem_cachep);
पूर्ण
