<शैली गुरु>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter_bridge.h>
#समावेश <linux/netfilter_arp.h>
#समावेश <net/netfilter/nf_tables_ipv4.h>
#समावेश <net/netfilter/nf_tables_ipv6.h>

#अगर_घोषित CONFIG_NF_TABLES_IPV4
अटल अचिन्हित पूर्णांक nft_करो_chain_ipv4(व्योम *priv,
				      काष्ठा sk_buff *skb,
				      स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nft_pktinfo pkt;

	nft_set_pktinfo(&pkt, skb, state);
	nft_set_pktinfo_ipv4(&pkt, skb);

	वापस nft_करो_chain(&pkt, priv);
पूर्ण

अटल स्थिर काष्ठा nft_chain_type nft_chain_filter_ipv4 = अणु
	.name		= "filter",
	.type		= NFT_CHAIN_T_DEFAULT,
	.family		= NFPROTO_IPV4,
	.hook_mask	= (1 << NF_INET_LOCAL_IN) |
			  (1 << NF_INET_LOCAL_OUT) |
			  (1 << NF_INET_FORWARD) |
			  (1 << NF_INET_PRE_ROUTING) |
			  (1 << NF_INET_POST_ROUTING),
	.hooks		= अणु
		[NF_INET_LOCAL_IN]	= nft_करो_chain_ipv4,
		[NF_INET_LOCAL_OUT]	= nft_करो_chain_ipv4,
		[NF_INET_FORWARD]	= nft_करो_chain_ipv4,
		[NF_INET_PRE_ROUTING]	= nft_करो_chain_ipv4,
		[NF_INET_POST_ROUTING]	= nft_करो_chain_ipv4,
	पूर्ण,
पूर्ण;

अटल व्योम nft_chain_filter_ipv4_init(व्योम)
अणु
	nft_रेजिस्टर_chain_type(&nft_chain_filter_ipv4);
पूर्ण
अटल व्योम nft_chain_filter_ipv4_fini(व्योम)
अणु
	nft_unरेजिस्टर_chain_type(&nft_chain_filter_ipv4);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम nft_chain_filter_ipv4_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम nft_chain_filter_ipv4_fini(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_NF_TABLES_IPV4 */

#अगर_घोषित CONFIG_NF_TABLES_ARP
अटल अचिन्हित पूर्णांक nft_करो_chain_arp(व्योम *priv, काष्ठा sk_buff *skb,
				     स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nft_pktinfo pkt;

	nft_set_pktinfo(&pkt, skb, state);
	nft_set_pktinfo_unspec(&pkt, skb);

	वापस nft_करो_chain(&pkt, priv);
पूर्ण

अटल स्थिर काष्ठा nft_chain_type nft_chain_filter_arp = अणु
	.name		= "filter",
	.type		= NFT_CHAIN_T_DEFAULT,
	.family		= NFPROTO_ARP,
	.owner		= THIS_MODULE,
	.hook_mask	= (1 << NF_ARP_IN) |
			  (1 << NF_ARP_OUT),
	.hooks		= अणु
		[NF_ARP_IN]		= nft_करो_chain_arp,
		[NF_ARP_OUT]		= nft_करो_chain_arp,
	पूर्ण,
पूर्ण;

अटल व्योम nft_chain_filter_arp_init(व्योम)
अणु
	nft_रेजिस्टर_chain_type(&nft_chain_filter_arp);
पूर्ण

अटल व्योम nft_chain_filter_arp_fini(व्योम)
अणु
	nft_unरेजिस्टर_chain_type(&nft_chain_filter_arp);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम nft_chain_filter_arp_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम nft_chain_filter_arp_fini(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_NF_TABLES_ARP */

#अगर_घोषित CONFIG_NF_TABLES_IPV6
अटल अचिन्हित पूर्णांक nft_करो_chain_ipv6(व्योम *priv,
				      काष्ठा sk_buff *skb,
				      स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nft_pktinfo pkt;

	nft_set_pktinfo(&pkt, skb, state);
	nft_set_pktinfo_ipv6(&pkt, skb);

	वापस nft_करो_chain(&pkt, priv);
पूर्ण

अटल स्थिर काष्ठा nft_chain_type nft_chain_filter_ipv6 = अणु
	.name		= "filter",
	.type		= NFT_CHAIN_T_DEFAULT,
	.family		= NFPROTO_IPV6,
	.hook_mask	= (1 << NF_INET_LOCAL_IN) |
			  (1 << NF_INET_LOCAL_OUT) |
			  (1 << NF_INET_FORWARD) |
			  (1 << NF_INET_PRE_ROUTING) |
			  (1 << NF_INET_POST_ROUTING),
	.hooks		= अणु
		[NF_INET_LOCAL_IN]	= nft_करो_chain_ipv6,
		[NF_INET_LOCAL_OUT]	= nft_करो_chain_ipv6,
		[NF_INET_FORWARD]	= nft_करो_chain_ipv6,
		[NF_INET_PRE_ROUTING]	= nft_करो_chain_ipv6,
		[NF_INET_POST_ROUTING]	= nft_करो_chain_ipv6,
	पूर्ण,
पूर्ण;

अटल व्योम nft_chain_filter_ipv6_init(व्योम)
अणु
	nft_रेजिस्टर_chain_type(&nft_chain_filter_ipv6);
पूर्ण

अटल व्योम nft_chain_filter_ipv6_fini(व्योम)
अणु
	nft_unरेजिस्टर_chain_type(&nft_chain_filter_ipv6);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम nft_chain_filter_ipv6_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम nft_chain_filter_ipv6_fini(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_NF_TABLES_IPV6 */

#अगर_घोषित CONFIG_NF_TABLES_INET
अटल अचिन्हित पूर्णांक nft_करो_chain_inet(व्योम *priv, काष्ठा sk_buff *skb,
				      स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nft_pktinfo pkt;

	nft_set_pktinfo(&pkt, skb, state);

	चयन (state->pf) अणु
	हाल NFPROTO_IPV4:
		nft_set_pktinfo_ipv4(&pkt, skb);
		अवरोध;
	हाल NFPROTO_IPV6:
		nft_set_pktinfo_ipv6(&pkt, skb);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस nft_करो_chain(&pkt, priv);
पूर्ण

अटल अचिन्हित पूर्णांक nft_करो_chain_inet_ingress(व्योम *priv, काष्ठा sk_buff *skb,
					      स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nf_hook_state ingress_state = *state;
	काष्ठा nft_pktinfo pkt;

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		/* Original hook is NFPROTO_NETDEV and NF_NETDEV_INGRESS. */
		ingress_state.pf = NFPROTO_IPV4;
		ingress_state.hook = NF_INET_INGRESS;
		nft_set_pktinfo(&pkt, skb, &ingress_state);

		अगर (nft_set_pktinfo_ipv4_ingress(&pkt, skb) < 0)
			वापस NF_DROP;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		ingress_state.pf = NFPROTO_IPV6;
		ingress_state.hook = NF_INET_INGRESS;
		nft_set_pktinfo(&pkt, skb, &ingress_state);

		अगर (nft_set_pktinfo_ipv6_ingress(&pkt, skb) < 0)
			वापस NF_DROP;
		अवरोध;
	शेष:
		वापस NF_ACCEPT;
	पूर्ण

	वापस nft_करो_chain(&pkt, priv);
पूर्ण

अटल स्थिर काष्ठा nft_chain_type nft_chain_filter_inet = अणु
	.name		= "filter",
	.type		= NFT_CHAIN_T_DEFAULT,
	.family		= NFPROTO_INET,
	.hook_mask	= (1 << NF_INET_INGRESS) |
			  (1 << NF_INET_LOCAL_IN) |
			  (1 << NF_INET_LOCAL_OUT) |
			  (1 << NF_INET_FORWARD) |
			  (1 << NF_INET_PRE_ROUTING) |
			  (1 << NF_INET_POST_ROUTING),
	.hooks		= अणु
		[NF_INET_INGRESS]	= nft_करो_chain_inet_ingress,
		[NF_INET_LOCAL_IN]	= nft_करो_chain_inet,
		[NF_INET_LOCAL_OUT]	= nft_करो_chain_inet,
		[NF_INET_FORWARD]	= nft_करो_chain_inet,
		[NF_INET_PRE_ROUTING]	= nft_करो_chain_inet,
		[NF_INET_POST_ROUTING]	= nft_करो_chain_inet,
        पूर्ण,
पूर्ण;

अटल व्योम nft_chain_filter_inet_init(व्योम)
अणु
	nft_रेजिस्टर_chain_type(&nft_chain_filter_inet);
पूर्ण

अटल व्योम nft_chain_filter_inet_fini(व्योम)
अणु
	nft_unरेजिस्टर_chain_type(&nft_chain_filter_inet);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम nft_chain_filter_inet_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम nft_chain_filter_inet_fini(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_NF_TABLES_IPV6 */

#अगर IS_ENABLED(CONFIG_NF_TABLES_BRIDGE)
अटल अचिन्हित पूर्णांक
nft_करो_chain_bridge(व्योम *priv,
		    काष्ठा sk_buff *skb,
		    स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nft_pktinfo pkt;

	nft_set_pktinfo(&pkt, skb, state);

	चयन (eth_hdr(skb)->h_proto) अणु
	हाल htons(ETH_P_IP):
		nft_set_pktinfo_ipv4_validate(&pkt, skb);
		अवरोध;
	हाल htons(ETH_P_IPV6):
		nft_set_pktinfo_ipv6_validate(&pkt, skb);
		अवरोध;
	शेष:
		nft_set_pktinfo_unspec(&pkt, skb);
		अवरोध;
	पूर्ण

	वापस nft_करो_chain(&pkt, priv);
पूर्ण

अटल स्थिर काष्ठा nft_chain_type nft_chain_filter_bridge = अणु
	.name		= "filter",
	.type		= NFT_CHAIN_T_DEFAULT,
	.family		= NFPROTO_BRIDGE,
	.hook_mask	= (1 << NF_BR_PRE_ROUTING) |
			  (1 << NF_BR_LOCAL_IN) |
			  (1 << NF_BR_FORWARD) |
			  (1 << NF_BR_LOCAL_OUT) |
			  (1 << NF_BR_POST_ROUTING),
	.hooks		= अणु
		[NF_BR_PRE_ROUTING]	= nft_करो_chain_bridge,
		[NF_BR_LOCAL_IN]	= nft_करो_chain_bridge,
		[NF_BR_FORWARD]		= nft_करो_chain_bridge,
		[NF_BR_LOCAL_OUT]	= nft_करो_chain_bridge,
		[NF_BR_POST_ROUTING]	= nft_करो_chain_bridge,
	पूर्ण,
पूर्ण;

अटल व्योम nft_chain_filter_bridge_init(व्योम)
अणु
	nft_रेजिस्टर_chain_type(&nft_chain_filter_bridge);
पूर्ण

अटल व्योम nft_chain_filter_bridge_fini(व्योम)
अणु
	nft_unरेजिस्टर_chain_type(&nft_chain_filter_bridge);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम nft_chain_filter_bridge_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम nft_chain_filter_bridge_fini(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_NF_TABLES_BRIDGE */

#अगर_घोषित CONFIG_NF_TABLES_NETDEV
अटल अचिन्हित पूर्णांक nft_करो_chain_netdev(व्योम *priv, काष्ठा sk_buff *skb,
					स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nft_pktinfo pkt;

	nft_set_pktinfo(&pkt, skb, state);

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		nft_set_pktinfo_ipv4_validate(&pkt, skb);
		अवरोध;
	हाल htons(ETH_P_IPV6):
		nft_set_pktinfo_ipv6_validate(&pkt, skb);
		अवरोध;
	शेष:
		nft_set_pktinfo_unspec(&pkt, skb);
		अवरोध;
	पूर्ण

	वापस nft_करो_chain(&pkt, priv);
पूर्ण

अटल स्थिर काष्ठा nft_chain_type nft_chain_filter_netdev = अणु
	.name		= "filter",
	.type		= NFT_CHAIN_T_DEFAULT,
	.family		= NFPROTO_NETDEV,
	.hook_mask	= (1 << NF_NETDEV_INGRESS),
	.hooks		= अणु
		[NF_NETDEV_INGRESS]	= nft_करो_chain_netdev,
	पूर्ण,
पूर्ण;

अटल व्योम nft_netdev_event(अचिन्हित दीर्घ event, काष्ठा net_device *dev,
			     काष्ठा nft_ctx *ctx)
अणु
	काष्ठा nft_base_chain *basechain = nft_base_chain(ctx->chain);
	काष्ठा nft_hook *hook, *found = शून्य;
	पूर्णांक n = 0;

	अगर (event != NETDEV_UNREGISTER)
		वापस;

	list_क्रम_each_entry(hook, &basechain->hook_list, list) अणु
		अगर (hook->ops.dev == dev)
			found = hook;

		n++;
	पूर्ण
	अगर (!found)
		वापस;

	अगर (n > 1) अणु
		nf_unरेजिस्टर_net_hook(ctx->net, &found->ops);
		list_del_rcu(&found->list);
		kमुक्त_rcu(found, rcu);
		वापस;
	पूर्ण

	/* UNREGISTER events are also happening on netns निकास.
	 *
	 * Although nf_tables core releases all tables/chains, only this event
	 * handler provides guarantee that hook->ops.dev is still accessible,
	 * so we cannot skip निकासing net namespaces.
	 */
	__nft_release_basechain(ctx);
पूर्ण

अटल पूर्णांक nf_tables_netdev_event(काष्ठा notअगरier_block *this,
				  अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा nftables_pernet *nft_net;
	काष्ठा nft_table *table;
	काष्ठा nft_chain *chain, *nr;
	काष्ठा nft_ctx ctx = अणु
		.net	= dev_net(dev),
	पूर्ण;

	अगर (event != NETDEV_UNREGISTER &&
	    event != NETDEV_CHANGENAME)
		वापस NOTIFY_DONE;

	nft_net = nft_pernet(ctx.net);
	mutex_lock(&nft_net->commit_mutex);
	list_क्रम_each_entry(table, &nft_net->tables, list) अणु
		अगर (table->family != NFPROTO_NETDEV)
			जारी;

		ctx.family = table->family;
		ctx.table = table;
		list_क्रम_each_entry_safe(chain, nr, &table->chains, list) अणु
			अगर (!nft_is_base_chain(chain))
				जारी;

			ctx.chain = chain;
			nft_netdev_event(event, dev, &ctx);
		पूर्ण
	पूर्ण
	mutex_unlock(&nft_net->commit_mutex);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block nf_tables_netdev_notअगरier = अणु
	.notअगरier_call	= nf_tables_netdev_event,
पूर्ण;

अटल पूर्णांक nft_chain_filter_netdev_init(व्योम)
अणु
	पूर्णांक err;

	nft_रेजिस्टर_chain_type(&nft_chain_filter_netdev);

	err = रेजिस्टर_netdevice_notअगरier(&nf_tables_netdev_notअगरier);
	अगर (err)
		जाओ err_रेजिस्टर_netdevice_notअगरier;

	वापस 0;

err_रेजिस्टर_netdevice_notअगरier:
	nft_unरेजिस्टर_chain_type(&nft_chain_filter_netdev);

	वापस err;
पूर्ण

अटल व्योम nft_chain_filter_netdev_fini(व्योम)
अणु
	nft_unरेजिस्टर_chain_type(&nft_chain_filter_netdev);
	unरेजिस्टर_netdevice_notअगरier(&nf_tables_netdev_notअगरier);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक nft_chain_filter_netdev_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम nft_chain_filter_netdev_fini(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_NF_TABLES_NETDEV */

पूर्णांक __init nft_chain_filter_init(व्योम)
अणु
	पूर्णांक err;

	err = nft_chain_filter_netdev_init();
	अगर (err < 0)
		वापस err;

	nft_chain_filter_ipv4_init();
	nft_chain_filter_ipv6_init();
	nft_chain_filter_arp_init();
	nft_chain_filter_inet_init();
	nft_chain_filter_bridge_init();

	वापस 0;
पूर्ण

व्योम nft_chain_filter_fini(व्योम)
अणु
	nft_chain_filter_bridge_fini();
	nft_chain_filter_inet_fini();
	nft_chain_filter_arp_fini();
	nft_chain_filter_ipv6_fini();
	nft_chain_filter_ipv4_fini();
	nft_chain_filter_netdev_fini();
पूर्ण
