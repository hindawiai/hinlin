<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 Arturo Borrero Gonzalez <arturo@debian.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_nat_redirect.h>
#समावेश <net/netfilter/nf_tables.h>

काष्ठा nft_redir अणु
	u8			sreg_proto_min;
	u8			sreg_proto_max;
	u16			flags;
पूर्ण;

अटल स्थिर काष्ठा nla_policy nft_redir_policy[NFTA_REसूची_MAX + 1] = अणु
	[NFTA_REसूची_REG_PROTO_MIN]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_REसूची_REG_PROTO_MAX]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_REसूची_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_redir_validate(स्थिर काष्ठा nft_ctx *ctx,
			      स्थिर काष्ठा nft_expr *expr,
			      स्थिर काष्ठा nft_data **data)
अणु
	पूर्णांक err;

	err = nft_chain_validate_dependency(ctx->chain, NFT_CHAIN_T_NAT);
	अगर (err < 0)
		वापस err;

	वापस nft_chain_validate_hooks(ctx->chain,
					(1 << NF_INET_PRE_ROUTING) |
					(1 << NF_INET_LOCAL_OUT));
पूर्ण

अटल पूर्णांक nft_redir_init(स्थिर काष्ठा nft_ctx *ctx,
			  स्थिर काष्ठा nft_expr *expr,
			  स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_redir *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक plen;
	पूर्णांक err;

	plen = माप_field(काष्ठा nf_nat_range, min_addr.all);
	अगर (tb[NFTA_REसूची_REG_PROTO_MIN]) अणु
		err = nft_parse_रेजिस्टर_load(tb[NFTA_REसूची_REG_PROTO_MIN],
					      &priv->sreg_proto_min, plen);
		अगर (err < 0)
			वापस err;

		अगर (tb[NFTA_REसूची_REG_PROTO_MAX]) अणु
			err = nft_parse_रेजिस्टर_load(tb[NFTA_REसूची_REG_PROTO_MAX],
						      &priv->sreg_proto_max,
						      plen);
			अगर (err < 0)
				वापस err;
		पूर्ण अन्यथा अणु
			priv->sreg_proto_max = priv->sreg_proto_min;
		पूर्ण
	पूर्ण

	अगर (tb[NFTA_REसूची_FLAGS]) अणु
		priv->flags = ntohl(nla_get_be32(tb[NFTA_REसूची_FLAGS]));
		अगर (priv->flags & ~NF_NAT_RANGE_MASK)
			वापस -EINVAL;
	पूर्ण

	वापस nf_ct_netns_get(ctx->net, ctx->family);
पूर्ण

अटल पूर्णांक nft_redir_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_redir *priv = nft_expr_priv(expr);

	अगर (priv->sreg_proto_min) अणु
		अगर (nft_dump_रेजिस्टर(skb, NFTA_REसूची_REG_PROTO_MIN,
				      priv->sreg_proto_min))
			जाओ nla_put_failure;
		अगर (nft_dump_रेजिस्टर(skb, NFTA_REसूची_REG_PROTO_MAX,
				      priv->sreg_proto_max))
			जाओ nla_put_failure;
	पूर्ण

	अगर (priv->flags != 0 &&
	    nla_put_be32(skb, NFTA_REसूची_FLAGS, htonl(priv->flags)))
			जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल व्योम nft_redir_ipv4_eval(स्थिर काष्ठा nft_expr *expr,
				काष्ठा nft_regs *regs,
				स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_redir *priv = nft_expr_priv(expr);
	काष्ठा nf_nat_ipv4_multi_range_compat mr;

	स_रखो(&mr, 0, माप(mr));
	अगर (priv->sreg_proto_min) अणु
		mr.range[0].min.all = (__क्रमce __be16)nft_reg_load16(
			&regs->data[priv->sreg_proto_min]);
		mr.range[0].max.all = (__क्रमce __be16)nft_reg_load16(
			&regs->data[priv->sreg_proto_max]);
		mr.range[0].flags |= NF_NAT_RANGE_PROTO_SPECIFIED;
	पूर्ण

	mr.range[0].flags |= priv->flags;

	regs->verdict.code = nf_nat_redirect_ipv4(pkt->skb, &mr, nft_hook(pkt));
पूर्ण

अटल व्योम
nft_redir_ipv4_destroy(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr)
अणु
	nf_ct_netns_put(ctx->net, NFPROTO_IPV4);
पूर्ण

अटल काष्ठा nft_expr_type nft_redir_ipv4_type;
अटल स्थिर काष्ठा nft_expr_ops nft_redir_ipv4_ops = अणु
	.type		= &nft_redir_ipv4_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_redir)),
	.eval		= nft_redir_ipv4_eval,
	.init		= nft_redir_init,
	.destroy	= nft_redir_ipv4_destroy,
	.dump		= nft_redir_dump,
	.validate	= nft_redir_validate,
पूर्ण;

अटल काष्ठा nft_expr_type nft_redir_ipv4_type __पढ़ो_mostly = अणु
	.family		= NFPROTO_IPV4,
	.name		= "redir",
	.ops		= &nft_redir_ipv4_ops,
	.policy		= nft_redir_policy,
	.maxattr	= NFTA_REसूची_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

