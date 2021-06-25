<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_count.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_tuple.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>

काष्ठा nft_connlimit अणु
	काष्ठा nf_conncount_list	list;
	u32				limit;
	bool				invert;
पूर्ण;

अटल अंतरभूत व्योम nft_connlimit_करो_eval(काष्ठा nft_connlimit *priv,
					 काष्ठा nft_regs *regs,
					 स्थिर काष्ठा nft_pktinfo *pkt,
					 स्थिर काष्ठा nft_set_ext *ext)
अणु
	स्थिर काष्ठा nf_conntrack_zone *zone = &nf_ct_zone_dflt;
	स्थिर काष्ठा nf_conntrack_tuple *tuple_ptr;
	काष्ठा nf_conntrack_tuple tuple;
	क्रमागत ip_conntrack_info ctinfo;
	स्थिर काष्ठा nf_conn *ct;
	अचिन्हित पूर्णांक count;

	tuple_ptr = &tuple;

	ct = nf_ct_get(pkt->skb, &ctinfo);
	अगर (ct != शून्य) अणु
		tuple_ptr = &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple;
		zone = nf_ct_zone(ct);
	पूर्ण अन्यथा अगर (!nf_ct_get_tuplepr(pkt->skb, skb_network_offset(pkt->skb),
				      nft_pf(pkt), nft_net(pkt), &tuple)) अणु
		regs->verdict.code = NF_DROP;
		वापस;
	पूर्ण

	अगर (nf_conncount_add(nft_net(pkt), &priv->list, tuple_ptr, zone)) अणु
		regs->verdict.code = NF_DROP;
		वापस;
	पूर्ण

	count = priv->list.count;

	अगर ((count > priv->limit) ^ priv->invert) अणु
		regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक nft_connlimit_करो_init(स्थिर काष्ठा nft_ctx *ctx,
				 स्थिर काष्ठा nlattr * स्थिर tb[],
				 काष्ठा nft_connlimit *priv)
अणु
	bool invert = false;
	u32 flags, limit;

	अगर (!tb[NFTA_CONNLIMIT_COUNT])
		वापस -EINVAL;

	limit = ntohl(nla_get_be32(tb[NFTA_CONNLIMIT_COUNT]));

	अगर (tb[NFTA_CONNLIMIT_FLAGS]) अणु
		flags = ntohl(nla_get_be32(tb[NFTA_CONNLIMIT_FLAGS]));
		अगर (flags & ~NFT_CONNLIMIT_F_INV)
			वापस -EOPNOTSUPP;
		अगर (flags & NFT_CONNLIMIT_F_INV)
			invert = true;
	पूर्ण

	nf_conncount_list_init(&priv->list);
	priv->limit	= limit;
	priv->invert	= invert;

	वापस nf_ct_netns_get(ctx->net, ctx->family);
पूर्ण

अटल व्योम nft_connlimit_करो_destroy(स्थिर काष्ठा nft_ctx *ctx,
				     काष्ठा nft_connlimit *priv)
अणु
	nf_ct_netns_put(ctx->net, ctx->family);
	nf_conncount_cache_मुक्त(&priv->list);
पूर्ण

अटल पूर्णांक nft_connlimit_करो_dump(काष्ठा sk_buff *skb,
				 काष्ठा nft_connlimit *priv)
