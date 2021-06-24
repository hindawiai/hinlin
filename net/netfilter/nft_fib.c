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
#समावेश <net/netfilter/nft_fib.h>

स्थिर काष्ठा nla_policy nft_fib_policy[NFTA_FIB_MAX + 1] = अणु
	[NFTA_FIB_DREG]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_FIB_RESULT]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_FIB_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;
EXPORT_SYMBOL(nft_fib_policy);

#घोषणा NFTA_FIB_F_ALL (NFTA_FIB_F_SADDR | NFTA_FIB_F_DADDR | \
			NFTA_FIB_F_MARK | NFTA_FIB_F_IIF | NFTA_FIB_F_OIF | \
			NFTA_FIB_F_PRESENT)

पूर्णांक nft_fib_validate(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr,
		     स्थिर काष्ठा nft_data **data)
अणु
	स्थिर काष्ठा nft_fib *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक hooks;

	चयन (priv->result) अणु
	हाल NFT_FIB_RESULT_OIF:
	हाल NFT_FIB_RESULT_OIFNAME:
		hooks = (1 << NF_INET_PRE_ROUTING);
		अवरोध;
	हाल NFT_FIB_RESULT_ADDRTYPE:
		अगर (priv->flags & NFTA_FIB_F_IIF)
			hooks = (1 << NF_INET_PRE_ROUTING) |
				(1 << NF_INET_LOCAL_IN) |
				(1 << NF_INET_FORWARD);
		अन्यथा अगर (priv->flags & NFTA_FIB_F_OIF)
			hooks = (1 << NF_INET_LOCAL_OUT) |
				(1 << NF_INET_POST_ROUTING) |
				(1 << NF_INET_FORWARD);
		अन्यथा
			hooks = (1 << NF_INET_LOCAL_IN) |
				(1 << NF_INET_LOCAL_OUT) |
				(1 << NF_INET_FORWARD) |
				(1 << NF_INET_PRE_ROUTING) |
				(1 << NF_INET_POST_ROUTING);

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस nft_chain_validate_hooks(ctx->chain, hooks);
पूर्ण
EXPORT_SYMBOL_GPL(nft_fib_validate);

पूर्णांक nft_fib_init(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr,
		 स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_fib *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक len;
	पूर्णांक err;

	अगर (!tb[NFTA_FIB_DREG] || !tb[NFTA_FIB_RESULT] || !tb[NFTA_FIB_FLAGS])
		वापस -EINVAL;

	priv->flags = ntohl(nla_get_be32(tb[NFTA_FIB_FLAGS]));

	अगर (priv->flags == 0 || (priv->flags & ~NFTA_FIB_F_ALL))
		वापस -EINVAL;

	अगर ((priv->flags & (NFTA_FIB_F_SADDR | NFTA_FIB_F_DADDR)) ==
			   (NFTA_FIB_F_SADDR | NFTA_FIB_F_DADDR))
		वापस -EINVAL;
	अगर ((priv->flags & (NFTA_FIB_F_IIF | NFTA_FIB_F_OIF)) ==
			   (NFTA_FIB_F_IIF | NFTA_FIB_F_OIF))
		वापस -EINVAL;
	अगर ((priv->flags & (NFTA_FIB_F_SADDR | NFTA_FIB_F_DADDR)) == 0)
		वापस -EINVAL;

	priv->result = ntohl(nla_get_be32(tb[NFTA_FIB_RESULT]));

	चयन (priv->result) अणु
	हाल NFT_FIB_RESULT_OIF:
		अगर (priv->flags & NFTA_FIB_F_OIF)
			वापस -EINVAL;
		len = माप(पूर्णांक);
		अवरोध;
	हाल NFT_FIB_RESULT_OIFNAME:
		अगर (priv->flags & NFTA_FIB_F_OIF)
			वापस -EINVAL;
		len = IFNAMSIZ;
		अवरोध;
	हाल NFT_FIB_RESULT_ADDRTYPE:
		len = माप(u32);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	err = nft_parse_रेजिस्टर_store(ctx, tb[NFTA_FIB_DREG], &priv->dreg,
				       शून्य, NFT_DATA_VALUE, len);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nft_fib_init);

पूर्णांक nft_fib_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_fib *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_FIB_DREG, priv->dreg))
		वापस -1;

	अगर (nla_put_be32(skb, NFTA_FIB_RESULT, htonl(priv->result)))
		वापस -1;

	अगर (nla_put_be32(skb, NFTA_FIB_FLAGS, htonl(priv->flags)))
		वापस -1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nft_fib_dump);

व्योम nft_fib_store_result(व्योम *reg, स्थिर काष्ठा nft_fib *priv,
			  स्थिर काष्ठा net_device *dev)
अणु
	u32 *dreg = reg;
	पूर्णांक index;

	चयन (priv->result) अणु
	हाल NFT_FIB_RESULT_OIF:
		index = dev ? dev->अगरindex : 0;
		*dreg = (priv->flags & NFTA_FIB_F_PRESENT) ? !!index : index;
		अवरोध;
	हाल NFT_FIB_RESULT_OIFNAME:
		अगर (priv->flags & NFTA_FIB_F_PRESENT)
			*dreg = !!dev;
		अन्यथा
			म_नकलन(reg, dev ? dev->name : "", IFNAMSIZ);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		*dreg = 0;
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nft_fib_store_result);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Florian Westphal <fw@strlen.de>");
