<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Pablo Neira Ayuso <pablo@netfilter.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_tables.h>

काष्ठा nft_range_expr अणु
	काष्ठा nft_data		data_from;
	काष्ठा nft_data		data_to;
	u8			sreg;
	u8			len;
	क्रमागत nft_range_ops	op:8;
पूर्ण;

व्योम nft_range_eval(स्थिर काष्ठा nft_expr *expr,
		    काष्ठा nft_regs *regs, स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_range_expr *priv = nft_expr_priv(expr);
	पूर्णांक d1, d2;

	d1 = स_भेद(&regs->data[priv->sreg], &priv->data_from, priv->len);
	d2 = स_भेद(&regs->data[priv->sreg], &priv->data_to, priv->len);
	चयन (priv->op) अणु
	हाल NFT_RANGE_EQ:
		अगर (d1 < 0 || d2 > 0)
			regs->verdict.code = NFT_BREAK;
		अवरोध;
	हाल NFT_RANGE_NEQ:
		अगर (d1 >= 0 && d2 <= 0)
			regs->verdict.code = NFT_BREAK;
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_range_policy[NFTA_RANGE_MAX + 1] = अणु
	[NFTA_RANGE_SREG]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_RANGE_OP]			= अणु .type = NLA_U32 पूर्ण,
	[NFTA_RANGE_FROM_DATA]		= अणु .type = NLA_NESTED पूर्ण,
	[NFTA_RANGE_TO_DATA]		= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक nft_range_init(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr,
			स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_range_expr *priv = nft_expr_priv(expr);
	काष्ठा nft_data_desc desc_from, desc_to;
	पूर्णांक err;
	u32 op;

	अगर (!tb[NFTA_RANGE_SREG]      ||
	    !tb[NFTA_RANGE_OP]	      ||
	    !tb[NFTA_RANGE_FROM_DATA] ||
	    !tb[NFTA_RANGE_TO_DATA])
		वापस -EINVAL;

	err = nft_data_init(शून्य, &priv->data_from, माप(priv->data_from),
			    &desc_from, tb[NFTA_RANGE_FROM_DATA]);
	अगर (err < 0)
		वापस err;

	अगर (desc_from.type != NFT_DATA_VALUE) अणु
		err = -EINVAL;
		जाओ err1;
	पूर्ण

	err = nft_data_init(शून्य, &priv->data_to, माप(priv->data_to),
			    &desc_to, tb[NFTA_RANGE_TO_DATA]);
	अगर (err < 0)
		जाओ err1;

	अगर (desc_to.type != NFT_DATA_VALUE) अणु
		err = -EINVAL;
		जाओ err2;
	पूर्ण

	अगर (desc_from.len != desc_to.len) अणु
		err = -EINVAL;
		जाओ err2;
	पूर्ण

	err = nft_parse_रेजिस्टर_load(tb[NFTA_RANGE_SREG], &priv->sreg,
				      desc_from.len);
	अगर (err < 0)
		जाओ err2;

	err = nft_parse_u32_check(tb[NFTA_RANGE_OP], U8_MAX, &op);
	अगर (err < 0)
		जाओ err2;

	चयन (op) अणु
	हाल NFT_RANGE_EQ:
	हाल NFT_RANGE_NEQ:
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ err2;
	पूर्ण

	priv->op  = op;
	priv->len = desc_from.len;
	वापस 0;
err2:
	nft_data_release(&priv->data_to, desc_to.type);
err1:
	nft_data_release(&priv->data_from, desc_from.type);
	वापस err;
पूर्ण

अटल पूर्णांक nft_range_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_range_expr *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_RANGE_SREG, priv->sreg))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_RANGE_OP, htonl(priv->op)))
		जाओ nla_put_failure;

	अगर (nft_data_dump(skb, NFTA_RANGE_FROM_DATA, &priv->data_from,
			  NFT_DATA_VALUE, priv->len) < 0 ||
	    nft_data_dump(skb, NFTA_RANGE_TO_DATA, &priv->data_to,
			  NFT_DATA_VALUE, priv->len) < 0)
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा nft_expr_ops nft_range_ops = अणु
	.type		= &nft_range_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_range_expr)),
	.eval		= nft_range_eval,
	.init		= nft_range_init,
	.dump		= nft_range_dump,
पूर्ण;

काष्ठा nft_expr_type nft_range_type __पढ़ो_mostly = अणु
	.name		= "range",
	.ops		= &nft_range_ops,
	.policy		= nft_range_policy,
	.maxattr	= NFTA_RANGE_MAX,
	.owner		= THIS_MODULE,
पूर्ण;
