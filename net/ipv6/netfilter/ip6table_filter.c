<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This is the 1999 reग_लिखो of IP Firewalling, aiming क्रम kernel 2.3.x.
 *
 * Copyright (C) 1999 Paul `Rusty' Russell & Michael J. Neuling
 * Copyright (C) 2000-2004 Netfilter Core Team <coreteam@netfilter.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Netfilter Core Team <coreteam@netfilter.org>");
MODULE_DESCRIPTION("ip6tables filter table");

#घोषणा FILTER_VALID_HOOKS ((1 << NF_INET_LOCAL_IN) | \
			    (1 << NF_INET_FORWARD) | \
			    (1 << NF_INET_LOCAL_OUT))

अटल पूर्णांक __net_init ip6table_filter_table_init(काष्ठा net *net);

अटल स्थिर काष्ठा xt_table packet_filter = अणु
	.name		= "filter",
	.valid_hooks	= FILTER_VALID_HOOKS,
	.me		= THIS_MODULE,
	.af		= NFPROTO_IPV6,
	.priority	= NF_IP6_PRI_FILTER,
	.table_init	= ip6table_filter_table_init,
पूर्ण;

/* The work comes in here from netfilter.c. */
अटल अचिन्हित पूर्णांक
ip6table_filter_hook(व्योम *priv, काष्ठा sk_buff *skb,
		     स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस ip6t_करो_table(skb, state, priv);
पूर्ण

अटल काष्ठा nf_hook_ops *filter_ops __पढ़ो_mostly;

/* Default to क्रमward because I got too much mail alपढ़ोy. */
अटल bool क्रमward = true;
module_param(क्रमward, bool, 0000);

अटल पूर्णांक __net_init ip6table_filter_table_init(काष्ठा net *net)
अणु
	काष्ठा ip6t_replace *repl;
	पूर्णांक err;

	repl = ip6t_alloc_initial_table(&packet_filter);
	अगर (repl == शून्य)
		वापस -ENOMEM;
	/* Entry 1 is the FORWARD hook */
	((काष्ठा ip6t_standard *)repl->entries)[1].target.verdict =
		क्रमward ? -NF_ACCEPT - 1 : -NF_DROP - 1;

	err = ip6t_रेजिस्टर_table(net, &packet_filter, repl, filter_ops);
	kमुक्त(repl);
	वापस err;
पूर्ण

अटल पूर्णांक __net_init ip6table_filter_net_init(काष्ठा net *net)
अणु
	अगर (net == &init_net || !क्रमward)
		वापस ip6table_filter_table_init(net);

	वापस 0;
पूर्ण

अटल व्योम __net_निकास ip6table_filter_net_pre_निकास(काष्ठा net *net)
अणु
	ip6t_unरेजिस्टर_table_pre_निकास(net, "filter");
पूर्ण

अटल व्योम __net_निकास ip6table_filter_net_निकास(काष्ठा net *net)
अणु
	ip6t_unरेजिस्टर_table_निकास(net, "filter");
पूर्ण

अटल काष्ठा pernet_operations ip6table_filter_net_ops = अणु
	.init = ip6table_filter_net_init,
	.pre_निकास = ip6table_filter_net_pre_निकास,
	.निकास = ip6table_filter_net_निकास,
पूर्ण;

अटल पूर्णांक __init ip6table_filter_init(व्योम)
अणु
	पूर्णांक ret;

	filter_ops = xt_hook_ops_alloc(&packet_filter, ip6table_filter_hook);
	अगर (IS_ERR(filter_ops))
		वापस PTR_ERR(filter_ops);

	ret = रेजिस्टर_pernet_subsys(&ip6table_filter_net_ops);
	अगर (ret < 0)
		kमुक्त(filter_ops);

	वापस ret;
पूर्ण

अटल व्योम __निकास ip6table_filter_fini(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&ip6table_filter_net_ops);
	kमुक्त(filter_ops);
पूर्ण

module_init(ip6table_filter_init);
module_निकास(ip6table_filter_fini);
