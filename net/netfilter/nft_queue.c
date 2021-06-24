<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 Eric Leblond <eric@regit.org>
 *
 * Development of this code partly funded by OISF
 * (http://www.खोलोinfosecfoundation.org/)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/jhash.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_queue.h>

अटल u32 jhash_initval __पढ़ो_mostly;

काष्ठा nft_queue अणु
	u8	sreg_qnum;
	u16	queuक्रमागत;
	u16	queues_total;
	u16	flags;
पूर्ण;

अटल व्योम nft_queue_eval(स्थिर काष्ठा nft_expr *expr,
			   काष्ठा nft_regs *regs,
			   स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_queue *priv = nft_expr_priv(expr);
	u32 queue = priv->queuक्रमागत;
	u32 ret;

	अगर (priv->queues_total > 1) अणु
		अगर (priv->flags & NFT_QUEUE_FLAG_CPU_FANOUT) अणु
			पूर्णांक cpu = raw_smp_processor_id();

			queue = priv->queuक्रमागत + cpu % priv->queues_total;
		पूर्ण अन्यथा अणु
			queue = nfqueue_hash(pkt->skb, queue,
					     priv->queues_total, nft_pf(pkt),
					     jhash_initval);
		पूर्ण
	पूर्ण

	ret = NF_QUEUE_NR(queue);
	अगर (priv->flags & NFT_QUEUE_FLAG_BYPASS)
		ret |= NF_VERDICT_FLAG_QUEUE_BYPASS;

	regs->verdict.code = ret;
पूर्ण

अटल व्योम nft_queue_sreg_eval(स्थिर काष्ठा nft_expr *expr,
				काष्ठा nft_regs *regs,
				स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_queue *priv = nft_expr_priv(expr);
	u32 queue, ret;

	queue = regs->data[priv->sreg_qnum];

	ret = NF_QUEUE_NR(queue);
	अगर (priv->flags & NFT_QUEUE_FLAG_BYPASS)
		ret |= NF_VERDICT_FLAG_QUEUE_BYPASS;

	regs->verdict.code = ret;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_queue_policy[NFTA_QUEUE_MAX + 1] = अणु
	[NFTA_QUEUE_NUM]	= अणु .type = NLA_U16 पूर्ण,
	[NFTA_QUEUE_TOTAL]	= अणु .type = NLA_U16 पूर्ण,
	[NFTA_QUEUE_FLAGS]	= अणु .type = NLA_U16 पूर्ण,
	[NFTA_QUEUE_SREG_QNUM]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_queue_init(स्थिर काष्ठा nft_ctx *ctx,
			  स्थिर काष्ठा nft_expr *expr,
			  स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_queue *priv = nft_expr_priv(expr);
	u32 maxid;

	priv->queuक्रमागत = ntohs(nla_get_be16(tb[NFTA_QUEUE_NUM]));

	अगर (tb[NFTA_QUEUE_TOTAL])
		priv->queues_total = ntohs(nla_get_be16(tb[NFTA_QUEUE_TOTAL]));
	अन्यथा
		priv->queues_total = 1;

	अगर (priv->queues_total == 0)
		वापस -EINVAL;

	maxid = priv->queues_total - 1 + priv->queuक्रमागत;
	अगर (maxid > U16_MAX)
		वापस -दुस्फल;

	अगर (tb[NFTA_QUEUE_FLAGS]) अणु
		priv->flags = ntohs(nla_get_be16(tb[NFTA_QUEUE_FLAGS]));
		अगर (priv->flags & ~NFT_QUEUE_FLAG_MASK)
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nft_queue_sreg_init(स्थिर काष्ठा nft_ctx *ctx,
			       स्थिर काष्ठा nft_expr *expr,
			       स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_queue *priv = nft_expr_priv(expr);
	पूर्णांक err;

	err = nft_parse_रेजिस्टर_load(tb[NFTA_QUEUE_SREG_QNUM],
				      &priv->sreg_qnum, माप(u32));
	अगर (err < 0)
		वापस err;

	अगर (tb[NFTA_QUEUE_FLAGS]) अणु
		priv->flags = ntohs(nla_get_be16(tb[NFTA_QUEUE_FLAGS]));
		अगर (priv->flags & ~NFT_QUEUE_FLAG_MASK)
			वापस -EINVAL;
		अगर (priv->flags & NFT_QUEUE_FLAG_CPU_FANOUT)
			वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nft_queue_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_queue *priv = nft_expr_priv(expr);

	अगर (nla_put_be16(skb, NFTA_QUEUE_NUM, htons(priv->queuक्रमागत)) ||
	    nla_put_be16(skb, NFTA_QUEUE_TOTAL, htons(priv->queues_total)) ||
	    nla_put_be16(skb, NFTA_QUEUE_FLAGS, htons(priv->flags)))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक
nft_queue_sreg_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_queue *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_QUEUE_SREG_QNUM, priv->sreg_qnum) ||
	    nla_put_be16(skb, NFTA_QUEUE_FLAGS, htons(priv->flags)))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल काष्ठा nft_expr_type nft_queue_type;
अटल स्थिर काष्ठा nft_expr_ops nft_queue_ops = अणु
	.type		= &nft_queue_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_queue)),
	.eval		= nft_queue_eval,
	.init		= nft_queue_init,
	.dump		= nft_queue_dump,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops nft_queue_sreg_ops = अणु
	.type		= &nft_queue_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_queue)),
	.eval		= nft_queue_sreg_eval,
	.init		= nft_queue_sreg_init,
	.dump		= nft_queue_sreg_dump,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops *
nft_queue_select_ops(स्थिर काष्ठा nft_ctx *ctx,
		     स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	अगर (tb[NFTA_QUEUE_NUM] && tb[NFTA_QUEUE_SREG_QNUM])
		वापस ERR_PTR(-EINVAL);

	init_hashअक्रमom(&jhash_initval);

	अगर (tb[NFTA_QUEUE_NUM])
		वापस &nft_queue_ops;

	अगर (tb[NFTA_QUEUE_SREG_QNUM])
		वापस &nft_queue_sreg_ops;

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा nft_expr_type nft_queue_type __पढ़ो_mostly = अणु
	.name		= "queue",
	.select_ops	= nft_queue_select_ops,
	.policy		= nft_queue_policy,
	.maxattr	= NFTA_QUEUE_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_queue_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_queue_type);
पूर्ण

अटल व्योम __निकास nft_queue_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_queue_type);
पूर्ण

module_init(nft_queue_module_init);
module_निकास(nft_queue_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Eric Leblond <eric@regit.org>");
MODULE_ALIAS_NFT_EXPR("queue");
MODULE_DESCRIPTION("Netfilter nftables queue module");
