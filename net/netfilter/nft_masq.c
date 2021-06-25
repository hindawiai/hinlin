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
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_nat_masquerade.h>

काष्ठा nft_masq अणु
	u32			flags;
	u8			sreg_proto_min;
	u8			sreg_proto_max;
पूर्ण;

अटल स्थिर काष्ठा nla_policy nft_masq_policy[NFTA_MASQ_MAX + 1] = अणु
	[NFTA_MASQ_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_MASQ_REG_PROTO_MIN]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_MASQ_REG_PROTO_MAX]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_masq_validate(स्थिर काष्ठा nft_ctx *ctx,
			     स्थिर काष्ठा nft_expr *expr,
			     स्थिर काष्ठा nft_data **data)
अणु
	पूर्णांक err;

	err = nft_chain_validate_dependency(ctx->chain, NFT_CHAIN_T_NAT);
	अगर (err < 0)
		वापस err;

	वापस nft_chain_validate_hooks(ctx->chain,
				        (1 << NF_INET_POST_ROUTING));
पूर्ण

अटल पूर्णांक nft_masq_init(स्थिर काष्ठा nft_ctx *ctx,
			 स्थिर काष्ठा nft_expr *expr,
			 स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	u32 plen = माप_field(काष्ठा nf_nat_range, min_addr.all);
	काष्ठा nft_masq *priv = nft_expr_priv(expr);
	पूर्णांक err;

	अगर (tb[NFTA_MASQ_FLAGS]) अणु
		priv->flags = ntohl(nla_get_be32(tb[NFTA_MASQ_FLAGS]));
		अगर (priv->flags & ~NF_NAT_RANGE_MASK)
			वापस -EINVAL;
	पूर्ण

	अगर (tb[NFTA_MASQ_REG_PROTO_MIN]) अणु
		err = nft_parse_रेजिस्टर_load(tb[NFTA_MASQ_REG_PROTO_MIN],
					      &priv->sreg_proto_min, plen);
		अगर (err < 0)
			वापस err;

		अगर (tb[NFTA_MASQ_REG_PROTO_MAX]) अणु
			err = nft_parse_रेजिस्टर_load(tb[NFTA_MASQ_REG_PROTO_MAX],
						      &priv->sreg_proto_max,
						      plen);
			अगर (err < 0)
				वापस err;
		पूर्ण अन्यथा अणु
			priv->sreg_proto_max = priv->sreg_proto_min;
		पूर्ण
	पूर्ण

	वापस nf_ct_netns_get(ctx->net, ctx->family);
पूर्ण

अटल पूर्णांक nft_masq_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_masq *priv = nft_expr_priv(expr);

	अगर (priv->flags != 0 &&
	    nla_put_be32(skb, NFTA_MASQ_FLAGS, htonl(priv->flags)))
		जाओ nla_put_failure;

	अगर (priv->sreg_proto_min) अणु
		अगर (nft_dump_रेजिस्टर(skb, NFTA_MASQ_REG_PROTO_MIN,
				      priv->sreg_proto_min) ||
		    nft_dump_रेजिस्टर(skb, NFTA_MASQ_REG_PROTO_MAX,
				      priv->sreg_proto_max))
			जाओ nla_put_failure;
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल व्योम nft_masq_ipv4_eval(स्थिर काष्ठा nft_expr *expr,
			       काष्ठा nft_regs *regs,
			       स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_masq *priv = nft_expr_priv(expr);
	काष्ठा nf_nat_range2 range;

	स_रखो(&range, 0, माप(range));
	range.flags = priv->flags;
	अगर (priv->sreg_proto_min) अणु
		range.min_proto.all = (__क्रमce __be16)nft_reg_load16(
			&regs->data[priv->sreg_proto_min]);
		range.max_proto.all = (__क्रमce __be16)nft_reg_load16(
			&regs->data[priv->sreg_proto_max]);
	पूर्ण
	regs->verdict.code = nf_nat_masquerade_ipv4(pkt->skb, nft_hook(pkt),
						    &range, nft_out(pkt));
पूर्ण

अटल व्योम
nft_masq_ipv4_destroy(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr)
अणु
	nf_ct_netns_put(ctx->net, NFPROTO_IPV4);
पूर्ण

अटल काष्ठा nft_expr_type nft_masq_ipv4_type;
अटल स्थिर काष्ठा nft_expr_ops nft_masq_ipv4_ops = अणु
	.type		= &nft_masq_ipv4_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_masq)),
	.eval		= nft_masq_ipv4_eval,
	.init		= nft_masq_init,
	.destroy	= nft_masq_ipv4_destroy,
	.dump		= nft_masq_dump,
	.validate	= nft_masq_validate,
पूर्ण;

अटल काष्ठा nft_expr_type nft_masq_ipv4_type __पढ़ो_mostly = अणु
	.family		= NFPROTO_IPV4,
	.name		= "masq",
	.ops		= &nft_masq_ipv4_ops,
	.policy		= nft_masq_policy,
	.maxattr	= NFTA_MASQ_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

