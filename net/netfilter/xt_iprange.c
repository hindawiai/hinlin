<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	xt_iprange - Netfilter module to match IP address ranges
 *
 *	(C) 2003 Jozsef Kadlecsik <kadlec@netfilter.org>
 *	(C) CC Computer Consultants GmbH, 2008
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_iprange.h>

अटल bool
iprange_mt4(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_iprange_mtinfo *info = par->matchinfo;
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	bool m;

	अगर (info->flags & IPRANGE_SRC) अणु
		m  = ntohl(iph->saddr) < ntohl(info->src_min.ip);
		m |= ntohl(iph->saddr) > ntohl(info->src_max.ip);
		m ^= !!(info->flags & IPRANGE_SRC_INV);
		अगर (m) अणु
			pr_debug("src IP %pI4 NOT in range %s%pI4-%pI4\n",
			         &iph->saddr,
			         (info->flags & IPRANGE_SRC_INV) ? "(INV) " : "",
			         &info->src_min.ip,
			         &info->src_max.ip);
			वापस false;
		पूर्ण
	पूर्ण
	अगर (info->flags & IPRANGE_DST) अणु
		m  = ntohl(iph->daddr) < ntohl(info->dst_min.ip);
		m |= ntohl(iph->daddr) > ntohl(info->dst_max.ip);
		m ^= !!(info->flags & IPRANGE_DST_INV);
		अगर (m) अणु
			pr_debug("dst IP %pI4 NOT in range %s%pI4-%pI4\n",
			         &iph->daddr,
			         (info->flags & IPRANGE_DST_INV) ? "(INV) " : "",
			         &info->dst_min.ip,
			         &info->dst_max.ip);
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक
iprange_ipv6_lt(स्थिर काष्ठा in6_addr *a, स्थिर काष्ठा in6_addr *b)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 4; ++i) अणु
		अगर (a->s6_addr32[i] != b->s6_addr32[i])
			वापस ntohl(a->s6_addr32[i]) < ntohl(b->s6_addr32[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
iprange_mt6(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_iprange_mtinfo *info = par->matchinfo;
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	bool m;

	अगर (info->flags & IPRANGE_SRC) अणु
		m  = iprange_ipv6_lt(&iph->saddr, &info->src_min.in6);
		m |= iprange_ipv6_lt(&info->src_max.in6, &iph->saddr);
		m ^= !!(info->flags & IPRANGE_SRC_INV);
		अगर (m) अणु
			pr_debug("src IP %pI6 NOT in range %s%pI6-%pI6\n",
				 &iph->saddr,
				 (info->flags & IPRANGE_SRC_INV) ? "(INV) " : "",
				 &info->src_min.in6,
				 &info->src_max.in6);
			वापस false;
		पूर्ण
	पूर्ण
	अगर (info->flags & IPRANGE_DST) अणु
		m  = iprange_ipv6_lt(&iph->daddr, &info->dst_min.in6);
		m |= iprange_ipv6_lt(&info->dst_max.in6, &iph->daddr);
		m ^= !!(info->flags & IPRANGE_DST_INV);
		अगर (m) अणु
			pr_debug("dst IP %pI6 NOT in range %s%pI6-%pI6\n",
				 &iph->daddr,
				 (info->flags & IPRANGE_DST_INV) ? "(INV) " : "",
				 &info->dst_min.in6,
				 &info->dst_max.in6);
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल काष्ठा xt_match iprange_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name      = "iprange",
		.revision  = 1,
		.family    = NFPROTO_IPV4,
		.match     = iprange_mt4,
		.matchsize = माप(काष्ठा xt_iprange_mtinfo),
		.me        = THIS_MODULE,
	पूर्ण,
	अणु
		.name      = "iprange",
		.revision  = 1,
		.family    = NFPROTO_IPV6,
		.match     = iprange_mt6,
		.matchsize = माप(काष्ठा xt_iprange_mtinfo),
		.me        = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init iprange_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(iprange_mt_reg, ARRAY_SIZE(iprange_mt_reg));
पूर्ण

अटल व्योम __निकास iprange_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(iprange_mt_reg, ARRAY_SIZE(iprange_mt_reg));
पूर्ण

module_init(iprange_mt_init);
module_निकास(iprange_mt_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jozsef Kadlecsik <kadlec@netfilter.org>");
MODULE_AUTHOR("Jan Engelhardt <jengelh@medozas.de>");
MODULE_DESCRIPTION("Xtables: arbitrary IPv4 range matching");
MODULE_ALIAS("ipt_iprange");
MODULE_ALIAS("ip6t_iprange");