अणु
	अगर (nla_put_be32(skb, NFTA_CONNLIMIT_COUNT, htonl(priv->limit)))
		जाओ nla_put_failure;
	अगर (priv->invert &&
	    nla_put_be32(skb, NFTA_CONNLIMIT_FLAGS, htonl(NFT_CONNLIMIT_F_INV)))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल अंतरभूत व्योम nft_connlimit_obj_eval(काष्ठा nft_object *obj,
					काष्ठा nft_regs *regs,
					स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_connlimit *priv = nft_obj_data(obj);

	nft_connlimit_करो_eval(priv, regs, pkt, शून्य);
पूर्ण

अटल पूर्णांक nft_connlimit_obj_init(स्थिर काष्ठा nft_ctx *ctx,
				स्थिर काष्ठा nlattr * स्थिर tb[],
				काष्ठा nft_object *obj)
अणु
	काष्ठा nft_connlimit *priv = nft_obj_data(obj);

	वापस nft_connlimit_करो_init(ctx, tb, priv);
पूर्ण

अटल व्योम nft_connlimit_obj_destroy(स्थिर काष्ठा nft_ctx *ctx,
				      काष्ठा nft_object *obj)
अणु
	काष्ठा nft_connlimit *priv = nft_obj_data(obj);

	nft_connlimit_करो_destroy(ctx, priv);
पूर्ण

अटल पूर्णांक nft_connlimit_obj_dump(काष्ठा sk_buff *skb,
				  काष्ठा nft_object *obj, bool reset)
अणु
	काष्ठा nft_connlimit *priv = nft_obj_data(obj);

	वापस nft_connlimit_करो_dump(skb, priv);
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_connlimit_policy[NFTA_CONNLIMIT_MAX + 1] = अणु
	[NFTA_CONNLIMIT_COUNT]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_CONNLIMIT_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल काष्ठा nft_object_type nft_connlimit_obj_type;
अटल स्थिर काष्ठा nft_object_ops nft_connlimit_obj_ops = अणु
	.type		= &nft_connlimit_obj_type,
	.size		= माप(काष्ठा nft_connlimit),
	.eval		= nft_connlimit_obj_eval,
	.init		= nft_connlimit_obj_init,
	.destroy	= nft_connlimit_obj_destroy,
	.dump		= nft_connlimit_obj_dump,
पूर्ण;

अटल काष्ठा nft_object_type nft_connlimit_obj_type __पढ़ो_mostly = अणु
	.type		= NFT_OBJECT_CONNLIMIT,
	.ops		= &nft_connlimit_obj_ops,
	.maxattr	= NFTA_CONNLIMIT_MAX,
	.policy		= nft_connlimit_policy,
	.owner		= THIS_MODULE,
पूर्ण;

अटल व्योम nft_connlimit_eval(स्थिर काष्ठा nft_expr *expr,
			       काष्ठा nft_regs *regs,
			       स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_connlimit *priv = nft_expr_priv(expr);

	nft_connlimit_करो_eval(priv, regs, pkt, शून्य);
पूर्ण

अटल पूर्णांक nft_connlimit_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_connlimit *priv = nft_expr_priv(expr);

	वापस nft_connlimit_करो_dump(skb, priv);
पूर्ण

अटल पूर्णांक nft_connlimit_init(स्थिर काष्ठा nft_ctx *ctx,
			      स्थिर काष्ठा nft_expr *expr,
			      स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_connlimit *priv = nft_expr_priv(expr);

	वापस nft_connlimit_करो_init(ctx, tb, priv);
पूर्ण

अटल व्योम nft_connlimit_destroy(स्थिर काष्ठा nft_ctx *ctx,
				स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_connlimit *priv = nft_expr_priv(expr);

	nft_connlimit_करो_destroy(ctx, priv);
पूर्ण

अटल पूर्णांक nft_connlimit_clone(काष्ठा nft_expr *dst, स्थिर काष्ठा nft_expr *src)
अणु
	काष्ठा nft_connlimit *priv_dst = nft_expr_priv(dst);
	काष्ठा nft_connlimit *priv_src = nft_expr_priv(src);

	nf_conncount_list_init(&priv_dst->list);
	priv_dst->limit	 = priv_src->limit;
	priv_dst->invert = priv_src->invert;

	वापस 0;
पूर्ण

अटल व्योम nft_connlimit_destroy_clone(स्थिर काष्ठा nft_ctx *ctx,
					स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_connlimit *priv = nft_expr_priv(expr);

	nf_conncount_cache_मुक्त(&priv->list);
पूर्ण

अटल bool nft_connlimit_gc(काष्ठा net *net, स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_connlimit *priv = nft_expr_priv(expr);
	bool ret;

	local_bh_disable();
	ret = nf_conncount_gc_list(net, &priv->list);
	local_bh_enable();

	वापस ret;
पूर्ण

अटल काष्ठा nft_expr_type nft_connlimit_type;
अटल स्थिर काष्ठा nft_expr_ops nft_connlimit_ops = अणु
	.type		= &nft_connlimit_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_connlimit)),
	.eval		= nft_connlimit_eval,
	.init		= nft_connlimit_init,
	.destroy	= nft_connlimit_destroy,
	.clone		= nft_connlimit_clone,
	.destroy_clone	= nft_connlimit_destroy_clone,
	.dump		= nft_connlimit_dump,
	.gc		= nft_connlimit_gc,
पूर्ण;

अटल काष्ठा nft_expr_type nft_connlimit_type __पढ़ो_mostly = अणु
	.name		= "connlimit",
	.ops		= &nft_connlimit_ops,
	.policy		= nft_connlimit_policy,
	.maxattr	= NFTA_CONNLIMIT_MAX,
	.flags		= NFT_EXPR_STATEFUL | NFT_EXPR_GC,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_connlimit_module_init(व्योम)
अणु
	पूर्णांक err;

	err = nft_रेजिस्टर_obj(&nft_connlimit_obj_type);
	अगर (err < 0)
		वापस err;

	err = nft_रेजिस्टर_expr(&nft_connlimit_type);
	अगर (err < 0)
		जाओ err1;

	वापस 0;
err1:
	nft_unरेजिस्टर_obj(&nft_connlimit_obj_type);
	वापस err;
पूर्ण

अटल व्योम __निकास nft_connlimit_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_connlimit_type);
	nft_unरेजिस्टर_obj(&nft_connlimit_obj_type);
पूर्ण

module_init(nft_connlimit_module_init);
module_निकास(nft_connlimit_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Neira Ayuso");
MODULE_ALIAS_NFT_EXPR("connlimit");
MODULE_ALIAS_NFT_OBJ(NFT_OBJECT_CONNLIMIT);
MODULE_DESCRIPTION("nftables connlimit rule support");
