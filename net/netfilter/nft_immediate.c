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
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_offload.h>

व्योम nft_immediate_eval(स्थिर काष्ठा nft_expr *expr,
			काष्ठा nft_regs *regs,
			स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_immediate_expr *priv = nft_expr_priv(expr);

	nft_data_copy(&regs->data[priv->dreg], &priv->data, priv->dlen);
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_immediate_policy[NFTA_IMMEDIATE_MAX + 1] = अणु
	[NFTA_IMMEDIATE_DREG]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_IMMEDIATE_DATA]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक nft_immediate_init(स्थिर काष्ठा nft_ctx *ctx,
			      स्थिर काष्ठा nft_expr *expr,
			      स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_immediate_expr *priv = nft_expr_priv(expr);
	काष्ठा nft_data_desc desc;
	पूर्णांक err;

	अगर (tb[NFTA_IMMEDIATE_DREG] == शून्य ||
	    tb[NFTA_IMMEDIATE_DATA] == शून्य)
		वापस -EINVAL;

	err = nft_data_init(ctx, &priv->data, माप(priv->data), &desc,
			    tb[NFTA_IMMEDIATE_DATA]);
	अगर (err < 0)
		वापस err;

	priv->dlen = desc.len;

	err = nft_parse_रेजिस्टर_store(ctx, tb[NFTA_IMMEDIATE_DREG],
				       &priv->dreg, &priv->data, desc.type,
				       desc.len);
	अगर (err < 0)
		जाओ err1;

	अगर (priv->dreg == NFT_REG_VERDICT) अणु
		काष्ठा nft_chain *chain = priv->data.verdict.chain;

		चयन (priv->data.verdict.code) अणु
		हाल NFT_JUMP:
		हाल NFT_GOTO:
			अगर (nft_chain_is_bound(chain)) अणु
				err = -EBUSY;
				जाओ err1;
			पूर्ण
			chain->bound = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;

err1:
	nft_data_release(&priv->data, desc.type);
	वापस err;
पूर्ण

अटल व्योम nft_immediate_activate(स्थिर काष्ठा nft_ctx *ctx,
				   स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_immediate_expr *priv = nft_expr_priv(expr);

	वापस nft_data_hold(&priv->data, nft_dreg_to_type(priv->dreg));
पूर्ण

अटल व्योम nft_immediate_deactivate(स्थिर काष्ठा nft_ctx *ctx,
				     स्थिर काष्ठा nft_expr *expr,
				     क्रमागत nft_trans_phase phase)
अणु
	स्थिर काष्ठा nft_immediate_expr *priv = nft_expr_priv(expr);

	अगर (phase == NFT_TRANS_COMMIT)
		वापस;

	वापस nft_data_release(&priv->data, nft_dreg_to_type(priv->dreg));
पूर्ण

अटल व्योम nft_immediate_destroy(स्थिर काष्ठा nft_ctx *ctx,
				  स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_immediate_expr *priv = nft_expr_priv(expr);
	स्थिर काष्ठा nft_data *data = &priv->data;
	काष्ठा nft_rule *rule, *n;
	काष्ठा nft_ctx chain_ctx;
	काष्ठा nft_chain *chain;

	अगर (priv->dreg != NFT_REG_VERDICT)
		वापस;

	चयन (data->verdict.code) अणु
	हाल NFT_JUMP:
	हाल NFT_GOTO:
		chain = data->verdict.chain;

		अगर (!nft_chain_is_bound(chain))
			अवरोध;

		chain_ctx = *ctx;
		chain_ctx.chain = chain;

		list_क्रम_each_entry_safe(rule, n, &chain->rules, list)
			nf_tables_rule_release(&chain_ctx, rule);

		nf_tables_chain_destroy(&chain_ctx);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक nft_immediate_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_immediate_expr *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_IMMEDIATE_DREG, priv->dreg))
		जाओ nla_put_failure;

	वापस nft_data_dump(skb, NFTA_IMMEDIATE_DATA, &priv->data,
			     nft_dreg_to_type(priv->dreg), priv->dlen);

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nft_immediate_validate(स्थिर काष्ठा nft_ctx *ctx,
				  स्थिर काष्ठा nft_expr *expr,
				  स्थिर काष्ठा nft_data **d)
अणु
	स्थिर काष्ठा nft_immediate_expr *priv = nft_expr_priv(expr);
	काष्ठा nft_ctx *pctx = (काष्ठा nft_ctx *)ctx;
	स्थिर काष्ठा nft_data *data;
	पूर्णांक err;

	अगर (priv->dreg != NFT_REG_VERDICT)
		वापस 0;

	data = &priv->data;

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

अटल पूर्णांक nft_immediate_offload_verdict(काष्ठा nft_offload_ctx *ctx,
					 काष्ठा nft_flow_rule *flow,
					 स्थिर काष्ठा nft_immediate_expr *priv)
अणु
	काष्ठा flow_action_entry *entry;
	स्थिर काष्ठा nft_data *data;

	entry = &flow->rule->action.entries[ctx->num_actions++];

	data = &priv->data;
	चयन (data->verdict.code) अणु
	हाल NF_ACCEPT:
		entry->id = FLOW_ACTION_ACCEPT;
		अवरोध;
	हाल NF_DROP:
		entry->id = FLOW_ACTION_DROP;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nft_immediate_offload(काष्ठा nft_offload_ctx *ctx,
				 काष्ठा nft_flow_rule *flow,
				 स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_immediate_expr *priv = nft_expr_priv(expr);

	अगर (priv->dreg == NFT_REG_VERDICT)
		वापस nft_immediate_offload_verdict(ctx, flow, priv);

	स_नकल(&ctx->regs[priv->dreg].data, &priv->data, माप(priv->data));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nft_expr_ops nft_imm_ops = अणु
	.type		= &nft_imm_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_immediate_expr)),
	.eval		= nft_immediate_eval,
	.init		= nft_immediate_init,
	.activate	= nft_immediate_activate,
	.deactivate	= nft_immediate_deactivate,
	.destroy	= nft_immediate_destroy,
	.dump		= nft_immediate_dump,
	.validate	= nft_immediate_validate,
	.offload	= nft_immediate_offload,
	.offload_flags	= NFT_OFFLOAD_F_ACTION,
पूर्ण;

काष्ठा nft_expr_type nft_imm_type __पढ़ो_mostly = अणु
	.name		= "immediate",
	.ops		= &nft_imm_ops,
	.policy		= nft_immediate_policy,
	.maxattr	= NFTA_IMMEDIATE_MAX,
	.owner		= THIS_MODULE,
पूर्ण;
