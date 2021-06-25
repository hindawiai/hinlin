<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011 Patrick McHardy <kaber@trash.net>
 *
 * Based on Rusty Russell's IPv4 NAT code. Development of IPv6 NAT
 * funded by Astaro.
 */

#समावेश <linux/module.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ipv6.h>

#समावेश <net/netfilter/nf_nat.h>

काष्ठा ip6table_nat_pernet अणु
	काष्ठा nf_hook_ops *nf_nat_ops;
पूर्ण;

अटल पूर्णांक __net_init ip6table_nat_table_init(काष्ठा net *net);

अटल अचिन्हित पूर्णांक ip6table_nat_net_id __पढ़ो_mostly;

अटल स्थिर काष्ठा xt_table nf_nat_ipv6_table = अणु
	.name		= "nat",
	.valid_hooks	= (1 << NF_INET_PRE_ROUTING) |
			  (1 << NF_INET_POST_ROUTING) |
			  (1 << NF_INET_LOCAL_OUT) |
			  (1 << NF_INET_LOCAL_IN),
	.me		= THIS_MODULE,
	.af		= NFPROTO_IPV6,
	.table_init	= ip6table_nat_table_init,
पूर्ण;

अटल अचिन्हित पूर्णांक ip6table_nat_करो_chain(व्योम *priv,
					  काष्ठा sk_buff *skb,
					  स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस ip6t_करो_table(skb, state, priv);
पूर्ण

अटल स्थिर काष्ठा nf_hook_ops nf_nat_ipv6_ops[] = अणु
	अणु
		.hook		= ip6table_nat_करो_chain,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_PRE_ROUTING,
		.priority	= NF_IP6_PRI_NAT_DST,
	पूर्ण,
	अणु
		.hook		= ip6table_nat_करो_chain,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_POST_ROUTING,
		.priority	= NF_IP6_PRI_NAT_SRC,
	पूर्ण,
	अणु
		.hook		= ip6table_nat_करो_chain,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_LOCAL_OUT,
		.priority	= NF_IP6_PRI_NAT_DST,
	पूर्ण,
	अणु
		.hook		= ip6table_nat_करो_chain,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_LOCAL_IN,
		.priority	= NF_IP6_PRI_NAT_SRC,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ip6t_nat_रेजिस्टर_lookups(काष्ठा net *net)
अणु
	काष्ठा ip6table_nat_pernet *xt_nat_net;
	काष्ठा nf_hook_ops *ops;
	काष्ठा xt_table *table;
	पूर्णांक i, ret;

	table = xt_find_table(net, NFPROTO_IPV6, "nat");
	अगर (WARN_ON_ONCE(!table))
		वापस -ENOENT;

	xt_nat_net = net_generic(net, ip6table_nat_net_id);
	ops = kmemdup(nf_nat_ipv6_ops, माप(nf_nat_ipv6_ops), GFP_KERNEL);
	अगर (!ops)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(nf_nat_ipv6_ops); i++) अणु
		ops[i].priv = table;
		ret = nf_nat_ipv6_रेजिस्टर_fn(net, &ops[i]);
		अगर (ret) अणु
			जबतक (i)
				nf_nat_ipv6_unरेजिस्टर_fn(net, &ops[--i]);

			kमुक्त(ops);
			वापस ret;
		पूर्ण
	पूर्ण

	xt_nat_net->nf_nat_ops = ops;
	वापस 0;
पूर्ण

अटल व्योम ip6t_nat_unरेजिस्टर_lookups(काष्ठा net *net)
अणु
	काष्ठा ip6table_nat_pernet *xt_nat_net = net_generic(net, ip6table_nat_net_id);
	काष्ठा nf_hook_ops *ops = xt_nat_net->nf_nat_ops;
	पूर्णांक i;

	अगर (!ops)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(nf_nat_ipv6_ops); i++)
		nf_nat_ipv6_unरेजिस्टर_fn(net, &ops[i]);

	kमुक्त(ops);
पूर्ण

अटल पूर्णांक __net_init ip6table_nat_table_init(काष्ठा net *net)
अणु
	काष्ठा ip6t_replace *repl;
	पूर्णांक ret;

	repl = ip6t_alloc_initial_table(&nf_nat_ipv6_table);
	अगर (repl == शून्य)
		वापस -ENOMEM;
	ret = ip6t_रेजिस्टर_table(net, &nf_nat_ipv6_table, repl,
				  शून्य);
	अगर (ret < 0) अणु
		kमुक्त(repl);
		वापस ret;
	पूर्ण

	ret = ip6t_nat_रेजिस्टर_lookups(net);
	अगर (ret < 0)
		ip6t_unरेजिस्टर_table_निकास(net, "nat");

	kमुक्त(repl);
	वापस ret;
पूर्ण

अटल व्योम __net_निकास ip6table_nat_net_pre_निकास(काष्ठा net *net)
अणु
	ip6t_nat_unरेजिस्टर_lookups(net);
पूर्ण

अटल व्योम __net_निकास ip6table_nat_net_निकास(काष्ठा net *net)
अणु
	ip6t_unरेजिस्टर_table_निकास(net, "nat");
पूर्ण

अटल काष्ठा pernet_operations ip6table_nat_net_ops = अणु
	.pre_निकास = ip6table_nat_net_pre_निकास,
	.निकास	= ip6table_nat_net_निकास,
	.id	= &ip6table_nat_net_id,
	.size	= माप(काष्ठा ip6table_nat_pernet),
पूर्ण;

अटल पूर्णांक __init ip6table_nat_init(व्योम)
अणु
	पूर्णांक ret = रेजिस्टर_pernet_subsys(&ip6table_nat_net_ops);

	अगर (ret)
		वापस ret;

	ret = ip6table_nat_table_init(&init_net);
	अगर (ret)
		unरेजिस्टर_pernet_subsys(&ip6table_nat_net_ops);
	वापस ret;
पूर्ण

अटल व्योम __निकास ip6table_nat_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&ip6table_nat_net_ops);
पूर्ण

module_init(ip6table_nat_init);
module_निकास(ip6table_nat_निकास);

MODULE_LICENSE("GPL");
