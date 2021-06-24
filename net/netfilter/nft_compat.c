<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 2012-2013 by Pablo Neira Ayuso <pablo@netfilter.org>
 *
 * This software has been sponsored by Sophos Astaro <http://www.sophos.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <linux/netfilter/nf_tables_compat.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/netfilter_arp/arp_tables.h>
#समावेश <net/netfilter/nf_tables.h>

/* Used क्रम matches where *info is larger than X byte */
#घोषणा NFT_MATCH_LARGE_THRESH	192

काष्ठा nft_xt_match_priv अणु
	व्योम *info;
पूर्ण;

अटल पूर्णांक nft_compat_chain_validate_dependency(स्थिर काष्ठा nft_ctx *ctx,
						स्थिर अक्षर *tablename)
अणु
	क्रमागत nft_chain_types type = NFT_CHAIN_T_DEFAULT;
	स्थिर काष्ठा nft_chain *chain = ctx->chain;
	स्थिर काष्ठा nft_base_chain *basechain;

	अगर (!tablename ||
	    !nft_is_base_chain(chain))
		वापस 0;

	basechain = nft_base_chain(chain);
	अगर (म_भेद(tablename, "nat") == 0) अणु
		अगर (ctx->family != NFPROTO_BRIDGE)
			type = NFT_CHAIN_T_NAT;
		अगर (basechain->type->type != type)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

जोड़ nft_entry अणु
	काष्ठा ipt_entry e4;
	काष्ठा ip6t_entry e6;
	काष्ठा ebt_entry ebt;
	काष्ठा arpt_entry arp;
पूर्ण;

अटल अंतरभूत व्योम
nft_compat_set_par(काष्ठा xt_action_param *par, व्योम *xt, स्थिर व्योम *xt_info)
अणु
	par->target	= xt;
	par->targinfo	= xt_info;
	par->hotdrop	= false;
पूर्ण

