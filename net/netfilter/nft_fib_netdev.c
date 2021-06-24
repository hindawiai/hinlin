<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 Pablo M. Bermuकरो Garay <pablombg@gmail.com>
 *
 * This code is based on net/netfilter/nft_fib_inet.c, written by
 * Florian Westphal <fw@म_माप.de>.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/ipv6.h>

#समावेश <net/netfilter/nft_fib.h>

अटल व्योम nft_fib_netdev_eval(स्थिर काष्ठा nft_expr *expr,
				काष्ठा nft_regs *regs,
				स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_fib *priv = nft_expr_priv(expr);

	चयन (ntohs(pkt->skb->protocol)) अणु
	हाल ETH_P_IP:
		चयन (priv->result) अणु
		हाल NFT_FIB_RESULT_OIF:
		हाल NFT_FIB_RESULT_OIFNAME:
			वापस nft_fib4_eval(expr, regs, pkt);
		हाल NFT_FIB_RESULT_ADDRTYPE:
			वापस nft_fib4_eval_type(expr, regs, pkt);
		पूर्ण
		अवरोध;
	हाल ETH_P_IPV6:
		अगर (!ipv6_mod_enabled())
			अवरोध;
		चयन (priv->result) अणु
		हाल NFT_FIB_RESULT_OIF:
		हाल NFT_FIB_RESULT_OIFNAME:
			वापस nft_fib6_eval(expr, regs, pkt);
		हाल NFT_FIB_RESULT_ADDRTYPE:
			वापस nft_fib6_eval_type(expr, regs, pkt);
		पूर्ण
		अवरोध;
	पूर्ण

	regs->verdict.code = NFT_BREAK;
पूर्ण

अटल काष्ठा nft_expr_type nft_fib_netdev_type;
अटल स्थिर काष्ठा nft_expr_ops nft_fib_netdev_ops = अणु
	.type		= &nft_fib_netdev_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_fib)),
	.eval		= nft_fib_netdev_eval,
	.init		= nft_fib_init,
	.dump		= nft_fib_dump,
	.validate	= nft_fib_validate,
पूर्ण;

अटल काष्ठा nft_expr_type nft_fib_netdev_type __पढ़ो_mostly = अणु
	.family		= NFPROTO_NETDEV,
	.name		= "fib",
	.ops		= &nft_fib_netdev_ops,
	.policy		= nft_fib_policy,
	.maxattr	= NFTA_FIB_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_fib_netdev_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_fib_netdev_type);
पूर्ण

अटल व्योम __निकास nft_fib_netdev_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_fib_netdev_type);
पूर्ण

module_init(nft_fib_netdev_module_init);
module_निकास(nft_fib_netdev_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo M. Bermudo Garay <pablombg@gmail.com>");
MODULE_ALIAS_NFT_AF_EXPR(5, "fib");
MODULE_DESCRIPTION("nftables netdev fib lookups support");
