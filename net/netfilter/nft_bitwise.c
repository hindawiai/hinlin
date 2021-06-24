<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008-2009 Patrick McHardy <kaber@trash.net>
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_offload.h>

काष्ठा nft_bitwise अणु
	u8			sreg;
	u8			dreg;
	क्रमागत nft_bitwise_ops	op:8;
	u8			len;
	काष्ठा nft_data		mask;
	काष्ठा nft_data		xor;
	काष्ठा nft_data		data;
पूर्ण;

अटल व्योम nft_bitwise_eval_bool(u32 *dst, स्थिर u32 *src,
				  स्थिर काष्ठा nft_bitwise *priv)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < DIV_ROUND_UP(priv->len, 4); i++)
		dst[i] = (src[i] & priv->mask.data[i]) ^ priv->xor.data[i];
पूर्ण

अटल व्योम nft_bitwise_eval_lshअगरt(u32 *dst, स्थिर u32 *src,
				    स्थिर काष्ठा nft_bitwise *priv)
अणु
	u32 shअगरt = priv->data.data[0];
	अचिन्हित पूर्णांक i;
	u32 carry = 0;

	क्रम (i = DIV_ROUND_UP(priv->len, माप(u32)); i > 0; i--) अणु
		dst[i - 1] = (src[i - 1] << shअगरt) | carry;
		carry = src[i - 1] >> (BITS_PER_TYPE(u32) - shअगरt);
	पूर्ण
पूर्ण

अटल व्योम nft_bitwise_eval_rshअगरt(u32 *dst, स्थिर u32 *src,
				    स्थिर काष्ठा nft_bitwise *priv)
अणु
	u32 shअगरt = priv->data.data[0];
	अचिन्हित पूर्णांक i;
	u32 carry = 0;

	क्रम (i = 0; i < DIV_ROUND_UP(priv->len, माप(u32)); i++) अणु
		dst[i] = carry | (src[i] >> shअगरt);
		carry = src[i] << (BITS_PER_TYPE(u32) - shअगरt);
	पूर्ण
पूर्ण

व्योम nft_bitwise_eval(स्थिर काष्ठा nft_expr *expr,
		      काष्ठा nft_regs *regs, स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_bitwise *priv = nft_expr_priv(expr);
	स्थिर u32 *src = &regs->data[priv->sreg];
	u32 *dst = &regs->data[priv->dreg];

	चयन (priv->op) अणु
	हाल NFT_BITWISE_BOOL:
		nft_bitwise_eval_bool(dst, src, priv);
		अवरोध;
	हाल NFT_BITWISE_LSHIFT:
		nft_bitwise_eval_lshअगरt(dst, src, priv);
		अवरोध;
	हाल NFT_BITWISE_RSHIFT:
		nft_bitwise_eval_rshअगरt(dst, src, priv);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_bitwise_policy[NFTA_BITWISE_MAX + 1] = अणु
	[NFTA_BITWISE_SREG]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_BITWISE_DREG]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_BITWISE_LEN]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_BITWISE_MASK]	= अणु .type = NLA_NESTED पूर्ण,
	[NFTA_BITWISE_XOR]	= अणु .type = NLA_NESTED पूर्ण,
	[NFTA_BITWISE_OP]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_BITWISE_DATA]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक nft_bitwise_init_bool(काष्ठा nft_bitwise *priv,
				 स्थिर काष्ठा nlattr *स्थिर tb[])
अणु
	काष्ठा nft_data_desc mask, xor;
	पूर्णांक err;

	अगर (tb[NFTA_BITWISE_DATA])
		वापस -EINVAL;

	अगर (!tb[NFTA_BITWISE_MASK] ||
	    !tb[NFTA_BITWISE_XOR])
		वापस -EINVAL;

	err = nft_data_init(शून्य, &priv->mask, माप(priv->mask), &mask,
			    tb[NFTA_BITWISE_MASK]);
	अगर (err < 0)
		वापस err;
	अगर (mask.type != NFT_DATA_VALUE || mask.len != priv->len) अणु
		err = -EINVAL;
		जाओ err1;
	पूर्ण

	err = nft_data_init(शून्य, &priv->xor, माप(priv->xor), &xor,
			    tb[NFTA_BITWISE_XOR]);
	अगर (err < 0)
		जाओ err1;
	अगर (xor.type != NFT_DATA_VALUE || xor.len != priv->len) अणु
		err = -EINVAL;
		जाओ err2;
	पूर्ण

	वापस 0;
err2:
	nft_data_release(&priv->xor, xor.type);
err1:
	nft_data_release(&priv->mask, mask.type);
	वापस err;
पूर्ण

अटल पूर्णांक nft_bitwise_init_shअगरt(काष्ठा nft_bitwise *priv,
				  स्थिर काष्ठा nlattr *स्थिर tb[])
