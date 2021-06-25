<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011 Florian Westphal <fw@म_माप.de>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/route.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/ip6_route.h>

#समावेश <linux/netfilter/xt_rpfilter.h>
#समावेश <linux/netfilter/x_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Florian Westphal <fw@strlen.de>");
MODULE_DESCRIPTION("Xtables: IPv6 reverse path filter match");

अटल bool rpfilter_addr_unicast(स्थिर काष्ठा in6_addr *addr)
अणु
	पूर्णांक addr_type = ipv6_addr_type(addr);
	वापस addr_type & IPV6_ADDR_UNICAST;
पूर्ण

अटल bool rpfilter_addr_linklocal(स्थिर काष्ठा in6_addr *addr)
अणु
	पूर्णांक addr_type = ipv6_addr_type(addr);
	वापस addr_type & IPV6_ADDR_LINKLOCAL;
पूर्ण

अटल bool rpfilter_lookup_reverse6(काष्ठा net *net, स्थिर काष्ठा sk_buff *skb,
				     स्थिर काष्ठा net_device *dev, u8 flags)
अणु
	काष्ठा rt6_info *rt;
	काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	bool ret = false;
	काष्ठा flowi6 fl6 = अणु
		.flowi6_iअगर = LOOPBACK_IFINDEX,
		.flowlabel = (* (__be32 *) iph) & IPV6_FLOWINFO_MASK,
		.flowi6_proto = iph->nexthdr,
		.daddr = iph->saddr,
	पूर्ण;
	पूर्णांक lookup_flags;

	अगर (rpfilter_addr_unicast(&iph->daddr)) अणु
		स_नकल(&fl6.saddr, &iph->daddr, माप(काष्ठा in6_addr));
		lookup_flags = RT6_LOOKUP_F_HAS_SADDR;
	पूर्ण अन्यथा अणु
		lookup_flags = 0;
	पूर्ण

	fl6.flowi6_mark = flags & XT_RPFILTER_VALID_MARK ? skb->mark : 0;

	अगर (rpfilter_addr_linklocal(&iph->saddr)) अणु
		lookup_flags |= RT6_LOOKUP_F_IFACE;
		fl6.flowi6_oअगर = dev->अगरindex;
	/* Set flowi6_oअगर क्रम vrf devices to lookup route in l3mdev करोमुख्य. */
	पूर्ण अन्यथा अगर (netअगर_is_l3_master(dev) || netअगर_is_l3_slave(dev) ||
		  (flags & XT_RPFILTER_LOOSE) == 0)
		fl6.flowi6_oअगर = dev->अगरindex;

	rt = (व्योम *)ip6_route_lookup(net, &fl6, skb, lookup_flags);
	अगर (rt->dst.error)
		जाओ out;

	अगर (rt->rt6i_flags & (RTF_REJECT|RTF_ANYCAST))
		जाओ out;

	अगर (rt->rt6i_flags & RTF_LOCAL) अणु
		ret = flags & XT_RPFILTER_ACCEPT_LOCAL;
		जाओ out;
	पूर्ण

	अगर (rt->rt6i_idev->dev == dev ||
	    l3mdev_master_अगरindex_rcu(rt->rt6i_idev->dev) == dev->अगरindex ||
	    (flags & XT_RPFILTER_LOOSE))
		ret = true;
 out:
	ip6_rt_put(rt);
	वापस ret;
पूर्ण

अटल bool
rpfilter_is_loopback(स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *in)
अणु
	वापस skb->pkt_type == PACKET_LOOPBACK || in->flags & IFF_LOOPBACK;
पूर्ण

अटल bool rpfilter_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_rpfilter_info *info = par->matchinfo;
	पूर्णांक saddrtype;
	काष्ठा ipv6hdr *iph;
	bool invert = info->flags & XT_RPFILTER_INVERT;

	अगर (rpfilter_is_loopback(skb, xt_in(par)))
		वापस true ^ invert;

	iph = ipv6_hdr(skb);
	saddrtype = ipv6_addr_type(&iph->saddr);
	अगर (unlikely(saddrtype == IPV6_ADDR_ANY))
		वापस true ^ invert; /* not routable: क्रमward path will drop it */

	वापस rpfilter_lookup_reverse6(xt_net(par), skb, xt_in(par),
					info->flags) ^ invert;
पूर्ण

अटल पूर्णांक rpfilter_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_rpfilter_info *info = par->matchinfo;
	अचिन्हित पूर्णांक options = ~XT_RPFILTER_OPTION_MASK;

	अगर (info->flags & options) अणु
		pr_info_ratelimited("unknown options\n");
		वापस -EINVAL;
	पूर्ण

	अगर (म_भेद(par->table, "mangle") != 0 &&
	    म_भेद(par->table, "raw") != 0) अणु
		pr_info_ratelimited("only valid in \'raw\' or \'mangle\' table, not \'%s\'\n",
				    par->table);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा xt_match rpfilter_mt_reg __पढ़ो_mostly = अणु
	.name		= "rpfilter",
	.family		= NFPROTO_IPV6,
	.checkentry	= rpfilter_check,
	.match		= rpfilter_mt,
	.matchsize	= माप(काष्ठा xt_rpfilter_info),
	.hooks		= (1 << NF_INET_PRE_ROUTING),
	.me		= THIS_MODULE
पूर्ण;

अटल पूर्णांक __init rpfilter_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&rpfilter_mt_reg);
पूर्ण

अटल व्योम __निकास rpfilter_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&rpfilter_mt_reg);
पूर्ण

module_init(rpfilter_mt_init);
module_निकास(rpfilter_mt_निकास);
