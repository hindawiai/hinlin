<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Pablo Neira Ayuso <pablo@netfilter.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/atomic.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>

काष्ठा nft_quota अणु
	atomic64_t	quota;
	अचिन्हित दीर्घ	flags;
	atomic64_t	consumed;
पूर्ण;

अटल अंतरभूत bool nft_overquota(काष्ठा nft_quota *priv,
				 स्थिर काष्ठा sk_buff *skb)
अणु
	वापस atomic64_add_वापस(skb->len, &priv->consumed) >=
	       atomic64_पढ़ो(&priv->quota);
पूर्ण

अटल अंतरभूत bool nft_quota_invert(काष्ठा nft_quota *priv)
अणु
	वापस priv->flags & NFT_QUOTA_F_INV;
पूर्ण

अटल अंतरभूत व्योम nft_quota_करो_eval(काष्ठा nft_quota *priv,
				     काष्ठा nft_regs *regs,
				     स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	अगर (nft_overquota(priv, pkt->skb) ^ nft_quota_invert(priv))
		regs->verdict.code = NFT_BREAK;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_quota_policy[NFTA_QUOTA_MAX + 1] = अणु
	[NFTA_QUOTA_BYTES]	= अणु .type = NLA_U64 पूर्ण,
	[NFTA_QUOTA_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_QUOTA_CONSUMED]	= अणु .type = NLA_U64 पूर्ण,
पूर्ण;

#घोषणा NFT_QUOTA_DEPLETED_BIT	1	/* From NFT_QUOTA_F_DEPLETED. */

अटल व्योम nft_quota_obj_eval(काष्ठा nft_object *obj,
			       काष्ठा nft_regs *regs,
			       स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_quota *priv = nft_obj_data(obj);
	bool overquota;

	overquota = nft_overquota(priv, pkt->skb);
	अगर (overquota ^ nft_quota_invert(priv))
		regs->verdict.code = NFT_BREAK;

	अगर (overquota &&
	    !test_and_set_bit(NFT_QUOTA_DEPLETED_BIT, &priv->flags))
		nft_obj_notअगरy(nft_net(pkt), obj->key.table, obj, 0, 0,
			       NFT_MSG_NEWOBJ, nft_pf(pkt), 0, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक nft_quota_करो_init(स्थिर काष्ठा nlattr * स्थिर tb[],
			     काष्ठा nft_quota *priv)
अणु
	अचिन्हित दीर्घ flags = 0;
	u64 quota, consumed = 0;

	अगर (!tb[NFTA_QUOTA_BYTES])
		वापस -EINVAL;

	quota = be64_to_cpu(nla_get_be64(tb[NFTA_QUOTA_BYTES]));
	अगर (quota > S64_MAX)
		वापस -EOVERFLOW;

	अगर (tb[NFTA_QUOTA_CONSUMED]) अणु
		consumed = be64_to_cpu(nla_get_be64(tb[NFTA_QUOTA_CONSUMED]));
		अगर (consumed > quota)
			वापस -EINVAL;
	पूर्ण

	अगर (tb[NFTA_QUOTA_FLAGS]) अणु
		flags = ntohl(nla_get_be32(tb[NFTA_QUOTA_FLAGS]));
		अगर (flags & ~NFT_QUOTA_F_INV)
			वापस -EINVAL;
		अगर (flags & NFT_QUOTA_F_DEPLETED)
			वापस -EOPNOTSUPP;
	पूर्ण

	atomic64_set(&priv->quota, quota);
	priv->flags = flags;
	atomic64_set(&priv->consumed, consumed);

	वापस 0;
पूर्ण

अटल पूर्णांक nft_quota_obj_init(स्थिर काष्ठा nft_ctx *ctx,
			      स्थिर काष्ठा nlattr * स्थिर tb[],
			      काष्ठा nft_object *obj)
अणु
	काष्ठा nft_quota *priv = nft_obj_data(obj);

	वापस nft_quota_करो_init(tb, priv);
पूर्ण

अटल व्योम nft_quota_obj_update(काष्ठा nft_object *obj,
				 काष्ठा nft_object *newobj)
अणु
	काष्ठा nft_quota *newpriv = nft_obj_data(newobj);
	काष्ठा nft_quota *priv = nft_obj_data(obj);
	u64 newquota;

	newquota = atomic64_पढ़ो(&newpriv->quota);
	atomic64_set(&priv->quota, newquota);
	priv->flags = newpriv->flags;
पूर्ण

अटल पूर्णांक nft_quota_करो_dump(काष्ठा sk_buff *skb, काष्ठा nft_quota *priv,
			     bool reset)
अणु
	u64 consumed, consumed_cap, quota;
	u32 flags = priv->flags;

	/* Since we inconditionally increment consumed quota क्रम each packet
	 * that we see, करोn't go over the quota boundary in what we send to
	 * userspace.
	 */
	consumed = atomic64_पढ़ो(&priv->consumed);
	quota = atomic64_पढ़ो(&priv->quota);
	अगर (consumed >= quota) अणु
		consumed_cap = quota;
		flags |= NFT_QUOTA_F_DEPLETED;
	पूर्ण अन्यथा अणु
		consumed_cap = consumed;
	पूर्ण

	अगर (nla_put_be64(skb, NFTA_QUOTA_BYTES, cpu_to_be64(quota),
			 NFTA_QUOTA_PAD) ||
	    nla_put_be64(skb, NFTA_QUOTA_CONSUMED, cpu_to_be64(consumed_cap),
			 NFTA_QUOTA_PAD) ||
	    nla_put_be32(skb, NFTA_QUOTA_FLAGS, htonl(flags)))
		जाओ nla_put_failure;

	अगर (reset) अणु
		atomic64_sub(consumed, &priv->consumed);
		clear_bit(NFT_QUOTA_DEPLETED_BIT, &priv->flags);
	पूर्ण
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nft_quota_obj_dump(काष्ठा sk_buff *skb, काष्ठा nft_object *obj,
			      bool reset)
अणु
	काष्ठा nft_quota *priv = nft_obj_data(obj);

	वापस nft_quota_करो_dump(skb, priv, reset);
पूर्ण

अटल काष्ठा nft_object_type nft_quota_obj_type;
अटल स्थिर काष्ठा nft_object_ops nft_quota_obj_ops = अणु
	.type		= &nft_quota_obj_type,
	.size		= माप(काष्ठा nft_quota),
	.init		= nft_quota_obj_init,
	.eval		= nft_quota_obj_eval,
	.dump		= nft_quota_obj_dump,
	.update		= nft_quota_obj_update,
पूर्ण;

अटल काष्ठा nft_object_type nft_quota_obj_type __पढ़ो_mostly = अणु
	.type		= NFT_OBJECT_QUOTA,
	.ops		= &nft_quota_obj_ops,
	.maxattr	= NFTA_QUOTA_MAX,
	.policy		= nft_quota_policy,
	.owner		= THIS_MODULE,
पूर्ण;

अटल व्योम nft_quota_eval(स्थिर काष्ठा nft_expr *expr,
			   काष्ठा nft_regs *regs,
			   स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_quota *priv = nft_expr_priv(expr);

	nft_quota_करो_eval(priv, regs, pkt);
पूर्ण

अटल पूर्णांक nft_quota_init(स्थिर काष्ठा nft_ctx *ctx,
			  स्थिर काष्ठा nft_expr *expr,
			  स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_quota *priv = nft_expr_priv(expr);

	वापस nft_quota_करो_init(tb, priv);
पूर्ण

अटल पूर्णांक nft_quota_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_quota *priv = nft_expr_priv(expr);

	वापस nft_quota_करो_dump(skb, priv, false);
पूर्ण

अटल काष्ठा nft_expr_type nft_quota_type;
अटल स्थिर काष्ठा nft_expr_ops nft_quota_ops = अणु
	.type		= &nft_quota_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_quota)),
	.eval		= nft_quota_eval,
	.init		= nft_quota_init,
	.dump		= nft_quota_dump,
पूर्ण;

अटल काष्ठा nft_expr_type nft_quota_type __पढ़ो_mostly = अणु
	.name		= "quota",
	.ops		= &nft_quota_ops,
	.policy		= nft_quota_policy,
	.maxattr	= NFTA_QUOTA_MAX,
	.flags		= NFT_EXPR_STATEFUL,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_quota_module_init(व्योम)
अणु
	पूर्णांक err;

	err = nft_रेजिस्टर_obj(&nft_quota_obj_type);
	अगर (err < 0)
		वापस err;

	err = nft_रेजिस्टर_expr(&nft_quota_type);
	अगर (err < 0)
		जाओ err1;

	वापस 0;
err1:
	nft_unरेजिस्टर_obj(&nft_quota_obj_type);
	वापस err;
पूर्ण

अटल व्योम __निकास nft_quota_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_quota_type);
	nft_unरेजिस्टर_obj(&nft_quota_obj_type);
पूर्ण

module_init(nft_quota_module_init);
module_निकास(nft_quota_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_ALIAS_NFT_EXPR("quota");
MODULE_ALIAS_NFT_OBJ(NFT_OBJECT_QUOTA);
MODULE_DESCRIPTION("Netfilter nftables quota module");