अणु
	काष्ठा nft_data_desc d;
	पूर्णांक err;

	अगर (tb[NFTA_BITWISE_MASK] ||
	    tb[NFTA_BITWISE_XOR])
		वापस -EINVAL;

	अगर (!tb[NFTA_BITWISE_DATA])
		वापस -EINVAL;

	err = nft_data_init(शून्य, &priv->data, माप(priv->data), &d,
			    tb[NFTA_BITWISE_DATA]);
	अगर (err < 0)
		वापस err;
	अगर (d.type != NFT_DATA_VALUE || d.len != माप(u32) ||
	    priv->data.data[0] >= BITS_PER_TYPE(u32)) अणु
		nft_data_release(&priv->data, d.type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nft_bitwise_init(स्थिर काष्ठा nft_ctx *ctx,
			    स्थिर काष्ठा nft_expr *expr,
			    स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_bitwise *priv = nft_expr_priv(expr);
	u32 len;
	पूर्णांक err;

	err = nft_parse_u32_check(tb[NFTA_BITWISE_LEN], U8_MAX, &len);
	अगर (err < 0)
		वापस err;

	priv->len = len;

	err = nft_parse_रेजिस्टर_load(tb[NFTA_BITWISE_SREG], &priv->sreg,
				      priv->len);
	अगर (err < 0)
		वापस err;

	err = nft_parse_रेजिस्टर_store(ctx, tb[NFTA_BITWISE_DREG],
				       &priv->dreg, शून्य, NFT_DATA_VALUE,
				       priv->len);
	अगर (err < 0)
		वापस err;

	अगर (tb[NFTA_BITWISE_OP]) अणु
		priv->op = ntohl(nla_get_be32(tb[NFTA_BITWISE_OP]));
		चयन (priv->op) अणु
		हाल NFT_BITWISE_BOOL:
		हाल NFT_BITWISE_LSHIFT:
		हाल NFT_BITWISE_RSHIFT:
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->op = NFT_BITWISE_BOOL;
	पूर्ण

	चयन(priv->op) अणु
	हाल NFT_BITWISE_BOOL:
		err = nft_bitwise_init_bool(priv, tb);
		अवरोध;
	हाल NFT_BITWISE_LSHIFT:
	हाल NFT_BITWISE_RSHIFT:
		err = nft_bitwise_init_shअगरt(priv, tb);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक nft_bitwise_dump_bool(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा nft_bitwise *priv)
अणु
	अगर (nft_data_dump(skb, NFTA_BITWISE_MASK, &priv->mask,
			  NFT_DATA_VALUE, priv->len) < 0)
		वापस -1;

	अगर (nft_data_dump(skb, NFTA_BITWISE_XOR, &priv->xor,
			  NFT_DATA_VALUE, priv->len) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक nft_bitwise_dump_shअगरt(काष्ठा sk_buff *skb,
				  स्थिर काष्ठा nft_bitwise *priv)
अणु
	अगर (nft_data_dump(skb, NFTA_BITWISE_DATA, &priv->data,
			  NFT_DATA_VALUE, माप(u32)) < 0)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक nft_bitwise_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_bitwise *priv = nft_expr_priv(expr);
	पूर्णांक err = 0;

	अगर (nft_dump_रेजिस्टर(skb, NFTA_BITWISE_SREG, priv->sreg))
		वापस -1;
	अगर (nft_dump_रेजिस्टर(skb, NFTA_BITWISE_DREG, priv->dreg))
		वापस -1;
	अगर (nla_put_be32(skb, NFTA_BITWISE_LEN, htonl(priv->len)))
		वापस -1;
	अगर (nla_put_be32(skb, NFTA_BITWISE_OP, htonl(priv->op)))
		वापस -1;

	चयन (priv->op) अणु
	हाल NFT_BITWISE_BOOL:
		err = nft_bitwise_dump_bool(skb, priv);
		अवरोध;
	हाल NFT_BITWISE_LSHIFT:
	हाल NFT_BITWISE_RSHIFT:
		err = nft_bitwise_dump_shअगरt(skb, priv);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा nft_data zero;

अटल पूर्णांक nft_bitwise_offload(काष्ठा nft_offload_ctx *ctx,
			       काष्ठा nft_flow_rule *flow,
			       स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_bitwise *priv = nft_expr_priv(expr);
	काष्ठा nft_offload_reg *reg = &ctx->regs[priv->dreg];

	अगर (priv->op != NFT_BITWISE_BOOL)
		वापस -EOPNOTSUPP;

	अगर (स_भेद(&priv->xor, &zero, माप(priv->xor)) ||
	    priv->sreg != priv->dreg || priv->len != reg->len)
		वापस -EOPNOTSUPP;

	स_नकल(&reg->mask, &priv->mask, माप(priv->mask));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nft_expr_ops nft_bitwise_ops = अणु
	.type		= &nft_bitwise_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_bitwise)),
	.eval		= nft_bitwise_eval,
	.init		= nft_bitwise_init,
	.dump		= nft_bitwise_dump,
	.offload	= nft_bitwise_offload,
पूर्ण;

अटल पूर्णांक
nft_bitwise_extract_u32_data(स्थिर काष्ठा nlattr * स्थिर tb, u32 *out)
अणु
	काष्ठा nft_data_desc desc;
	काष्ठा nft_data data;
	पूर्णांक err = 0;

	err = nft_data_init(शून्य, &data, माप(data), &desc, tb);
	अगर (err < 0)
		वापस err;

	अगर (desc.type != NFT_DATA_VALUE || desc.len != माप(u32)) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण
	*out = data.data[0];
err:
	nft_data_release(&data, desc.type);
	वापस err;
पूर्ण

अटल पूर्णांक nft_bitwise_fast_init(स्थिर काष्ठा nft_ctx *ctx,
				 स्थिर काष्ठा nft_expr *expr,
				 स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_bitwise_fast_expr *priv = nft_expr_priv(expr);
	पूर्णांक err;

	err = nft_parse_रेजिस्टर_load(tb[NFTA_BITWISE_SREG], &priv->sreg,
				      माप(u32));
	अगर (err < 0)
		वापस err;

	err = nft_parse_रेजिस्टर_store(ctx, tb[NFTA_BITWISE_DREG], &priv->dreg,
				       शून्य, NFT_DATA_VALUE, माप(u32));
	अगर (err < 0)
		वापस err;

	अगर (tb[NFTA_BITWISE_DATA])
		वापस -EINVAL;

	अगर (!tb[NFTA_BITWISE_MASK] ||
	    !tb[NFTA_BITWISE_XOR])
		वापस -EINVAL;

	err = nft_bitwise_extract_u32_data(tb[NFTA_BITWISE_MASK], &priv->mask);
	अगर (err < 0)
		वापस err;

	err = nft_bitwise_extract_u32_data(tb[NFTA_BITWISE_XOR], &priv->xor);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक
nft_bitwise_fast_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_bitwise_fast_expr *priv = nft_expr_priv(expr);
	काष्ठा nft_data data;

	अगर (nft_dump_रेजिस्टर(skb, NFTA_BITWISE_SREG, priv->sreg))
		वापस -1;
	अगर (nft_dump_रेजिस्टर(skb, NFTA_BITWISE_DREG, priv->dreg))
		वापस -1;
	अगर (nla_put_be32(skb, NFTA_BITWISE_LEN, htonl(माप(u32))))
		वापस -1;
	अगर (nla_put_be32(skb, NFTA_BITWISE_OP, htonl(NFT_BITWISE_BOOL)))
		वापस -1;

	data.data[0] = priv->mask;
	अगर (nft_data_dump(skb, NFTA_BITWISE_MASK, &data,
			  NFT_DATA_VALUE, माप(u32)) < 0)
		वापस -1;

	data.data[0] = priv->xor;
	अगर (nft_data_dump(skb, NFTA_BITWISE_XOR, &data,
			  NFT_DATA_VALUE, माप(u32)) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक nft_bitwise_fast_offload(काष्ठा nft_offload_ctx *ctx,
				    काष्ठा nft_flow_rule *flow,
				    स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_bitwise_fast_expr *priv = nft_expr_priv(expr);
	काष्ठा nft_offload_reg *reg = &ctx->regs[priv->dreg];

	अगर (priv->xor || priv->sreg != priv->dreg || reg->len != माप(u32))
		वापस -EOPNOTSUPP;

	reg->mask.data[0] = priv->mask;
	वापस 0;
पूर्ण

स्थिर काष्ठा nft_expr_ops nft_bitwise_fast_ops = अणु
	.type		= &nft_bitwise_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_bitwise_fast_expr)),
	.eval		= शून्य, /* अंतरभूतd */
	.init		= nft_bitwise_fast_init,
	.dump		= nft_bitwise_fast_dump,
	.offload	= nft_bitwise_fast_offload,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops *
nft_bitwise_select_ops(स्थिर काष्ठा nft_ctx *ctx,
		       स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	पूर्णांक err;
	u32 len;

	अगर (!tb[NFTA_BITWISE_LEN] ||
	    !tb[NFTA_BITWISE_SREG] ||
	    !tb[NFTA_BITWISE_DREG])
		वापस ERR_PTR(-EINVAL);

	err = nft_parse_u32_check(tb[NFTA_BITWISE_LEN], U8_MAX, &len);
	अगर (err < 0)
		वापस ERR_PTR(err);

	अगर (len != माप(u32))
		वापस &nft_bitwise_ops;

	अगर (tb[NFTA_BITWISE_OP] &&
	    ntohl(nla_get_be32(tb[NFTA_BITWISE_OP])) != NFT_BITWISE_BOOL)
		वापस &nft_bitwise_ops;

	वापस &nft_bitwise_fast_ops;
पूर्ण

काष्ठा nft_expr_type nft_bitwise_type __पढ़ो_mostly = अणु
	.name		= "bitwise",
	.select_ops	= nft_bitwise_select_ops,
	.policy		= nft_bitwise_policy,
	.maxattr	= NFTA_BITWISE_MAX,
	.owner		= THIS_MODULE,
पूर्ण;
