<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This is the 1999 reग_लिखो of IP Firewalling, aiming क्रम kernel 2.3.x.
 *
 * Copyright (C) 1999 Paul `Rusty' Russell & Michael J. Neuling
 * Copyright (C) 2000-2004 Netfilter Core Team <coreteam@netfilter.org>
 */
#समावेश <linux/module.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/route.h>
#समावेश <linux/ip.h>
#समावेश <net/ip.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Netfilter Core Team <coreteam@netfilter.org>");
MODULE_DESCRIPTION("iptables mangle table");

#घोषणा MANGLE_VALID_HOOKS ((1 << NF_INET_PRE_ROUTING) | \
			    (1 << NF_INET_LOCAL_IN) | \
			    (1 << NF_INET_FORWARD) | \
			    (1 << NF_INET_LOCAL_OUT) | \
			    (1 << NF_INET_POST_ROUTING))

अटल पूर्णांक __net_init iptable_mangle_table_init(काष्ठा net *net);

अटल स्थिर काष्ठा xt_table packet_mangler = अणु
	.name		= "mangle",
	.valid_hooks	= MANGLE_VALID_HOOKS,
	.me		= THIS_MODULE,
	.af		= NFPROTO_IPV4,
	.priority	= NF_IP_PRI_MANGLE,
	.table_init	= iptable_mangle_table_init,
पूर्ण;

अटल अचिन्हित पूर्णांक
ipt_mangle_out(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_hook_state *state, व्योम *priv)
अणु
	अचिन्हित पूर्णांक ret;
	स्थिर काष्ठा iphdr *iph;
	u_पूर्णांक8_t tos;
	__be32 saddr, daddr;
	u_पूर्णांक32_t mark;
	पूर्णांक err;

	/* Save things which could affect route */
	mark = skb->mark;
	iph = ip_hdr(skb);
	saddr = iph->saddr;
	daddr = iph->daddr;
	tos = iph->tos;

	ret = ipt_करो_table(skb, state, priv);
	/* Reroute क्रम ANY change. */
	अगर (ret != NF_DROP && ret != NF_STOLEN) अणु
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

/* The work comes in here from netfilter.c. */
अटल अचिन्हित पूर्णांक
iptable_mangle_hook(व्योम *priv,
		     काष्ठा sk_buff *skb,
		     स्थिर काष्ठा nf_hook_state *state)
अणु
	अगर (state->hook == NF_INET_LOCAL_OUT)
		वापस ipt_mangle_out(skb, state, priv);
	वापस ipt_करो_table(skb, state, priv);
पूर्ण

अटल काष्ठा nf_hook_ops *mangle_ops __पढ़ो_mostly;
अटल पूर्णांक __net_init iptable_mangle_table_init(काष्ठा net *net)
अणु
	काष्ठा ipt_replace *repl;
	पूर्णांक ret;

	repl = ipt_alloc_initial_table(&packet_mangler);
	अगर (repl == शून्य)
		वापस -ENOMEM;
	ret = ipt_रेजिस्टर_table(net, &packet_mangler, repl, mangle_ops);
	kमुक्त(repl);
	वापस ret;
पूर्ण

अटल व्योम __net_निकास iptable_mangle_net_pre_निकास(काष्ठा net *net)
अणु
	ipt_unरेजिस्टर_table_pre_निकास(net, "mangle");
पूर्ण

अटल व्योम __net_निकास iptable_mangle_net_निकास(काष्ठा net *net)
अणु
	ipt_unरेजिस्टर_table_निकास(net, "mangle");
पूर्ण

अटल काष्ठा pernet_operations iptable_mangle_net_ops = अणु
	.pre_निकास = iptable_mangle_net_pre_निकास,
	.निकास = iptable_mangle_net_निकास,
पूर्ण;

अटल पूर्णांक __init iptable_mangle_init(व्योम)
अणु
	पूर्णांक ret;

	mangle_ops = xt_hook_ops_alloc(&packet_mangler, iptable_mangle_hook);
	अगर (IS_ERR(mangle_ops)) अणु
		ret = PTR_ERR(mangle_ops);
		वापस ret;
	पूर्ण

	ret = रेजिस्टर_pernet_subsys(&iptable_mangle_net_ops);
	अगर (ret < 0) अणु
		kमुक्त(mangle_ops);
		वापस ret;
	पूर्ण

	ret = iptable_mangle_table_init(&init_net);
	अगर (ret) अणु
		unरेजिस्टर_pernet_subsys(&iptable_mangle_net_ops);
		kमुक्त(mangle_ops);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास iptable_mangle_fini(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&iptable_mangle_net_ops);
	kमुक्त(mangle_ops);
पूर्ण

module_init(iptable_mangle_init);
module_निकास(iptable_mangle_fini);
