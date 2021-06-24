<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 2000-2001 Svenning Soerensen <svenning@post5.tele.dk>
 * Copyright (c) 2011 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/ip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <net/netfilter/nf_nat.h>

अटल अचिन्हित पूर्णांक
neपंचांगap_tg6(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा nf_nat_range2 *range = par->targinfo;
	काष्ठा nf_nat_range2 newrange;
	काष्ठा nf_conn *ct;
	क्रमागत ip_conntrack_info ctinfo;
	जोड़ nf_inet_addr new_addr, neपंचांगask;
	अचिन्हित पूर्णांक i;

	ct = nf_ct_get(skb, &ctinfo);
	क्रम (i = 0; i < ARRAY_SIZE(range->min_addr.ip6); i++)
		neपंचांगask.ip6[i] = ~(range->min_addr.ip6[i] ^
				   range->max_addr.ip6[i]);

	अगर (xt_hooknum(par) == NF_INET_PRE_ROUTING ||
	    xt_hooknum(par) == NF_INET_LOCAL_OUT)
		new_addr.in6 = ipv6_hdr(skb)->daddr;
	अन्यथा
		new_addr.in6 = ipv6_hdr(skb)->saddr;

	क्रम (i = 0; i < ARRAY_SIZE(new_addr.ip6); i++) अणु
		new_addr.ip6[i] &= ~neपंचांगask.ip6[i];
		new_addr.ip6[i] |= range->min_addr.ip6[i] &
				   neपंचांगask.ip6[i];
	पूर्ण

	newrange.flags	= range->flags | NF_NAT_RANGE_MAP_IPS;
	newrange.min_addr	= new_addr;
	newrange.max_addr	= new_addr;
	newrange.min_proto	= range->min_proto;
	newrange.max_proto	= range->max_proto;

	वापस nf_nat_setup_info(ct, &newrange, HOOK2MANIP(xt_hooknum(par)));
पूर्ण

अटल पूर्णांक neपंचांगap_tg6_checkentry(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा nf_nat_range2 *range = par->targinfo;

	अगर (!(range->flags & NF_NAT_RANGE_MAP_IPS))
		वापस -EINVAL;
	वापस nf_ct_netns_get(par->net, par->family);
पूर्ण

अटल व्योम neपंचांगap_tg_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	nf_ct_netns_put(par->net, par->family);
पूर्ण

अटल अचिन्हित पूर्णांक
neपंचांगap_tg4(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	काष्ठा nf_conn *ct;
	क्रमागत ip_conntrack_info ctinfo;
	__be32 new_ip, neपंचांगask;
	स्थिर काष्ठा nf_nat_ipv4_multi_range_compat *mr = par->targinfo;
	काष्ठा nf_nat_range2 newrange;

	WARN_ON(xt_hooknum(par) != NF_INET_PRE_ROUTING &&
		xt_hooknum(par) != NF_INET_POST_ROUTING &&
		xt_hooknum(par) != NF_INET_LOCAL_OUT &&
		xt_hooknum(par) != NF_INET_LOCAL_IN);
	ct = nf_ct_get(skb, &ctinfo);

	neपंचांगask = ~(mr->range[0].min_ip ^ mr->range[0].max_ip);

	अगर (xt_hooknum(par) == NF_INET_PRE_ROUTING ||
	    xt_hooknum(par) == NF_INET_LOCAL_OUT)
		new_ip = ip_hdr(skb)->daddr & ~neपंचांगask;
	अन्यथा
		new_ip = ip_hdr(skb)->saddr & ~neपंचांगask;
	new_ip |= mr->range[0].min_ip & neपंचांगask;

	स_रखो(&newrange.min_addr, 0, माप(newrange.min_addr));
	स_रखो(&newrange.max_addr, 0, माप(newrange.max_addr));
	newrange.flags	     = mr->range[0].flags | NF_NAT_RANGE_MAP_IPS;
	newrange.min_addr.ip = new_ip;
	newrange.max_addr.ip = new_ip;
	newrange.min_proto   = mr->range[0].min;
	newrange.max_proto   = mr->range[0].max;

	/* Hand modअगरied range to generic setup. */
	वापस nf_nat_setup_info(ct, &newrange, HOOK2MANIP(xt_hooknum(par)));
पूर्ण

अटल पूर्णांक neपंचांगap_tg4_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा nf_nat_ipv4_multi_range_compat *mr = par->targinfo;

	अगर (!(mr->range[0].flags & NF_NAT_RANGE_MAP_IPS)) अणु
		pr_debug("bad MAP_IPS.\n");
		वापस -EINVAL;
	पूर्ण
	अगर (mr->rangesize != 1) अणु
		pr_debug("bad rangesize %u.\n", mr->rangesize);
		वापस -EINVAL;
	पूर्ण
	वापस nf_ct_netns_get(par->net, par->family);
पूर्ण

अटल काष्ठा xt_target neपंचांगap_tg_reg[] __पढ़ो_mostly = अणु
	अणु
		.name       = "NETMAP",
		.family     = NFPROTO_IPV6,
		.revision   = 0,
		.target     = neपंचांगap_tg6,
		.tarमाला_लोize = माप(काष्ठा nf_nat_range),
		.table      = "nat",
		.hooks      = (1 << NF_INET_PRE_ROUTING) |
		              (1 << NF_INET_POST_ROUTING) |
		              (1 << NF_INET_LOCAL_OUT) |
		              (1 << NF_INET_LOCAL_IN),
		.checkentry = neपंचांगap_tg6_checkentry,
		.destroy    = neपंचांगap_tg_destroy,
		.me         = THIS_MODULE,
	पूर्ण,
	अणु
		.name       = "NETMAP",
		.family     = NFPROTO_IPV4,
		.revision   = 0,
		.target     = neपंचांगap_tg4,
		.tarमाला_लोize = माप(काष्ठा nf_nat_ipv4_multi_range_compat),
		.table      = "nat",
		.hooks      = (1 << NF_INET_PRE_ROUTING) |
		              (1 << NF_INET_POST_ROUTING) |
		              (1 << NF_INET_LOCAL_OUT) |
		              (1 << NF_INET_LOCAL_IN),
		.checkentry = neपंचांगap_tg4_check,
		.destroy    = neपंचांगap_tg_destroy,
		.me         = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init neपंचांगap_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_tarमाला_लो(neपंचांगap_tg_reg, ARRAY_SIZE(neपंचांगap_tg_reg));
पूर्ण

अटल व्योम neपंचांगap_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(neपंचांगap_tg_reg, ARRAY_SIZE(neपंचांगap_tg_reg));
पूर्ण

module_init(neपंचांगap_tg_init);
module_निकास(neपंचांगap_tg_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Xtables: 1:1 NAT mapping of subnets");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_ALIAS("ip6t_NETMAP");
MODULE_ALIAS("ipt_NETMAP");
