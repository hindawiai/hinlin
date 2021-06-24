<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2016 Pablo Neira Ayuso <pablo@netfilter.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>

#घोषणा nft_objref_priv(expr)	*((काष्ठा nft_object **)nft_expr_priv(expr))

अटल व्योम nft_objref_eval(स्थिर काष्ठा nft_expr *expr,
			    काष्ठा nft_regs *regs,
			    स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_object *obj = nft_objref_priv(expr);

	obj->ops->eval(obj, regs, pkt);
पूर्ण

अटल पूर्णांक nft_objref_init(स्थिर काष्ठा nft_ctx *ctx,
			   स्थिर काष्ठा nft_expr *expr,
			   स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_object *obj = nft_objref_priv(expr);
	u8 genmask = nft_genmask_next(ctx->net);
	u32 objtype;

	अगर (!tb[NFTA_OBJREF_IMM_NAME] ||
	    !tb[NFTA_OBJREF_IMM_TYPE])
		वापस -EINVAL;

	objtype = ntohl(nla_get_be32(tb[NFTA_OBJREF_IMM_TYPE]));
	obj = nft_obj_lookup(ctx->net, ctx->table,
			     tb[NFTA_OBJREF_IMM_NAME], objtype,
			     genmask);
	अगर (IS_ERR(obj))
		वापस -ENOENT;

	nft_objref_priv(expr) = obj;
	obj->use++;

	वापस 0;
पूर्ण

अटल पूर्णांक nft_objref_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_object *obj = nft_objref_priv(expr);

	अगर (nla_put_string(skb, NFTA_OBJREF_IMM_NAME, obj->key.name) ||
	    nla_put_be32(skb, NFTA_OBJREF_IMM_TYPE,
			 htonl(obj->ops->type->type)))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल व्योम nft_objref_deactivate(स्थिर काष्ठा nft_ctx *ctx,
				  स्थिर काष्ठा nft_expr *expr,
				  क्रमागत nft_trans_phase phase)
अणु
	काष्ठा nft_object *obj = nft_objref_priv(expr);

	अगर (phase == NFT_TRANS_COMMIT)
		वापस;

	obj->use--;
पूर्ण

अटल व्योम nft_objref_activate(स्थिर काष्ठा nft_ctx *ctx,
				स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_object *obj = nft_objref_priv(expr);

	obj->use++;
पूर्ण

अटल काष्ठा nft_expr_type nft_objref_type;
अटल स्थिर काष्ठा nft_expr_ops nft_objref_ops = अणु
	.type		= &nft_objref_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_object *)),
	.eval		= nft_objref_eval,
	.init		= nft_objref_init,
	.activate	= nft_objref_activate,
	.deactivate	= nft_objref_deactivate,
	.dump		= nft_objref_dump,
पूर्ण;

काष्ठा nft_objref_map अणु
	काष्ठा nft_set		*set;
	u8			sreg;
	काष्ठा nft_set_binding	binding;
पूर्ण;

अटल व्योम nft_objref_map_eval(स्थिर काष्ठा nft_expr *expr,
				काष्ठा nft_regs *regs,
				स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_objref_map *priv = nft_expr_priv(expr);
	स्थिर काष्ठा nft_set *set = priv->set;
	काष्ठा net *net = nft_net(pkt);
	स्थिर काष्ठा nft_set_ext *ext;
	काष्ठा nft_object *obj;
	bool found;

	found = set->ops->lookup(net, set, &regs->data[priv->sreg], &ext);
	अगर (!found) अणु
		ext = nft_set_catchall_lookup(net, set);
		अगर (!ext) अणु
			regs->verdict.code = NFT_BREAK;
			वापस;
		पूर्ण
	पूर्ण
	obj = *nft_set_ext_obj(ext);
	obj->ops->eval(obj, regs, pkt);
पूर्ण

अटल पूर्णांक nft_objref_map_init(स्थिर काष्ठा nft_ctx *ctx,
			       स्थिर काष्ठा nft_expr *expr,
			       स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_objref_map *priv = nft_expr_priv(expr);
	u8 genmask = nft_genmask_next(ctx->net);
	काष्ठा nft_set *set;
	पूर्णांक err;

	set = nft_set_lookup_global(ctx->net, ctx->table,
				    tb[NFTA_OBJREF_SET_NAME],
				    tb[NFTA_OBJREF_SET_ID], genmask);
	अगर (IS_ERR(set))
		वापस PTR_ERR(set);

	अगर (!(set->flags & NFT_SET_OBJECT))
		वापस -EINVAL;

	err = nft_parse_रेजिस्टर_load(tb[NFTA_OBJREF_SET_SREG], &priv->sreg,
				      set->klen);
	अगर (err < 0)
		वापस err;

	priv->binding.flags = set->flags & NFT_SET_OBJECT;

	err = nf_tables_bind_set(ctx, set, &priv->binding);
	अगर (err < 0)
		वापस err;

	priv->set = set;
	वापस 0;
पूर्ण

अटल पूर्णांक nft_objref_map_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_objref_map *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_OBJREF_SET_SREG, priv->sreg) ||
	    nla_put_string(skb, NFTA_OBJREF_SET_NAME, priv->set->name))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल व्योम nft_objref_map_deactivate(स्थिर काष्ठा nft_ctx *ctx,
				      स्थिर काष्ठा nft_expr *expr,
				      क्रमागत nft_trans_phase phase)
अणु
	काष्ठा nft_objref_map *priv = nft_expr_priv(expr);

	nf_tables_deactivate_set(ctx, priv->set, &priv->binding, phase);
पूर्ण

अटल व्योम nft_objref_map_activate(स्थिर काष्ठा nft_ctx *ctx,
				    स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_objref_map *priv = nft_expr_priv(expr);

	priv->set->use++;
पूर्ण

अटल व्योम nft_objref_map_destroy(स्थिर काष्ठा nft_ctx *ctx,
				   स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_objref_map *priv = nft_expr_priv(expr);

	nf_tables_destroy_set(ctx, priv->set);
पूर्ण

अटल काष्ठा nft_expr_type nft_objref_type;
अटल स्थिर काष्ठा nft_expr_ops nft_objref_map_ops = अणु
	.type		= &nft_objref_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_objref_map)),
	.eval		= nft_objref_map_eval,
	.init		= nft_objref_map_init,
	.activate	= nft_objref_map_activate,
	.deactivate	= nft_objref_map_deactivate,
	.destroy	= nft_objref_map_destroy,
	.dump		= nft_objref_map_dump,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops *
nft_objref_select_ops(स्थिर काष्ठा nft_ctx *ctx,
                      स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	अगर (tb[NFTA_OBJREF_SET_SREG] &&
	    (tb[NFTA_OBJREF_SET_NAME] ||
	     tb[NFTA_OBJREF_SET_ID]))
		वापस &nft_objref_map_ops;
	अन्यथा अगर (tb[NFTA_OBJREF_IMM_NAME] &&
		 tb[NFTA_OBJREF_IMM_TYPE])
		वापस &nft_objref_ops;

	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_objref_policy[NFTA_OBJREF_MAX + 1] = अणु
	[NFTA_OBJREF_IMM_NAME]	= अणु .type = NLA_STRING,
				    .len = NFT_OBJ_MAXNAMELEN - 1 पूर्ण,
	[NFTA_OBJREF_IMM_TYPE]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_OBJREF_SET_SREG]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_OBJREF_SET_NAME]	= अणु .type = NLA_STRING,
				    .len = NFT_SET_MAXNAMELEN - 1 पूर्ण,
	[NFTA_OBJREF_SET_ID]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल काष्ठा nft_expr_type nft_objref_type __पढ़ो_mostly = अणु
	.name		= "objref",
	.select_ops	= nft_objref_select_ops,
	.policy		= nft_objref_policy,
	.maxattr	= NFTA_OBJREF_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_objref_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_objref_type);
पूर्ण

अटल व्योम __निकास nft_objref_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_objref_type);
पूर्ण

module_init(nft_objref_module_init);
module_निकास(nft_objref_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_ALIAS_NFT_EXPR("objref");
MODULE_DESCRIPTION("nftables stateful object reference module");
