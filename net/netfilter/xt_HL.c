<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TTL modअगरication target क्रम IP tables
 * (C) 2000,2005 by Harald Welte <laक्रमge@netfilter.org>
 *
 * Hop Limit modअगरication target क्रम ip6tables
 * Maciej Soltysiak <solt@dns.toxicfilms.tv>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/checksum.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv4/ipt_TTL.h>
#समावेश <linux/netfilter_ipv6/ip6t_HL.h>

MODULE_AUTHOR("Harald Welte <laforge@netfilter.org>");
MODULE_AUTHOR("Maciej Soltysiak <solt@dns.toxicfilms.tv>");
MODULE_DESCRIPTION("Xtables: Hoplimit/TTL Limit field modification target");
MODULE_LICENSE("GPL");

अटल अचिन्हित पूर्णांक
ttl_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	काष्ठा iphdr *iph;
	स्थिर काष्ठा ipt_TTL_info *info = par->targinfo;
	पूर्णांक new_ttl;

	अगर (skb_ensure_writable(skb, माप(*iph)))
		वापस NF_DROP;

	iph = ip_hdr(skb);

	चयन (info->mode) अणु
	हाल IPT_TTL_SET:
		new_ttl = info->ttl;
		अवरोध;
	हाल IPT_TTL_INC:
		new_ttl = iph->ttl + info->ttl;
		अगर (new_ttl > 255)
			new_ttl = 255;
		अवरोध;
	हाल IPT_TTL_DEC:
		new_ttl = iph->ttl - info->ttl;
		अगर (new_ttl < 0)
			new_ttl = 0;
		अवरोध;
	शेष:
		new_ttl = iph->ttl;
		अवरोध;
	पूर्ण

	अगर (new_ttl != iph->ttl) अणु
		csum_replace2(&iph->check, htons(iph->ttl << 8),
					   htons(new_ttl << 8));
		iph->ttl = new_ttl;
	पूर्ण

	वापस XT_CONTINUE;
पूर्ण

अटल अचिन्हित पूर्णांक
hl_tg6(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	काष्ठा ipv6hdr *ip6h;
	स्थिर काष्ठा ip6t_HL_info *info = par->targinfo;
	पूर्णांक new_hl;

	अगर (skb_ensure_writable(skb, माप(*ip6h)))
		वापस NF_DROP;

	ip6h = ipv6_hdr(skb);

	चयन (info->mode) अणु
	हाल IP6T_HL_SET:
		new_hl = info->hop_limit;
		अवरोध;
	हाल IP6T_HL_INC:
		new_hl = ip6h->hop_limit + info->hop_limit;
		अगर (new_hl > 255)
			new_hl = 255;
		अवरोध;
	हाल IP6T_HL_DEC:
		new_hl = ip6h->hop_limit - info->hop_limit;
		अगर (new_hl < 0)
			new_hl = 0;
		अवरोध;
	शेष:
		new_hl = ip6h->hop_limit;
		अवरोध;
	पूर्ण

	ip6h->hop_limit = new_hl;

	वापस XT_CONTINUE;
पूर्ण

अटल पूर्णांक ttl_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा ipt_TTL_info *info = par->targinfo;

	अगर (info->mode > IPT_TTL_MAXMODE)
		वापस -EINVAL;
	अगर (info->mode != IPT_TTL_SET && info->ttl == 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक hl_tg6_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा ip6t_HL_info *info = par->targinfo;

	अगर (info->mode > IP6T_HL_MAXMODE)
		वापस -EINVAL;
	अगर (info->mode != IP6T_HL_SET && info->hop_limit == 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा xt_target hl_tg_reg[] __पढ़ो_mostly = अणु
	अणु
		.name       = "TTL",
		.revision   = 0,
		.family     = NFPROTO_IPV4,
		.target     = ttl_tg,
		.tarमाला_लोize = माप(काष्ठा ipt_TTL_info),
		.table      = "mangle",
		.checkentry = ttl_tg_check,
		.me         = THIS_MODULE,
	पूर्ण,
	अणु
		.name       = "HL",
		.revision   = 0,
		.family     = NFPROTO_IPV6,
		.target     = hl_tg6,
		.tarमाला_लोize = माप(काष्ठा ip6t_HL_info),
		.table      = "mangle",
		.checkentry = hl_tg6_check,
		.me         = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init hl_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_tarमाला_लो(hl_tg_reg, ARRAY_SIZE(hl_tg_reg));
पूर्ण

अटल व्योम __निकास hl_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(hl_tg_reg, ARRAY_SIZE(hl_tg_reg));
पूर्ण

module_init(hl_tg_init);
module_निकास(hl_tg_निकास);
MODULE_ALIAS("ipt_TTL");
MODULE_ALIAS("ip6t_HL");
