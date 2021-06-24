<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2006 Netfilter Core Team <coreteam@netfilter.org>
 * Copyright (c) 2011 Patrick McHardy <kaber@trash.net>
 *
 * Based on Rusty Russell's IPv4 REसूचीECT target. Development of IPv6
 * NAT funded by Astaro.
 */

#समावेश <linux/अगर.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/types.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <net/addrconf.h>
#समावेश <net/checksum.h>
#समावेश <net/protocol.h>
#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_nat_redirect.h>

अटल अचिन्हित पूर्णांक
redirect_tg6(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	वापस nf_nat_redirect_ipv6(skb, par->targinfo, xt_hooknum(par));
पूर्ण

अटल पूर्णांक redirect_tg6_checkentry(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा nf_nat_range2 *range = par->targinfo;

	अगर (range->flags & NF_NAT_RANGE_MAP_IPS)
		वापस -EINVAL;

	वापस nf_ct_netns_get(par->net, par->family);
पूर्ण

अटल व्योम redirect_tg_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	nf_ct_netns_put(par->net, par->family);
पूर्ण

/* FIXME: Take multiple ranges --RR */
अटल पूर्णांक redirect_tg4_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा nf_nat_ipv4_multi_range_compat *mr = par->targinfo;

	अगर (mr->range[0].flags & NF_NAT_RANGE_MAP_IPS) अणु
		pr_debug("bad MAP_IPS.\n");
		वापस -EINVAL;
	पूर्ण
	अगर (mr->rangesize != 1) अणु
		pr_debug("bad rangesize %u.\n", mr->rangesize);
		वापस -EINVAL;
	पूर्ण
	वापस nf_ct_netns_get(par->net, par->family);
पूर्ण

अटल अचिन्हित पूर्णांक
redirect_tg4(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	वापस nf_nat_redirect_ipv4(skb, par->targinfo, xt_hooknum(par));
पूर्ण

अटल काष्ठा xt_target redirect_tg_reg[] __पढ़ो_mostly = अणु
	अणु
		.name       = "REDIRECT",
		.family     = NFPROTO_IPV6,
		.revision   = 0,
		.table      = "nat",
		.checkentry = redirect_tg6_checkentry,
		.destroy    = redirect_tg_destroy,
		.target     = redirect_tg6,
		.tarमाला_लोize = माप(काष्ठा nf_nat_range),
		.hooks      = (1 << NF_INET_PRE_ROUTING) |
		              (1 << NF_INET_LOCAL_OUT),
		.me         = THIS_MODULE,
	पूर्ण,
	अणु
		.name       = "REDIRECT",
		.family     = NFPROTO_IPV4,
		.revision   = 0,
		.table      = "nat",
		.target     = redirect_tg4,
		.checkentry = redirect_tg4_check,
		.destroy    = redirect_tg_destroy,
		.tarमाला_लोize = माप(काष्ठा nf_nat_ipv4_multi_range_compat),
		.hooks      = (1 << NF_INET_PRE_ROUTING) |
		              (1 << NF_INET_LOCAL_OUT),
		.me         = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init redirect_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_tarमाला_लो(redirect_tg_reg,
				   ARRAY_SIZE(redirect_tg_reg));
पूर्ण

अटल व्योम __निकास redirect_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(redirect_tg_reg, ARRAY_SIZE(redirect_tg_reg));
पूर्ण

module_init(redirect_tg_init);
module_निकास(redirect_tg_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_DESCRIPTION("Xtables: Connection redirection to localhost");
MODULE_ALIAS("ip6t_REDIRECT");
MODULE_ALIAS("ipt_REDIRECT");
