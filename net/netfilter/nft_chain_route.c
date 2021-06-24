<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_ipv4.h>
#समावेश <net/netfilter/nf_tables_ipv6.h>
#समावेश <net/route.h>
#समावेश <net/ip.h>

#अगर_घोषित CONFIG_NF_TABLES_IPV4
अटल अचिन्हित पूर्णांक nf_route_table_hook4(व्योम *priv,
					 काष्ठा sk_buff *skb,
					 स्थिर काष्ठा nf_hook_state *state)
अणु
	स्थिर काष्ठा iphdr *iph;
	काष्ठा nft_pktinfo pkt;
	__be32 saddr, daddr;
	अचिन्हित पूर्णांक ret;
	u32 mark;
	पूर्णांक err;
	u8 tos;

	nft_set_pktinfo(&pkt, skb, state);
	nft_set_pktinfo_ipv4(&pkt, skb);

	mark = skb->mark;
	iph = ip_hdr(skb);
	saddr = iph->saddr;
	daddr = iph->daddr;
	tos = iph->tos;

	ret = nft_करो_chain(&pkt, priv);
	अगर (ret == NF_ACCEPT) अणु
		iph = ip_hdr(skb);

		अगर (iph->saddr != saddr ||
		    iph->daddr != daddr ||
		    skb->mark != mark ||
		    iph->tos != tos) अणु
			err = ip_route_me_harder(state->net, state->sk, skb, RTN_UNSPEC);
			अगर (err < 0)
				ret = NF_DROP_ERR(err);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nft_chain_type nft_chain_route_ipv4 = अणु
	.name		= "route",
	.type		= NFT_CHAIN_T_ROUTE,
	.family		= NFPROTO_IPV4,
	.hook_mask	= (1 << NF_INET_LOCAL_OUT),
	.hooks		= अणु
		[NF_INET_LOCAL_OUT]	= nf_route_table_hook4,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_TABLES_IPV6
अटल अचिन्हित पूर्णांक nf_route_table_hook6(व्योम *priv,
					 काष्ठा sk_buff *skb,
					 स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा in6_addr saddr, daddr;
	काष्ठा nft_pktinfo pkt;
	u32 mark, flowlabel;
	अचिन्हित पूर्णांक ret;
	u8 hop_limit;
	पूर्णांक err;

	nft_set_pktinfo(&pkt, skb, state);
	nft_set_pktinfo_ipv6(&pkt, skb);

	/* save source/dest address, mark, hoplimit, flowlabel, priority */
	स_नकल(&saddr, &ipv6_hdr(skb)->saddr, माप(saddr));
	स_नकल(&daddr, &ipv6_hdr(skb)->daddr, माप(daddr));
	mark = skb->mark;
	hop_limit = ipv6_hdr(skb)->hop_limit;

	/* flowlabel and prio (includes version, which shouldn't change either)*/
	flowlabel = *((u32 *)ipv6_hdr(skb));

	ret = nft_करो_chain(&pkt, priv);
	अगर (ret == NF_ACCEPT &&
	    (स_भेद(&ipv6_hdr(skb)->saddr, &saddr, माप(saddr)) ||
	     स_भेद(&ipv6_hdr(skb)->daddr, &daddr, माप(daddr)) ||
	     skb->mark != mark ||
	     ipv6_hdr(skb)->hop_limit != hop_limit ||
	     flowlabel != *((u32 *)ipv6_hdr(skb)))) अणु
		err = nf_ip6_route_me_harder(state->net, state->sk, skb);
		अगर (err < 0)
			ret = NF_DROP_ERR(err);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nft_chain_type nft_chain_route_ipv6 = अणु
	.name		= "route",
	.type		= NFT_CHAIN_T_ROUTE,
	.family		= NFPROTO_IPV6,
	.hook_mask	= (1 << NF_INET_LOCAL_OUT),
	.hooks		= अणु
		[NF_INET_LOCAL_OUT]	= nf_route_table_hook6,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_TABLES_INET
अटल अचिन्हित पूर्णांक nf_route_table_inet(व्योम *priv,
					काष्ठा sk_buff *skb,
					स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nft_pktinfo pkt;

	चयन (state->pf) अणु
	हाल NFPROTO_IPV4:
		वापस nf_route_table_hook4(priv, skb, state);
	हाल NFPROTO_IPV6:
		वापस nf_route_table_hook6(priv, skb, state);
	शेष:
		nft_set_pktinfo(&pkt, skb, state);
		अवरोध;
	पूर्ण

	वापस nft_करो_chain(&pkt, priv);
पूर्ण

अटल स्थिर काष्ठा nft_chain_type nft_chain_route_inet = अणु
	.name		= "route",
	.type		= NFT_CHAIN_T_ROUTE,
	.family		= NFPROTO_INET,
	.hook_mask	= (1 << NF_INET_LOCAL_OUT),
	.hooks		= अणु
		[NF_INET_LOCAL_OUT]	= nf_route_table_inet,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

व्योम __init nft_chain_route_init(व्योम)
अणु
#अगर_घोषित CONFIG_NF_TABLES_IPV6
	nft_रेजिस्टर_chain_type(&nft_chain_route_ipv6);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_TABLES_IPV4
	nft_रेजिस्टर_chain_type(&nft_chain_route_ipv4);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_TABLES_INET
	nft_रेजिस्टर_chain_type(&nft_chain_route_inet);
#पूर्ण_अगर
पूर्ण

व्योम __निकास nft_chain_route_fini(व्योम)
अणु
#अगर_घोषित CONFIG_NF_TABLES_IPV6
	nft_unरेजिस्टर_chain_type(&nft_chain_route_ipv6);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_TABLES_IPV4
	nft_unरेजिस्टर_chain_type(&nft_chain_route_ipv4);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_TABLES_INET
	nft_unरेजिस्टर_chain_type(&nft_chain_route_inet);
#पूर्ण_अगर
पूर्ण
