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
#समावेश <linux/अगर_arp.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_tables_offload.h>
#समावेश <net/netfilter/nf_tables.h>

काष्ठा nft_cmp_expr अणु
	काष्ठा nft_data		data;
	u8			sreg;
	u8			len;
	क्रमागत nft_cmp_ops	op:8;
पूर्ण;

व्योम nft_cmp_eval(स्थिर काष्ठा nft_expr *expr,
		  काष्ठा nft_regs *regs,
		  स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_cmp_expr *priv = nft_expr_priv(expr);
	पूर्णांक d;

	d = स_भेद(&regs->data[priv->sreg], &priv->data, priv->len);
	चयन (priv->op) अणु
	हाल NFT_CMP_EQ:
		अगर (d != 0)
			जाओ mismatch;
		अवरोध;
	हाल NFT_CMP_NEQ:
		अगर (d == 0)
			जाओ mismatch;
		अवरोध;
	हाल NFT_CMP_LT:
		अगर (d == 0)
			जाओ mismatch;
		fallthrough;
	हाल NFT_CMP_LTE:
		अगर (d > 0)
			जाओ mismatch;
		अवरोध;
	हाल NFT_CMP_GT:
		अगर (d == 0)
			जाओ mismatch;
		fallthrough;
	हाल NFT_CMP_GTE:
		अगर (d < 0)
			जाओ mismatch;
		अवरोध;
	पूर्ण
	वापस;

mismatch:
	regs->verdict.code = NFT_BREAK;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_cmp_policy[NFTA_CMP_MAX + 1] = अणु
	[NFTA_CMP_SREG]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_CMP_OP]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_CMP_DATA]		= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक nft_cmp_init(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr,
			स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_cmp_expr *priv = nft_expr_priv(expr);
	काष्ठा nft_data_desc desc;
	पूर्णांक err;

	err = nft_data_init(शून्य, &priv->data, माप(priv->data), &desc,
			    tb[NFTA_CMP_DATA]);
	अगर (err < 0)
		वापस err;

	अगर (desc.type != NFT_DATA_VALUE) अणु
		err = -EINVAL;
		nft_data_release(&priv->data, desc.type);
		वापस err;
	पूर्ण

	err = nft_parse_रेजिस्टर_load(tb[NFTA_CMP_SREG], &priv->sreg, desc.len);
	अगर (err < 0)
		वापस err;

	priv->op  = ntohl(nla_get_be32(tb[NFTA_CMP_OP]));
	priv->len = desc.len;
	वापस 0;
पूर्ण

अटल पूर्णांक nft_cmp_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_cmp_expr *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_CMP_SREG, priv->sreg))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_CMP_OP, htonl(priv->op)))
		जाओ nla_put_failure;

	अगर (nft_data_dump(skb, NFTA_CMP_DATA, &priv->data,
			  NFT_DATA_VALUE, priv->len) < 0)
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

जोड़ nft_cmp_offload_data अणु
	u16	val16;
	u32	val32;
	u64	val64;
पूर्ण;

अटल व्योम nft_payload_n2h(जोड़ nft_cmp_offload_data *data,
			    स्थिर u8 *val, u32 len)
अणु
	चयन (len) अणु
	हाल 2:
		data->val16 = ntohs(*((u16 *)val));
		अवरोध;
	हाल 4:
		data->val32 = ntohl(*((u32 *)val));
		अवरोध;
	हाल 8:
		data->val64 = be64_to_cpu(*((u64 *)val));
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक __nft_cmp_offload(काष्ठा nft_offload_ctx *ctx,
			     काष्ठा nft_flow_rule *flow,
			     स्थिर काष्ठा nft_cmp_expr *priv)
अणु
	काष्ठा nft_offload_reg *reg = &ctx->regs[priv->sreg];
	जोड़ nft_cmp_offload_data _data, _datamask;
	u8 *mask = (u8 *)&flow->match.mask;
	u8 *key = (u8 *)&flow->match.key;
	u8 *data, *datamask;

	अगर (priv->op != NFT_CMP_EQ || priv->len > reg->len)
		वापस -EOPNOTSUPP;

	अगर (reg->flags & NFT_OFFLOAD_F_NETWORK2HOST) अणु
		nft_payload_n2h(&_data, (u8 *)&priv->data, reg->len);
		nft_payload_n2h(&_datamask, (u8 *)&reg->mask, reg->len);
		data = (u8 *)&_data;
		datamask = (u8 *)&_datamask;
	पूर्ण अन्यथा अणु
		data = (u8 *)&priv->data;
		datamask = (u8 *)&reg->mask;
	पूर्ण

	स_नकल(key + reg->offset, data, reg->len);
	स_नकल(mask + reg->offset, datamask, reg->len);

	flow->match.dissector.used_keys |= BIT(reg->key);
	flow->match.dissector.offset[reg->key] = reg->base_offset;

	अगर (reg->key == FLOW_DISSECTOR_KEY_META &&
	    reg->offset == दुरत्व(काष्ठा nft_flow_key, meta.ingress_अगरtype) &&
	    nft_reg_load16(priv->data.data) != ARPHRD_ETHER)
		वापस -EOPNOTSUPP;

	nft_offload_update_dependency(ctx, &priv->data, reg->len);

	वापस 0;
