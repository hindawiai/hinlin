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
#समावेश <net/netfilter/nf_tables_offload.h>
#समावेश <net/netfilter/nf_dup_netdev.h>

काष्ठा nft_dup_netdev अणु
	u8	sreg_dev;
पूर्ण;

अटल व्योम nft_dup_netdev_eval(स्थिर काष्ठा nft_expr *expr,
				काष्ठा nft_regs *regs,
				स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_dup_netdev *priv = nft_expr_priv(expr);
	पूर्णांक oअगर = regs->data[priv->sreg_dev];

	nf_dup_netdev_egress(pkt, oअगर);
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_dup_netdev_policy[NFTA_DUP_MAX + 1] = अणु
	[NFTA_DUP_SREG_DEV]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_dup_netdev_init(स्थिर काष्ठा nft_ctx *ctx,
			       स्थिर काष्ठा nft_expr *expr,
			       स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_dup_netdev *priv = nft_expr_priv(expr);

	अगर (tb[NFTA_DUP_SREG_DEV] == शून्य)
		वापस -EINVAL;

	वापस nft_parse_रेजिस्टर_load(tb[NFTA_DUP_SREG_DEV], &priv->sreg_dev,
				       माप(पूर्णांक));
पूर्ण

अटल पूर्णांक nft_dup_netdev_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_dup_netdev *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_DUP_SREG_DEV, priv->sreg_dev))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nft_dup_netdev_offload(काष्ठा nft_offload_ctx *ctx,
				  काष्ठा nft_flow_rule *flow,
				  स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_dup_netdev *priv = nft_expr_priv(expr);
	पूर्णांक oअगर = ctx->regs[priv->sreg_dev].data.data[0];

	वापस nft_fwd_dup_netdev_offload(ctx, flow, FLOW_ACTION_MIRRED, oअगर);
पूर्ण

अटल काष्ठा nft_expr_type nft_dup_netdev_type;
अटल स्थिर काष्ठा nft_expr_ops nft_dup_netdev_ops = अणु
	.type		= &nft_dup_netdev_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_dup_netdev)),
	.eval		= nft_dup_netdev_eval,
	.init		= nft_dup_netdev_init,
	.dump		= nft_dup_netdev_dump,
	.offload	= nft_dup_netdev_offload,
पूर्ण;

अटल काष्ठा nft_expr_type nft_dup_netdev_type __पढ़ो_mostly = अणु
	.family		= NFPROTO_NETDEV,
	.name		= "dup",
	.ops		= &nft_dup_netdev_ops,
	.policy		= nft_dup_netdev_policy,
	.maxattr	= NFTA_DUP_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_dup_netdev_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_dup_netdev_type);
पूर्ण

अटल व्योम __निकास nft_dup_netdev_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_dup_netdev_type);
पूर्ण

module_init(nft_dup_netdev_module_init);
module_निकास(nft_dup_netdev_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_ALIAS_NFT_AF_EXPR(5, "dup");
MODULE_DESCRIPTION("nftables netdev packet duplication support");
