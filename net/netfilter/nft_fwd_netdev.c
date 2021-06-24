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
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_offload.h>
#समावेश <net/netfilter/nf_dup_netdev.h>
#समावेश <net/neighbour.h>
#समावेश <net/ip.h>

काष्ठा nft_fwd_netdev अणु
	u8	sreg_dev;
पूर्ण;

अटल व्योम nft_fwd_netdev_eval(स्थिर काष्ठा nft_expr *expr,
				काष्ठा nft_regs *regs,
				स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_fwd_netdev *priv = nft_expr_priv(expr);
	पूर्णांक oअगर = regs->data[priv->sreg_dev];

	/* This is used by अगरb only. */
	skb_set_redirected(pkt->skb, true);

	nf_fwd_netdev_egress(pkt, oअगर);
	regs->verdict.code = NF_STOLEN;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_fwd_netdev_policy[NFTA_FWD_MAX + 1] = अणु
	[NFTA_FWD_SREG_DEV]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_FWD_SREG_ADDR]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_FWD_NFPROTO]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_fwd_netdev_init(स्थिर काष्ठा nft_ctx *ctx,
			       स्थिर काष्ठा nft_expr *expr,
			       स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_fwd_netdev *priv = nft_expr_priv(expr);

	अगर (tb[NFTA_FWD_SREG_DEV] == शून्य)
		वापस -EINVAL;

	वापस nft_parse_रेजिस्टर_load(tb[NFTA_FWD_SREG_DEV], &priv->sreg_dev,
				       माप(पूर्णांक));
पूर्ण

अटल पूर्णांक nft_fwd_netdev_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_fwd_netdev *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_FWD_SREG_DEV, priv->sreg_dev))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nft_fwd_netdev_offload(काष्ठा nft_offload_ctx *ctx,
				  काष्ठा nft_flow_rule *flow,
				  स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_fwd_netdev *priv = nft_expr_priv(expr);
	पूर्णांक oअगर = ctx->regs[priv->sreg_dev].data.data[0];

	वापस nft_fwd_dup_netdev_offload(ctx, flow, FLOW_ACTION_REसूचीECT, oअगर);
पूर्ण

काष्ठा nft_fwd_neigh अणु
	u8			sreg_dev;
	u8			sreg_addr;
	u8			nfproto;
पूर्ण;

अटल व्योम nft_fwd_neigh_eval(स्थिर काष्ठा nft_expr *expr,
			      काष्ठा nft_regs *regs,
			      स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_fwd_neigh *priv = nft_expr_priv(expr);
	व्योम *addr = &regs->data[priv->sreg_addr];
	पूर्णांक oअगर = regs->data[priv->sreg_dev];
	अचिन्हित पूर्णांक verdict = NF_STOLEN;
	काष्ठा sk_buff *skb = pkt->skb;
	काष्ठा net_device *dev;
	पूर्णांक neigh_table;

	चयन (priv->nfproto) अणु
	हाल NFPROTO_IPV4: अणु
		काष्ठा iphdr *iph;

		अगर (skb->protocol != htons(ETH_P_IP)) अणु
			verdict = NFT_BREAK;
			जाओ out;
		पूर्ण
		अगर (skb_try_make_writable(skb, माप(*iph))) अणु
			verdict = NF_DROP;
			जाओ out;
		पूर्ण
		iph = ip_hdr(skb);
		ip_decrease_ttl(iph);
		neigh_table = NEIGH_ARP_TABLE;
		अवरोध;
		पूर्ण
	हाल NFPROTO_IPV6: अणु
		काष्ठा ipv6hdr *ip6h;

		अगर (skb->protocol != htons(ETH_P_IPV6)) अणु
			verdict = NFT_BREAK;
			जाओ out;
		पूर्ण
		अगर (skb_try_make_writable(skb, माप(*ip6h))) अणु
			verdict = NF_DROP;
			जाओ out;
		पूर्ण
		ip6h = ipv6_hdr(skb);
		ip6h->hop_limit--;
		neigh_table = NEIGH_ND_TABLE;
		अवरोध;
		पूर्ण
	शेष:
		verdict = NFT_BREAK;
		जाओ out;
	पूर्ण

	dev = dev_get_by_index_rcu(nft_net(pkt), oअगर);
	अगर (dev == शून्य)
		वापस;

	skb->dev = dev;
	skb->tstamp = 0;
	neigh_xmit(neigh_table, dev, addr, skb);
out:
	regs->verdict.code = verdict;
पूर्ण

अटल पूर्णांक nft_fwd_neigh_init(स्थिर काष्ठा nft_ctx *ctx,
			      स्थिर काष्ठा nft_expr *expr,
			      स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_fwd_neigh *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक addr_len;
	पूर्णांक err;

	अगर (!tb[NFTA_FWD_SREG_DEV] ||
	    !tb[NFTA_FWD_SREG_ADDR] ||
	    !tb[NFTA_FWD_NFPROTO])
		वापस -EINVAL;

	priv->nfproto = ntohl(nla_get_be32(tb[NFTA_FWD_NFPROTO]));

	चयन (priv->nfproto) अणु
	हाल NFPROTO_IPV4:
		addr_len = माप(काष्ठा in_addr);
		अवरोध;
	हाल NFPROTO_IPV6:
		addr_len = माप(काष्ठा in6_addr);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	err = nft_parse_रेजिस्टर_load(tb[NFTA_FWD_SREG_DEV], &priv->sreg_dev,
				      माप(पूर्णांक));
	अगर (err < 0)
		वापस err;

	वापस nft_parse_रेजिस्टर_load(tb[NFTA_FWD_SREG_ADDR], &priv->sreg_addr,
				       addr_len);
पूर्ण

अटल पूर्णांक nft_fwd_neigh_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_fwd_neigh *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_FWD_SREG_DEV, priv->sreg_dev) ||
	    nft_dump_रेजिस्टर(skb, NFTA_FWD_SREG_ADDR, priv->sreg_addr) ||
	    nla_put_be32(skb, NFTA_FWD_NFPROTO, htonl(priv->nfproto)))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nft_fwd_validate(स्थिर काष्ठा nft_ctx *ctx,
			    स्थिर काष्ठा nft_expr *expr,
			    स्थिर काष्ठा nft_data **data)
अणु
	वापस nft_chain_validate_hooks(ctx->chain, (1 << NF_NETDEV_INGRESS));
पूर्ण

अटल काष्ठा nft_expr_type nft_fwd_netdev_type;
अटल स्थिर काष्ठा nft_expr_ops nft_fwd_neigh_netdev_ops = अणु
	.type		= &nft_fwd_netdev_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_fwd_neigh)),
	.eval		= nft_fwd_neigh_eval,
	.init		= nft_fwd_neigh_init,
	.dump		= nft_fwd_neigh_dump,
	.validate	= nft_fwd_validate,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops nft_fwd_netdev_ops = अणु
	.type		= &nft_fwd_netdev_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_fwd_netdev)),
	.eval		= nft_fwd_netdev_eval,
	.init		= nft_fwd_netdev_init,
	.dump		= nft_fwd_netdev_dump,
	.validate	= nft_fwd_validate,
	.offload	= nft_fwd_netdev_offload,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops *
nft_fwd_select_ops(स्थिर काष्ठा nft_ctx *ctx,
		   स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	अगर (tb[NFTA_FWD_SREG_ADDR])
		वापस &nft_fwd_neigh_netdev_ops;
	अगर (tb[NFTA_FWD_SREG_DEV])
		वापस &nft_fwd_netdev_ops;

        वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल काष्ठा nft_expr_type nft_fwd_netdev_type __पढ़ो_mostly = अणु
	.family		= NFPROTO_NETDEV,
	.name		= "fwd",
	.select_ops	= nft_fwd_select_ops,
	.policy		= nft_fwd_netdev_policy,
	.maxattr	= NFTA_FWD_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_fwd_netdev_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_fwd_netdev_type);
पूर्ण

अटल व्योम __निकास nft_fwd_netdev_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_fwd_netdev_type);
पूर्ण

module_init(nft_fwd_netdev_module_init);
module_निकास(nft_fwd_netdev_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_ALIAS_NFT_AF_EXPR(5, "fwd");
