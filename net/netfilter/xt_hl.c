<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IP tables module क्रम matching the value of the TTL
 * (C) 2000,2001 by Harald Welte <laक्रमge@netfilter.org>
 *
 * Hop Limit matching module
 * (C) 2001-2002 Maciej Soltysiak <solt@dns.toxicfilms.tv>
 */

#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv4/ipt_ttl.h>
#समावेश <linux/netfilter_ipv6/ip6t_hl.h>

MODULE_AUTHOR("Maciej Soltysiak <solt@dns.toxicfilms.tv>");
MODULE_DESCRIPTION("Xtables: Hoplimit/TTL field match");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_ttl");
MODULE_ALIAS("ip6t_hl");

अटल bool ttl_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ipt_ttl_info *info = par->matchinfo;
	स्थिर u8 ttl = ip_hdr(skb)->ttl;

	चयन (info->mode) अणु
	हाल IPT_TTL_EQ:
		वापस ttl == info->ttl;
	हाल IPT_TTL_NE:
		वापस ttl != info->ttl;
	हाल IPT_TTL_LT:
		वापस ttl < info->ttl;
	हाल IPT_TTL_GT:
		वापस ttl > info->ttl;
	पूर्ण

	वापस false;
पूर्ण

अटल bool hl_mt6(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ip6t_hl_info *info = par->matchinfo;
	स्थिर काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);

	चयन (info->mode) अणु
	हाल IP6T_HL_EQ:
		वापस ip6h->hop_limit == info->hop_limit;
	हाल IP6T_HL_NE:
		वापस ip6h->hop_limit != info->hop_limit;
	हाल IP6T_HL_LT:
		वापस ip6h->hop_limit < info->hop_limit;
	हाल IP6T_HL_GT:
		वापस ip6h->hop_limit > info->hop_limit;
	पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा xt_match hl_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name       = "ttl",
		.revision   = 0,
		.family     = NFPROTO_IPV4,
		.match      = ttl_mt,
		.matchsize  = माप(काष्ठा ipt_ttl_info),
		.me         = THIS_MODULE,
	पूर्ण,
	अणु
		.name       = "hl",
		.revision   = 0,
		.family     = NFPROTO_IPV6,
		.match      = hl_mt6,
		.matchsize  = माप(काष्ठा ip6t_hl_info),
		.me         = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init hl_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(hl_mt_reg, ARRAY_SIZE(hl_mt_reg));
पूर्ण

अटल व्योम __निकास hl_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(hl_mt_reg, ARRAY_SIZE(hl_mt_reg));
पूर्ण

module_init(hl_mt_init);
module_निकास(hl_mt_निकास);
