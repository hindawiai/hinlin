<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008-2009 Patrick McHardy <kaber@trash.net>
 * Copyright (c) 2013 Eric Leblond <eric@regit.org>
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nft_reject.h>
#समावेश <net/netfilter/ipv6/nf_reject.h>

अटल व्योम nft_reject_ipv6_eval(स्थिर काष्ठा nft_expr *expr,
				 काष्ठा nft_regs *regs,
				 स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_reject *priv = nft_expr_priv(expr);

	चयन (priv->type) अणु
	हाल NFT_REJECT_ICMP_UNREACH:
		nf_send_unreach6(nft_net(pkt), pkt->skb, priv->icmp_code,
				 nft_hook(pkt));
		अवरोध;
	हाल NFT_REJECT_TCP_RST:
		nf_send_reset6(nft_net(pkt), pkt->xt.state->sk, pkt->skb,
			       nft_hook(pkt));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	regs->verdict.code = NF_DROP;
पूर्ण

अटल काष्ठा nft_expr_type nft_reject_ipv6_type;
अटल स्थिर काष्ठा nft_expr_ops nft_reject_ipv6_ops = अणु
	.type		= &nft_reject_ipv6_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_reject)),
	.eval		= nft_reject_ipv6_eval,
	.init		= nft_reject_init,
	.dump		= nft_reject_dump,
	.validate	= nft_reject_validate,
पूर्ण;

अटल काष्ठा nft_expr_type nft_reject_ipv6_type __पढ़ो_mostly = अणु
	.family		= NFPROTO_IPV6,
	.name		= "reject",
	.ops		= &nft_reject_ipv6_ops,
	.policy		= nft_reject_policy,
	.maxattr	= NFTA_REJECT_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_reject_ipv6_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_reject_ipv6_type);
पूर्ण

अटल व्योम __निकास nft_reject_ipv6_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_reject_ipv6_type);
पूर्ण

module_init(nft_reject_ipv6_module_init);
module_निकास(nft_reject_ipv6_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_ALIAS_NFT_AF_EXPR(AF_INET6, "reject");
MODULE_DESCRIPTION("IPv6 packet rejection for nftables");
