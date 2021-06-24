<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>

काष्ठा nft_dynset अणु
	काष्ठा nft_set			*set;
	काष्ठा nft_set_ext_पंचांगpl		पंचांगpl;
	क्रमागत nft_dynset_ops		op:8;
	u8				sreg_key;
	u8				sreg_data;
	bool				invert;
	bool				expr;
	u8				num_exprs;
	u64				समयout;
	काष्ठा nft_expr			*expr_array[NFT_SET_EXPR_MAX];
	काष्ठा nft_set_binding		binding;
पूर्ण;

अटल पूर्णांक nft_dynset_expr_setup(स्थिर काष्ठा nft_dynset *priv,
				 स्थिर काष्ठा nft_set_ext *ext)
अणु
	काष्ठा nft_set_elem_expr *elem_expr = nft_set_ext_expr(ext);
	काष्ठा nft_expr *expr;
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_exprs; i++) अणु
		expr = nft_setelem_expr_at(elem_expr, elem_expr->size);
		अगर (nft_expr_clone(expr, priv->expr_array[i]) < 0)
			वापस -1;

		elem_expr->size += priv->expr_array[i]->ops->size;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम *nft_dynset_new(काष्ठा nft_set *set, स्थिर काष्ठा nft_expr *expr,
			    काष्ठा nft_regs *regs)
अणु
	स्थिर काष्ठा nft_dynset *priv = nft_expr_priv(expr);
	काष्ठा nft_set_ext *ext;
	u64 समयout;
	व्योम *elem;

	अगर (!atomic_add_unless(&set->nelems, 1, set->size))
		वापस शून्य;

	समयout = priv->समयout ? : set->समयout;
	elem = nft_set_elem_init(set, &priv->पंचांगpl,
				 &regs->data[priv->sreg_key], शून्य,
				 &regs->data[priv->sreg_data],
				 समयout, 0, GFP_ATOMIC);
	अगर (elem == शून्य)
		जाओ err1;

	ext = nft_set_elem_ext(set, elem);
	अगर (priv->num_exprs && nft_dynset_expr_setup(priv, ext) < 0)
		जाओ err2;

	वापस elem;

err2:
	nft_set_elem_destroy(set, elem, false);
err1:
	अगर (set->size)
		atomic_dec(&set->nelems);
	वापस शून्य;
पूर्ण

व्योम nft_dynset_eval(स्थिर काष्ठा nft_expr *expr,
		     काष्ठा nft_regs *regs, स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_dynset *priv = nft_expr_priv(expr);
	काष्ठा nft_set *set = priv->set;
	स्थिर काष्ठा nft_set_ext *ext;
	u64 समयout;

	अगर (priv->op == NFT_DYNSET_OP_DELETE) अणु
		set->ops->delete(set, &regs->data[priv->sreg_key]);
		वापस;
	पूर्ण

	अगर (set->ops->update(set, &regs->data[priv->sreg_key], nft_dynset_new,
			     expr, regs, &ext)) अणु
		अगर (priv->op == NFT_DYNSET_OP_UPDATE &&
		    nft_set_ext_exists(ext, NFT_SET_EXT_EXPIRATION)) अणु
			समयout = priv->समयout ? : set->समयout;
			*nft_set_ext_expiration(ext) = get_jअगरfies_64() + समयout;
		पूर्ण

		nft_set_elem_update_expr(ext, regs, pkt);

		अगर (priv->invert)
			regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण

	अगर (!priv->invert)
		regs->verdict.code = NFT_BREAK;
पूर्ण

अटल व्योम nft_dynset_ext_add_expr(काष्ठा nft_dynset *priv)
अणु
	u8 size = 0;
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_exprs; i++)
		size += priv->expr_array[i]->ops->size;

	nft_set_ext_add_length(&priv->पंचांगpl, NFT_SET_EXT_EXPRESSIONS,
			       माप(काष्ठा nft_set_elem_expr) + size);
पूर्ण

अटल काष्ठा nft_expr *
nft_dynset_expr_alloc(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_set *set,
		      स्थिर काष्ठा nlattr *attr, पूर्णांक pos)