अटल व्योम nft_target_eval_xt(स्थिर काष्ठा nft_expr *expr,
			       काष्ठा nft_regs *regs,
			       स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	व्योम *info = nft_expr_priv(expr);
	काष्ठा xt_target *target = expr->ops->data;
	काष्ठा sk_buff *skb = pkt->skb;
	पूर्णांक ret;

	nft_compat_set_par((काष्ठा xt_action_param *)&pkt->xt, target, info);

	ret = target->target(skb, &pkt->xt);

	अगर (pkt->xt.hotdrop)
		ret = NF_DROP;

	चयन (ret) अणु
	हाल XT_CONTINUE:
		regs->verdict.code = NFT_CONTINUE;
		अवरोध;
	शेष:
		regs->verdict.code = ret;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम nft_target_eval_bridge(स्थिर काष्ठा nft_expr *expr,
				   काष्ठा nft_regs *regs,
				   स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	व्योम *info = nft_expr_priv(expr);
	काष्ठा xt_target *target = expr->ops->data;
	काष्ठा sk_buff *skb = pkt->skb;
	पूर्णांक ret;

	nft_compat_set_par((काष्ठा xt_action_param *)&pkt->xt, target, info);

	ret = target->target(skb, &pkt->xt);

	अगर (pkt->xt.hotdrop)
		ret = NF_DROP;

	चयन (ret) अणु
	हाल EBT_ACCEPT:
		regs->verdict.code = NF_ACCEPT;
		अवरोध;
	हाल EBT_DROP:
		regs->verdict.code = NF_DROP;
		अवरोध;
	हाल EBT_CONTINUE:
		regs->verdict.code = NFT_CONTINUE;
		अवरोध;
	हाल EBT_RETURN:
		regs->verdict.code = NFT_RETURN;
		अवरोध;
	शेष:
		regs->verdict.code = ret;
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_target_policy[NFTA_TARGET_MAX + 1] = अणु
	[NFTA_TARGET_NAME]	= अणु .type = NLA_NUL_STRING पूर्ण,
	[NFTA_TARGET_REV]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_TARGET_INFO]	= अणु .type = NLA_BINARY पूर्ण,
पूर्ण;

अटल व्योम
nft_target_set_tgchk_param(काष्ठा xt_tgchk_param *par,
			   स्थिर काष्ठा nft_ctx *ctx,
			   काष्ठा xt_target *target, व्योम *info,
			   जोड़ nft_entry *entry, u16 proto, bool inv)
अणु
	par->net	= ctx->net;
	par->table	= ctx->table->name;
	चयन (ctx->family) अणु
	हाल AF_INET:
		entry->e4.ip.proto = proto;
		entry->e4.ip.invflags = inv ? IPT_INV_PROTO : 0;
		अवरोध;
	हाल AF_INET6:
		अगर (proto)
			entry->e6.ipv6.flags |= IP6T_F_PROTO;

		entry->e6.ipv6.proto = proto;
		entry->e6.ipv6.invflags = inv ? IP6T_INV_PROTO : 0;
		अवरोध;
	हाल NFPROTO_BRIDGE:
		entry->ebt.ethproto = (__क्रमce __be16)proto;
		entry->ebt.invflags = inv ? EBT_IPROTO : 0;
		अवरोध;
	हाल NFPROTO_ARP:
		अवरोध;
	पूर्ण
	par->entryinfo	= entry;
	par->target	= target;
	par->targinfo	= info;
	अगर (nft_is_base_chain(ctx->chain)) अणु
		स्थिर काष्ठा nft_base_chain *basechain =
						nft_base_chain(ctx->chain);
		स्थिर काष्ठा nf_hook_ops *ops = &basechain->ops;

		par->hook_mask = 1 << ops->hooknum;
	पूर्ण अन्यथा अणु
		par->hook_mask = 0;
	पूर्ण
	par->family	= ctx->family;
	par->nft_compat = true;
पूर्ण

अटल व्योम target_compat_from_user(काष्ठा xt_target *t, व्योम *in, व्योम *out)
अणु
	पूर्णांक pad;

	स_नकल(out, in, t->tarमाला_लोize);
	pad = XT_ALIGN(t->tarमाला_लोize) - t->tarमाला_लोize;
	अगर (pad > 0)
		स_रखो(out + t->tarमाला_लोize, 0, pad);
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_rule_compat_policy[NFTA_RULE_COMPAT_MAX + 1] = अणु
	[NFTA_RULE_COMPAT_PROTO]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_RULE_COMPAT_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_parse_compat(स्थिर काष्ठा nlattr *attr, u16 *proto, bool *inv)
अणु
	काष्ठा nlattr *tb[NFTA_RULE_COMPAT_MAX+1];
	u32 flags;
	पूर्णांक err;

	err = nla_parse_nested_deprecated(tb, NFTA_RULE_COMPAT_MAX, attr,
					  nft_rule_compat_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[NFTA_RULE_COMPAT_PROTO] || !tb[NFTA_RULE_COMPAT_FLAGS])
		वापस -EINVAL;

	flags = ntohl(nla_get_be32(tb[NFTA_RULE_COMPAT_FLAGS]));
	अगर (flags & ~NFT_RULE_COMPAT_F_MASK)
		वापस -EINVAL;
	अगर (flags & NFT_RULE_COMPAT_F_INV)
		*inv = true;

	*proto = ntohl(nla_get_be32(tb[NFTA_RULE_COMPAT_PROTO]));
	वापस 0;
पूर्ण

अटल व्योम nft_compat_रुको_क्रम_deकाष्ठाors(व्योम)
अणु
	/* xtables matches or tarमाला_लो can have side effects, e.g.
	 * creation/deकाष्ठाion of /proc files.
	 * The xt ->destroy functions are run asynchronously from
	 * work queue.  If we have pending invocations we thus
	 * need to रुको क्रम those to finish.
	 */
	nf_tables_trans_destroy_flush_work();
पूर्ण

अटल पूर्णांक
nft_target_init(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr,
		स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	व्योम *info = nft_expr_priv(expr);
	काष्ठा xt_target *target = expr->ops->data;
	काष्ठा xt_tgchk_param par;
	माप_प्रकार size = XT_ALIGN(nla_len(tb[NFTA_TARGET_INFO]));
	u16 proto = 0;
	bool inv = false;
	जोड़ nft_entry e = अणुपूर्ण;
	पूर्णांक ret;

	target_compat_from_user(target, nla_data(tb[NFTA_TARGET_INFO]), info);

	अगर (ctx->nla[NFTA_RULE_COMPAT]) अणु
		ret = nft_parse_compat(ctx->nla[NFTA_RULE_COMPAT], &proto, &inv);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	nft_target_set_tgchk_param(&par, ctx, target, info, &e, proto, inv);

	nft_compat_रुको_क्रम_deकाष्ठाors();

	ret = xt_check_target(&par, size, proto, inv);
	अगर (ret < 0)
		वापस ret;

	/* The standard target cannot be used */
	अगर (!target->target)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम __nft_mt_tg_destroy(काष्ठा module *me, स्थिर काष्ठा nft_expr *expr)
अणु
	module_put(me);
	kमुक्त(expr->ops);
पूर्ण

अटल व्योम
nft_target_destroy(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा xt_target *target = expr->ops->data;
	व्योम *info = nft_expr_priv(expr);
	काष्ठा module *me = target->me;
	काष्ठा xt_tgdtor_param par;

	par.net = ctx->net;
	par.target = target;
	par.targinfo = info;
	par.family = ctx->family;
	अगर (par.target->destroy != शून्य)
		par.target->destroy(&par);

	__nft_mt_tg_destroy(me, expr);
पूर्ण

अटल पूर्णांक nft_extension_dump_info(काष्ठा sk_buff *skb, पूर्णांक attr,
				   स्थिर व्योम *info,
				   अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक user_size)
अणु
	अचिन्हित पूर्णांक info_size, aligned_size = XT_ALIGN(size);
	काष्ठा nlattr *nla;

	nla = nla_reserve(skb, attr, aligned_size);
	अगर (!nla)
		वापस -1;

	info_size = user_size ? : size;
	स_नकल(nla_data(nla), info, info_size);
	स_रखो(nla_data(nla) + info_size, 0, aligned_size - info_size);

	वापस 0;
पूर्ण

अटल पूर्णांक nft_target_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा xt_target *target = expr->ops->data;
	व्योम *info = nft_expr_priv(expr);

	अगर (nla_put_string(skb, NFTA_TARGET_NAME, target->name) ||
	    nla_put_be32(skb, NFTA_TARGET_REV, htonl(target->revision)) ||
	    nft_extension_dump_info(skb, NFTA_TARGET_INFO, info,
				    target->tarमाला_लोize, target->usersize))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nft_target_validate(स्थिर काष्ठा nft_ctx *ctx,
			       स्थिर काष्ठा nft_expr *expr,
			       स्थिर काष्ठा nft_data **data)
अणु
	काष्ठा xt_target *target = expr->ops->data;
	अचिन्हित पूर्णांक hook_mask = 0;
	पूर्णांक ret;

	अगर (nft_is_base_chain(ctx->chain)) अणु
		स्थिर काष्ठा nft_base_chain *basechain =
						nft_base_chain(ctx->chain);
		स्थिर काष्ठा nf_hook_ops *ops = &basechain->ops;

		hook_mask = 1 << ops->hooknum;
		अगर (target->hooks && !(hook_mask & target->hooks))
			वापस -EINVAL;

		ret = nft_compat_chain_validate_dependency(ctx, target->table);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __nft_match_eval(स्थिर काष्ठा nft_expr *expr,
			     काष्ठा nft_regs *regs,
			     स्थिर काष्ठा nft_pktinfo *pkt,
			     व्योम *info)
अणु
	काष्ठा xt_match *match = expr->ops->data;
	काष्ठा sk_buff *skb = pkt->skb;
	bool ret;

	nft_compat_set_par((काष्ठा xt_action_param *)&pkt->xt, match, info);

	ret = match->match(skb, (काष्ठा xt_action_param *)&pkt->xt);

	अगर (pkt->xt.hotdrop) अणु
		regs->verdict.code = NF_DROP;
		वापस;
	पूर्ण

	चयन (ret ? 1 : 0) अणु
	हाल 1:
		regs->verdict.code = NFT_CONTINUE;
		अवरोध;
	हाल 0:
		regs->verdict.code = NFT_BREAK;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम nft_match_large_eval(स्थिर काष्ठा nft_expr *expr,
				 काष्ठा nft_regs *regs,
				 स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_xt_match_priv *priv = nft_expr_priv(expr);

	__nft_match_eval(expr, regs, pkt, priv->info);
पूर्ण

अटल व्योम nft_match_eval(स्थिर काष्ठा nft_expr *expr,
			   काष्ठा nft_regs *regs,
			   स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	__nft_match_eval(expr, regs, pkt, nft_expr_priv(expr));
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_match_policy[NFTA_MATCH_MAX + 1] = अणु
	[NFTA_MATCH_NAME]	= अणु .type = NLA_NUL_STRING पूर्ण,
	[NFTA_MATCH_REV]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_MATCH_INFO]	= अणु .type = NLA_BINARY पूर्ण,
पूर्ण;

/* काष्ठा xt_mtchk_param and xt_tgchk_param look very similar */
अटल व्योम
nft_match_set_mtchk_param(काष्ठा xt_mtchk_param *par, स्थिर काष्ठा nft_ctx *ctx,
			  काष्ठा xt_match *match, व्योम *info,
			  जोड़ nft_entry *entry, u16 proto, bool inv)
अणु
	par->net	= ctx->net;
	par->table	= ctx->table->name;
	चयन (ctx->family) अणु
	हाल AF_INET:
		entry->e4.ip.proto = proto;
		entry->e4.ip.invflags = inv ? IPT_INV_PROTO : 0;
		अवरोध;
	हाल AF_INET6:
		अगर (proto)
			entry->e6.ipv6.flags |= IP6T_F_PROTO;

		entry->e6.ipv6.proto = proto;
		entry->e6.ipv6.invflags = inv ? IP6T_INV_PROTO : 0;
		अवरोध;
	हाल NFPROTO_BRIDGE:
		entry->ebt.ethproto = (__क्रमce __be16)proto;
		entry->ebt.invflags = inv ? EBT_IPROTO : 0;
		अवरोध;
	हाल NFPROTO_ARP:
		अवरोध;
	पूर्ण
	par->entryinfo	= entry;
	par->match	= match;
	par->matchinfo	= info;
	अगर (nft_is_base_chain(ctx->chain)) अणु
		स्थिर काष्ठा nft_base_chain *basechain =
						nft_base_chain(ctx->chain);
		स्थिर काष्ठा nf_hook_ops *ops = &basechain->ops;

		par->hook_mask = 1 << ops->hooknum;
	पूर्ण अन्यथा अणु
		par->hook_mask = 0;
	पूर्ण
	par->family	= ctx->family;
	par->nft_compat = true;
पूर्ण

अटल व्योम match_compat_from_user(काष्ठा xt_match *m, व्योम *in, व्योम *out)
अणु
	पूर्णांक pad;

	स_नकल(out, in, m->matchsize);
	pad = XT_ALIGN(m->matchsize) - m->matchsize;
	अगर (pad > 0)
		स_रखो(out + m->matchsize, 0, pad);
पूर्ण

अटल पूर्णांक
__nft_match_init(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr,
		 स्थिर काष्ठा nlattr * स्थिर tb[],
		 व्योम *info)
अणु
	काष्ठा xt_match *match = expr->ops->data;
	काष्ठा xt_mtchk_param par;
	माप_प्रकार size = XT_ALIGN(nla_len(tb[NFTA_MATCH_INFO]));
	u16 proto = 0;
	bool inv = false;
	जोड़ nft_entry e = अणुपूर्ण;
	पूर्णांक ret;

	match_compat_from_user(match, nla_data(tb[NFTA_MATCH_INFO]), info);

	अगर (ctx->nla[NFTA_RULE_COMPAT]) अणु
		ret = nft_parse_compat(ctx->nla[NFTA_RULE_COMPAT], &proto, &inv);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	nft_match_set_mtchk_param(&par, ctx, match, info, &e, proto, inv);

	nft_compat_रुको_क्रम_deकाष्ठाors();

	वापस xt_check_match(&par, size, proto, inv);
पूर्ण

अटल पूर्णांक
nft_match_init(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr,
	       स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	वापस __nft_match_init(ctx, expr, tb, nft_expr_priv(expr));
पूर्ण

अटल पूर्णांक
nft_match_large_init(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr,
		     स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_xt_match_priv *priv = nft_expr_priv(expr);
	काष्ठा xt_match *m = expr->ops->data;
	पूर्णांक ret;

	priv->info = kदो_स्मृति(XT_ALIGN(m->matchsize), GFP_KERNEL);
	अगर (!priv->info)
		वापस -ENOMEM;

	ret = __nft_match_init(ctx, expr, tb, priv->info);
	अगर (ret)
		kमुक्त(priv->info);
	वापस ret;
पूर्ण

अटल व्योम
__nft_match_destroy(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr,
		    व्योम *info)
अणु
	काष्ठा xt_match *match = expr->ops->data;
	काष्ठा module *me = match->me;
	काष्ठा xt_mtdtor_param par;

	par.net = ctx->net;
	par.match = match;
	par.matchinfo = info;
	par.family = ctx->family;
	अगर (par.match->destroy != शून्य)
		par.match->destroy(&par);

	__nft_mt_tg_destroy(me, expr);
पूर्ण

अटल व्योम
nft_match_destroy(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr)
अणु
	__nft_match_destroy(ctx, expr, nft_expr_priv(expr));
पूर्ण

अटल व्योम
nft_match_large_destroy(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_xt_match_priv *priv = nft_expr_priv(expr);

	__nft_match_destroy(ctx, expr, priv->info);
	kमुक्त(priv->info);
पूर्ण

अटल पूर्णांक __nft_match_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr,
			    व्योम *info)
अणु
	काष्ठा xt_match *match = expr->ops->data;

	अगर (nla_put_string(skb, NFTA_MATCH_NAME, match->name) ||
	    nla_put_be32(skb, NFTA_MATCH_REV, htonl(match->revision)) ||
	    nft_extension_dump_info(skb, NFTA_MATCH_INFO, info,
				    match->matchsize, match->usersize))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nft_match_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	वापस __nft_match_dump(skb, expr, nft_expr_priv(expr));
पूर्ण

अटल पूर्णांक nft_match_large_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *e)
अणु
	काष्ठा nft_xt_match_priv *priv = nft_expr_priv(e);

	वापस __nft_match_dump(skb, e, priv->info);
पूर्ण

अटल पूर्णांक nft_match_validate(स्थिर काष्ठा nft_ctx *ctx,
			      स्थिर काष्ठा nft_expr *expr,
			      स्थिर काष्ठा nft_data **data)
अणु
	काष्ठा xt_match *match = expr->ops->data;
	अचिन्हित पूर्णांक hook_mask = 0;
	पूर्णांक ret;

	अगर (nft_is_base_chain(ctx->chain)) अणु
		स्थिर काष्ठा nft_base_chain *basechain =
						nft_base_chain(ctx->chain);
		स्थिर काष्ठा nf_hook_ops *ops = &basechain->ops;

		hook_mask = 1 << ops->hooknum;
		अगर (match->hooks && !(hook_mask & match->hooks))
			वापस -EINVAL;

		ret = nft_compat_chain_validate_dependency(ctx, match->table);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
nfnl_compat_fill_info(काष्ठा sk_buff *skb, u32 portid, u32 seq, u32 type,
		      पूर्णांक event, u16 family, स्थिर अक्षर *name,
		      पूर्णांक rev, पूर्णांक target)
अणु
	काष्ठा nlmsghdr *nlh;
	अचिन्हित पूर्णांक flags = portid ? NLM_F_MULTI : 0;

	event = nfnl_msg_type(NFNL_SUBSYS_NFT_COMPAT, event);
	nlh = nfnl_msg_put(skb, portid, seq, event, flags, family,
			   NFNETLINK_V0, 0);
	अगर (!nlh)
		जाओ nlmsg_failure;

	अगर (nla_put_string(skb, NFTA_COMPAT_NAME, name) ||
	    nla_put_be32(skb, NFTA_COMPAT_REV, htonl(rev)) ||
	    nla_put_be32(skb, NFTA_COMPAT_TYPE, htonl(target)))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस skb->len;

nlmsg_failure:
nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -1;
पूर्ण

अटल पूर्णांक nfnl_compat_get_rcu(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा nfnl_info *info,
			       स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nfgenmsg *nfmsg;
	स्थिर अक्षर *name, *fmt;
	काष्ठा sk_buff *skb2;
	पूर्णांक ret = 0, target;
	u32 rev;

	अगर (tb[NFTA_COMPAT_NAME] == शून्य ||
	    tb[NFTA_COMPAT_REV] == शून्य ||
	    tb[NFTA_COMPAT_TYPE] == शून्य)
		वापस -EINVAL;

	name = nla_data(tb[NFTA_COMPAT_NAME]);
	rev = ntohl(nla_get_be32(tb[NFTA_COMPAT_REV]));
	target = ntohl(nla_get_be32(tb[NFTA_COMPAT_TYPE]));

	nfmsg = nlmsg_data(info->nlh);

	चयन(nfmsg->nfgen_family) अणु
	हाल AF_INET:
		fmt = "ipt_%s";
		अवरोध;
	हाल AF_INET6:
		fmt = "ip6t_%s";
		अवरोध;
	हाल NFPROTO_BRIDGE:
		fmt = "ebt_%s";
		अवरोध;
	हाल NFPROTO_ARP:
		fmt = "arpt_%s";
		अवरोध;
	शेष:
		pr_err("nft_compat: unsupported protocol %d\n",
			nfmsg->nfgen_family);
		वापस -EINVAL;
	पूर्ण

	अगर (!try_module_get(THIS_MODULE))
		वापस -EINVAL;

	rcu_पढ़ो_unlock();
	try_then_request_module(xt_find_revision(nfmsg->nfgen_family, name,
						 rev, target, &ret),
						 fmt, name);
	अगर (ret < 0)
		जाओ out_put;

	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (skb2 == शून्य) अणु
		ret = -ENOMEM;
		जाओ out_put;
	पूर्ण

	/* include the best revision क्रम this extension in the message */
	अगर (nfnl_compat_fill_info(skb2, NETLINK_CB(skb).portid,
				  info->nlh->nlmsg_seq,
				  NFNL_MSG_TYPE(info->nlh->nlmsg_type),
				  NFNL_MSG_COMPAT_GET,
				  nfmsg->nfgen_family,
				  name, ret, target) <= 0) अणु
		kमुक्त_skb(skb2);
		जाओ out_put;
	पूर्ण

	ret = netlink_unicast(info->sk, skb2, NETLINK_CB(skb).portid,
			      MSG_DONTWAIT);
	अगर (ret > 0)
		ret = 0;
out_put:
	rcu_पढ़ो_lock();
	module_put(THIS_MODULE);
	वापस ret == -EAGAIN ? -ENOBUFS : ret;
पूर्ण

अटल स्थिर काष्ठा nla_policy nfnl_compat_policy_get[NFTA_COMPAT_MAX+1] = अणु
	[NFTA_COMPAT_NAME]	= अणु .type = NLA_NUL_STRING,
				    .len = NFT_COMPAT_NAME_MAX-1 पूर्ण,
	[NFTA_COMPAT_REV]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_COMPAT_TYPE]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nfnl_callback nfnl_nft_compat_cb[NFNL_MSG_COMPAT_MAX] = अणु
	[NFNL_MSG_COMPAT_GET]	= अणु
		.call		= nfnl_compat_get_rcu,
		.type		= NFNL_CB_RCU,
		.attr_count	= NFTA_COMPAT_MAX,
		.policy		= nfnl_compat_policy_get
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nfnetlink_subप्रणाली nfnl_compat_subsys = अणु
	.name		= "nft-compat",
	.subsys_id	= NFNL_SUBSYS_NFT_COMPAT,
	.cb_count	= NFNL_MSG_COMPAT_MAX,
	.cb		= nfnl_nft_compat_cb,
पूर्ण;

अटल काष्ठा nft_expr_type nft_match_type;

अटल स्थिर काष्ठा nft_expr_ops *
nft_match_select_ops(स्थिर काष्ठा nft_ctx *ctx,
		     स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_expr_ops *ops;
	काष्ठा xt_match *match;
	अचिन्हित पूर्णांक matchsize;
	अक्षर *mt_name;
	u32 rev, family;
	पूर्णांक err;

	अगर (tb[NFTA_MATCH_NAME] == शून्य ||
	    tb[NFTA_MATCH_REV] == शून्य ||
	    tb[NFTA_MATCH_INFO] == शून्य)
		वापस ERR_PTR(-EINVAL);

	mt_name = nla_data(tb[NFTA_MATCH_NAME]);
	rev = ntohl(nla_get_be32(tb[NFTA_MATCH_REV]));
	family = ctx->family;

	match = xt_request_find_match(family, mt_name, rev);
	अगर (IS_ERR(match))
		वापस ERR_PTR(-ENOENT);

	अगर (match->matchsize > nla_len(tb[NFTA_MATCH_INFO])) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	ops = kzalloc(माप(काष्ठा nft_expr_ops), GFP_KERNEL);
	अगर (!ops) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	ops->type = &nft_match_type;
	ops->eval = nft_match_eval;
	ops->init = nft_match_init;
	ops->destroy = nft_match_destroy;
	ops->dump = nft_match_dump;
	ops->validate = nft_match_validate;
	ops->data = match;

	matchsize = NFT_EXPR_SIZE(XT_ALIGN(match->matchsize));
	अगर (matchsize > NFT_MATCH_LARGE_THRESH) अणु
		matchsize = NFT_EXPR_SIZE(माप(काष्ठा nft_xt_match_priv));

		ops->eval = nft_match_large_eval;
		ops->init = nft_match_large_init;
		ops->destroy = nft_match_large_destroy;
		ops->dump = nft_match_large_dump;
	पूर्ण

	ops->size = matchsize;

	वापस ops;
err:
	module_put(match->me);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम nft_match_release_ops(स्थिर काष्ठा nft_expr_ops *ops)
अणु
	काष्ठा xt_match *match = ops->data;

	module_put(match->me);
	kमुक्त(ops);
पूर्ण

अटल काष्ठा nft_expr_type nft_match_type __पढ़ो_mostly = अणु
	.name		= "match",
	.select_ops	= nft_match_select_ops,
	.release_ops	= nft_match_release_ops,
	.policy		= nft_match_policy,
	.maxattr	= NFTA_MATCH_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा nft_expr_type nft_target_type;

अटल स्थिर काष्ठा nft_expr_ops *
nft_target_select_ops(स्थिर काष्ठा nft_ctx *ctx,
		      स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_expr_ops *ops;
	काष्ठा xt_target *target;
	अक्षर *tg_name;
	u32 rev, family;
	पूर्णांक err;

	अगर (tb[NFTA_TARGET_NAME] == शून्य ||
	    tb[NFTA_TARGET_REV] == शून्य ||
	    tb[NFTA_TARGET_INFO] == शून्य)
		वापस ERR_PTR(-EINVAL);

	tg_name = nla_data(tb[NFTA_TARGET_NAME]);
	rev = ntohl(nla_get_be32(tb[NFTA_TARGET_REV]));
	family = ctx->family;

	अगर (म_भेद(tg_name, XT_ERROR_TARGET) == 0 ||
	    म_भेद(tg_name, XT_STANDARD_TARGET) == 0 ||
	    म_भेद(tg_name, "standard") == 0)
		वापस ERR_PTR(-EINVAL);

	target = xt_request_find_target(family, tg_name, rev);
	अगर (IS_ERR(target))
		वापस ERR_PTR(-ENOENT);

	अगर (!target->target) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (target->tarमाला_लोize > nla_len(tb[NFTA_TARGET_INFO])) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	ops = kzalloc(माप(काष्ठा nft_expr_ops), GFP_KERNEL);
	अगर (!ops) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	ops->type = &nft_target_type;
	ops->size = NFT_EXPR_SIZE(XT_ALIGN(target->tarमाला_लोize));
	ops->init = nft_target_init;
	ops->destroy = nft_target_destroy;
	ops->dump = nft_target_dump;
	ops->validate = nft_target_validate;
	ops->data = target;

	अगर (family == NFPROTO_BRIDGE)
		ops->eval = nft_target_eval_bridge;
	अन्यथा
		ops->eval = nft_target_eval_xt;

	वापस ops;
err:
	module_put(target->me);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम nft_target_release_ops(स्थिर काष्ठा nft_expr_ops *ops)
अणु
	काष्ठा xt_target *target = ops->data;

	module_put(target->me);
	kमुक्त(ops);
पूर्ण

अटल काष्ठा nft_expr_type nft_target_type __पढ़ो_mostly = अणु
	.name		= "target",
	.select_ops	= nft_target_select_ops,
	.release_ops	= nft_target_release_ops,
	.policy		= nft_target_policy,
	.maxattr	= NFTA_TARGET_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_compat_module_init(व्योम)
अणु
	पूर्णांक ret;

	ret = nft_रेजिस्टर_expr(&nft_match_type);
	अगर (ret < 0)
		वापस ret;

	ret = nft_रेजिस्टर_expr(&nft_target_type);
	अगर (ret < 0)
		जाओ err_match;

	ret = nfnetlink_subsys_रेजिस्टर(&nfnl_compat_subsys);
	अगर (ret < 0) अणु
		pr_err("nft_compat: cannot register with nfnetlink.\n");
		जाओ err_target;
	पूर्ण

	वापस ret;
err_target:
	nft_unरेजिस्टर_expr(&nft_target_type);
err_match:
	nft_unरेजिस्टर_expr(&nft_match_type);
	वापस ret;
पूर्ण

अटल व्योम __निकास nft_compat_module_निकास(व्योम)
अणु
	nfnetlink_subsys_unरेजिस्टर(&nfnl_compat_subsys);
	nft_unरेजिस्टर_expr(&nft_target_type);
	nft_unरेजिस्टर_expr(&nft_match_type);
पूर्ण

MODULE_ALIAS_NFNL_SUBSYS(NFNL_SUBSYS_NFT_COMPAT);

module_init(nft_compat_module_init);
module_निकास(nft_compat_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_ALIAS_NFT_EXPR("match");
MODULE_ALIAS_NFT_EXPR("target");
MODULE_DESCRIPTION("x_tables over nftables support");