#अगर_घोषित CONFIG_NF_TABLES_IPV6
अटल व्योम nft_redir_ipv6_eval(स्थिर काष्ठा nft_expr *expr,
				काष्ठा nft_regs *regs,
				स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_redir *priv = nft_expr_priv(expr);
	काष्ठा nf_nat_range2 range;

	स_रखो(&range, 0, माप(range));
	अगर (priv->sreg_proto_min) अणु
		range.min_proto.all = (__क्रमce __be16)nft_reg_load16(
			&regs->data[priv->sreg_proto_min]);
		range.max_proto.all = (__क्रमce __be16)nft_reg_load16(
			&regs->data[priv->sreg_proto_max]);
		range.flags |= NF_NAT_RANGE_PROTO_SPECIFIED;
	पूर्ण

	range.flags |= priv->flags;

	regs->verdict.code =
		nf_nat_redirect_ipv6(pkt->skb, &range, nft_hook(pkt));
पूर्ण

अटल व्योम
nft_redir_ipv6_destroy(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr)
अणु
	nf_ct_netns_put(ctx->net, NFPROTO_IPV6);
पूर्ण

अटल काष्ठा nft_expr_type nft_redir_ipv6_type;
अटल स्थिर काष्ठा nft_expr_ops nft_redir_ipv6_ops = अणु
	.type		= &nft_redir_ipv6_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_redir)),
	.eval		= nft_redir_ipv6_eval,
	.init		= nft_redir_init,
	.destroy	= nft_redir_ipv6_destroy,
	.dump		= nft_redir_dump,
	.validate	= nft_redir_validate,
पूर्ण;

अटल काष्ठा nft_expr_type nft_redir_ipv6_type __पढ़ो_mostly = अणु
	.family		= NFPROTO_IPV6,
	.name		= "redir",
	.ops		= &nft_redir_ipv6_ops,
	.policy		= nft_redir_policy,
	.maxattr	= NFTA_REसूची_MAX,
	.owner		= THIS_MODULE,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_TABLES_INET
अटल व्योम nft_redir_inet_eval(स्थिर काष्ठा nft_expr *expr,
				काष्ठा nft_regs *regs,
				स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	चयन (nft_pf(pkt)) अणु
	हाल NFPROTO_IPV4:
		वापस nft_redir_ipv4_eval(expr, regs, pkt);
	हाल NFPROTO_IPV6:
		वापस nft_redir_ipv6_eval(expr, regs, pkt);
	पूर्ण

	WARN_ON_ONCE(1);
पूर्ण

अटल व्योम
nft_redir_inet_destroy(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr)
अणु
	nf_ct_netns_put(ctx->net, NFPROTO_INET);
पूर्ण

अटल काष्ठा nft_expr_type nft_redir_inet_type;
अटल स्थिर काष्ठा nft_expr_ops nft_redir_inet_ops = अणु
	.type		= &nft_redir_inet_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_redir)),
	.eval		= nft_redir_inet_eval,
	.init		= nft_redir_init,
	.destroy	= nft_redir_inet_destroy,
	.dump		= nft_redir_dump,
	.validate	= nft_redir_validate,
पूर्ण;

अटल काष्ठा nft_expr_type nft_redir_inet_type __पढ़ो_mostly = अणु
	.family		= NFPROTO_INET,
	.name		= "redir",
	.ops		= &nft_redir_inet_ops,
	.policy		= nft_redir_policy,
	.maxattr	= NFTA_MASQ_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_redir_module_init_inet(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_redir_inet_type);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक nft_redir_module_init_inet(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init nft_redir_module_init(व्योम)
अणु
	पूर्णांक ret = nft_रेजिस्टर_expr(&nft_redir_ipv4_type);

	अगर (ret)
		वापस ret;

#अगर_घोषित CONFIG_NF_TABLES_IPV6
	ret = nft_रेजिस्टर_expr(&nft_redir_ipv6_type);
	अगर (ret) अणु
		nft_unरेजिस्टर_expr(&nft_redir_ipv4_type);
		वापस ret;
	पूर्ण
#पूर्ण_अगर

	ret = nft_redir_module_init_inet();
	अगर (ret < 0) अणु
		nft_unरेजिस्टर_expr(&nft_redir_ipv4_type);
#अगर_घोषित CONFIG_NF_TABLES_IPV6
		nft_unरेजिस्टर_expr(&nft_redir_ipv6_type);
#पूर्ण_अगर
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास nft_redir_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_redir_ipv4_type);
#अगर_घोषित CONFIG_NF_TABLES_IPV6
	nft_unरेजिस्टर_expr(&nft_redir_ipv6_type);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_TABLES_INET
	nft_unरेजिस्टर_expr(&nft_redir_inet_type);
#पूर्ण_अगर
पूर्ण

module_init(nft_redir_module_init);
module_निकास(nft_redir_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arturo Borrero Gonzalez <arturo@debian.org>");
MODULE_ALIAS_NFT_EXPR("redir");
MODULE_DESCRIPTION("Netfilter nftables redirect support");