अणु
	काष्ठा nft_expr *expr;
	पूर्णांक err;

	expr = nft_set_elem_expr_alloc(ctx, set, attr);
	अगर (IS_ERR(expr))
		वापस expr;

	अगर (set->exprs[pos] && set->exprs[pos]->ops != expr->ops) अणु
		err = -EOPNOTSUPP;
		जाओ err_dynset_expr;
	पूर्ण

	वापस expr;

err_dynset_expr:
	nft_expr_destroy(ctx, expr);
	वापस ERR_PTR(err);
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_dynset_policy[NFTA_DYNSET_MAX + 1] = अणु
	[NFTA_DYNSET_SET_NAME]	= अणु .type = NLA_STRING,
				    .len = NFT_SET_MAXNAMELEN - 1 पूर्ण,
	[NFTA_DYNSET_SET_ID]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_DYNSET_OP]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_DYNSET_SREG_KEY]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_DYNSET_SREG_DATA]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_DYNSET_TIMEOUT]	= अणु .type = NLA_U64 पूर्ण,
	[NFTA_DYNSET_EXPR]	= अणु .type = NLA_NESTED पूर्ण,
	[NFTA_DYNSET_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_DYNSET_EXPRESSIONS] = अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक nft_dynset_init(स्थिर काष्ठा nft_ctx *ctx,
			   स्थिर काष्ठा nft_expr *expr,
			   स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(ctx->net);
	काष्ठा nft_dynset *priv = nft_expr_priv(expr);
	u8 genmask = nft_genmask_next(ctx->net);
	काष्ठा nft_set *set;
	u64 समयout;
	पूर्णांक err, i;

	lockdep_निश्चित_held(&nft_net->commit_mutex);

	अगर (tb[NFTA_DYNSET_SET_NAME] == शून्य ||
	    tb[NFTA_DYNSET_OP] == शून्य ||
	    tb[NFTA_DYNSET_SREG_KEY] == शून्य)
		वापस -EINVAL;

	अगर (tb[NFTA_DYNSET_FLAGS]) अणु
		u32 flags = ntohl(nla_get_be32(tb[NFTA_DYNSET_FLAGS]));
		अगर (flags & ~(NFT_DYNSET_F_INV | NFT_DYNSET_F_EXPR))
			वापस -EOPNOTSUPP;
		अगर (flags & NFT_DYNSET_F_INV)
			priv->invert = true;
		अगर (flags & NFT_DYNSET_F_EXPR)
			priv->expr = true;
	पूर्ण

	set = nft_set_lookup_global(ctx->net, ctx->table,
				    tb[NFTA_DYNSET_SET_NAME],
				    tb[NFTA_DYNSET_SET_ID], genmask);
	अगर (IS_ERR(set))
		वापस PTR_ERR(set);

	अगर (set->ops->update == शून्य)
		वापस -EOPNOTSUPP;

	अगर (set->flags & NFT_SET_CONSTANT)
		वापस -EBUSY;

	priv->op = ntohl(nla_get_be32(tb[NFTA_DYNSET_OP]));
	चयन (priv->op) अणु
	हाल NFT_DYNSET_OP_ADD:
	हाल NFT_DYNSET_OP_DELETE:
		अवरोध;
	हाल NFT_DYNSET_OP_UPDATE:
		अगर (!(set->flags & NFT_SET_TIMEOUT))
			वापस -EOPNOTSUPP;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	समयout = 0;
	अगर (tb[NFTA_DYNSET_TIMEOUT] != शून्य) अणु
		अगर (!(set->flags & NFT_SET_TIMEOUT))
			वापस -EOPNOTSUPP;

		err = nf_msecs_to_jअगरfies64(tb[NFTA_DYNSET_TIMEOUT], &समयout);
		अगर (err)
			वापस err;
	पूर्ण

	err = nft_parse_रेजिस्टर_load(tb[NFTA_DYNSET_SREG_KEY], &priv->sreg_key,
				      set->klen);
	अगर (err < 0)
		वापस err;

	अगर (tb[NFTA_DYNSET_SREG_DATA] != शून्य) अणु
		अगर (!(set->flags & NFT_SET_MAP))
			वापस -EOPNOTSUPP;
		अगर (set->dtype == NFT_DATA_VERDICT)
			वापस -EOPNOTSUPP;

		err = nft_parse_रेजिस्टर_load(tb[NFTA_DYNSET_SREG_DATA],
					      &priv->sreg_data, set->dlen);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अगर (set->flags & NFT_SET_MAP)
		वापस -EINVAL;

	अगर ((tb[NFTA_DYNSET_EXPR] || tb[NFTA_DYNSET_EXPRESSIONS]) &&
	    !(set->flags & NFT_SET_EVAL))
		वापस -EINVAL;

	अगर (tb[NFTA_DYNSET_EXPR]) अणु
		काष्ठा nft_expr *dynset_expr;

		dynset_expr = nft_dynset_expr_alloc(ctx, set,
						    tb[NFTA_DYNSET_EXPR], 0);
		अगर (IS_ERR(dynset_expr))
			वापस PTR_ERR(dynset_expr);

		priv->num_exprs++;
		priv->expr_array[0] = dynset_expr;

		अगर (set->num_exprs > 1 ||
		    (set->num_exprs == 1 &&
		     dynset_expr->ops != set->exprs[0]->ops)) अणु
			err = -EOPNOTSUPP;
			जाओ err_expr_मुक्त;
		पूर्ण
	पूर्ण अन्यथा अगर (tb[NFTA_DYNSET_EXPRESSIONS]) अणु
		काष्ठा nft_expr *dynset_expr;
		काष्ठा nlattr *पंचांगp;
		पूर्णांक left;

		अगर (!priv->expr)
			वापस -EINVAL;

		i = 0;
		nla_क्रम_each_nested(पंचांगp, tb[NFTA_DYNSET_EXPRESSIONS], left) अणु
			अगर (i == NFT_SET_EXPR_MAX) अणु
				err = -E2BIG;
				जाओ err_expr_मुक्त;
			पूर्ण
			अगर (nla_type(पंचांगp) != NFTA_LIST_ELEM) अणु
				err = -EINVAL;
				जाओ err_expr_मुक्त;
			पूर्ण
			dynset_expr = nft_dynset_expr_alloc(ctx, set, पंचांगp, i);
			अगर (IS_ERR(dynset_expr)) अणु
				err = PTR_ERR(dynset_expr);
				जाओ err_expr_मुक्त;
			पूर्ण
			priv->expr_array[i] = dynset_expr;
			priv->num_exprs++;

			अगर (set->num_exprs &&
			    dynset_expr->ops != set->exprs[i]->ops) अणु
				err = -EOPNOTSUPP;
				जाओ err_expr_मुक्त;
			पूर्ण
			i++;
		पूर्ण
		अगर (set->num_exprs && set->num_exprs != i) अणु
			err = -EOPNOTSUPP;
			जाओ err_expr_मुक्त;
		पूर्ण
	पूर्ण अन्यथा अगर (set->num_exprs > 0) अणु
		err = nft_set_elem_expr_clone(ctx, set, priv->expr_array);
		अगर (err < 0)
			वापस err;

		priv->num_exprs = set->num_exprs;
	पूर्ण

	nft_set_ext_prepare(&priv->पंचांगpl);
	nft_set_ext_add_length(&priv->पंचांगpl, NFT_SET_EXT_KEY, set->klen);
	अगर (set->flags & NFT_SET_MAP)
		nft_set_ext_add_length(&priv->पंचांगpl, NFT_SET_EXT_DATA, set->dlen);

	अगर (priv->num_exprs)
		nft_dynset_ext_add_expr(priv);

	अगर (set->flags & NFT_SET_TIMEOUT) अणु
		अगर (समयout || set->समयout) अणु
			nft_set_ext_add(&priv->पंचांगpl, NFT_SET_EXT_TIMEOUT);
			nft_set_ext_add(&priv->पंचांगpl, NFT_SET_EXT_EXPIRATION);
		पूर्ण
	पूर्ण

	priv->समयout = समयout;

	err = nf_tables_bind_set(ctx, set, &priv->binding);
	अगर (err < 0)
		जाओ err_expr_मुक्त;

	अगर (set->size == 0)
		set->size = 0xffff;

	priv->set = set;
	वापस 0;

err_expr_मुक्त:
	क्रम (i = 0; i < priv->num_exprs; i++)
		nft_expr_destroy(ctx, priv->expr_array[i]);
	वापस err;
पूर्ण

अटल व्योम nft_dynset_deactivate(स्थिर काष्ठा nft_ctx *ctx,
				  स्थिर काष्ठा nft_expr *expr,
				  क्रमागत nft_trans_phase phase)
अणु
	काष्ठा nft_dynset *priv = nft_expr_priv(expr);

	nf_tables_deactivate_set(ctx, priv->set, &priv->binding, phase);
पूर्ण

अटल व्योम nft_dynset_activate(स्थिर काष्ठा nft_ctx *ctx,
				स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_dynset *priv = nft_expr_priv(expr);

	priv->set->use++;
पूर्ण

अटल व्योम nft_dynset_destroy(स्थिर काष्ठा nft_ctx *ctx,
			       स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_dynset *priv = nft_expr_priv(expr);
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_exprs; i++)
		nft_expr_destroy(ctx, priv->expr_array[i]);

	nf_tables_destroy_set(ctx, priv->set);
पूर्ण

अटल पूर्णांक nft_dynset_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_dynset *priv = nft_expr_priv(expr);
	u32 flags = priv->invert ? NFT_DYNSET_F_INV : 0;
	पूर्णांक i;

	अगर (nft_dump_रेजिस्टर(skb, NFTA_DYNSET_SREG_KEY, priv->sreg_key))
		जाओ nla_put_failure;
	अगर (priv->set->flags & NFT_SET_MAP &&
	    nft_dump_रेजिस्टर(skb, NFTA_DYNSET_SREG_DATA, priv->sreg_data))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_DYNSET_OP, htonl(priv->op)))
		जाओ nla_put_failure;
	अगर (nla_put_string(skb, NFTA_DYNSET_SET_NAME, priv->set->name))
		जाओ nla_put_failure;
	अगर (nla_put_be64(skb, NFTA_DYNSET_TIMEOUT,
			 nf_jअगरfies64_to_msecs(priv->समयout),
			 NFTA_DYNSET_PAD))
		जाओ nla_put_failure;
	अगर (priv->set->num_exprs == 0) अणु
		अगर (priv->num_exprs == 1) अणु
			अगर (nft_expr_dump(skb, NFTA_DYNSET_EXPR,
					  priv->expr_array[0]))
				जाओ nla_put_failure;
		पूर्ण अन्यथा अगर (priv->num_exprs > 1) अणु
			काष्ठा nlattr *nest;

			nest = nla_nest_start_noflag(skb, NFTA_DYNSET_EXPRESSIONS);
			अगर (!nest)
				जाओ nla_put_failure;

			क्रम (i = 0; i < priv->num_exprs; i++) अणु
				अगर (nft_expr_dump(skb, NFTA_LIST_ELEM,
						  priv->expr_array[i]))
					जाओ nla_put_failure;
			पूर्ण
			nla_nest_end(skb, nest);
		पूर्ण
	पूर्ण
	अगर (nla_put_be32(skb, NFTA_DYNSET_FLAGS, htonl(flags)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा nft_expr_ops nft_dynset_ops = अणु
	.type		= &nft_dynset_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_dynset)),
	.eval		= nft_dynset_eval,
	.init		= nft_dynset_init,
	.destroy	= nft_dynset_destroy,
	.activate	= nft_dynset_activate,
	.deactivate	= nft_dynset_deactivate,
	.dump		= nft_dynset_dump,
पूर्ण;

काष्ठा nft_expr_type nft_dynset_type __पढ़ो_mostly = अणु
	.name		= "dynset",
	.ops		= &nft_dynset_ops,
	.policy		= nft_dynset_policy,
	.maxattr	= NFTA_DYNSET_MAX,
	.owner		= THIS_MODULE,
पूर्ण;