#अगर_घोषित CONFIG_NF_TABLES_IPV6
अटल व्योम nft_masq_ipv6_eval(स्थिर काष्ठा nft_expr *expr,
			       काष्ठा nft_regs *regs,
			       स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_masq *priv = nft_expr_priv(expr);
	काष्ठा nf_nat_range2 range;

	स_रखो(&range, 0, माप(range));
	range.flags = priv->flags;
	अगर (priv->sreg_proto_min) अणु
		range.min_proto.all = (__क्रमce __be16)nft_reg_load16(
			&regs->data[priv->sreg_proto_min]);
		range.max_proto.all = (__क्रमce __be16)nft_reg_load16(
			&regs->data[priv->sreg_proto_max]);
	पूर्ण
	regs->verdict.code = nf_nat_masquerade_ipv6(pkt->skb, &range,
						    nft_out(pkt));
पूर्ण

अटल व्योम
nft_masq_ipv6_destroy(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr)
अणु
	nf_ct_netns_put(ctx->net, NFPROTO_IPV6);
पूर्ण

अटल काष्ठा nft_expr_type nft_masq_ipv6_type;
अटल स्थिर काष्ठा nft_expr_ops nft_masq_ipv6_ops = अणु
	.type		= &nft_masq_ipv6_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_masq)),
	.eval		= nft_masq_ipv6_eval,
	.init		= nft_masq_init,
	.destroy	= nft_masq_ipv6_destroy,
	.dump		= nft_masq_dump,
	.validate	= nft_masq_validate,
पूर्ण;

अटल काष्ठा nft_expr_type nft_masq_ipv6_type __पढ़ो_mostly = अणु
	.family		= NFPROTO_IPV6,
	.name		= "masq",
	.ops		= &nft_masq_ipv6_ops,
	.policy		= nft_masq_policy,
	.maxattr	= NFTA_MASQ_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_masq_module_init_ipv6(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_masq_ipv6_type);
पूर्ण

अटल व्योम nft_masq_module_निकास_ipv6(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_masq_ipv6_type);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक nft_masq_module_init_ipv6(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम nft_masq_module_निकास_ipv6(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_TABLES_INET
अटल व्योम nft_masq_inet_eval(स्थिर काष्ठा nft_expr *expr,
			       काष्ठा nft_regs *regs,
			       स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	चयन (nft_pf(pkt)) अणु
	हाल NFPROTO_IPV4:
		वापस nft_masq_ipv4_eval(expr, regs, pkt);
	हाल NFPROTO_IPV6:
		वापस nft_masq_ipv6_eval(expr, regs, pkt);
	पूर्ण

	WARN_ON_ONCE(1);
पूर्ण

अटल व्योम
nft_masq_inet_destroy(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr)
अणु
	nf_ct_netns_put(ctx->net, NFPROTO_INET);
पूर्ण

अटल काष्ठा nft_expr_type nft_masq_inet_type;
अटल स्थिर काष्ठा nft_expr_ops nft_masq_inet_ops = अणु
	.type		= &nft_masq_inet_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_masq)),
	.eval		= nft_masq_inet_eval,
	.init		= nft_masq_init,
	.destroy	= nft_masq_inet_destroy,
	.dump		= nft_masq_dump,
	.validate	= nft_masq_validate,
पूर्ण;

अटल काष्ठा nft_expr_type nft_masq_inet_type __पढ़ो_mostly = अणु
	.family		= NFPROTO_INET,
	.name		= "masq",
	.ops		= &nft_masq_inet_ops,
	.policy		= nft_masq_policy,
	.maxattr	= NFTA_MASQ_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_masq_module_init_inet(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_masq_inet_type);
पूर्ण

अटल व्योम nft_masq_module_निकास_inet(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_masq_inet_type);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक nft_masq_module_init_inet(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम nft_masq_module_निकास_inet(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init nft_masq_module_init(व्योम)
अणु
	पूर्णांक ret;

	ret = nft_masq_module_init_ipv6();
	अगर (ret < 0)
		वापस ret;

	ret = nft_masq_module_init_inet();
	अगर (ret < 0) अणु
		nft_masq_module_निकास_ipv6();
		वापस ret;
	पूर्ण

	ret = nft_रेजिस्टर_expr(&nft_masq_ipv4_type);
	अगर (ret < 0) अणु
		nft_masq_module_निकास_inet();
		nft_masq_module_निकास_ipv6();
		वापस ret;
	पूर्ण

	ret = nf_nat_masquerade_inet_रेजिस्टर_notअगरiers();
	अगर (ret < 0) अणु
		nft_masq_module_निकास_ipv6();
		nft_masq_module_निकास_inet();
		nft_unरेजिस्टर_expr(&nft_masq_ipv4_type);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास nft_masq_module_निकास(व्योम)
अणु
	nft_masq_module_निकास_ipv6();
	nft_masq_module_निकास_inet();
	nft_unरेजिस्टर_expr(&nft_masq_ipv4_type);
	nf_nat_masquerade_inet_unरेजिस्टर_notअगरiers();
पूर्ण

module_init(nft_masq_module_init);
module_निकास(nft_masq_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arturo Borrero Gonzalez <arturo@debian.org>");
MODULE_ALIAS_NFT_EXPR("masq");
MODULE_DESCRIPTION("Netfilter nftables masquerade expression support");
