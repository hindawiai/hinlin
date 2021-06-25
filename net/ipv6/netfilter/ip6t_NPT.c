<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011, 2012 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ipv6.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter_ipv6/ip6t_NPT.h>
#समावेश <linux/netfilter/x_tables.h>

अटल पूर्णांक ip6t_npt_checkentry(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	काष्ठा ip6t_npt_tginfo *npt = par->targinfo;
	काष्ठा in6_addr pfx;
	__wsum src_sum, dst_sum;

	अगर (npt->src_pfx_len > 64 || npt->dst_pfx_len > 64)
		वापस -EINVAL;

	/* Ensure that LSB of prefix is zero */
	ipv6_addr_prefix(&pfx, &npt->src_pfx.in6, npt->src_pfx_len);
	अगर (!ipv6_addr_equal(&pfx, &npt->src_pfx.in6))
		वापस -EINVAL;
	ipv6_addr_prefix(&pfx, &npt->dst_pfx.in6, npt->dst_pfx_len);
	अगर (!ipv6_addr_equal(&pfx, &npt->dst_pfx.in6))
		वापस -EINVAL;

	src_sum = csum_partial(&npt->src_pfx.in6, माप(npt->src_pfx.in6), 0);
	dst_sum = csum_partial(&npt->dst_pfx.in6, माप(npt->dst_pfx.in6), 0);

	npt->adjusपंचांगent = ~csum_fold(csum_sub(src_sum, dst_sum));
	वापस 0;
पूर्ण

अटल bool ip6t_npt_map_pfx(स्थिर काष्ठा ip6t_npt_tginfo *npt,
			     काष्ठा in6_addr *addr)
अणु
	अचिन्हित पूर्णांक pfx_len;
	अचिन्हित पूर्णांक i, idx;
	__be32 mask;
	__sum16 sum;

	pfx_len = max(npt->src_pfx_len, npt->dst_pfx_len);
	क्रम (i = 0; i < pfx_len; i += 32) अणु
		अगर (pfx_len - i >= 32)
			mask = 0;
		अन्यथा
			mask = htonl((1 << (i - pfx_len + 32)) - 1);

		idx = i / 32;
		addr->s6_addr32[idx] &= mask;
		addr->s6_addr32[idx] |= ~mask & npt->dst_pfx.in6.s6_addr32[idx];
	पूर्ण

	अगर (pfx_len <= 48)
		idx = 3;
	अन्यथा अणु
		क्रम (idx = 4; idx < ARRAY_SIZE(addr->s6_addr16); idx++) अणु
			अगर ((__क्रमce __sum16)addr->s6_addr16[idx] !=
			    CSUM_MANGLED_0)
				अवरोध;
		पूर्ण
		अगर (idx == ARRAY_SIZE(addr->s6_addr16))
			वापस false;
	पूर्ण

	sum = ~csum_fold(csum_add(csum_unfold((__क्रमce __sum16)addr->s6_addr16[idx]),
				  csum_unfold(npt->adjusपंचांगent)));
	अगर (sum == CSUM_MANGLED_0)
		sum = 0;
	*(__क्रमce __sum16 *)&addr->s6_addr16[idx] = sum;

	वापस true;
पूर्ण

अटल काष्ठा ipv6hdr *icmpv6_bounced_ipv6hdr(काष्ठा sk_buff *skb,
					      काष्ठा ipv6hdr *_bounced_hdr)
अणु
	अगर (ipv6_hdr(skb)->nexthdr != IPPROTO_ICMPV6)
		वापस शून्य;

	अगर (!icmpv6_is_err(icmp6_hdr(skb)->icmp6_type))
		वापस शून्य;

	वापस skb_header_poपूर्णांकer(skb,
				  skb_transport_offset(skb) + माप(काष्ठा icmp6hdr),
				  माप(काष्ठा ipv6hdr),
				  _bounced_hdr);
पूर्ण

अटल अचिन्हित पूर्णांक
ip6t_snpt_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ip6t_npt_tginfo *npt = par->targinfo;
	काष्ठा ipv6hdr _bounced_hdr;
	काष्ठा ipv6hdr *bounced_hdr;
	काष्ठा in6_addr bounced_pfx;

	अगर (!ip6t_npt_map_pfx(npt, &ipv6_hdr(skb)->saddr)) अणु
		icmpv6_send(skb, ICMPV6_PARAMPROB, ICMPV6_HDR_FIELD,
			    दुरत्व(काष्ठा ipv6hdr, saddr));
		वापस NF_DROP;
	पूर्ण

	/* reग_लिखो dst addr of bounced packet which was sent to dst range */
	bounced_hdr = icmpv6_bounced_ipv6hdr(skb, &_bounced_hdr);
	अगर (bounced_hdr) अणु
		ipv6_addr_prefix(&bounced_pfx, &bounced_hdr->daddr, npt->src_pfx_len);
		अगर (ipv6_addr_cmp(&bounced_pfx, &npt->src_pfx.in6) == 0)
			ip6t_npt_map_pfx(npt, &bounced_hdr->daddr);
	पूर्ण

	वापस XT_CONTINUE;
पूर्ण

अटल अचिन्हित पूर्णांक
ip6t_dnpt_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ip6t_npt_tginfo *npt = par->targinfo;
	काष्ठा ipv6hdr _bounced_hdr;
	काष्ठा ipv6hdr *bounced_hdr;
	काष्ठा in6_addr bounced_pfx;

	अगर (!ip6t_npt_map_pfx(npt, &ipv6_hdr(skb)->daddr)) अणु
		icmpv6_send(skb, ICMPV6_PARAMPROB, ICMPV6_HDR_FIELD,
			    दुरत्व(काष्ठा ipv6hdr, daddr));
		वापस NF_DROP;
	पूर्ण

	/* reग_लिखो src addr of bounced packet which was sent from dst range */
	bounced_hdr = icmpv6_bounced_ipv6hdr(skb, &_bounced_hdr);
	अगर (bounced_hdr) अणु
		ipv6_addr_prefix(&bounced_pfx, &bounced_hdr->saddr, npt->src_pfx_len);
		अगर (ipv6_addr_cmp(&bounced_pfx, &npt->src_pfx.in6) == 0)
			ip6t_npt_map_pfx(npt, &bounced_hdr->saddr);
	पूर्ण

	वापस XT_CONTINUE;
पूर्ण

अटल काष्ठा xt_target ip6t_npt_target_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "SNPT",
		.table		= "mangle",
		.target		= ip6t_snpt_tg,
		.tarमाला_लोize	= माप(काष्ठा ip6t_npt_tginfo),
		.usersize	= दुरत्व(काष्ठा ip6t_npt_tginfo, adjusपंचांगent),
		.checkentry	= ip6t_npt_checkentry,
		.family		= NFPROTO_IPV6,
		.hooks		= (1 << NF_INET_LOCAL_IN) |
				  (1 << NF_INET_POST_ROUTING),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "DNPT",
		.table		= "mangle",
		.target		= ip6t_dnpt_tg,
		.tarमाला_लोize	= माप(काष्ठा ip6t_npt_tginfo),
		.usersize	= दुरत्व(काष्ठा ip6t_npt_tginfo, adjusपंचांगent),
		.checkentry	= ip6t_npt_checkentry,
		.family		= NFPROTO_IPV6,
		.hooks		= (1 << NF_INET_PRE_ROUTING) |
				  (1 << NF_INET_LOCAL_OUT),
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ip6t_npt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_tarमाला_लो(ip6t_npt_target_reg,
				   ARRAY_SIZE(ip6t_npt_target_reg));
पूर्ण

अटल व्योम __निकास ip6t_npt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(ip6t_npt_target_reg,
			      ARRAY_SIZE(ip6t_npt_target_reg));
पूर्ण

module_init(ip6t_npt_init);
module_निकास(ip6t_npt_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("IPv6-to-IPv6 Network Prefix Translation (RFC 6296)");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_ALIAS("ip6t_SNPT");
MODULE_ALIAS("ip6t_DNPT");
