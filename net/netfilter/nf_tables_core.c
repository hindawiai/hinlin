<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008 Patrick McHardy <kaber@trash.net>
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/rculist.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_log.h>
#समावेश <net/netfilter/nft_meta.h>

अटल noअंतरभूत व्योम __nft_trace_packet(काष्ठा nft_traceinfo *info,
					स्थिर काष्ठा nft_chain *chain,
					क्रमागत nft_trace_types type)
अणु
	स्थिर काष्ठा nft_pktinfo *pkt = info->pkt;

	अगर (!info->trace || !pkt->skb->nf_trace)
		वापस;

	info->chain = chain;
	info->type = type;

	nft_trace_notअगरy(info);
पूर्ण

अटल अंतरभूत व्योम nft_trace_packet(काष्ठा nft_traceinfo *info,
				    स्थिर काष्ठा nft_chain *chain,
				    स्थिर काष्ठा nft_rule *rule,
				    क्रमागत nft_trace_types type)
अणु
	अगर (अटल_branch_unlikely(&nft_trace_enabled)) अणु
		info->rule = rule;
		__nft_trace_packet(info, chain, type);
	पूर्ण
पूर्ण

अटल व्योम nft_bitwise_fast_eval(स्थिर काष्ठा nft_expr *expr,
				  काष्ठा nft_regs *regs)
अणु
	स्थिर काष्ठा nft_bitwise_fast_expr *priv = nft_expr_priv(expr);
	u32 *src = &regs->data[priv->sreg];
	u32 *dst = &regs->data[priv->dreg];

	*dst = (*src & priv->mask) ^ priv->xor;
पूर्ण

अटल व्योम nft_cmp_fast_eval(स्थिर काष्ठा nft_expr *expr,
			      काष्ठा nft_regs *regs)
अणु
	स्थिर काष्ठा nft_cmp_fast_expr *priv = nft_expr_priv(expr);

	अगर (((regs->data[priv->sreg] & priv->mask) == priv->data) ^ priv->inv)
		वापस;
	regs->verdict.code = NFT_BREAK;
पूर्ण

