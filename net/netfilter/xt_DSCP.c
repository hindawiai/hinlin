<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* x_tables module क्रम setting the IPv4/IPv6 DSCP field, Version 1.8
 *
 * (C) 2002 by Harald Welte <laक्रमge@netfilter.org>
 * based on ipt_FTOS.c (C) 2000 by Matthew G. Marsh <mgm@paktronix.com>
 *
 * See RFC2474 क्रम a description of the DSCP field within the IP Header.
*/
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/dsfield.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_DSCP.h>

MODULE_AUTHOR("Harald Welte <laforge@netfilter.org>");
MODULE_DESCRIPTION("Xtables: DSCP/TOS field modification");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_DSCP");
MODULE_ALIAS("ip6t_DSCP");
MODULE_ALIAS("ipt_TOS");
MODULE_ALIAS("ip6t_TOS");

अटल अचिन्हित पूर्णांक
dscp_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_DSCP_info *dinfo = par->targinfo;
	u_पूर्णांक8_t dscp = ipv4_get_dsfield(ip_hdr(skb)) >> XT_DSCP_SHIFT;

	अगर (dscp != dinfo->dscp) अणु
		अगर (skb_ensure_writable(skb, माप(काष्ठा iphdr)))
			वापस NF_DROP;

		ipv4_change_dsfield(ip_hdr(skb),
				    (__क्रमce __u8)(~XT_DSCP_MASK),
				    dinfo->dscp << XT_DSCP_SHIFT);

	पूर्ण
	वापस XT_CONTINUE;
पूर्ण

अटल अचिन्हित पूर्णांक
dscp_tg6(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_DSCP_info *dinfo = par->targinfo;
	u_पूर्णांक8_t dscp = ipv6_get_dsfield(ipv6_hdr(skb)) >> XT_DSCP_SHIFT;

	अगर (dscp != dinfo->dscp) अणु
		अगर (skb_ensure_writable(skb, माप(काष्ठा ipv6hdr)))
			वापस NF_DROP;

		ipv6_change_dsfield(ipv6_hdr(skb),
				    (__क्रमce __u8)(~XT_DSCP_MASK),
				    dinfo->dscp << XT_DSCP_SHIFT);
	पूर्ण
	वापस XT_CONTINUE;
पूर्ण

अटल पूर्णांक dscp_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा xt_DSCP_info *info = par->targinfo;

	अगर (info->dscp > XT_DSCP_MAX)
		वापस -गलत_तर्क;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
tos_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_tos_target_info *info = par->targinfo;
	काष्ठा iphdr *iph = ip_hdr(skb);
	u_पूर्णांक8_t orig, nv;

	orig = ipv4_get_dsfield(iph);
	nv   = (orig & ~info->tos_mask) ^ info->tos_value;

	अगर (orig != nv) अणु
		अगर (skb_ensure_writable(skb, माप(काष्ठा iphdr)))
			वापस NF_DROP;
		iph = ip_hdr(skb);
		ipv4_change_dsfield(iph, 0, nv);
	पूर्ण

	वापस XT_CONTINUE;
पूर्ण

अटल अचिन्हित पूर्णांक
tos_tg6(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_tos_target_info *info = par->targinfo;
	काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	u_पूर्णांक8_t orig, nv;

	orig = ipv6_get_dsfield(iph);
	nv   = (orig & ~info->tos_mask) ^ info->tos_value;

	अगर (orig != nv) अणु
		अगर (skb_ensure_writable(skb, माप(काष्ठा iphdr)))
			वापस NF_DROP;
		iph = ipv6_hdr(skb);
		ipv6_change_dsfield(iph, 0, nv);
	पूर्ण

	वापस XT_CONTINUE;
पूर्ण

अटल काष्ठा xt_target dscp_tg_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "DSCP",
		.family		= NFPROTO_IPV4,
		.checkentry	= dscp_tg_check,
		.target		= dscp_tg,
		.tarमाला_लोize	= माप(काष्ठा xt_DSCP_info),
		.table		= "mangle",
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "DSCP",
		.family		= NFPROTO_IPV6,
		.checkentry	= dscp_tg_check,
		.target		= dscp_tg6,
		.tarमाला_लोize	= माप(काष्ठा xt_DSCP_info),
		.table		= "mangle",
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "TOS",
		.revision	= 1,
		.family		= NFPROTO_IPV4,
		.table		= "mangle",
		.target		= tos_tg,
		.tarमाला_लोize	= माप(काष्ठा xt_tos_target_info),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "TOS",
		.revision	= 1,
		.family		= NFPROTO_IPV6,
		.table		= "mangle",
		.target		= tos_tg6,
		.tarमाला_लोize	= माप(काष्ठा xt_tos_target_info),
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init dscp_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_tarमाला_लो(dscp_tg_reg, ARRAY_SIZE(dscp_tg_reg));
पूर्ण

अटल व्योम __निकास dscp_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(dscp_tg_reg, ARRAY_SIZE(dscp_tg_reg));
पूर्ण

module_init(dscp_tg_init);
module_निकास(dscp_tg_निकास);
