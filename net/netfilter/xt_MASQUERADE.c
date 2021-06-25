<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Masquerade.  Simple mapping which alters range to a local IP address
   (depending on route). */

/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2006 Netfilter Core Team <coreteam@netfilter.org>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_nat_masquerade.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Netfilter Core Team <coreteam@netfilter.org>");
MODULE_DESCRIPTION("Xtables: automatic-address SNAT");

/* FIXME: Multiple tarमाला_लो. --RR */
अटल पूर्णांक masquerade_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा nf_nat_ipv4_multi_range_compat *mr = par->targinfo;

	अगर (mr->range[0].flags & NF_NAT_RANGE_MAP_IPS) अणु
		pr_debug("bad MAP_IPS.\n");
		वापस -EINVAL;
	पूर्ण
	अगर (mr->rangesize != 1) अणु
		pr_debug("bad rangesize %u\n", mr->rangesize);
		वापस -EINVAL;
	पूर्ण
	वापस nf_ct_netns_get(par->net, par->family);
पूर्ण

अटल अचिन्हित पूर्णांक
masquerade_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	काष्ठा nf_nat_range2 range;
	स्थिर काष्ठा nf_nat_ipv4_multi_range_compat *mr;

	mr = par->targinfo;
	range.flags = mr->range[0].flags;
	range.min_proto = mr->range[0].min;
	range.max_proto = mr->range[0].max;

	वापस nf_nat_masquerade_ipv4(skb, xt_hooknum(par), &range,
				      xt_out(par));
पूर्ण

अटल व्योम masquerade_tg_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	nf_ct_netns_put(par->net, par->family);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल अचिन्हित पूर्णांक
masquerade_tg6(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	वापस nf_nat_masquerade_ipv6(skb, par->targinfo, xt_out(par));
पूर्ण

अटल पूर्णांक masquerade_tg6_checkentry(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा nf_nat_range2 *range = par->targinfo;

	अगर (range->flags & NF_NAT_RANGE_MAP_IPS)
		वापस -EINVAL;

	वापस nf_ct_netns_get(par->net, par->family);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा xt_target masquerade_tg_reg[] __पढ़ो_mostly = अणु
	अणु
#अगर IS_ENABLED(CONFIG_IPV6)
		.name		= "MASQUERADE",
		.family		= NFPROTO_IPV6,
		.target		= masquerade_tg6,
		.tarमाला_लोize	= माप(काष्ठा nf_nat_range),
		.table		= "nat",
		.hooks		= 1 << NF_INET_POST_ROUTING,
		.checkentry	= masquerade_tg6_checkentry,
		.destroy	= masquerade_tg_destroy,
		.me		= THIS_MODULE,
	पूर्ण, अणु
#पूर्ण_अगर
		.name		= "MASQUERADE",
		.family		= NFPROTO_IPV4,
		.target		= masquerade_tg,
		.tarमाला_लोize	= माप(काष्ठा nf_nat_ipv4_multi_range_compat),
		.table		= "nat",
		.hooks		= 1 << NF_INET_POST_ROUTING,
		.checkentry	= masquerade_tg_check,
		.destroy	= masquerade_tg_destroy,
		.me		= THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init masquerade_tg_init(व्योम)
अणु
	पूर्णांक ret;

	ret = xt_रेजिस्टर_tarमाला_लो(masquerade_tg_reg,
				  ARRAY_SIZE(masquerade_tg_reg));
	अगर (ret)
		वापस ret;

	ret = nf_nat_masquerade_inet_रेजिस्टर_notअगरiers();
	अगर (ret) अणु
		xt_unरेजिस्टर_tarमाला_लो(masquerade_tg_reg,
				      ARRAY_SIZE(masquerade_tg_reg));
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास masquerade_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(masquerade_tg_reg, ARRAY_SIZE(masquerade_tg_reg));
	nf_nat_masquerade_inet_unरेजिस्टर_notअगरiers();
पूर्ण

module_init(masquerade_tg_init);
module_निकास(masquerade_tg_निकास);
#अगर IS_ENABLED(CONFIG_IPV6)
MODULE_ALIAS("ip6t_MASQUERADE");
#पूर्ण_अगर
MODULE_ALIAS("ipt_MASQUERADE");