पूर्ण

अटल पूर्णांक nft_cmp_offload(काष्ठा nft_offload_ctx *ctx,
			   काष्ठा nft_flow_rule *flow,
			   स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_cmp_expr *priv = nft_expr_priv(expr);

	वापस __nft_cmp_offload(ctx, flow, priv);
पूर्ण

अटल स्थिर काष्ठा nft_expr_ops nft_cmp_ops = अणु
	.type		= &nft_cmp_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_cmp_expr)),
	.eval		= nft_cmp_eval,
	.init		= nft_cmp_init,
	.dump		= nft_cmp_dump,
	.offload	= nft_cmp_offload,
पूर्ण;

अटल पूर्णांक nft_cmp_fast_init(स्थिर काष्ठा nft_ctx *ctx,
			     स्थिर काष्ठा nft_expr *expr,
			     स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_cmp_fast_expr *priv = nft_expr_priv(expr);
	काष्ठा nft_data_desc desc;
	काष्ठा nft_data data;
	पूर्णांक err;

	err = nft_data_init(शून्य, &data, माप(data), &desc,
			    tb[NFTA_CMP_DATA]);
	अगर (err < 0)
		वापस err;

	err = nft_parse_रेजिस्टर_load(tb[NFTA_CMP_SREG], &priv->sreg, desc.len);
	अगर (err < 0)
		वापस err;

	desc.len *= BITS_PER_BYTE;

	priv->mask = nft_cmp_fast_mask(desc.len);
	priv->data = data.data[0] & priv->mask;
	priv->len  = desc.len;
	priv->inv  = ntohl(nla_get_be32(tb[NFTA_CMP_OP])) != NFT_CMP_EQ;
	वापस 0;
पूर्ण

अटल पूर्णांक nft_cmp_fast_offload(काष्ठा nft_offload_ctx *ctx,
				काष्ठा nft_flow_rule *flow,
				स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_cmp_fast_expr *priv = nft_expr_priv(expr);
	काष्ठा nft_cmp_expr cmp = अणु
		.data	= अणु
			.data	= अणु
				[0] = priv->data,
			पूर्ण,
		पूर्ण,
		.sreg	= priv->sreg,
		.len	= priv->len / BITS_PER_BYTE,
		.op	= priv->inv ? NFT_CMP_NEQ : NFT_CMP_EQ,
	पूर्ण;

	वापस __nft_cmp_offload(ctx, flow, &cmp);
पूर्ण

अटल पूर्णांक nft_cmp_fast_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_cmp_fast_expr *priv = nft_expr_priv(expr);
	क्रमागत nft_cmp_ops op = priv->inv ? NFT_CMP_NEQ : NFT_CMP_EQ;
	काष्ठा nft_data data;

	अगर (nft_dump_रेजिस्टर(skb, NFTA_CMP_SREG, priv->sreg))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_CMP_OP, htonl(op)))
		जाओ nla_put_failure;

	data.data[0] = priv->data;
	अगर (nft_data_dump(skb, NFTA_CMP_DATA, &data,
			  NFT_DATA_VALUE, priv->len / BITS_PER_BYTE) < 0)
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

स्थिर काष्ठा nft_expr_ops nft_cmp_fast_ops = अणु
	.type		= &nft_cmp_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_cmp_fast_expr)),
	.eval		= शून्य,	/* अंतरभूतd */
	.init		= nft_cmp_fast_init,
	.dump		= nft_cmp_fast_dump,
	.offload	= nft_cmp_fast_offload,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops *
nft_cmp_select_ops(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_data_desc desc;
	काष्ठा nft_data data;
	क्रमागत nft_cmp_ops op;
	पूर्णांक err;

	अगर (tb[NFTA_CMP_SREG] == शून्य ||
	    tb[NFTA_CMP_OP] == शून्य ||
	    tb[NFTA_CMP_DATA] == शून्य)
		वापस ERR_PTR(-EINVAL);

	op = ntohl(nla_get_be32(tb[NFTA_CMP_OP]));
	चयन (op) अणु
	हाल NFT_CMP_EQ:
	हाल NFT_CMP_NEQ:
	हाल NFT_CMP_LT:
	हाल NFT_CMP_LTE:
	हाल NFT_CMP_GT:
	हाल NFT_CMP_GTE:
		अवरोध;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	err = nft_data_init(शून्य, &data, माप(data), &desc,
			    tb[NFTA_CMP_DATA]);
	अगर (err < 0)
		वापस ERR_PTR(err);

	अगर (desc.type != NFT_DATA_VALUE)
		जाओ err1;

	अगर (desc.len <= माप(u32) && (op == NFT_CMP_EQ || op == NFT_CMP_NEQ))
		वापस &nft_cmp_fast_ops;

	वापस &nft_cmp_ops;
err1:
	nft_data_release(&data, desc.type);
	वापस ERR_PTR(-EINVAL);
पूर्ण

काष्ठा nft_expr_type nft_cmp_type __पढ़ो_mostly = अणु
	.name		= "cmp",
	.select_ops	= nft_cmp_select_ops,
	.policy		= nft_cmp_policy,
	.maxattr	= NFTA_CMP_MAX,
	.owner		= THIS_MODULE,
पूर्ण;
