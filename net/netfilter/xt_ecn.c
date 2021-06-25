<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Xtables module क्रम matching the value of the IPv4/IPv6 and TCP ECN bits
 *
 * (C) 2002 by Harald Welte <laक्रमge@gnumonks.org>
 * (C) 2011 Patrick McHardy <kaber@trash.net>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <net/ip.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/tcp.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_ecn.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>

MODULE_AUTHOR("Harald Welte <laforge@netfilter.org>");
MODULE_DESCRIPTION("Xtables: Explicit Congestion Notification (ECN) flag match");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_ecn");
MODULE_ALIAS("ip6t_ecn");

अटल bool match_tcp(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_ecn_info *einfo = par->matchinfo;
	काष्ठा tcphdr _tcph;
	स्थिर काष्ठा tcphdr *th;

	/* In practice, TCP match करोes this, so can't fail.  But let's
	 * be good citizens.
	 */
	th = skb_header_poपूर्णांकer(skb, par->thoff, माप(_tcph), &_tcph);
	अगर (th == शून्य)
		वापस false;

	अगर (einfo->operation & XT_ECN_OP_MATCH_ECE) अणु
		अगर (einfo->invert & XT_ECN_OP_MATCH_ECE) अणु
			अगर (th->ece == 1)
				वापस false;
		पूर्ण अन्यथा अणु
			अगर (th->ece == 0)
				वापस false;
		पूर्ण
	पूर्ण

	अगर (einfo->operation & XT_ECN_OP_MATCH_CWR) अणु
		अगर (einfo->invert & XT_ECN_OP_MATCH_CWR) अणु
			अगर (th->cwr == 1)
				वापस false;
		पूर्ण अन्यथा अणु
			अगर (th->cwr == 0)
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल अंतरभूत bool match_ip(स्थिर काष्ठा sk_buff *skb,
			    स्थिर काष्ठा xt_ecn_info *einfo)
अणु
	वापस ((ip_hdr(skb)->tos & XT_ECN_IP_MASK) == einfo->ip_ect) ^
	       !!(einfo->invert & XT_ECN_OP_MATCH_IP);
पूर्ण

अटल bool ecn_mt4(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_ecn_info *info = par->matchinfo;

	अगर (info->operation & XT_ECN_OP_MATCH_IP && !match_ip(skb, info))
		वापस false;

	अगर (info->operation & (XT_ECN_OP_MATCH_ECE | XT_ECN_OP_MATCH_CWR) &&
	    !match_tcp(skb, par))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक ecn_mt_check4(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_ecn_info *info = par->matchinfo;
	स्थिर काष्ठा ipt_ip *ip = par->entryinfo;

	अगर (info->operation & XT_ECN_OP_MATCH_MASK)
		वापस -EINVAL;

	अगर (info->invert & XT_ECN_OP_MATCH_MASK)
		वापस -EINVAL;

	अगर (info->operation & (XT_ECN_OP_MATCH_ECE | XT_ECN_OP_MATCH_CWR) &&
	    (ip->proto != IPPROTO_TCP || ip->invflags & IPT_INV_PROTO)) अणु
		pr_info_ratelimited("cannot match TCP bits for non-tcp packets\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत bool match_ipv6(स्थिर काष्ठा sk_buff *skb,
			      स्थिर काष्ठा xt_ecn_info *einfo)
अणु
	वापस (((ipv6_hdr(skb)->flow_lbl[0] >> 4) & XT_ECN_IP_MASK) ==
	        einfo->ip_ect) ^
	       !!(einfo->invert & XT_ECN_OP_MATCH_IP);
पूर्ण

अटल bool ecn_mt6(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_ecn_info *info = par->matchinfo;

	अगर (info->operation & XT_ECN_OP_MATCH_IP && !match_ipv6(skb, info))
		वापस false;

	अगर (info->operation & (XT_ECN_OP_MATCH_ECE | XT_ECN_OP_MATCH_CWR) &&
	    !match_tcp(skb, par))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक ecn_mt_check6(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_ecn_info *info = par->matchinfo;
	स्थिर काष्ठा ip6t_ip6 *ip = par->entryinfo;

	अगर (info->operation & XT_ECN_OP_MATCH_MASK)
		वापस -EINVAL;

	अगर (info->invert & XT_ECN_OP_MATCH_MASK)
		वापस -EINVAL;

	अगर (info->operation & (XT_ECN_OP_MATCH_ECE | XT_ECN_OP_MATCH_CWR) &&
	    (ip->proto != IPPROTO_TCP || ip->invflags & IP6T_INV_PROTO)) अणु
		pr_info_ratelimited("cannot match TCP bits for non-tcp packets\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा xt_match ecn_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "ecn",
		.family		= NFPROTO_IPV4,
		.match		= ecn_mt4,
		.matchsize	= माप(काष्ठा xt_ecn_info),
		.checkentry	= ecn_mt_check4,
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "ecn",
		.family		= NFPROTO_IPV6,
		.match		= ecn_mt6,
		.matchsize	= माप(काष्ठा xt_ecn_info),
		.checkentry	= ecn_mt_check6,
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ecn_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(ecn_mt_reg, ARRAY_SIZE(ecn_mt_reg));
पूर्ण

अटल व्योम __निकास ecn_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(ecn_mt_reg, ARRAY_SIZE(ecn_mt_reg));
पूर्ण

module_init(ecn_mt_init);
module_निकास(ecn_mt_निकास);
