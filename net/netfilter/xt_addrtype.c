<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  iptables module to match inet_addr_type() of an ip.
 *
 *  Copyright (c) 2004 Patrick McHardy <kaber@trash.net>
 *  (C) 2007 Laszlo Attila Toth <panther@balabit.hu>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ip.h>
#समावेश <net/route.h>

#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/ip6_fib.h>
#पूर्ण_अगर

#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter/xt_addrtype.h>
#समावेश <linux/netfilter/x_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_DESCRIPTION("Xtables: address type match");
MODULE_ALIAS("ipt_addrtype");
MODULE_ALIAS("ip6t_addrtype");

#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
अटल u32 match_lookup_rt6(काष्ठा net *net, स्थिर काष्ठा net_device *dev,
			    स्थिर काष्ठा in6_addr *addr, u16 mask)
अणु
	काष्ठा flowi6 flow;
	काष्ठा rt6_info *rt;
	u32 ret = 0;
	पूर्णांक route_err;

	स_रखो(&flow, 0, माप(flow));
	flow.daddr = *addr;
	अगर (dev)
		flow.flowi6_oअगर = dev->अगरindex;

	अगर (dev && (mask & XT_ADDRTYPE_LOCAL)) अणु
		अगर (nf_ipv6_chk_addr(net, addr, dev, true))
			ret = XT_ADDRTYPE_LOCAL;
	पूर्ण

	route_err = nf_ip6_route(net, (काष्ठा dst_entry **)&rt,
				 flowi6_to_flowi(&flow), false);
	अगर (route_err)
		वापस XT_ADDRTYPE_UNREACHABLE;

	अगर (rt->rt6i_flags & RTF_REJECT)
		ret = XT_ADDRTYPE_UNREACHABLE;

	अगर (dev == शून्य && rt->rt6i_flags & RTF_LOCAL)
		ret |= XT_ADDRTYPE_LOCAL;
	अगर (ipv6_anycast_destination((काष्ठा dst_entry *)rt, addr))
		ret |= XT_ADDRTYPE_ANYCAST;

	dst_release(&rt->dst);
	वापस ret;
पूर्ण

अटल bool match_type6(काष्ठा net *net, स्थिर काष्ठा net_device *dev,
				स्थिर काष्ठा in6_addr *addr, u16 mask)
अणु
	पूर्णांक addr_type = ipv6_addr_type(addr);

	अगर ((mask & XT_ADDRTYPE_MULTICAST) &&
	    !(addr_type & IPV6_ADDR_MULTICAST))
		वापस false;
	अगर ((mask & XT_ADDRTYPE_UNICAST) && !(addr_type & IPV6_ADDR_UNICAST))
		वापस false;
	अगर ((mask & XT_ADDRTYPE_UNSPEC) && addr_type != IPV6_ADDR_ANY)
		वापस false;

	अगर ((XT_ADDRTYPE_LOCAL | XT_ADDRTYPE_ANYCAST |
	     XT_ADDRTYPE_UNREACHABLE) & mask)
		वापस !!(mask & match_lookup_rt6(net, dev, addr, mask));
	वापस true;
पूर्ण

अटल bool
addrtype_mt6(काष्ठा net *net, स्थिर काष्ठा net_device *dev,
	स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा xt_addrtype_info_v1 *info)
अणु
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	bool ret = true;

	अगर (info->source)
		ret &= match_type6(net, dev, &iph->saddr, info->source) ^
		       (info->flags & XT_ADDRTYPE_INVERT_SOURCE);
	अगर (ret && info->dest)
		ret &= match_type6(net, dev, &iph->daddr, info->dest) ^
		       !!(info->flags & XT_ADDRTYPE_INVERT_DEST);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool match_type(काष्ठा net *net, स्थिर काष्ठा net_device *dev,
			      __be32 addr, u_पूर्णांक16_t mask)
अणु
	वापस !!(mask & (1 << inet_dev_addr_type(net, dev, addr)));
पूर्ण

