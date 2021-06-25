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
#समावेश <linux/icmp.h>
#समावेश <linux/icmpv6.h>

स्थिर काष्ठा nla_policy nft_reject_policy[NFTA_REJECT_MAX + 1] = अणु
	[NFTA_REJECT_TYPE]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_REJECT_ICMP_CODE]		= अणु .type = NLA_U8 पूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(nft_reject_policy);

पूर्णांक nft_reject_validate(स्थिर काष्ठा nft_ctx *ctx,
			स्थिर काष्ठा nft_expr *expr,
			स्थिर काष्ठा nft_data **data)
अणु
	वापस nft_chain_validate_hooks(ctx->chain,
					(1 << NF_INET_LOCAL_IN) |
					(1 << NF_INET_FORWARD) |
					(1 << NF_INET_LOCAL_OUT) |
					(1 << NF_INET_PRE_ROUTING));
पूर्ण
EXPORT_SYMBOL_GPL(nft_reject_validate);

पूर्णांक nft_reject_init(स्थिर काष्ठा nft_ctx *ctx,
		    स्थिर काष्ठा nft_expr *expr,
		    स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_reject *priv = nft_expr_priv(expr);
	पूर्णांक icmp_code;

	अगर (tb[NFTA_REJECT_TYPE] == शून्य)
		वापस -EINVAL;

	priv->type = ntohl(nla_get_be32(tb[NFTA_REJECT_TYPE]));
	चयन (priv->type) अणु
	हाल NFT_REJECT_ICMP_UNREACH:
	हाल NFT_REJECT_ICMPX_UNREACH:
		अगर (tb[NFTA_REJECT_ICMP_CODE] == शून्य)
			वापस -EINVAL;

		icmp_code = nla_get_u8(tb[NFTA_REJECT_ICMP_CODE]);
		अगर (priv->type == NFT_REJECT_ICMPX_UNREACH &&
		    icmp_code > NFT_REJECT_ICMPX_MAX)
			वापस -EINVAL;

		priv->icmp_code = icmp_code;
		अवरोध;
	हाल NFT_REJECT_TCP_RST:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nft_reject_init);

पूर्णांक nft_reject_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_reject *priv = nft_expr_priv(expr);

	अगर (nla_put_be32(skb, NFTA_REJECT_TYPE, htonl(priv->type)))
		जाओ nla_put_failure;

	चयन (priv->type) अणु
	हाल NFT_REJECT_ICMP_UNREACH:
	हाल NFT_REJECT_ICMPX_UNREACH:
		अगर (nla_put_u8(skb, NFTA_REJECT_ICMP_CODE, priv->icmp_code))
			जाओ nla_put_failure;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(nft_reject_dump);

अटल u8 icmp_code_v4[NFT_REJECT_ICMPX_MAX + 1] = अणु
	[NFT_REJECT_ICMPX_NO_ROUTE]		= ICMP_NET_UNREACH,
	[NFT_REJECT_ICMPX_PORT_UNREACH]		= ICMP_PORT_UNREACH,
	[NFT_REJECT_ICMPX_HOST_UNREACH]		= ICMP_HOST_UNREACH,
	[NFT_REJECT_ICMPX_ADMIN_PROHIBITED]	= ICMP_PKT_FILTERED,
पूर्ण;

पूर्णांक nft_reject_icmp_code(u8 code)
अणु
	अगर (WARN_ON_ONCE(code > NFT_REJECT_ICMPX_MAX))
		वापस ICMP_NET_UNREACH;

	वापस icmp_code_v4[code];
पूर्ण

EXPORT_SYMBOL_GPL(nft_reject_icmp_code);


अटल u8 icmp_code_v6[NFT_REJECT_ICMPX_MAX + 1] = अणु
	[NFT_REJECT_ICMPX_NO_ROUTE]		= ICMPV6_NOROUTE,
	[NFT_REJECT_ICMPX_PORT_UNREACH]		= ICMPV6_PORT_UNREACH,
	[NFT_REJECT_ICMPX_HOST_UNREACH]		= ICMPV6_ADDR_UNREACH,
	[NFT_REJECT_ICMPX_ADMIN_PROHIBITED]	= ICMPV6_ADM_PROHIBITED,
पूर्ण;

पूर्णांक nft_reject_icmpv6_code(u8 code)
अणु
	अगर (WARN_ON_ONCE(code > NFT_REJECT_ICMPX_MAX))
		वापस ICMPV6_NOROUTE;

	वापस icmp_code_v6[code];
पूर्ण

EXPORT_SYMBOL_GPL(nft_reject_icmpv6_code);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_DESCRIPTION("Netfilter x_tables over nftables module");
