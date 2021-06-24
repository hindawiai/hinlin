<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008-2009 Patrick McHardy <kaber@trash.net>
 * Copyright (c) 2012 Pablo Neira Ayuso <pablo@netfilter.org>
 * Copyright (c) 2012 Intel Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/माला.स>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/ip.h>

काष्ठा nft_nat अणु
	u8			sreg_addr_min;
	u8			sreg_addr_max;
	u8			sreg_proto_min;
	u8			sreg_proto_max;
	क्रमागत nf_nat_manip_type  type:8;
	u8			family;
	u16			flags;
पूर्ण;

अटल व्योम nft_nat_setup_addr(काष्ठा nf_nat_range2 *range,
			       स्थिर काष्ठा nft_regs *regs,
			       स्थिर काष्ठा nft_nat *priv)
अणु
	चयन (priv->family) अणु
	हाल AF_INET:
		range->min_addr.ip = (__क्रमce __be32)
				regs->data[priv->sreg_addr_min];
		range->max_addr.ip = (__क्रमce __be32)
				regs->data[priv->sreg_addr_max];
		अवरोध;
	हाल AF_INET6:
		स_नकल(range->min_addr.ip6, &regs->data[priv->sreg_addr_min],
		       माप(range->min_addr.ip6));
		स_नकल(range->max_addr.ip6, &regs->data[priv->sreg_addr_max],
		       माप(range->max_addr.ip6));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम nft_nat_setup_proto(काष्ठा nf_nat_range2 *range,
				स्थिर काष्ठा nft_regs *regs,
				स्थिर काष्ठा nft_nat *priv)
अणु
	range->min_proto.all = (__क्रमce __be16)
		nft_reg_load16(&regs->data[priv->sreg_proto_min]);
	range->max_proto.all = (__क्रमce __be16)
		nft_reg_load16(&regs->data[priv->sreg_proto_max]);
पूर्ण

अटल व्योम nft_nat_setup_neपंचांगap(काष्ठा nf_nat_range2 *range,
				 स्थिर काष्ठा nft_pktinfo *pkt,
				 स्थिर काष्ठा nft_nat *priv)
अणु
	काष्ठा sk_buff *skb = pkt->skb;
	जोड़ nf_inet_addr new_addr;
	__be32 neपंचांगask;
	पूर्णांक i, len = 0;

	चयन (priv->type) अणु
	हाल NFT_NAT_SNAT:
		अगर (nft_pf(pkt) == NFPROTO_IPV4) अणु
			new_addr.ip = ip_hdr(skb)->saddr;
			len = माप(काष्ठा in_addr);
		पूर्ण अन्यथा अणु
			new_addr.in6 = ipv6_hdr(skb)->saddr;
			len = माप(काष्ठा in6_addr);
		पूर्ण
		अवरोध;
	हाल NFT_NAT_DNAT:
		अगर (nft_pf(pkt) == NFPROTO_IPV4) अणु
			new_addr.ip = ip_hdr(skb)->daddr;
			len = माप(काष्ठा in_addr);
		पूर्ण अन्यथा अणु
			new_addr.in6 = ipv6_hdr(skb)->daddr;
			len = माप(काष्ठा in6_addr);
		पूर्ण
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < len / माप(__be32); i++) अणु
		neपंचांगask = ~(range->min_addr.ip6[i] ^ range->max_addr.ip6[i]);
		new_addr.ip6[i] &= ~neपंचांगask;
		new_addr.ip6[i] |= range->min_addr.ip6[i] & neपंचांगask;
	पूर्ण

	range->min_addr = new_addr;
	range->max_addr = new_addr;
पूर्ण