अटल bool nft_payload_fast_eval(स्थिर काष्ठा nft_expr *expr,
				  काष्ठा nft_regs *regs,
				  स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_payload *priv = nft_expr_priv(expr);
	स्थिर काष्ठा sk_buff *skb = pkt->skb;
	u32 *dest = &regs->data[priv->dreg];
	अचिन्हित अक्षर *ptr;

	अगर (priv->base == NFT_PAYLOAD_NETWORK_HEADER)
		ptr = skb_network_header(skb);
	अन्यथा अणु
		अगर (!pkt->tprot_set)
			वापस false;
		ptr = skb_network_header(skb) + pkt->xt.thoff;
	पूर्ण

	ptr += priv->offset;

	अगर (unlikely(ptr + priv->len > skb_tail_poपूर्णांकer(skb)))
		वापस false;

	*dest = 0;
	अगर (priv->len == 2)
		*(u16 *)dest = *(u16 *)ptr;
	अन्यथा अगर (priv->len == 4)
		*(u32 *)dest = *(u32 *)ptr;
	अन्यथा
		*(u8 *)dest = *(u8 *)ptr;
	वापस true;
पूर्ण

DEFINE_STATIC_KEY_FALSE(nft_counters_enabled);

अटल noअंतरभूत व्योम nft_update_chain_stats(स्थिर काष्ठा nft_chain *chain,
					    स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_base_chain *base_chain;
	काष्ठा nft_stats __percpu *pstats;
	काष्ठा nft_stats *stats;

	base_chain = nft_base_chain(chain);

	rcu_पढ़ो_lock();
	pstats = READ_ONCE(base_chain->stats);
	अगर (pstats) अणु
		local_bh_disable();
		stats = this_cpu_ptr(pstats);
		u64_stats_update_begin(&stats->syncp);
		stats->pkts++;
		stats->bytes += pkt->skb->len;
		u64_stats_update_end(&stats->syncp);
		local_bh_enable();
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

काष्ठा nft_jumpstack अणु
	स्थिर काष्ठा nft_chain	*chain;
	काष्ठा nft_rule	*स्थिर *rules;
पूर्ण;

अटल व्योम expr_call_ops_eval(स्थिर काष्ठा nft_expr *expr,
			       काष्ठा nft_regs *regs,
			       काष्ठा nft_pktinfo *pkt)
अणु
#अगर_घोषित CONFIG_RETPOLINE
	अचिन्हित दीर्घ e = (अचिन्हित दीर्घ)expr->ops->eval;
#घोषणा X(e, fun) \
	करो अणु अगर ((e) == (अचिन्हित दीर्घ)(fun)) \
		वापस fun(expr, regs, pkt); पूर्ण जबतक (0)

	X(e, nft_payload_eval);
	X(e, nft_cmp_eval);
	X(e, nft_meta_get_eval);
	X(e, nft_lookup_eval);
	X(e, nft_range_eval);
	X(e, nft_immediate_eval);
	X(e, nft_byteorder_eval);
	X(e, nft_dynset_eval);
	X(e, nft_rt_get_eval);
	X(e, nft_bitwise_eval);
#अघोषित  X
#पूर्ण_अगर /* CONFIG_RETPOLINE */
	expr->ops->eval(expr, regs, pkt);
पूर्ण

अचिन्हित पूर्णांक
nft_करो_chain(काष्ठा nft_pktinfo *pkt, व्योम *priv)
अणु
	स्थिर काष्ठा nft_chain *chain = priv, *basechain = chain;
	स्थिर काष्ठा net *net = nft_net(pkt);
	काष्ठा nft_rule *स्थिर *rules;
	स्थिर काष्ठा nft_rule *rule;
	स्थिर काष्ठा nft_expr *expr, *last;
	काष्ठा nft_regs regs;
	अचिन्हित पूर्णांक stackptr = 0;
	काष्ठा nft_jumpstack jumpstack[NFT_JUMP_STACK_SIZE];
	bool genbit = READ_ONCE(net->nft.gencursor);
	काष्ठा nft_traceinfo info;

	info.trace = false;
	अगर (अटल_branch_unlikely(&nft_trace_enabled))
		nft_trace_init(&info, pkt, &regs.verdict, basechain);
करो_chain:
	अगर (genbit)
		rules = rcu_dereference(chain->rules_gen_1);
	अन्यथा
		rules = rcu_dereference(chain->rules_gen_0);

next_rule:
	rule = *rules;
	regs.verdict.code = NFT_CONTINUE;
	क्रम (; *rules ; rules++) अणु
		rule = *rules;
		nft_rule_क्रम_each_expr(expr, last, rule) अणु
			अगर (expr->ops == &nft_cmp_fast_ops)
				nft_cmp_fast_eval(expr, &regs);
			अन्यथा अगर (expr->ops == &nft_bitwise_fast_ops)
				nft_bitwise_fast_eval(expr, &regs);
			अन्यथा अगर (expr->ops != &nft_payload_fast_ops ||
				 !nft_payload_fast_eval(expr, &regs, pkt))
				expr_call_ops_eval(expr, &regs, pkt);

			अगर (regs.verdict.code != NFT_CONTINUE)
				अवरोध;
		पूर्ण

		चयन (regs.verdict.code) अणु
		हाल NFT_BREAK:
			regs.verdict.code = NFT_CONTINUE;
			जारी;
		हाल NFT_CONTINUE:
			nft_trace_packet(&info, chain, rule,
					 NFT_TRACETYPE_RULE);
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण

	चयन (regs.verdict.code & NF_VERDICT_MASK) अणु
	हाल NF_ACCEPT:
	हाल NF_DROP:
	हाल NF_QUEUE:
	हाल NF_STOLEN:
		nft_trace_packet(&info, chain, rule,
				 NFT_TRACETYPE_RULE);
		वापस regs.verdict.code;
	पूर्ण

	चयन (regs.verdict.code) अणु
	हाल NFT_JUMP:
		अगर (WARN_ON_ONCE(stackptr >= NFT_JUMP_STACK_SIZE))
			वापस NF_DROP;
		jumpstack[stackptr].chain = chain;
		jumpstack[stackptr].rules = rules + 1;
		stackptr++;
		fallthrough;
	हाल NFT_GOTO:
		nft_trace_packet(&info, chain, rule,
				 NFT_TRACETYPE_RULE);

		chain = regs.verdict.chain;
		जाओ करो_chain;
	हाल NFT_CONTINUE:
	हाल NFT_RETURN:
		nft_trace_packet(&info, chain, rule,
				 NFT_TRACETYPE_RETURN);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	अगर (stackptr > 0) अणु
		stackptr--;
		chain = jumpstack[stackptr].chain;
		rules = jumpstack[stackptr].rules;
		जाओ next_rule;
	पूर्ण

	nft_trace_packet(&info, basechain, शून्य, NFT_TRACETYPE_POLICY);

	अगर (अटल_branch_unlikely(&nft_counters_enabled))
		nft_update_chain_stats(basechain, pkt);

	वापस nft_base_chain(basechain)->policy;
पूर्ण
EXPORT_SYMBOL_GPL(nft_करो_chain);

अटल काष्ठा nft_expr_type *nft_basic_types[] = अणु
	&nft_imm_type,
	&nft_cmp_type,
	&nft_lookup_type,
	&nft_bitwise_type,
	&nft_byteorder_type,
	&nft_payload_type,
	&nft_dynset_type,
	&nft_range_type,
	&nft_meta_type,
	&nft_rt_type,
	&nft_exthdr_type,
पूर्ण;

अटल काष्ठा nft_object_type *nft_basic_objects[] = अणु
#अगर_घोषित CONFIG_NETWORK_SECMARK
	&nft_secmark_obj_type,
#पूर्ण_अगर
पूर्ण;

पूर्णांक __init nf_tables_core_module_init(व्योम)
अणु
	पूर्णांक err, i, j = 0;

	क्रम (i = 0; i < ARRAY_SIZE(nft_basic_objects); i++) अणु
		err = nft_रेजिस्टर_obj(nft_basic_objects[i]);
		अगर (err)
			जाओ err;
	पूर्ण

	क्रम (j = 0; j < ARRAY_SIZE(nft_basic_types); j++) अणु
		err = nft_रेजिस्टर_expr(nft_basic_types[j]);
		अगर (err)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	जबतक (j-- > 0)
		nft_unरेजिस्टर_expr(nft_basic_types[j]);

	जबतक (i-- > 0)
		nft_unरेजिस्टर_obj(nft_basic_objects[i]);

	वापस err;
पूर्ण

व्योम nf_tables_core_module_निकास(व्योम)
अणु
	पूर्णांक i;

	i = ARRAY_SIZE(nft_basic_types);
	जबतक (i-- > 0)
		nft_unरेजिस्टर_expr(nft_basic_types[i]);

	i = ARRAY_SIZE(nft_basic_objects);
	जबतक (i-- > 0)
		nft_unरेजिस्टर_obj(nft_basic_objects[i]);
पूर्ण
