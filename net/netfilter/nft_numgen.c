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
#समावेश <linux/अटल_key.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>

अटल DEFINE_PER_CPU(काष्ठा rnd_state, nft_numgen_pअक्रमom_state);

काष्ठा nft_ng_inc अणु
	u8			dreg;
	u32			modulus;
	atomic_t		counter;
	u32			offset;
पूर्ण;

अटल u32 nft_ng_inc_gen(काष्ठा nft_ng_inc *priv)
अणु
	u32 nval, oval;

	करो अणु
		oval = atomic_पढ़ो(&priv->counter);
		nval = (oval + 1 < priv->modulus) ? oval + 1 : 0;
	पूर्ण जबतक (atomic_cmpxchg(&priv->counter, oval, nval) != oval);

	वापस nval + priv->offset;
पूर्ण

अटल व्योम nft_ng_inc_eval(स्थिर काष्ठा nft_expr *expr,
			    काष्ठा nft_regs *regs,
			    स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_ng_inc *priv = nft_expr_priv(expr);

	regs->data[priv->dreg] = nft_ng_inc_gen(priv);
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_ng_policy[NFTA_NG_MAX + 1] = अणु
	[NFTA_NG_DREG]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_NG_MODULUS]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_NG_TYPE]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_NG_OFFSET]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_ng_inc_init(स्थिर काष्ठा nft_ctx *ctx,
			   स्थिर काष्ठा nft_expr *expr,
			   स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_ng_inc *priv = nft_expr_priv(expr);

	अगर (tb[NFTA_NG_OFFSET])
		priv->offset = ntohl(nla_get_be32(tb[NFTA_NG_OFFSET]));

	priv->modulus = ntohl(nla_get_be32(tb[NFTA_NG_MODULUS]));
	अगर (priv->modulus == 0)
		वापस -दुस्फल;

	अगर (priv->offset + priv->modulus - 1 < priv->offset)
		वापस -EOVERFLOW;

	atomic_set(&priv->counter, priv->modulus - 1);

	वापस nft_parse_रेजिस्टर_store(ctx, tb[NFTA_NG_DREG], &priv->dreg,
					शून्य, NFT_DATA_VALUE, माप(u32));
पूर्ण

अटल पूर्णांक nft_ng_dump(काष्ठा sk_buff *skb, क्रमागत nft_रेजिस्टरs dreg,
		       u32 modulus, क्रमागत nft_ng_types type, u32 offset)
अणु
	अगर (nft_dump_रेजिस्टर(skb, NFTA_NG_DREG, dreg))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_NG_MODULUS, htonl(modulus)))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_NG_TYPE, htonl(type)))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_NG_OFFSET, htonl(offset)))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nft_ng_inc_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_ng_inc *priv = nft_expr_priv(expr);

	वापस nft_ng_dump(skb, priv->dreg, priv->modulus, NFT_NG_INCREMENTAL,
			   priv->offset);
पूर्ण

काष्ठा nft_ng_अक्रमom अणु
	u8			dreg;
	u32			modulus;
	u32			offset;
पूर्ण;

अटल u32 nft_ng_अक्रमom_gen(काष्ठा nft_ng_अक्रमom *priv)
अणु
	काष्ठा rnd_state *state = this_cpu_ptr(&nft_numgen_pअक्रमom_state);

	वापस reciprocal_scale(pअक्रमom_u32_state(state), priv->modulus) +
	       priv->offset;
पूर्ण

अटल व्योम nft_ng_अक्रमom_eval(स्थिर काष्ठा nft_expr *expr,
			       काष्ठा nft_regs *regs,
			       स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_ng_अक्रमom *priv = nft_expr_priv(expr);

	regs->data[priv->dreg] = nft_ng_अक्रमom_gen(priv);
पूर्ण

अटल पूर्णांक nft_ng_अक्रमom_init(स्थिर काष्ठा nft_ctx *ctx,
			      स्थिर काष्ठा nft_expr *expr,
			      स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_ng_अक्रमom *priv = nft_expr_priv(expr);

	अगर (tb[NFTA_NG_OFFSET])
		priv->offset = ntohl(nla_get_be32(tb[NFTA_NG_OFFSET]));

	priv->modulus = ntohl(nla_get_be32(tb[NFTA_NG_MODULUS]));
	अगर (priv->modulus == 0)
		वापस -दुस्फल;

	अगर (priv->offset + priv->modulus - 1 < priv->offset)
		वापस -EOVERFLOW;

	pअक्रमom_init_once(&nft_numgen_pअक्रमom_state);

	वापस nft_parse_रेजिस्टर_store(ctx, tb[NFTA_NG_DREG], &priv->dreg,
					शून्य, NFT_DATA_VALUE, माप(u32));
पूर्ण

अटल पूर्णांक nft_ng_अक्रमom_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_ng_अक्रमom *priv = nft_expr_priv(expr);

	वापस nft_ng_dump(skb, priv->dreg, priv->modulus, NFT_NG_RANDOM,
			   priv->offset);
पूर्ण

अटल काष्ठा nft_expr_type nft_ng_type;
अटल स्थिर काष्ठा nft_expr_ops nft_ng_inc_ops = अणु
	.type		= &nft_ng_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_ng_inc)),
	.eval		= nft_ng_inc_eval,
	.init		= nft_ng_inc_init,
	.dump		= nft_ng_inc_dump,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops nft_ng_अक्रमom_ops = अणु
	.type		= &nft_ng_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_ng_अक्रमom)),
	.eval		= nft_ng_अक्रमom_eval,
	.init		= nft_ng_अक्रमom_init,
	.dump		= nft_ng_अक्रमom_dump,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops *
nft_ng_select_ops(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	u32 type;

	अगर (!tb[NFTA_NG_DREG]	 ||
	    !tb[NFTA_NG_MODULUS] ||
	    !tb[NFTA_NG_TYPE])
		वापस ERR_PTR(-EINVAL);

	type = ntohl(nla_get_be32(tb[NFTA_NG_TYPE]));

	चयन (type) अणु
	हाल NFT_NG_INCREMENTAL:
		वापस &nft_ng_inc_ops;
	हाल NFT_NG_RANDOM:
		वापस &nft_ng_अक्रमom_ops;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा nft_expr_type nft_ng_type __पढ़ो_mostly = अणु
	.name		= "numgen",
	.select_ops	= nft_ng_select_ops,
	.policy		= nft_ng_policy,
	.maxattr	= NFTA_NG_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_ng_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_ng_type);
पूर्ण

अटल व्योम __निकास nft_ng_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_ng_type);
पूर्ण

module_init(nft_ng_module_init);
module_निकास(nft_ng_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Laura Garcia <nevola@gmail.com>");
MODULE_ALIAS_NFT_EXPR("numgen");
MODULE_DESCRIPTION("nftables number generator module");
