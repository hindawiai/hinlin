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
#समावेश <linux/spinlock.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>

काष्ठा nft_limit अणु
	spinlock_t	lock;
	u64		last;
	u64		tokens;
	u64		tokens_max;
	u64		rate;
	u64		nsecs;
	u32		burst;
	bool		invert;
पूर्ण;

अटल अंतरभूत bool nft_limit_eval(काष्ठा nft_limit *limit, u64 cost)
अणु
	u64 now, tokens;
	s64 delta;

	spin_lock_bh(&limit->lock);
	now = kसमय_get_ns();
	tokens = limit->tokens + now - limit->last;
	अगर (tokens > limit->tokens_max)
		tokens = limit->tokens_max;

	limit->last = now;
	delta = tokens - cost;
	अगर (delta >= 0) अणु
		limit->tokens = delta;
		spin_unlock_bh(&limit->lock);
		वापस limit->invert;
	पूर्ण
	limit->tokens = tokens;
	spin_unlock_bh(&limit->lock);
	वापस !limit->invert;
पूर्ण

/* Use same शेष as in iptables. */
#घोषणा NFT_LIMIT_PKT_BURST_DEFAULT	5

अटल पूर्णांक nft_limit_init(काष्ठा nft_limit *limit,
			  स्थिर काष्ठा nlattr * स्थिर tb[], bool pkts)
अणु
	u64 unit, tokens;

	अगर (tb[NFTA_LIMIT_RATE] == शून्य ||
	    tb[NFTA_LIMIT_UNIT] == शून्य)
		वापस -EINVAL;

	limit->rate = be64_to_cpu(nla_get_be64(tb[NFTA_LIMIT_RATE]));
	unit = be64_to_cpu(nla_get_be64(tb[NFTA_LIMIT_UNIT]));
	limit->nsecs = unit * NSEC_PER_SEC;
	अगर (limit->rate == 0 || limit->nsecs < unit)
		वापस -EOVERFLOW;

	अगर (tb[NFTA_LIMIT_BURST])
		limit->burst = ntohl(nla_get_be32(tb[NFTA_LIMIT_BURST]));

	अगर (pkts && limit->burst == 0)
		limit->burst = NFT_LIMIT_PKT_BURST_DEFAULT;

	अगर (limit->rate + limit->burst < limit->rate)
		वापस -EOVERFLOW;

	अगर (pkts) अणु
		tokens = भाग64_u64(limit->nsecs, limit->rate) * limit->burst;
	पूर्ण अन्यथा अणु
		/* The token bucket size limits the number of tokens can be
		 * accumulated. tokens_max specअगरies the bucket size.
		 * tokens_max = unit * (rate + burst) / rate.
		 */
		tokens = भाग64_u64(limit->nsecs * (limit->rate + limit->burst),
				 limit->rate);
	पूर्ण

	limit->tokens = tokens;
	limit->tokens_max = limit->tokens;

	अगर (tb[NFTA_LIMIT_FLAGS]) अणु
		u32 flags = ntohl(nla_get_be32(tb[NFTA_LIMIT_FLAGS]));

		अगर (flags & NFT_LIMIT_F_INV)
			limit->invert = true;
	पूर्ण
	limit->last = kसमय_get_ns();
	spin_lock_init(&limit->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक nft_limit_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_limit *limit,
			  क्रमागत nft_limit_type type)
