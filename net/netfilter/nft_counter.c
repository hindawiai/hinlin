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
#समावेश <linux/seqlock.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_offload.h>

काष्ठा nft_counter अणु
	s64		bytes;
	s64		packets;
पूर्ण;

काष्ठा nft_counter_percpu_priv अणु
	काष्ठा nft_counter __percpu *counter;
पूर्ण;

अटल DEFINE_PER_CPU(seqcount_t, nft_counter_seq);

अटल अंतरभूत व्योम nft_counter_करो_eval(काष्ठा nft_counter_percpu_priv *priv,
				       काष्ठा nft_regs *regs,
				       स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_counter *this_cpu;
	seqcount_t *myseq;

	local_bh_disable();
	this_cpu = this_cpu_ptr(priv->counter);
	myseq = this_cpu_ptr(&nft_counter_seq);

	ग_लिखो_seqcount_begin(myseq);

	this_cpu->bytes += pkt->skb->len;
	this_cpu->packets++;

	ग_लिखो_seqcount_end(myseq);
	local_bh_enable();
पूर्ण

अटल अंतरभूत व्योम nft_counter_obj_eval(काष्ठा nft_object *obj,
					काष्ठा nft_regs *regs,
					स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_counter_percpu_priv *priv = nft_obj_data(obj);

	nft_counter_करो_eval(priv, regs, pkt);
पूर्ण

अटल पूर्णांक nft_counter_करो_init(स्थिर काष्ठा nlattr * स्थिर tb[],
			       काष्ठा nft_counter_percpu_priv *priv)
अणु
	काष्ठा nft_counter __percpu *cpu_stats;
	काष्ठा nft_counter *this_cpu;

	cpu_stats = alloc_percpu(काष्ठा nft_counter);
	अगर (cpu_stats == शून्य)
		वापस -ENOMEM;

	preempt_disable();
	this_cpu = this_cpu_ptr(cpu_stats);
	अगर (tb[NFTA_COUNTER_PACKETS]) अणु
	        this_cpu->packets =
			be64_to_cpu(nla_get_be64(tb[NFTA_COUNTER_PACKETS]));
	पूर्ण
	अगर (tb[NFTA_COUNTER_BYTES]) अणु
		this_cpu->bytes =
			be64_to_cpu(nla_get_be64(tb[NFTA_COUNTER_BYTES]));
	पूर्ण
	preempt_enable();
	priv->counter = cpu_stats;
	वापस 0;
पूर्ण

अटल पूर्णांक nft_counter_obj_init(स्थिर काष्ठा nft_ctx *ctx,
				स्थिर काष्ठा nlattr * स्थिर tb[],
				काष्ठा nft_object *obj)
अणु
	काष्ठा nft_counter_percpu_priv *priv = nft_obj_data(obj);

	वापस nft_counter_करो_init(tb, priv);
पूर्ण

अटल व्योम nft_counter_करो_destroy(काष्ठा nft_counter_percpu_priv *priv)
अणु
	मुक्त_percpu(priv->counter);
पूर्ण

अटल व्योम nft_counter_obj_destroy(स्थिर काष्ठा nft_ctx *ctx,
				    काष्ठा nft_object *obj)
अणु
	काष्ठा nft_counter_percpu_priv *priv = nft_obj_data(obj);

	nft_counter_करो_destroy(priv);
पूर्ण

अटल व्योम nft_counter_reset(काष्ठा nft_counter_percpu_priv *priv,
			      काष्ठा nft_counter *total)
अणु
	काष्ठा nft_counter *this_cpu;

	local_bh_disable();
	this_cpu = this_cpu_ptr(priv->counter);
	this_cpu->packets -= total->packets;
	this_cpu->bytes -= total->bytes;
	local_bh_enable();
पूर्ण

अटल व्योम nft_counter_fetch(काष्ठा nft_counter_percpu_priv *priv,
			      काष्ठा nft_counter *total)
अणु
	काष्ठा nft_counter *this_cpu;
	स्थिर seqcount_t *myseq;
	u64 bytes, packets;
	अचिन्हित पूर्णांक seq;
	पूर्णांक cpu;

	स_रखो(total, 0, माप(*total));
	क्रम_each_possible_cpu(cpu) अणु
		myseq = per_cpu_ptr(&nft_counter_seq, cpu);
		this_cpu = per_cpu_ptr(priv->counter, cpu);
		करो अणु
			seq	= पढ़ो_seqcount_begin(myseq);
			bytes	= this_cpu->bytes;
			packets	= this_cpu->packets;
		पूर्ण जबतक (पढ़ो_seqcount_retry(myseq, seq));

		total->bytes	+= bytes;
		total->packets	+= packets;
	पूर्ण
पूर्ण

अटल पूर्णांक nft_counter_करो_dump(काष्ठा sk_buff *skb,
			       काष्ठा nft_counter_percpu_priv *priv,
			       bool reset)
अणु
	काष्ठा nft_counter total;

	nft_counter_fetch(priv, &total);

	अगर (nla_put_be64(skb, NFTA_COUNTER_BYTES, cpu_to_be64(total.bytes),
			 NFTA_COUNTER_PAD) ||
	    nla_put_be64(skb, NFTA_COUNTER_PACKETS, cpu_to_be64(total.packets),
			 NFTA_COUNTER_PAD))
		जाओ nla_put_failure;

	अगर (reset)
		nft_counter_reset(priv, &total);

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nft_counter_obj_dump(काष्ठा sk_buff *skb,
				काष्ठा nft_object *obj, bool reset)
अणु
	काष्ठा nft_counter_percpu_priv *priv = nft_obj_data(obj);

	वापस nft_counter_करो_dump(skb, priv, reset);
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_counter_policy[NFTA_COUNTER_MAX + 1] = अणु
	[NFTA_COUNTER_PACKETS]	= अणु .type = NLA_U64 पूर्ण,
	[NFTA_COUNTER_BYTES]	= अणु .type = NLA_U64 पूर्ण,
पूर्ण;

अटल काष्ठा nft_object_type nft_counter_obj_type;
अटल स्थिर काष्ठा nft_object_ops nft_counter_obj_ops = अणु
	.type		= &nft_counter_obj_type,
	.size		= माप(काष्ठा nft_counter_percpu_priv),
	.eval		= nft_counter_obj_eval,
	.init		= nft_counter_obj_init,
	.destroy	= nft_counter_obj_destroy,
	.dump		= nft_counter_obj_dump,
पूर्ण;

अटल काष्ठा nft_object_type nft_counter_obj_type __पढ़ो_mostly = अणु
	.type		= NFT_OBJECT_COUNTER,
	.ops		= &nft_counter_obj_ops,
	.maxattr	= NFTA_COUNTER_MAX,
	.policy		= nft_counter_policy,
	.owner		= THIS_MODULE,
पूर्ण;

अटल व्योम nft_counter_eval(स्थिर काष्ठा nft_expr *expr,
			     काष्ठा nft_regs *regs,
			     स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_counter_percpu_priv *priv = nft_expr_priv(expr);

	nft_counter_करो_eval(priv, regs, pkt);
पूर्ण

अटल पूर्णांक nft_counter_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_counter_percpu_priv *priv = nft_expr_priv(expr);

	वापस nft_counter_करो_dump(skb, priv, false);
पूर्ण

अटल पूर्णांक nft_counter_init(स्थिर काष्ठा nft_ctx *ctx,
			    स्थिर काष्ठा nft_expr *expr,
			    स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_counter_percpu_priv *priv = nft_expr_priv(expr);

	वापस nft_counter_करो_init(tb, priv);
पूर्ण

अटल व्योम nft_counter_destroy(स्थिर काष्ठा nft_ctx *ctx,
				स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_counter_percpu_priv *priv = nft_expr_priv(expr);

	nft_counter_करो_destroy(priv);
पूर्ण

अटल पूर्णांक nft_counter_clone(काष्ठा nft_expr *dst, स्थिर काष्ठा nft_expr *src)
अणु
	काष्ठा nft_counter_percpu_priv *priv = nft_expr_priv(src);
	काष्ठा nft_counter_percpu_priv *priv_clone = nft_expr_priv(dst);
	काष्ठा nft_counter __percpu *cpu_stats;
	काष्ठा nft_counter *this_cpu;
	काष्ठा nft_counter total;

	nft_counter_fetch(priv, &total);

	cpu_stats = alloc_percpu_gfp(काष्ठा nft_counter, GFP_ATOMIC);
	अगर (cpu_stats == शून्य)
		वापस -ENOMEM;

	preempt_disable();
	this_cpu = this_cpu_ptr(cpu_stats);
	this_cpu->packets = total.packets;
	this_cpu->bytes = total.bytes;
	preempt_enable();

	priv_clone->counter = cpu_stats;
	वापस 0;
पूर्ण

अटल पूर्णांक nft_counter_offload(काष्ठा nft_offload_ctx *ctx,
			       काष्ठा nft_flow_rule *flow,
			       स्थिर काष्ठा nft_expr *expr)
अणु
	/* No specअगरic offload action is needed, but report success. */
	वापस 0;
पूर्ण

अटल व्योम nft_counter_offload_stats(काष्ठा nft_expr *expr,
				      स्थिर काष्ठा flow_stats *stats)
अणु
	काष्ठा nft_counter_percpu_priv *priv = nft_expr_priv(expr);
	काष्ठा nft_counter *this_cpu;
	seqcount_t *myseq;

	preempt_disable();
	this_cpu = this_cpu_ptr(priv->counter);
	myseq = this_cpu_ptr(&nft_counter_seq);

	ग_लिखो_seqcount_begin(myseq);
	this_cpu->packets += stats->pkts;
	this_cpu->bytes += stats->bytes;
	ग_लिखो_seqcount_end(myseq);
	preempt_enable();
पूर्ण

अटल काष्ठा nft_expr_type nft_counter_type;
अटल स्थिर काष्ठा nft_expr_ops nft_counter_ops = अणु
	.type		= &nft_counter_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_counter_percpu_priv)),
	.eval		= nft_counter_eval,
	.init		= nft_counter_init,
	.destroy	= nft_counter_destroy,
	.destroy_clone	= nft_counter_destroy,
	.dump		= nft_counter_dump,
	.clone		= nft_counter_clone,
	.offload	= nft_counter_offload,
	.offload_stats	= nft_counter_offload_stats,
पूर्ण;

अटल काष्ठा nft_expr_type nft_counter_type __पढ़ो_mostly = अणु
	.name		= "counter",
	.ops		= &nft_counter_ops,
	.policy		= nft_counter_policy,
	.maxattr	= NFTA_COUNTER_MAX,
	.flags		= NFT_EXPR_STATEFUL,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_counter_module_init(व्योम)
अणु
	पूर्णांक cpu, err;

	क्रम_each_possible_cpu(cpu)
		seqcount_init(per_cpu_ptr(&nft_counter_seq, cpu));

	err = nft_रेजिस्टर_obj(&nft_counter_obj_type);
	अगर (err < 0)
		वापस err;

	err = nft_रेजिस्टर_expr(&nft_counter_type);
	अगर (err < 0)
		जाओ err1;

	वापस 0;
err1:
	nft_unरेजिस्टर_obj(&nft_counter_obj_type);
	वापस err;
पूर्ण

अटल व्योम __निकास nft_counter_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_counter_type);
	nft_unरेजिस्टर_obj(&nft_counter_obj_type);
पूर्ण

module_init(nft_counter_module_init);
module_निकास(nft_counter_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_ALIAS_NFT_EXPR("counter");
MODULE_ALIAS_NFT_OBJ(NFT_OBJECT_COUNTER);
MODULE_DESCRIPTION("nftables counter rule support");
