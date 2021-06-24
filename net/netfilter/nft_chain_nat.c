<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/module.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_ipv4.h>
#समावेश <net/netfilter/nf_tables_ipv6.h>

अटल अचिन्हित पूर्णांक nft_nat_करो_chain(व्योम *priv, काष्ठा sk_buff *skb,
				     स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nft_pktinfo pkt;

	nft_set_pktinfo(&pkt, skb, state);

	चयन (state->pf) अणु
#अगर_घोषित CONFIG_NF_TABLES_IPV4
	हाल NFPROTO_IPV4:
		nft_set_pktinfo_ipv4(&pkt, skb);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_TABLES_IPV6
	हाल NFPROTO_IPV6:
		nft_set_pktinfo_ipv6(&pkt, skb);
		अवरोध;
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण

	वापस nft_करो_chain(&pkt, priv);
पूर्ण

#अगर_घोषित CONFIG_NF_TABLES_IPV4
अटल स्थिर काष्ठा nft_chain_type nft_chain_nat_ipv4 = अणु
	.name		= "nat",
	.type		= NFT_CHAIN_T_NAT,
	.family		= NFPROTO_IPV4,
	.owner		= THIS_MODULE,
	.hook_mask	= (1 << NF_INET_PRE_ROUTING) |
			  (1 << NF_INET_POST_ROUTING) |
			  (1 << NF_INET_LOCAL_OUT) |
			  (1 << NF_INET_LOCAL_IN),
	.hooks		= अणु
		[NF_INET_PRE_ROUTING]	= nft_nat_करो_chain,
		[NF_INET_POST_ROUTING]	= nft_nat_करो_chain,
		[NF_INET_LOCAL_OUT]	= nft_nat_करो_chain,
		[NF_INET_LOCAL_IN]	= nft_nat_करो_chain,
	पूर्ण,
	.ops_रेजिस्टर = nf_nat_ipv4_रेजिस्टर_fn,
	.ops_unरेजिस्टर = nf_nat_ipv4_unरेजिस्टर_fn,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_TABLES_IPV6
अटल स्थिर काष्ठा nft_chain_type nft_chain_nat_ipv6 = अणु
	.name		= "nat",
	.type		= NFT_CHAIN_T_NAT,
	.family		= NFPROTO_IPV6,
	.owner		= THIS_MODULE,
	.hook_mask	= (1 << NF_INET_PRE_ROUTING) |
			  (1 << NF_INET_POST_ROUTING) |
			  (1 << NF_INET_LOCAL_OUT) |
			  (1 << NF_INET_LOCAL_IN),
	.hooks		= अणु
		[NF_INET_PRE_ROUTING]	= nft_nat_करो_chain,
		[NF_INET_POST_ROUTING]	= nft_nat_करो_chain,
		[NF_INET_LOCAL_OUT]	= nft_nat_करो_chain,
		[NF_INET_LOCAL_IN]	= nft_nat_करो_chain,
	पूर्ण,
	.ops_रेजिस्टर		= nf_nat_ipv6_रेजिस्टर_fn,
	.ops_unरेजिस्टर		= nf_nat_ipv6_unरेजिस्टर_fn,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_TABLES_INET
अटल पूर्णांक nft_nat_inet_reg(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops)
अणु
	वापस nf_nat_inet_रेजिस्टर_fn(net, ops);
पूर्ण

अटल व्योम nft_nat_inet_unreg(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops)
अणु
	nf_nat_inet_unरेजिस्टर_fn(net, ops);
पूर्ण

अटल स्थिर काष्ठा nft_chain_type nft_chain_nat_inet = अणु
	.name		= "nat",
	.type		= NFT_CHAIN_T_NAT,
	.family		= NFPROTO_INET,
	.owner		= THIS_MODULE,
	.hook_mask	= (1 << NF_INET_PRE_ROUTING) |
			  (1 << NF_INET_LOCAL_IN) |
			  (1 << NF_INET_LOCAL_OUT) |
			  (1 << NF_INET_POST_ROUTING),
	.hooks		= अणु
		[NF_INET_PRE_ROUTING]	= nft_nat_करो_chain,
		[NF_INET_LOCAL_IN]	= nft_nat_करो_chain,
		[NF_INET_LOCAL_OUT]	= nft_nat_करो_chain,
		[NF_INET_POST_ROUTING]	= nft_nat_करो_chain,
	पूर्ण,
	.ops_रेजिस्टर		= nft_nat_inet_reg,
	.ops_unरेजिस्टर		= nft_nat_inet_unreg,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init nft_chain_nat_init(व्योम)
अणु
#अगर_घोषित CONFIG_NF_TABLES_IPV6
	nft_रेजिस्टर_chain_type(&nft_chain_nat_ipv6);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_TABLES_IPV4
	nft_रेजिस्टर_chain_type(&nft_chain_nat_ipv4);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_TABLES_INET
	nft_रेजिस्टर_chain_type(&nft_chain_nat_inet);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम __निकास nft_chain_nat_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_NF_TABLES_IPV4
	nft_unरेजिस्टर_chain_type(&nft_chain_nat_ipv4);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_TABLES_IPV6
	nft_unरेजिस्टर_chain_type(&nft_chain_nat_ipv6);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_TABLES_INET
	nft_unरेजिस्टर_chain_type(&nft_chain_nat_inet);
#पूर्ण_अगर
पूर्ण

module_init(nft_chain_nat_init);
module_निकास(nft_chain_nat_निकास);

MODULE_LICENSE("GPL");
#अगर_घोषित CONFIG_NF_TABLES_IPV4
MODULE_ALIAS_NFT_CHAIN(AF_INET, "nat");
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_TABLES_IPV6
MODULE_ALIAS_NFT_CHAIN(AF_INET6, "nat");
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_TABLES_INET
MODULE_ALIAS_NFT_CHAIN(1, "nat");	/* NFPROTO_INET */
#पूर्ण_अगर
