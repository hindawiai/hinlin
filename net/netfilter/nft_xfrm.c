<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Generic part shared by ipv4 and ipv6 backends.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <linux/in.h>
#समावेश <net/xfrm.h>

अटल स्थिर काष्ठा nla_policy nft_xfrm_policy[NFTA_XFRM_MAX + 1] = अणु
	[NFTA_XFRM_KEY]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_XFRM_सूची]		= अणु .type = NLA_U8 पूर्ण,
	[NFTA_XFRM_SPNUM]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_XFRM_DREG]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

काष्ठा nft_xfrm अणु
	क्रमागत nft_xfrm_keys	key:8;
	u8			dreg;
	u8			dir;
	u8			spnum;
पूर्ण;

अटल पूर्णांक nft_xfrm_get_init(स्थिर काष्ठा nft_ctx *ctx,
			     स्थिर काष्ठा nft_expr *expr,
			     स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_xfrm *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक len = 0;
	u32 spnum = 0;
	u8 dir;

	अगर (!tb[NFTA_XFRM_KEY] || !tb[NFTA_XFRM_सूची] || !tb[NFTA_XFRM_DREG])
		वापस -EINVAL;

	चयन (ctx->family) अणु
	हाल NFPROTO_IPV4:
	हाल NFPROTO_IPV6:
	हाल NFPROTO_INET:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	priv->key = ntohl(nla_get_u32(tb[NFTA_XFRM_KEY]));
	चयन (priv->key) अणु
	हाल NFT_XFRM_KEY_REQID:
	हाल NFT_XFRM_KEY_SPI:
		len = माप(u32);
		अवरोध;
	हाल NFT_XFRM_KEY_DADDR_IP4:
	हाल NFT_XFRM_KEY_SADDR_IP4:
		len = माप(काष्ठा in_addr);
		अवरोध;
	हाल NFT_XFRM_KEY_DADDR_IP6:
	हाल NFT_XFRM_KEY_SADDR_IP6:
		len = माप(काष्ठा in6_addr);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dir = nla_get_u8(tb[NFTA_XFRM_सूची]);
	चयन (dir) अणु
	हाल XFRM_POLICY_IN:
	हाल XFRM_POLICY_OUT:
		priv->dir = dir;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (tb[NFTA_XFRM_SPNUM])
		spnum = ntohl(nla_get_be32(tb[NFTA_XFRM_SPNUM]));

	अगर (spnum >= XFRM_MAX_DEPTH)
		वापस -दुस्फल;

	priv->spnum = spnum;

	वापस nft_parse_रेजिस्टर_store(ctx, tb[NFTA_XFRM_DREG], &priv->dreg,
					शून्य, NFT_DATA_VALUE, len);
पूर्ण

/* Return true अगर key asks क्रम daddr/saddr and current
 * state करोes have a valid address (BEET, TUNNEL).
 */
अटल bool xfrm_state_addr_ok(क्रमागत nft_xfrm_keys k, u8 family, u8 mode)
अणु
	चयन (k) अणु
	हाल NFT_XFRM_KEY_DADDR_IP4:
	हाल NFT_XFRM_KEY_SADDR_IP4:
		अगर (family == NFPROTO_IPV4)
			अवरोध;
		वापस false;
	हाल NFT_XFRM_KEY_DADDR_IP6:
	हाल NFT_XFRM_KEY_SADDR_IP6:
		अगर (family == NFPROTO_IPV6)
			अवरोध;
		वापस false;
	शेष:
		वापस true;
	पूर्ण

	वापस mode == XFRM_MODE_BEET || mode == XFRM_MODE_TUNNEL;
पूर्ण

अटल व्योम nft_xfrm_state_get_key(स्थिर काष्ठा nft_xfrm *priv,
				   काष्ठा nft_regs *regs,
				   स्थिर काष्ठा xfrm_state *state)
अणु
	u32 *dest = &regs->data[priv->dreg];

	अगर (!xfrm_state_addr_ok(priv->key,
				state->props.family,
				state->props.mode)) अणु
		regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण

	चयन (priv->key) अणु
	हाल NFT_XFRM_KEY_UNSPEC:
	हाल __NFT_XFRM_KEY_MAX:
		WARN_ON_ONCE(1);
		अवरोध;
	हाल NFT_XFRM_KEY_DADDR_IP4:
		*dest = state->id.daddr.a4;
		वापस;
	हाल NFT_XFRM_KEY_DADDR_IP6:
		स_नकल(dest, &state->id.daddr.in6, माप(काष्ठा in6_addr));
		वापस;
	हाल NFT_XFRM_KEY_SADDR_IP4:
		*dest = state->props.saddr.a4;
		वापस;
	हाल NFT_XFRM_KEY_SADDR_IP6:
		स_नकल(dest, &state->props.saddr.in6, माप(काष्ठा in6_addr));
		वापस;
	हाल NFT_XFRM_KEY_REQID:
		*dest = state->props.reqid;
		वापस;
	हाल NFT_XFRM_KEY_SPI:
		*dest = state->id.spi;
		वापस;
	पूर्ण

	regs->verdict.code = NFT_BREAK;
पूर्ण

अटल व्योम nft_xfrm_get_eval_in(स्थिर काष्ठा nft_xfrm *priv,
				    काष्ठा nft_regs *regs,
				    स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा sec_path *sp = skb_sec_path(pkt->skb);
	स्थिर काष्ठा xfrm_state *state;

	अगर (sp == शून्य || sp->len <= priv->spnum) अणु
		regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण

	state = sp->xvec[priv->spnum];
	nft_xfrm_state_get_key(priv, regs, state);
पूर्ण

अटल व्योम nft_xfrm_get_eval_out(स्थिर काष्ठा nft_xfrm *priv,
				  काष्ठा nft_regs *regs,
				  स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा dst_entry *dst = skb_dst(pkt->skb);
	पूर्णांक i;

	क्रम (i = 0; dst && dst->xfrm;
	     dst = ((स्थिर काष्ठा xfrm_dst *)dst)->child, i++) अणु
		अगर (i < priv->spnum)
			जारी;

		nft_xfrm_state_get_key(priv, regs, dst->xfrm);
		वापस;
	पूर्ण

	regs->verdict.code = NFT_BREAK;
पूर्ण

अटल व्योम nft_xfrm_get_eval(स्थिर काष्ठा nft_expr *expr,
			      काष्ठा nft_regs *regs,
			      स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_xfrm *priv = nft_expr_priv(expr);

	चयन (priv->dir) अणु
	हाल XFRM_POLICY_IN:
		nft_xfrm_get_eval_in(priv, regs, pkt);
		अवरोध;
	हाल XFRM_POLICY_OUT:
		nft_xfrm_get_eval_out(priv, regs, pkt);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		regs->verdict.code = NFT_BREAK;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक nft_xfrm_get_dump(काष्ठा sk_buff *skb,
			     स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_xfrm *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_XFRM_DREG, priv->dreg))
		वापस -1;

	अगर (nla_put_be32(skb, NFTA_XFRM_KEY, htonl(priv->key)))
		वापस -1;
	अगर (nla_put_u8(skb, NFTA_XFRM_सूची, priv->dir))
		वापस -1;
	अगर (nla_put_be32(skb, NFTA_XFRM_SPNUM, htonl(priv->spnum)))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक nft_xfrm_validate(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr,
			     स्थिर काष्ठा nft_data **data)
अणु
	स्थिर काष्ठा nft_xfrm *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक hooks;

	चयन (priv->dir) अणु
	हाल XFRM_POLICY_IN:
		hooks = (1 << NF_INET_FORWARD) |
			(1 << NF_INET_LOCAL_IN) |
			(1 << NF_INET_PRE_ROUTING);
		अवरोध;
	हाल XFRM_POLICY_OUT:
		hooks = (1 << NF_INET_FORWARD) |
			(1 << NF_INET_LOCAL_OUT) |
			(1 << NF_INET_POST_ROUTING);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस -EINVAL;
	पूर्ण

	वापस nft_chain_validate_hooks(ctx->chain, hooks);
पूर्ण


अटल काष्ठा nft_expr_type nft_xfrm_type;
अटल स्थिर काष्ठा nft_expr_ops nft_xfrm_get_ops = अणु
	.type		= &nft_xfrm_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_xfrm)),
	.eval		= nft_xfrm_get_eval,
	.init		= nft_xfrm_get_init,
	.dump		= nft_xfrm_get_dump,
	.validate	= nft_xfrm_validate,
पूर्ण;

अटल काष्ठा nft_expr_type nft_xfrm_type __पढ़ो_mostly = अणु
	.name		= "xfrm",
	.ops		= &nft_xfrm_get_ops,
	.policy		= nft_xfrm_policy,
	.maxattr	= NFTA_XFRM_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_xfrm_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_xfrm_type);
पूर्ण

अटल व्योम __निकास nft_xfrm_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_xfrm_type);
पूर्ण

module_init(nft_xfrm_module_init);
module_निकास(nft_xfrm_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("nf_tables: xfrm/IPSec matching");
MODULE_AUTHOR("Florian Westphal <fw@strlen.de>");
MODULE_AUTHOR("Mथँtथऊ Eckl <ecklm94@gmail.com>");
MODULE_ALIAS_NFT_EXPR("xfrm");
