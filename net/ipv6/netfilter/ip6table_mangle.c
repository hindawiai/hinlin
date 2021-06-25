<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IPv6 packet mangling table, a port of the IPv4 mangle table to IPv6
 *
 * Copyright (C) 2000-2001 by Harald Welte <laक्रमge@gnumonks.org>
 * Copyright (C) 2000-2004 Netfilter Core Team <coreteam@netfilter.org>
 */
#समावेश <linux/module.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <linux/slab.h>
#समावेश <net/ipv6.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Netfilter Core Team <coreteam@netfilter.org>");
MODULE_DESCRIPTION("ip6tables mangle table");

#घोषणा MANGLE_VALID_HOOKS ((1 << NF_INET_PRE_ROUTING) | \
			    (1 << NF_INET_LOCAL_IN) | \
			    (1 << NF_INET_FORWARD) | \
			    (1 << NF_INET_LOCAL_OUT) | \
			    (1 << NF_INET_POST_ROUTING))

अटल पूर्णांक __net_init ip6table_mangle_table_init(काष्ठा net *net);

अटल स्थिर काष्ठा xt_table packet_mangler = अणु
	.name		= "mangle",
	.valid_hooks	= MANGLE_VALID_HOOKS,
	.me		= THIS_MODULE,
	.af		= NFPROTO_IPV6,
	.priority	= NF_IP6_PRI_MANGLE,
	.table_init	= ip6table_mangle_table_init,
पूर्ण;

अटल अचिन्हित पूर्णांक
ip6t_mangle_out(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_hook_state *state, व्योम *priv)
अणु
	अचिन्हित पूर्णांक ret;
	काष्ठा in6_addr saddr, daddr;
	u_पूर्णांक8_t hop_limit;
	u_पूर्णांक32_t flowlabel, mark;
	पूर्णांक err;

	/* save source/dest address, mark, hoplimit, flowlabel, priority,  */
	स_नकल(&saddr, &ipv6_hdr(skb)->saddr, माप(saddr));
	स_नकल(&daddr, &ipv6_hdr(skb)->daddr, माप(daddr));
	mark = skb->mark;
	hop_limit = ipv6_hdr(skb)->hop_limit;

	/* flowlabel and prio (includes version, which shouldn't change either */
	flowlabel = *((u_पूर्णांक32_t *)ipv6_hdr(skb));

	ret = ip6t_करो_table(skb, state, priv);

	अगर (ret != NF_DROP && ret != NF_STOLEN &&
	    (!ipv6_addr_equal(&ipv6_hdr(skb)->saddr, &saddr) ||
	     !ipv6_addr_equal(&ipv6_hdr(skb)->daddr, &daddr) ||
	     skb->mark != mark ||
	     ipv6_hdr(skb)->hop_limit != hop_limit ||
	     flowlabel != *((u_पूर्णांक32_t *)ipv6_hdr(skb)))) अणु
		err = ip6_route_me_harder(state->net, state->sk, skb);
		अगर (err < 0)
			ret = NF_DROP_ERR(err);
	पूर्ण

	वापस ret;
पूर्ण

/* The work comes in here from netfilter.c. */
अटल अचिन्हित पूर्णांक
ip6table_mangle_hook(व्योम *priv, काष्ठा sk_buff *skb,
		     स्थिर काष्ठा nf_hook_state *state)
अणु
	अगर (state->hook == NF_INET_LOCAL_OUT)
		वापस ip6t_mangle_out(skb, state, priv);
	वापस ip6t_करो_table(skb, state, priv);
पूर्ण

अटल काष्ठा nf_hook_ops *mangle_ops __पढ़ो_mostly;
अटल पूर्णांक __net_init ip6table_mangle_table_init(काष्ठा net *net)
अणु
	काष्ठा ip6t_replace *repl;
	पूर्णांक ret;

	repl = ip6t_alloc_initial_table(&packet_mangler);
	अगर (repl == शून्य)
		वापस -ENOMEM;
	ret = ip6t_रेजिस्टर_table(net, &packet_mangler, repl, mangle_ops);
	kमुक्त(repl);
	वापस ret;
पूर्ण

अटल व्योम __net_निकास ip6table_mangle_net_pre_निकास(काष्ठा net *net)
अणु
	ip6t_unरेजिस्टर_table_pre_निकास(net, "mangle");
पूर्ण

अटल व्योम __net_निकास ip6table_mangle_net_निकास(काष्ठा net *net)
अणु
	ip6t_unरेजिस्टर_table_निकास(net, "mangle");
पूर्ण

अटल काष्ठा pernet_operations ip6table_mangle_net_ops = अणु
	.pre_निकास = ip6table_mangle_net_pre_निकास,
	.निकास = ip6table_mangle_net_निकास,
पूर्ण;

अटल पूर्णांक __init ip6table_mangle_init(व्योम)
अणु
	पूर्णांक ret;

	mangle_ops = xt_hook_ops_alloc(&packet_mangler, ip6table_mangle_hook);
	अगर (IS_ERR(mangle_ops))
		वापस PTR_ERR(mangle_ops);

	ret = रेजिस्टर_pernet_subsys(&ip6table_mangle_net_ops);
	अगर (ret < 0) अणु
		kमुक्त(mangle_ops);
		वापस ret;
	पूर्ण

	ret = ip6table_mangle_table_init(&init_net);
	अगर (ret) अणु
		unरेजिस्टर_pernet_subsys(&ip6table_mangle_net_ops);
		kमुक्त(mangle_ops);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __निकास ip6table_mangle_fini(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&ip6table_mangle_net_ops);
	kमुक्त(mangle_ops);
पूर्ण

module_init(ip6table_mangle_init);
module_निकास(ip6table_mangle_fini);
