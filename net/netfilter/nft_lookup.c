<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2009 Patrick McHardy <kaber@trash.net>
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>

काष्ठा nft_lookup अणु
	काष्ठा nft_set			*set;
	u8				sreg;
	u8				dreg;
	bool				invert;
	काष्ठा nft_set_binding		binding;
पूर्ण;

व्योम nft_lookup_eval(स्थिर काष्ठा nft_expr *expr,
		     काष्ठा nft_regs *regs,
		     स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_lookup *priv = nft_expr_priv(expr);
	स्थिर काष्ठा nft_set *set = priv->set;
	स्थिर काष्ठा nft_set_ext *ext = शून्य;
	स्थिर काष्ठा net *net = nft_net(pkt);
	bool found;

	found = set->ops->lookup(net, set, &regs->data[priv->sreg], &ext) ^
				 priv->invert;
	अगर (!found) अणु
		ext = nft_set_catchall_lookup(net, set);
		अगर (!ext) अणु
			regs->verdict.code = NFT_BREAK;
			वापस;
		पूर्ण
	पूर्ण

	अगर (ext) अणु
		अगर (set->flags & NFT_SET_MAP)
			nft_data_copy(&regs->data[priv->dreg],
				      nft_set_ext_data(ext), set->dlen);

		nft_set_elem_update_expr(ext, regs, pkt);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_lookup_policy[NFTA_LOOKUP_MAX + 1] = अणु
	[NFTA_LOOKUP_SET]	= अणु .type = NLA_STRING,
				    .len = NFT_SET_MAXNAMELEN - 1 पूर्ण,
	[NFTA_LOOKUP_SET_ID]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_LOOKUP_SREG]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_LOOKUP_DREG]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_LOOKUP_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_lookup_init(स्थिर काष्ठा nft_ctx *ctx,
			   स्थिर काष्ठा nft_expr *expr,
			   स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_lookup *priv = nft_expr_priv(expr);
	u8 genmask = nft_genmask_next(ctx->net);
	काष्ठा nft_set *set;
	u32 flags;
	पूर्णांक err;

	अगर (tb[NFTA_LOOKUP_SET] == शून्य ||
	    tb[NFTA_LOOKUP_SREG] == शून्य)
		वापस -EINVAL;

	set = nft_set_lookup_global(ctx->net, ctx->table, tb[NFTA_LOOKUP_SET],
				    tb[NFTA_LOOKUP_SET_ID], genmask);
	अगर (IS_ERR(set))
		वापस PTR_ERR(set);

	err = nft_parse_रेजिस्टर_load(tb[NFTA_LOOKUP_SREG], &priv->sreg,
				      set->klen);
	अगर (err < 0)
		वापस err;

	अगर (tb[NFTA_LOOKUP_FLAGS]) अणु
		flags = ntohl(nla_get_be32(tb[NFTA_LOOKUP_FLAGS]));

		अगर (flags & ~NFT_LOOKUP_F_INV)
			वापस -EINVAL;

		अगर (flags & NFT_LOOKUP_F_INV) अणु
			अगर (set->flags & NFT_SET_MAP)
				वापस -EINVAL;
			priv->invert = true;
		पूर्ण
	पूर्ण

	अगर (tb[NFTA_LOOKUP_DREG] != शून्य) अणु
		अगर (priv->invert)
			वापस -EINVAL;
		अगर (!(set->flags & NFT_SET_MAP))
			वापस -EINVAL;

		err = nft_parse_रेजिस्टर_store(ctx, tb[NFTA_LOOKUP_DREG],
					       &priv->dreg, शून्य, set->dtype,
					       set->dlen);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अगर (set->flags & NFT_SET_MAP)
		वापस -EINVAL;

	priv->binding.flags = set->flags & NFT_SET_MAP;

	err = nf_tables_bind_set(ctx, set, &priv->binding);
	अगर (err < 0)
		वापस err;

	priv->set = set;
	वापस 0;
पूर्ण

अटल व्योम nft_lookup_deactivate(स्थिर काष्ठा nft_ctx *ctx,
				  स्थिर काष्ठा nft_expr *expr,
				  क्रमागत nft_trans_phase phase)
अणु
	काष्ठा nft_lookup *priv = nft_expr_priv(expr);

	nf_tables_deactivate_set(ctx, priv->set, &priv->binding, phase);
पूर्ण

अटल व्योम nft_lookup_activate(स्थिर काष्ठा nft_ctx *ctx,
				स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_lookup *priv = nft_expr_priv(expr);

	priv->set->use++;
पूर्ण

अटल व्योम nft_lookup_destroy(स्थिर काष्ठा nft_ctx *ctx,
			       स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_lookup *priv = nft_expr_priv(expr);

	nf_tables_destroy_set(ctx, priv->set);
पूर्ण

अटल पूर्णांक nft_lookup_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_lookup *priv = nft_expr_priv(expr);
	u32 flags = priv->invert ? NFT_LOOKUP_F_INV : 0;

	अगर (nla_put_string(skb, NFTA_LOOKUP_SET, priv->set->name))
		जाओ nla_put_failure;
	अगर (nft_dump_रेजिस्टर(skb, NFTA_LOOKUP_SREG, priv->sreg))
		जाओ nla_put_failure;
	अगर (priv->set->flags & NFT_SET_MAP)
		अगर (nft_dump_रेजिस्टर(skb, NFTA_LOOKUP_DREG, priv->dreg))
			जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_LOOKUP_FLAGS, htonl(flags)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nft_lookup_validate_setelem(स्थिर काष्ठा nft_ctx *ctx,
				       काष्ठा nft_set *set,
				       स्थिर काष्ठा nft_set_iter *iter,
				       काष्ठा nft_set_elem *elem)
अणु
	स्थिर काष्ठा nft_set_ext *ext = nft_set_elem_ext(set, elem->priv);
	काष्ठा nft_ctx *pctx = (काष्ठा nft_ctx *)ctx;
	स्थिर काष्ठा nft_data *data;
	पूर्णांक err;

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_FLAGS) &&
	    *nft_set_ext_flags(ext) & NFT_SET_ELEM_INTERVAL_END)
		वापस 0;

	data = nft_set_ext_data(ext);
	चयन (data->verdict.code) अणु
	हाल NFT_JUMP:
	हाल NFT_GOTO:
		pctx->level++;
		err = nft_chain_validate(ctx, data->verdict.chain);
		अगर (err < 0)
			वापस err;
		pctx->level--;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nft_lookup_validate(स्थिर काष्ठा nft_ctx *ctx,
			       स्थिर काष्ठा nft_expr *expr,
			       स्थिर काष्ठा nft_data **d)
अणु
	स्थिर काष्ठा nft_lookup *priv = nft_expr_priv(expr);
	काष्ठा nft_set_iter iter;

	अगर (!(priv->set->flags & NFT_SET_MAP) ||
	    priv->set->dtype != NFT_DATA_VERDICT)
		वापस 0;

	iter.genmask	= nft_genmask_next(ctx->net);
	iter.skip	= 0;
	iter.count	= 0;
	iter.err	= 0;
	iter.fn		= nft_lookup_validate_setelem;

	priv->set->ops->walk(ctx, priv->set, &iter);
	अगर (iter.err < 0)
		वापस iter.err;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nft_expr_ops nft_lookup_ops = अणु
	.type		= &nft_lookup_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_lookup)),
	.eval		= nft_lookup_eval,
	.init		= nft_lookup_init,
	.activate	= nft_lookup_activate,
	.deactivate	= nft_lookup_deactivate,
	.destroy	= nft_lookup_destroy,
	.dump		= nft_lookup_dump,
	.validate	= nft_lookup_validate,
पूर्ण;

काष्ठा nft_expr_type nft_lookup_type __पढ़ो_mostly = अणु
	.name		= "lookup",
	.ops		= &nft_lookup_ops,
	.policy		= nft_lookup_policy,
	.maxattr	= NFTA_LOOKUP_MAX,
	.owner		= THIS_MODULE,
पूर्ण;