अटल bool
addrtype_mt_v0(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	काष्ठा net *net = xt_net(par);
	स्थिर काष्ठा xt_addrtype_info *info = par->matchinfo;
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	bool ret = true;

	अगर (info->source)
		ret &= match_type(net, शून्य, iph->saddr, info->source) ^
		       info->invert_source;
	अगर (info->dest)
		ret &= match_type(net, शून्य, iph->daddr, info->dest) ^
		       info->invert_dest;

	वापस ret;
पूर्ण

अटल bool
addrtype_mt_v1(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	काष्ठा net *net = xt_net(par);
	स्थिर काष्ठा xt_addrtype_info_v1 *info = par->matchinfo;
	स्थिर काष्ठा iphdr *iph;
	स्थिर काष्ठा net_device *dev = शून्य;
	bool ret = true;

	अगर (info->flags & XT_ADDRTYPE_LIMIT_IFACE_IN)
		dev = xt_in(par);
	अन्यथा अगर (info->flags & XT_ADDRTYPE_LIMIT_IFACE_OUT)
		dev = xt_out(par);

#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	अगर (xt_family(par) == NFPROTO_IPV6)
		वापस addrtype_mt6(net, dev, skb, info);
#पूर्ण_अगर
	iph = ip_hdr(skb);
	अगर (info->source)
		ret &= match_type(net, dev, iph->saddr, info->source) ^
		       (info->flags & XT_ADDRTYPE_INVERT_SOURCE);
	अगर (ret && info->dest)
		ret &= match_type(net, dev, iph->daddr, info->dest) ^
		       !!(info->flags & XT_ADDRTYPE_INVERT_DEST);
	वापस ret;
पूर्ण

अटल पूर्णांक addrtype_mt_checkentry_v1(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर अक्षर *errmsg = "both incoming and outgoing interface limitation cannot be selected";
	काष्ठा xt_addrtype_info_v1 *info = par->matchinfo;

	अगर (info->flags & XT_ADDRTYPE_LIMIT_IFACE_IN &&
	    info->flags & XT_ADDRTYPE_LIMIT_IFACE_OUT)
		जाओ err;

	अगर (par->hook_mask & ((1 << NF_INET_PRE_ROUTING) |
	    (1 << NF_INET_LOCAL_IN)) &&
	    info->flags & XT_ADDRTYPE_LIMIT_IFACE_OUT) अणु
		errmsg = "output interface limitation not valid in PREROUTING and INPUT";
		जाओ err;
	पूर्ण

	अगर (par->hook_mask & ((1 << NF_INET_POST_ROUTING) |
	    (1 << NF_INET_LOCAL_OUT)) &&
	    info->flags & XT_ADDRTYPE_LIMIT_IFACE_IN) अणु
		errmsg = "input interface limitation not valid in POSTROUTING and OUTPUT";
		जाओ err;
	पूर्ण

#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	अगर (par->family == NFPROTO_IPV6) अणु
		अगर ((info->source | info->dest) & XT_ADDRTYPE_BLACKHOLE) अणु
			errmsg = "ipv6 BLACKHOLE matching not supported";
			जाओ err;
		पूर्ण
		अगर ((info->source | info->dest) >= XT_ADDRTYPE_PROHIBIT) अणु
			errmsg = "ipv6 PROHIBIT (THROW, NAT ..) matching not supported";
			जाओ err;
		पूर्ण
		अगर ((info->source | info->dest) & XT_ADDRTYPE_BROADCAST) अणु
			errmsg = "ipv6 does not support BROADCAST matching";
			जाओ err;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
err:
	pr_info_ratelimited("%s\n", errmsg);
	वापस -EINVAL;
पूर्ण

अटल काष्ठा xt_match addrtype_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "addrtype",
		.family		= NFPROTO_IPV4,
		.match		= addrtype_mt_v0,
		.matchsize	= माप(काष्ठा xt_addrtype_info),
		.me		= THIS_MODULE
	पूर्ण,
	अणु
		.name		= "addrtype",
		.family		= NFPROTO_UNSPEC,
		.revision	= 1,
		.match		= addrtype_mt_v1,
		.checkentry	= addrtype_mt_checkentry_v1,
		.matchsize	= माप(काष्ठा xt_addrtype_info_v1),
		.me		= THIS_MODULE
	पूर्ण
पूर्ण;

अटल पूर्णांक __init addrtype_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(addrtype_mt_reg,
				   ARRAY_SIZE(addrtype_mt_reg));
पूर्ण

अटल व्योम __निकास addrtype_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(addrtype_mt_reg, ARRAY_SIZE(addrtype_mt_reg));
पूर्ण

module_init(addrtype_mt_init);
module_निकास(addrtype_mt_निकास);
