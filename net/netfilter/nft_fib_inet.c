<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_tables.h>

#समावेश <net/netfilter/nft_fib.h>

अटल व्योम nft_fib_inet_eval(स्थिर काष्ठा nft_expr *expr,
			      काष्ठा nft_regs *regs,
			      स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_fib *priv = nft_expr_priv(expr);

	चयन (nft_pf(pkt)) अणु
	हाल NFPROTO_IPV4:
		चयन (priv->result) अणु
		हाल NFT_FIB_RESULT_OIF:
		हाल NFT_FIB_RESULT_OIFNAME:
			वापस nft_fib4_eval(expr, regs, pkt);
		हाल NFT_FIB_RESULT_ADDRTYPE:
			वापस nft_fib4_eval_type(expr, regs, pkt);
		पूर्ण
		अवरोध;
	हाल NFPROTO_IPV6:
		चयन (priv->result) अणु
		हाल NFT_FIB_RESULT_OIF:
		हाल NFT_FIB_RESULT_OIFNAME:
			वापस nft_fib6_eval(expr, regs, pkt);
		हाल NFT_FIB_RESULT_ADDRTYPE:
			वापस nft_fib6_eval_type(expr, regs, pkt);
		पूर्ण
		अवरोध;
	पूर्ण

	regs->verdict.code = NF_DROP;
पूर्ण

अटल काष्ठा nft_expr_type nft_fib_inet_type;
अटल स्थिर काष्ठा nft_expr_ops nft_fib_inet_ops = अणु
	.type		= &nft_fib_inet_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_fib)),
	.eval		= nft_fib_inet_eval,
	.init		= nft_fib_init,
	.dump		= nft_fib_dump,
	.validate	= nft_fib_validate,
पूर्ण;

अटल काष्ठा nft_expr_type nft_fib_inet_type __पढ़ो_mostly = अणु
	.family		= NFPROTO_INET,
	.name		= "fib",
	.ops		= &nft_fib_inet_ops,
	.policy		= nft_fib_policy,
	.maxattr	= NFTA_FIB_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_fib_inet_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_fib_inet_type);
पूर्ण

अटल व्योम __निकास nft_fib_inet_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_fib_inet_type);
पूर्ण

module_init(nft_fib_inet_module_init);
module_निकास(nft_fib_inet_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Florian Westphal <fw@strlen.de>");
MODULE_ALIAS_NFT_AF_EXPR(1, "fib");
MODULE_DESCRIPTION("nftables fib inet support");
