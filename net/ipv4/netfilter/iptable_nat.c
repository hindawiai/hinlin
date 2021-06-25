<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2006 Netfilter Core Team <coreteam@netfilter.org>
 * (C) 2011 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/ip.h>
#समावेश <net/ip.h>

#समावेश <net/netfilter/nf_nat.h>

काष्ठा iptable_nat_pernet अणु
	काष्ठा nf_hook_ops *nf_nat_ops;
पूर्ण;

अटल पूर्णांक __net_init iptable_nat_table_init(काष्ठा net *net);

अटल अचिन्हित पूर्णांक iptable_nat_net_id __पढ़ो_mostly;

अटल स्थिर काष्ठा xt_table nf_nat_ipv4_table = अणु
	.name		= "nat",
	.valid_hooks	= (1 << NF_INET_PRE_ROUTING) |
			  (1 << NF_INET_POST_ROUTING) |
			  (1 << NF_INET_LOCAL_OUT) |
			  (1 << NF_INET_LOCAL_IN),
	.me		= THIS_MODULE,
	.af		= NFPROTO_IPV4,
	.table_init	= iptable_nat_table_init,
पूर्ण;

अटल अचिन्हित पूर्णांक iptable_nat_करो_chain(व्योम *priv,
					 काष्ठा sk_buff *skb,
					 स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस ipt_करो_table(skb, state, priv);
पूर्ण

अटल स्थिर काष्ठा nf_hook_ops nf_nat_ipv4_ops[] = अणु
	अणु
		.hook		= iptable_nat_करो_chain,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_PRE_ROUTING,
		.priority	= NF_IP_PRI_NAT_DST,
	पूर्ण,
	अणु
		.hook		= iptable_nat_करो_chain,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_POST_ROUTING,
		.priority	= NF_IP_PRI_NAT_SRC,
	पूर्ण,
	अणु
		.hook		= iptable_nat_करो_chain,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_LOCAL_OUT,
		.priority	= NF_IP_PRI_NAT_DST,
	पूर्ण,
	अणु
		.hook		= iptable_nat_करो_chain,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_LOCAL_IN,
		.priority	= NF_IP_PRI_NAT_SRC,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ipt_nat_रेजिस्टर_lookups(काष्ठा net *net)
अणु
	काष्ठा iptable_nat_pernet *xt_nat_net;
	काष्ठा nf_hook_ops *ops;
	काष्ठा xt_table *table;
	पूर्णांक i, ret;

	xt_nat_net = net_generic(net, iptable_nat_net_id);
	table = xt_find_table(net, NFPROTO_IPV4, "nat");
	अगर (WARN_ON_ONCE(!table))
		वापस -ENOENT;

	ops = kmemdup(nf_nat_ipv4_ops, माप(nf_nat_ipv4_ops), GFP_KERNEL);
	अगर (!ops)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(nf_nat_ipv4_ops); i++) अणु
		ops[i].priv = table;
		ret = nf_nat_ipv4_रेजिस्टर_fn(net, &ops[i]);
		अगर (ret) अणु
			जबतक (i)
				nf_nat_ipv4_unरेजिस्टर_fn(net, &ops[--i]);

			kमुक्त(ops);
			वापस ret;
		पूर्ण
	पूर्ण

	xt_nat_net->nf_nat_ops = ops;
	वापस 0;
पूर्ण

अटल व्योम ipt_nat_unरेजिस्टर_lookups(काष्ठा net *net)
अणु
	काष्ठा iptable_nat_pernet *xt_nat_net = net_generic(net, iptable_nat_net_id);
	काष्ठा nf_hook_ops *ops = xt_nat_net->nf_nat_ops;
	पूर्णांक i;

	अगर (!ops)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(nf_nat_ipv4_ops); i++)
		nf_nat_ipv4_unरेजिस्टर_fn(net, &ops[i]);

	kमुक्त(ops);
पूर्ण

अटल पूर्णांक __net_init iptable_nat_table_init(काष्ठा net *net)
अणु
	काष्ठा ipt_replace *repl;
	पूर्णांक ret;

	repl = ipt_alloc_initial_table(&nf_nat_ipv4_table);
	अगर (repl == शून्य)
		वापस -ENOMEM;

	ret = ipt_रेजिस्टर_table(net, &nf_nat_ipv4_table, repl, शून्य);
	अगर (ret < 0) अणु
		kमुक्त(repl);
		वापस ret;
	पूर्ण

	ret = ipt_nat_रेजिस्टर_lookups(net);
	अगर (ret < 0)
		ipt_unरेजिस्टर_table_निकास(net, "nat");

	kमुक्त(repl);
	वापस ret;
पूर्ण

अटल व्योम __net_निकास iptable_nat_net_pre_निकास(काष्ठा net *net)
अणु
	ipt_nat_unरेजिस्टर_lookups(net);
पूर्ण

अटल व्योम __net_निकास iptable_nat_net_निकास(काष्ठा net *net)
अणु
	ipt_unरेजिस्टर_table_निकास(net, "nat");
पूर्ण

अटल काष्ठा pernet_operations iptable_nat_net_ops = अणु
	.pre_निकास = iptable_nat_net_pre_निकास,
	.निकास	= iptable_nat_net_निकास,
	.id	= &iptable_nat_net_id,
	.size	= माप(काष्ठा iptable_nat_pernet),
पूर्ण;

अटल पूर्णांक __init iptable_nat_init(व्योम)
अणु
	पूर्णांक ret = रेजिस्टर_pernet_subsys(&iptable_nat_net_ops);

	अगर (ret)
		वापस ret;

	ret = iptable_nat_table_init(&init_net);
	अगर (ret)
		unरेजिस्टर_pernet_subsys(&iptable_nat_net_ops);
	वापस ret;
पूर्ण

अटल व्योम __निकास iptable_nat_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&iptable_nat_net_ops);
पूर्ण

module_init(iptable_nat_init);
module_निकास(iptable_nat_निकास);

MODULE_LICENSE("GPL");
