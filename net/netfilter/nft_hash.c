<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Laura Garcia <nevola@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <linux/jhash.h>

काष्ठा nft_jhash अणु
	u8			sreg;
	u8			dreg;
	u8			len;
	bool			स्वतःgen_seed:1;
	u32			modulus;
	u32			seed;
	u32			offset;
पूर्ण;

अटल व्योम nft_jhash_eval(स्थिर काष्ठा nft_expr *expr,
			   काष्ठा nft_regs *regs,
			   स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_jhash *priv = nft_expr_priv(expr);
	स्थिर व्योम *data = &regs->data[priv->sreg];
	u32 h;

	h = reciprocal_scale(jhash(data, priv->len, priv->seed),
			     priv->modulus);

	regs->data[priv->dreg] = h + priv->offset;
पूर्ण

काष्ठा nft_symhash अणु
	u8			dreg;
	u32			modulus;
	u32			offset;
पूर्ण;

अटल व्योम nft_symhash_eval(स्थिर काष्ठा nft_expr *expr,
			     काष्ठा nft_regs *regs,
			     स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_symhash *priv = nft_expr_priv(expr);
	काष्ठा sk_buff *skb = pkt->skb;
	u32 h;

	h = reciprocal_scale(__skb_get_hash_symmetric(skb), priv->modulus);

	regs->data[priv->dreg] = h + priv->offset;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_hash_policy[NFTA_HASH_MAX + 1] = अणु
	[NFTA_HASH_SREG]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_HASH_DREG]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_HASH_LEN]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_HASH_MODULUS]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_HASH_SEED]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_HASH_OFFSET]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_HASH_TYPE]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_jhash_init(स्थिर काष्ठा nft_ctx *ctx,
			  स्थिर काष्ठा nft_expr *expr,
			  स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_jhash *priv = nft_expr_priv(expr);
	u32 len;
	पूर्णांक err;

	अगर (!tb[NFTA_HASH_SREG] ||
	    !tb[NFTA_HASH_DREG] ||
	    !tb[NFTA_HASH_LEN]  ||
	    !tb[NFTA_HASH_MODULUS])
		वापस -EINVAL;

	अगर (tb[NFTA_HASH_OFFSET])
		priv->offset = ntohl(nla_get_be32(tb[NFTA_HASH_OFFSET]));

	err = nft_parse_u32_check(tb[NFTA_HASH_LEN], U8_MAX, &len);
	अगर (err < 0)
		वापस err;
	अगर (len == 0)
		वापस -दुस्फल;

	priv->len = len;

	err = nft_parse_रेजिस्टर_load(tb[NFTA_HASH_SREG], &priv->sreg, len);
	अगर (err < 0)
		वापस err;

	priv->modulus = ntohl(nla_get_be32(tb[NFTA_HASH_MODULUS]));
	अगर (priv->modulus < 1)
		वापस -दुस्फल;

	अगर (priv->offset + priv->modulus - 1 < priv->offset)
		वापस -EOVERFLOW;

	अगर (tb[NFTA_HASH_SEED]) अणु
		priv->seed = ntohl(nla_get_be32(tb[NFTA_HASH_SEED]));
	पूर्ण अन्यथा अणु
		priv->स्वतःgen_seed = true;
		get_अक्रमom_bytes(&priv->seed, माप(priv->seed));
	पूर्ण

	वापस nft_parse_रेजिस्टर_store(ctx, tb[NFTA_HASH_DREG], &priv->dreg,
					शून्य, NFT_DATA_VALUE, माप(u32));
पूर्ण

अटल पूर्णांक nft_symhash_init(स्थिर काष्ठा nft_ctx *ctx,
			    स्थिर काष्ठा nft_expr *expr,
			    स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_symhash *priv = nft_expr_priv(expr);

	अगर (!tb[NFTA_HASH_DREG]    ||
	    !tb[NFTA_HASH_MODULUS])
		वापस -EINVAL;

	अगर (tb[NFTA_HASH_OFFSET])
		priv->offset = ntohl(nla_get_be32(tb[NFTA_HASH_OFFSET]));

	priv->modulus = ntohl(nla_get_be32(tb[NFTA_HASH_MODULUS]));
	अगर (priv->modulus < 1)
		वापस -दुस्फल;

	अगर (priv->offset + priv->modulus - 1 < priv->offset)
		वापस -EOVERFLOW;

	वापस nft_parse_रेजिस्टर_store(ctx, tb[NFTA_HASH_DREG],
					&priv->dreg, शून्य, NFT_DATA_VALUE,
					माप(u32));
पूर्ण

अटल पूर्णांक nft_jhash_dump(काष्ठा sk_buff *skb,
			  स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_jhash *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_HASH_SREG, priv->sreg))
		जाओ nla_put_failure;
	अगर (nft_dump_रेजिस्टर(skb, NFTA_HASH_DREG, priv->dreg))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_HASH_LEN, htonl(priv->len)))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_HASH_MODULUS, htonl(priv->modulus)))
		जाओ nla_put_failure;
	अगर (!priv->स्वतःgen_seed &&
	    nla_put_be32(skb, NFTA_HASH_SEED, htonl(priv->seed)))
		जाओ nla_put_failure;
	अगर (priv->offset != 0)
		अगर (nla_put_be32(skb, NFTA_HASH_OFFSET, htonl(priv->offset)))
			जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_HASH_TYPE, htonl(NFT_HASH_JENKINS)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nft_symhash_dump(काष्ठा sk_buff *skb,
			    स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_symhash *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_HASH_DREG, priv->dreg))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_HASH_MODULUS, htonl(priv->modulus)))
		जाओ nla_put_failure;
	अगर (priv->offset != 0)
		अगर (nla_put_be32(skb, NFTA_HASH_OFFSET, htonl(priv->offset)))
			जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_HASH_TYPE, htonl(NFT_HASH_SYM)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल काष्ठा nft_expr_type nft_hash_type;
अटल स्थिर काष्ठा nft_expr_ops nft_jhash_ops = अणु
	.type		= &nft_hash_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_jhash)),
	.eval		= nft_jhash_eval,
	.init		= nft_jhash_init,
	.dump		= nft_jhash_dump,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops nft_symhash_ops = अणु
	.type		= &nft_hash_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_symhash)),
	.eval		= nft_symhash_eval,
	.init		= nft_symhash_init,
	.dump		= nft_symhash_dump,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops *
nft_hash_select_ops(स्थिर काष्ठा nft_ctx *ctx,
		    स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	u32 type;

	अगर (!tb[NFTA_HASH_TYPE])
		वापस &nft_jhash_ops;

	type = ntohl(nla_get_be32(tb[NFTA_HASH_TYPE]));
	चयन (type) अणु
	हाल NFT_HASH_SYM:
		वापस &nft_symhash_ops;
	हाल NFT_HASH_JENKINS:
		वापस &nft_jhash_ops;
	शेष:
		अवरोध;
	पूर्ण
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल काष्ठा nft_expr_type nft_hash_type __पढ़ो_mostly = अणु
	.name		= "hash",
	.select_ops	= nft_hash_select_ops,
	.policy		= nft_hash_policy,
	.maxattr	= NFTA_HASH_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_hash_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_hash_type);
पूर्ण

अटल व्योम __निकास nft_hash_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_hash_type);
पूर्ण

module_init(nft_hash_module_init);
module_निकास(nft_hash_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Laura Garcia <nevola@gmail.com>");
MODULE_ALIAS_NFT_EXPR("hash");
MODULE_DESCRIPTION("Netfilter nftables hash module");