अणु
	u32 flags = limit->invert ? NFT_LIMIT_F_INV : 0;
	u64 secs = भाग_u64(limit->nsecs, NSEC_PER_SEC);

	अगर (nla_put_be64(skb, NFTA_LIMIT_RATE, cpu_to_be64(limit->rate),
			 NFTA_LIMIT_PAD) ||
	    nla_put_be64(skb, NFTA_LIMIT_UNIT, cpu_to_be64(secs),
			 NFTA_LIMIT_PAD) ||
	    nla_put_be32(skb, NFTA_LIMIT_BURST, htonl(limit->burst)) ||
	    nla_put_be32(skb, NFTA_LIMIT_TYPE, htonl(type)) ||
	    nla_put_be32(skb, NFTA_LIMIT_FLAGS, htonl(flags)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

काष्ठा nft_limit_pkts अणु
	काष्ठा nft_limit	limit;
	u64			cost;
पूर्ण;

अटल व्योम nft_limit_pkts_eval(स्थिर काष्ठा nft_expr *expr,
				काष्ठा nft_regs *regs,
				स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_limit_pkts *priv = nft_expr_priv(expr);

	अगर (nft_limit_eval(&priv->limit, priv->cost))
		regs->verdict.code = NFT_BREAK;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_limit_policy[NFTA_LIMIT_MAX + 1] = अणु
	[NFTA_LIMIT_RATE]	= अणु .type = NLA_U64 पूर्ण,
	[NFTA_LIMIT_UNIT]	= अणु .type = NLA_U64 पूर्ण,
	[NFTA_LIMIT_BURST]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_LIMIT_TYPE]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_LIMIT_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_limit_pkts_init(स्थिर काष्ठा nft_ctx *ctx,
			       स्थिर काष्ठा nft_expr *expr,
			       स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_limit_pkts *priv = nft_expr_priv(expr);
	पूर्णांक err;

	err = nft_limit_init(&priv->limit, tb, true);
	अगर (err < 0)
		वापस err;

	priv->cost = भाग64_u64(priv->limit.nsecs, priv->limit.rate);
	वापस 0;
पूर्ण

अटल पूर्णांक nft_limit_pkts_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_limit_pkts *priv = nft_expr_priv(expr);

	वापस nft_limit_dump(skb, &priv->limit, NFT_LIMIT_PKTS);
पूर्ण

अटल काष्ठा nft_expr_type nft_limit_type;
अटल स्थिर काष्ठा nft_expr_ops nft_limit_pkts_ops = अणु
	.type		= &nft_limit_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_limit_pkts)),
	.eval		= nft_limit_pkts_eval,
	.init		= nft_limit_pkts_init,
	.dump		= nft_limit_pkts_dump,
पूर्ण;

अटल व्योम nft_limit_bytes_eval(स्थिर काष्ठा nft_expr *expr,
				 काष्ठा nft_regs *regs,
				 स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_limit *priv = nft_expr_priv(expr);
	u64 cost = भाग64_u64(priv->nsecs * pkt->skb->len, priv->rate);

	अगर (nft_limit_eval(priv, cost))
		regs->verdict.code = NFT_BREAK;
पूर्ण

अटल पूर्णांक nft_limit_bytes_init(स्थिर काष्ठा nft_ctx *ctx,
				स्थिर काष्ठा nft_expr *expr,
				स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_limit *priv = nft_expr_priv(expr);

	वापस nft_limit_init(priv, tb, false);
पूर्ण

अटल पूर्णांक nft_limit_bytes_dump(काष्ठा sk_buff *skb,
				स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_limit *priv = nft_expr_priv(expr);

	वापस nft_limit_dump(skb, priv, NFT_LIMIT_PKT_BYTES);
पूर्ण

अटल स्थिर काष्ठा nft_expr_ops nft_limit_bytes_ops = अणु
	.type		= &nft_limit_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_limit)),
	.eval		= nft_limit_bytes_eval,
	.init		= nft_limit_bytes_init,
	.dump		= nft_limit_bytes_dump,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops *
nft_limit_select_ops(स्थिर काष्ठा nft_ctx *ctx,
		     स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	अगर (tb[NFTA_LIMIT_TYPE] == शून्य)
		वापस &nft_limit_pkts_ops;

	चयन (ntohl(nla_get_be32(tb[NFTA_LIMIT_TYPE]))) अणु
	हाल NFT_LIMIT_PKTS:
		वापस &nft_limit_pkts_ops;
	हाल NFT_LIMIT_PKT_BYTES:
		वापस &nft_limit_bytes_ops;
	पूर्ण
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल काष्ठा nft_expr_type nft_limit_type __पढ़ो_mostly = अणु
	.name		= "limit",
	.select_ops	= nft_limit_select_ops,
	.policy		= nft_limit_policy,
	.maxattr	= NFTA_LIMIT_MAX,
	.flags		= NFT_EXPR_STATEFUL,
	.owner		= THIS_MODULE,
पूर्ण;

अटल व्योम nft_limit_obj_pkts_eval(काष्ठा nft_object *obj,
				    काष्ठा nft_regs *regs,
				    स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_limit_pkts *priv = nft_obj_data(obj);

	अगर (nft_limit_eval(&priv->limit, priv->cost))
		regs->verdict.code = NFT_BREAK;
पूर्ण

अटल पूर्णांक nft_limit_obj_pkts_init(स्थिर काष्ठा nft_ctx *ctx,
				   स्थिर काष्ठा nlattr * स्थिर tb[],
				   काष्ठा nft_object *obj)
अणु
	काष्ठा nft_limit_pkts *priv = nft_obj_data(obj);
	पूर्णांक err;

	err = nft_limit_init(&priv->limit, tb, true);
	अगर (err < 0)
		वापस err;

	priv->cost = भाग64_u64(priv->limit.nsecs, priv->limit.rate);
	वापस 0;
पूर्ण

अटल पूर्णांक nft_limit_obj_pkts_dump(काष्ठा sk_buff *skb,
				   काष्ठा nft_object *obj,
				   bool reset)
अणु
	स्थिर काष्ठा nft_limit_pkts *priv = nft_obj_data(obj);

	वापस nft_limit_dump(skb, &priv->limit, NFT_LIMIT_PKTS);
पूर्ण

अटल काष्ठा nft_object_type nft_limit_obj_type;
अटल स्थिर काष्ठा nft_object_ops nft_limit_obj_pkts_ops = अणु
	.type		= &nft_limit_obj_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_limit_pkts)),
	.init		= nft_limit_obj_pkts_init,
	.eval		= nft_limit_obj_pkts_eval,
	.dump		= nft_limit_obj_pkts_dump,
पूर्ण;

अटल व्योम nft_limit_obj_bytes_eval(काष्ठा nft_object *obj,
				     काष्ठा nft_regs *regs,
				     स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_limit *priv = nft_obj_data(obj);
	u64 cost = भाग64_u64(priv->nsecs * pkt->skb->len, priv->rate);

	अगर (nft_limit_eval(priv, cost))
		regs->verdict.code = NFT_BREAK;
पूर्ण

अटल पूर्णांक nft_limit_obj_bytes_init(स्थिर काष्ठा nft_ctx *ctx,
				    स्थिर काष्ठा nlattr * स्थिर tb[],
				    काष्ठा nft_object *obj)
अणु
	काष्ठा nft_limit *priv = nft_obj_data(obj);

	वापस nft_limit_init(priv, tb, false);
पूर्ण

अटल पूर्णांक nft_limit_obj_bytes_dump(काष्ठा sk_buff *skb,
				    काष्ठा nft_object *obj,
				    bool reset)
अणु
	स्थिर काष्ठा nft_limit *priv = nft_obj_data(obj);

	वापस nft_limit_dump(skb, priv, NFT_LIMIT_PKT_BYTES);
पूर्ण

अटल काष्ठा nft_object_type nft_limit_obj_type;
अटल स्थिर काष्ठा nft_object_ops nft_limit_obj_bytes_ops = अणु
	.type		= &nft_limit_obj_type,
	.size		= माप(काष्ठा nft_limit),
	.init		= nft_limit_obj_bytes_init,
	.eval		= nft_limit_obj_bytes_eval,
	.dump		= nft_limit_obj_bytes_dump,
पूर्ण;

अटल स्थिर काष्ठा nft_object_ops *
nft_limit_obj_select_ops(स्थिर काष्ठा nft_ctx *ctx,
			 स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	अगर (!tb[NFTA_LIMIT_TYPE])
		वापस &nft_limit_obj_pkts_ops;

	चयन (ntohl(nla_get_be32(tb[NFTA_LIMIT_TYPE]))) अणु
	हाल NFT_LIMIT_PKTS:
		वापस &nft_limit_obj_pkts_ops;
	हाल NFT_LIMIT_PKT_BYTES:
		वापस &nft_limit_obj_bytes_ops;
	पूर्ण
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल काष्ठा nft_object_type nft_limit_obj_type __पढ़ो_mostly = अणु
	.select_ops	= nft_limit_obj_select_ops,
	.type		= NFT_OBJECT_LIMIT,
	.maxattr	= NFTA_LIMIT_MAX,
	.policy		= nft_limit_policy,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_limit_module_init(व्योम)
अणु
	पूर्णांक err;

	err = nft_रेजिस्टर_obj(&nft_limit_obj_type);
	अगर (err < 0)
		वापस err;

	err = nft_रेजिस्टर_expr(&nft_limit_type);
	अगर (err < 0)
		जाओ err1;

	वापस 0;
err1:
	nft_unरेजिस्टर_obj(&nft_limit_obj_type);
	वापस err;
पूर्ण

अटल व्योम __निकास nft_limit_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_limit_type);
	nft_unरेजिस्टर_obj(&nft_limit_obj_type);
पूर्ण

module_init(nft_limit_module_init);
module_निकास(nft_limit_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_ALIAS_NFT_EXPR("limit");
MODULE_ALIAS_NFT_OBJ(NFT_OBJECT_LIMIT);
MODULE_DESCRIPTION("nftables limit expression support");
