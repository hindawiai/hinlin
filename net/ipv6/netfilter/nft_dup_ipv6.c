<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 Pablo Neira Ayuso <pablo@netfilter.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/ipv6/nf_dup_ipv6.h>

काष्ठा nft_dup_ipv6 अणु
	u8	sreg_addr;
	u8	sreg_dev;
पूर्ण;

अटल व्योम nft_dup_ipv6_eval(स्थिर काष्ठा nft_expr *expr,
			      काष्ठा nft_regs *regs,
			      स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_dup_ipv6 *priv = nft_expr_priv(expr);
	काष्ठा in6_addr *gw = (काष्ठा in6_addr *)&regs->data[priv->sreg_addr];
	पूर्णांक oअगर = priv->sreg_dev ? regs->data[priv->sreg_dev] : -1;

	nf_dup_ipv6(nft_net(pkt), pkt->skb, nft_hook(pkt), gw, oअगर);
पूर्ण

अटल पूर्णांक nft_dup_ipv6_init(स्थिर काष्ठा nft_ctx *ctx,
			     स्थिर काष्ठा nft_expr *expr,
			     स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_dup_ipv6 *priv = nft_expr_priv(expr);
	पूर्णांक err;

	अगर (tb[NFTA_DUP_SREG_ADDR] == शून्य)
		वापस -EINVAL;

	err = nft_parse_रेजिस्टर_load(tb[NFTA_DUP_SREG_ADDR], &priv->sreg_addr,
				      माप(काष्ठा in6_addr));
	अगर (err < 0)
		वापस err;

	अगर (tb[NFTA_DUP_SREG_DEV])
		err = nft_parse_रेजिस्टर_load(tb[NFTA_DUP_SREG_DEV],
					      &priv->sreg_dev, माप(पूर्णांक));

	वापस err;
पूर्ण

अटल पूर्णांक nft_dup_ipv6_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_dup_ipv6 *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_DUP_SREG_ADDR, priv->sreg_addr))
		जाओ nla_put_failure;
	अगर (priv->sreg_dev &&
	    nft_dump_रेजिस्टर(skb, NFTA_DUP_SREG_DEV, priv->sreg_dev))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल काष्ठा nft_expr_type nft_dup_ipv6_type;
अटल स्थिर काष्ठा nft_expr_ops nft_dup_ipv6_ops = अणु
	.type		= &nft_dup_ipv6_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_dup_ipv6)),
	.eval		= nft_dup_ipv6_eval,
	.init		= nft_dup_ipv6_init,
	.dump		= nft_dup_ipv6_dump,
पूर्ण;

अटल स्थिर काष्ठा nla_policy nft_dup_ipv6_policy[NFTA_DUP_MAX + 1] = अणु
	[NFTA_DUP_SREG_ADDR]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_DUP_SREG_DEV]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल काष्ठा nft_expr_type nft_dup_ipv6_type __पढ़ो_mostly = अणु
	.family		= NFPROTO_IPV6,
	.name		= "dup",
	.ops		= &nft_dup_ipv6_ops,
	.policy		= nft_dup_ipv6_policy,
	.maxattr	= NFTA_DUP_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_dup_ipv6_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_dup_ipv6_type);
पूर्ण

अटल व्योम __निकास nft_dup_ipv6_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_dup_ipv6_type);
पूर्ण

module_init(nft_dup_ipv6_module_init);
module_निकास(nft_dup_ipv6_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_ALIAS_NFT_AF_EXPR(AF_INET6, "dup");
MODULE_DESCRIPTION("IPv6 nftables packet duplication support");
