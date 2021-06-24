<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <net/ip.h>
#समावेश <net/tcp.h>

#समावेश <net/netfilter/nf_tables.h>
#समावेश <linux/netfilter/nfnetlink_osf.h>

काष्ठा nft_osf अणु
	u8			dreg;
	u8			ttl;
	u32			flags;
पूर्ण;

अटल स्थिर काष्ठा nla_policy nft_osf_policy[NFTA_OSF_MAX + 1] = अणु
	[NFTA_OSF_DREG]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_OSF_TTL]		= अणु .type = NLA_U8 पूर्ण,
	[NFTA_OSF_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल व्योम nft_osf_eval(स्थिर काष्ठा nft_expr *expr, काष्ठा nft_regs *regs,
			 स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_osf *priv = nft_expr_priv(expr);
	u32 *dest = &regs->data[priv->dreg];
	काष्ठा sk_buff *skb = pkt->skb;
	अक्षर os_match[NFT_OSF_MAXGENRELEN + 1];
	स्थिर काष्ठा tcphdr *tcp;
	काष्ठा nf_osf_data data;
	काष्ठा tcphdr _tcph;

	tcp = skb_header_poपूर्णांकer(skb, ip_hdrlen(skb),
				 माप(काष्ठा tcphdr), &_tcph);
	अगर (!tcp) अणु
		regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण
	अगर (!tcp->syn) अणु
		regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण

	अगर (!nf_osf_find(skb, nf_osf_fingers, priv->ttl, &data)) अणु
		म_नकलन((अक्षर *)dest, "unknown", NFT_OSF_MAXGENRELEN);
	पूर्ण अन्यथा अणु
		अगर (priv->flags & NFT_OSF_F_VERSION)
			snम_लिखो(os_match, NFT_OSF_MAXGENRELEN, "%s:%s",
				 data.genre, data.version);
		अन्यथा
			strlcpy(os_match, data.genre, NFT_OSF_MAXGENRELEN);

		म_नकलन((अक्षर *)dest, os_match, NFT_OSF_MAXGENRELEN);
	पूर्ण
पूर्ण

अटल पूर्णांक nft_osf_init(स्थिर काष्ठा nft_ctx *ctx,
			स्थिर काष्ठा nft_expr *expr,
			स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_osf *priv = nft_expr_priv(expr);
	u32 flags;
	पूर्णांक err;
	u8 ttl;

	अगर (!tb[NFTA_OSF_DREG])
		वापस -EINVAL;

	अगर (tb[NFTA_OSF_TTL]) अणु
		ttl = nla_get_u8(tb[NFTA_OSF_TTL]);
		अगर (ttl > 2)
			वापस -EINVAL;
		priv->ttl = ttl;
	पूर्ण

	अगर (tb[NFTA_OSF_FLAGS]) अणु
		flags = ntohl(nla_get_be32(tb[NFTA_OSF_FLAGS]));
		अगर (flags != NFT_OSF_F_VERSION)
			वापस -EINVAL;
		priv->flags = flags;
	पूर्ण

	err = nft_parse_रेजिस्टर_store(ctx, tb[NFTA_OSF_DREG], &priv->dreg,
				       शून्य, NFT_DATA_VALUE,
				       NFT_OSF_MAXGENRELEN);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक nft_osf_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_osf *priv = nft_expr_priv(expr);

	अगर (nla_put_u8(skb, NFTA_OSF_TTL, priv->ttl))
		जाओ nla_put_failure;

	अगर (nla_put_be32(skb, NFTA_OSF_FLAGS, ntohl(priv->flags)))
		जाओ nla_put_failure;

	अगर (nft_dump_रेजिस्टर(skb, NFTA_OSF_DREG, priv->dreg))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nft_osf_validate(स्थिर काष्ठा nft_ctx *ctx,
			    स्थिर काष्ठा nft_expr *expr,
			    स्थिर काष्ठा nft_data **data)
अणु
	वापस nft_chain_validate_hooks(ctx->chain, (1 << NF_INET_LOCAL_IN) |
						    (1 << NF_INET_PRE_ROUTING) |
						    (1 << NF_INET_FORWARD));
पूर्ण

अटल काष्ठा nft_expr_type nft_osf_type;
अटल स्थिर काष्ठा nft_expr_ops nft_osf_op = अणु
	.eval		= nft_osf_eval,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_osf)),
	.init		= nft_osf_init,
	.dump		= nft_osf_dump,
	.type		= &nft_osf_type,
	.validate	= nft_osf_validate,
पूर्ण;

अटल काष्ठा nft_expr_type nft_osf_type __पढ़ो_mostly = अणु
	.ops		= &nft_osf_op,
	.name		= "osf",
	.owner		= THIS_MODULE,
	.policy		= nft_osf_policy,
	.maxattr	= NFTA_OSF_MAX,
पूर्ण;

अटल पूर्णांक __init nft_osf_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_osf_type);
पूर्ण

अटल व्योम __निकास nft_osf_module_निकास(व्योम)
अणु
	वापस nft_unरेजिस्टर_expr(&nft_osf_type);
पूर्ण

module_init(nft_osf_module_init);
module_निकास(nft_osf_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fernando Fernandez <ffmancera@riseup.net>");
MODULE_ALIAS_NFT_EXPR("osf");
MODULE_DESCRIPTION("nftables passive OS fingerprint support");
