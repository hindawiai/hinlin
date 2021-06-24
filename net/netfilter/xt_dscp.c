<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* IP tables module क्रम matching the value of the IPv4/IPv6 DSCP field
 *
 * (C) 2002 by Harald Welte <laक्रमge@netfilter.org>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/dsfield.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_dscp.h>

MODULE_AUTHOR("Harald Welte <laforge@netfilter.org>");
MODULE_DESCRIPTION("Xtables: DSCP/TOS field match");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_dscp");
MODULE_ALIAS("ip6t_dscp");
MODULE_ALIAS("ipt_tos");
MODULE_ALIAS("ip6t_tos");

अटल bool
dscp_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_dscp_info *info = par->matchinfo;
	u_पूर्णांक8_t dscp = ipv4_get_dsfield(ip_hdr(skb)) >> XT_DSCP_SHIFT;

	वापस (dscp == info->dscp) ^ !!info->invert;
पूर्ण

अटल bool
dscp_mt6(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_dscp_info *info = par->matchinfo;
	u_पूर्णांक8_t dscp = ipv6_get_dsfield(ipv6_hdr(skb)) >> XT_DSCP_SHIFT;

	वापस (dscp == info->dscp) ^ !!info->invert;
पूर्ण

अटल पूर्णांक dscp_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_dscp_info *info = par->matchinfo;

	अगर (info->dscp > XT_DSCP_MAX)
		वापस -गलत_तर्क;

	वापस 0;
पूर्ण

अटल bool tos_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_tos_match_info *info = par->matchinfo;

	अगर (xt_family(par) == NFPROTO_IPV4)
		वापस ((ip_hdr(skb)->tos & info->tos_mask) ==
		       info->tos_value) ^ !!info->invert;
	अन्यथा
		वापस ((ipv6_get_dsfield(ipv6_hdr(skb)) & info->tos_mask) ==
		       info->tos_value) ^ !!info->invert;
पूर्ण

अटल काष्ठा xt_match dscp_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "dscp",
		.family		= NFPROTO_IPV4,
		.checkentry	= dscp_mt_check,
		.match		= dscp_mt,
		.matchsize	= माप(काष्ठा xt_dscp_info),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "dscp",
		.family		= NFPROTO_IPV6,
		.checkentry	= dscp_mt_check,
		.match		= dscp_mt6,
		.matchsize	= माप(काष्ठा xt_dscp_info),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "tos",
		.revision	= 1,
		.family		= NFPROTO_IPV4,
		.match		= tos_mt,
		.matchsize	= माप(काष्ठा xt_tos_match_info),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "tos",
		.revision	= 1,
		.family		= NFPROTO_IPV6,
		.match		= tos_mt,
		.matchsize	= माप(काष्ठा xt_tos_match_info),
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init dscp_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(dscp_mt_reg, ARRAY_SIZE(dscp_mt_reg));
पूर्ण

अटल व्योम __निकास dscp_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(dscp_mt_reg, ARRAY_SIZE(dscp_mt_reg));
पूर्ण

module_init(dscp_mt_init);
module_निकास(dscp_mt_निकास);