अटल व्योम nft_nat_eval(स्थिर काष्ठा nft_expr *expr,
			 काष्ठा nft_regs *regs,
			 स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_nat *priv = nft_expr_priv(expr);
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(pkt->skb, &ctinfo);
	काष्ठा nf_nat_range2 range;

	स_रखो(&range, 0, माप(range));

	अगर (priv->sreg_addr_min) अणु
		nft_nat_setup_addr(&range, regs, priv);
		अगर (priv->flags & NF_NAT_RANGE_NETMAP)
			nft_nat_setup_neपंचांगap(&range, pkt, priv);
	पूर्ण

	अगर (priv->sreg_proto_min)
		nft_nat_setup_proto(&range, regs, priv);

	range.flags = priv->flags;

	regs->verdict.code = nf_nat_setup_info(ct, &range, priv->type);
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_nat_policy[NFTA_NAT_MAX + 1] = अणु
	[NFTA_NAT_TYPE]		 = अणु .type = NLA_U32 पूर्ण,
	[NFTA_NAT_FAMILY]	 = अणु .type = NLA_U32 पूर्ण,
	[NFTA_NAT_REG_ADDR_MIN]	 = अणु .type = NLA_U32 पूर्ण,
	[NFTA_NAT_REG_ADDR_MAX]	 = अणु .type = NLA_U32 पूर्ण,
	[NFTA_NAT_REG_PROTO_MIN] = अणु .type = NLA_U32 पूर्ण,
	[NFTA_NAT_REG_PROTO_MAX] = अणु .type = NLA_U32 पूर्ण,
	[NFTA_NAT_FLAGS]	 = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_nat_validate(स्थिर काष्ठा nft_ctx *ctx,
			    स्थिर काष्ठा nft_expr *expr,
			    स्थिर काष्ठा nft_data **data)
अणु
	काष्ठा nft_nat *priv = nft_expr_priv(expr);
	पूर्णांक err;

	err = nft_chain_validate_dependency(ctx->chain, NFT_CHAIN_T_NAT);
	अगर (err < 0)
		वापस err;

	चयन (priv->type) अणु
	हाल NFT_NAT_SNAT:
		err = nft_chain_validate_hooks(ctx->chain,
					       (1 << NF_INET_POST_ROUTING) |
					       (1 << NF_INET_LOCAL_IN));
		अवरोध;
	हाल NFT_NAT_DNAT:
		err = nft_chain_validate_hooks(ctx->chain,
					       (1 << NF_INET_PRE_ROUTING) |
					       (1 << NF_INET_LOCAL_OUT));
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक nft_nat_init(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr,
			स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_nat *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक alen, plen;
	u32 family;
	पूर्णांक err;

	अगर (tb[NFTA_NAT_TYPE] == शून्य ||
	    (tb[NFTA_NAT_REG_ADDR_MIN] == शून्य &&
	     tb[NFTA_NAT_REG_PROTO_MIN] == शून्य))
		वापस -EINVAL;

	चयन (ntohl(nla_get_be32(tb[NFTA_NAT_TYPE]))) अणु
	हाल NFT_NAT_SNAT:
		priv->type = NF_NAT_MANIP_SRC;
		अवरोध;
	हाल NFT_NAT_DNAT:
		priv->type = NF_NAT_MANIP_DST;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (tb[NFTA_NAT_FAMILY] == शून्य)
		वापस -EINVAL;

	family = ntohl(nla_get_be32(tb[NFTA_NAT_FAMILY]));
	अगर (ctx->family != NFPROTO_INET && ctx->family != family)
		वापस -EOPNOTSUPP;

	चयन (family) अणु
	हाल NFPROTO_IPV4:
		alen = माप_field(काष्ठा nf_nat_range, min_addr.ip);
		अवरोध;
	हाल NFPROTO_IPV6:
		alen = माप_field(काष्ठा nf_nat_range, min_addr.ip6);
		अवरोध;
	शेष:
		वापस -EAFNOSUPPORT;
	पूर्ण
	priv->family = family;

	अगर (tb[NFTA_NAT_REG_ADDR_MIN]) अणु
		err = nft_parse_रेजिस्टर_load(tb[NFTA_NAT_REG_ADDR_MIN],
					      &priv->sreg_addr_min, alen);
		अगर (err < 0)
			वापस err;

		अगर (tb[NFTA_NAT_REG_ADDR_MAX]) अणु
			err = nft_parse_रेजिस्टर_load(tb[NFTA_NAT_REG_ADDR_MAX],
						      &priv->sreg_addr_max,
						      alen);
			अगर (err < 0)
				वापस err;
		पूर्ण अन्यथा अणु
			priv->sreg_addr_max = priv->sreg_addr_min;
		पूर्ण

		priv->flags |= NF_NAT_RANGE_MAP_IPS;
	पूर्ण

	plen = माप_field(काष्ठा nf_nat_range, min_addr.all);
	अगर (tb[NFTA_NAT_REG_PROTO_MIN]) अणु
		err = nft_parse_रेजिस्टर_load(tb[NFTA_NAT_REG_PROTO_MIN],
					      &priv->sreg_proto_min, plen);
		अगर (err < 0)
			वापस err;

		अगर (tb[NFTA_NAT_REG_PROTO_MAX]) अणु
			err = nft_parse_रेजिस्टर_load(tb[NFTA_NAT_REG_PROTO_MAX],
						      &priv->sreg_proto_max,
						      plen);
			अगर (err < 0)
				वापस err;
		पूर्ण अन्यथा अणु
			priv->sreg_proto_max = priv->sreg_proto_min;
		पूर्ण

		priv->flags |= NF_NAT_RANGE_PROTO_SPECIFIED;
	पूर्ण

	अगर (tb[NFTA_NAT_FLAGS]) अणु
		priv->flags |= ntohl(nla_get_be32(tb[NFTA_NAT_FLAGS]));
		अगर (priv->flags & ~NF_NAT_RANGE_MASK)
			वापस -EOPNOTSUPP;
	पूर्ण

	वापस nf_ct_netns_get(ctx->net, family);
पूर्ण

अटल पूर्णांक nft_nat_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_nat *priv = nft_expr_priv(expr);

	चयन (priv->type) अणु
	हाल NF_NAT_MANIP_SRC:
		अगर (nla_put_be32(skb, NFTA_NAT_TYPE, htonl(NFT_NAT_SNAT)))
			जाओ nla_put_failure;
		अवरोध;
	हाल NF_NAT_MANIP_DST:
		अगर (nla_put_be32(skb, NFTA_NAT_TYPE, htonl(NFT_NAT_DNAT)))
			जाओ nla_put_failure;
		अवरोध;
	पूर्ण

	अगर (nla_put_be32(skb, NFTA_NAT_FAMILY, htonl(priv->family)))
		जाओ nla_put_failure;

	अगर (priv->sreg_addr_min) अणु
		अगर (nft_dump_रेजिस्टर(skb, NFTA_NAT_REG_ADDR_MIN,
				      priv->sreg_addr_min) ||
		    nft_dump_रेजिस्टर(skb, NFTA_NAT_REG_ADDR_MAX,
				      priv->sreg_addr_max))
			जाओ nla_put_failure;
	पूर्ण

	अगर (priv->sreg_proto_min) अणु
		अगर (nft_dump_रेजिस्टर(skb, NFTA_NAT_REG_PROTO_MIN,
				      priv->sreg_proto_min) ||
		    nft_dump_रेजिस्टर(skb, NFTA_NAT_REG_PROTO_MAX,
				      priv->sreg_proto_max))
			जाओ nla_put_failure;
	पूर्ण

	अगर (priv->flags != 0) अणु
		अगर (nla_put_be32(skb, NFTA_NAT_FLAGS, htonl(priv->flags)))
			जाओ nla_put_failure;
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल व्योम
nft_nat_destroy(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_nat *priv = nft_expr_priv(expr);

	nf_ct_netns_put(ctx->net, priv->family);
पूर्ण

अटल काष्ठा nft_expr_type nft_nat_type;
अटल स्थिर काष्ठा nft_expr_ops nft_nat_ops = अणु
	.type           = &nft_nat_type,
	.size           = NFT_EXPR_SIZE(माप(काष्ठा nft_nat)),
	.eval           = nft_nat_eval,
	.init           = nft_nat_init,
	.destroy        = nft_nat_destroy,
	.dump           = nft_nat_dump,
	.validate	= nft_nat_validate,
पूर्ण;

अटल काष्ठा nft_expr_type nft_nat_type __पढ़ो_mostly = अणु
	.name           = "nat",
	.ops            = &nft_nat_ops,
	.policy         = nft_nat_policy,
	.maxattr        = NFTA_NAT_MAX,
	.owner          = THIS_MODULE,
पूर्ण;

#अगर_घोषित CONFIG_NF_TABLES_INET
अटल व्योम nft_nat_inet_eval(स्थिर काष्ठा nft_expr *expr,
			      काष्ठा nft_regs *regs,
			      स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_nat *priv = nft_expr_priv(expr);

	अगर (priv->family == nft_pf(pkt))
		nft_nat_eval(expr, regs, pkt);
पूर्ण

अटल स्थिर काष्ठा nft_expr_ops nft_nat_inet_ops = अणु
	.type           = &nft_nat_type,
	.size           = NFT_EXPR_SIZE(माप(काष्ठा nft_nat)),
	.eval           = nft_nat_inet_eval,
	.init           = nft_nat_init,
	.destroy        = nft_nat_destroy,
	.dump           = nft_nat_dump,
	.validate	= nft_nat_validate,
पूर्ण;

अटल काष्ठा nft_expr_type nft_inet_nat_type __पढ़ो_mostly = अणु
	.name           = "nat",
	.family		= NFPROTO_INET,
	.ops            = &nft_nat_inet_ops,
	.policy         = nft_nat_policy,
	.maxattr        = NFTA_NAT_MAX,
	.owner          = THIS_MODULE,
पूर्ण;

अटल पूर्णांक nft_nat_inet_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_inet_nat_type);
पूर्ण

अटल व्योम nft_nat_inet_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_inet_nat_type);
पूर्ण
#अन्यथा
अटल पूर्णांक nft_nat_inet_module_init(व्योम) अणु वापस 0; पूर्ण
अटल व्योम nft_nat_inet_module_निकास(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init nft_nat_module_init(व्योम)
अणु
	पूर्णांक ret = nft_nat_inet_module_init();

	अगर (ret)
		वापस ret;

	ret = nft_रेजिस्टर_expr(&nft_nat_type);
	अगर (ret)
		nft_nat_inet_module_निकास();

	वापस ret;
पूर्ण

अटल व्योम __निकास nft_nat_module_निकास(व्योम)
अणु
	nft_nat_inet_module_निकास();
	nft_unरेजिस्टर_expr(&nft_nat_type);
पूर्ण

module_init(nft_nat_module_init);
module_निकास(nft_nat_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tomasz Bursztyka <tomasz.bursztyka@linux.intel.com>");
MODULE_ALIAS_NFT_EXPR("nat");
MODULE_DESCRIPTION("Network Address Translation support");
