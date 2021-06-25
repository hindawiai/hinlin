<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * "security" table क्रम IPv6
 *
 * This is क्रम use by Mandatory Access Control (MAC) security models,
 * which need to be able to manage security policy in separate context
 * to DAC.
 *
 * Based on iptable_mangle.c
 *
 * Copyright (C) 1999 Paul `Rusty' Russell & Michael J. Neuling
 * Copyright (C) 2000-2004 Netfilter Core Team <coreteam <at> netfilter.org>
 * Copyright (C) 2008 Red Hat, Inc., James Morris <jmorris <at> redhat.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("James Morris <jmorris <at> redhat.com>");
MODULE_DESCRIPTION("ip6tables security table, for MAC rules");

#घोषणा SECURITY_VALID_HOOKS	(1 << NF_INET_LOCAL_IN) | \
				(1 << NF_INET_FORWARD) | \
				(1 << NF_INET_LOCAL_OUT)

अटल पूर्णांक __net_init ip6table_security_table_init(काष्ठा net *net);

अटल स्थिर काष्ठा xt_table security_table = अणु
	.name		= "security",
	.valid_hooks	= SECURITY_VALID_HOOKS,
	.me		= THIS_MODULE,
	.af		= NFPROTO_IPV6,
	.priority	= NF_IP6_PRI_SECURITY,
	.table_init     = ip6table_security_table_init,
पूर्ण;

अटल अचिन्हित पूर्णांक
ip6table_security_hook(व्योम *priv, काष्ठा sk_buff *skb,
		       स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस ip6t_करो_table(skb, state, priv);
पूर्ण

अटल काष्ठा nf_hook_ops *sectbl_ops __पढ़ो_mostly;

अटल पूर्णांक __net_init ip6table_security_table_init(काष्ठा net *net)
अणु
	काष्ठा ip6t_replace *repl;
	पूर्णांक ret;

	repl = ip6t_alloc_initial_table(&security_table);
	अगर (repl == शून्य)
		वापस -ENOMEM;
	ret = ip6t_रेजिस्टर_table(net, &security_table, repl, sectbl_ops);
	kमुक्त(repl);
	वापस ret;
पूर्ण

अटल व्योम __net_निकास ip6table_security_net_pre_निकास(काष्ठा net *net)
अणु
	ip6t_unरेजिस्टर_table_pre_निकास(net, "security");
पूर्ण

अटल व्योम __net_निकास ip6table_security_net_निकास(काष्ठा net *net)
अणु
	ip6t_unरेजिस्टर_table_निकास(net, "security");
पूर्ण

अटल काष्ठा pernet_operations ip6table_security_net_ops = अणु
	.pre_निकास = ip6table_security_net_pre_निकास,
	.निकास = ip6table_security_net_निकास,
पूर्ण;

अटल पूर्णांक __init ip6table_security_init(व्योम)
अणु
	पूर्णांक ret;

	sectbl_ops = xt_hook_ops_alloc(&security_table, ip6table_security_hook);
	अगर (IS_ERR(sectbl_ops))
		वापस PTR_ERR(sectbl_ops);

	ret = रेजिस्टर_pernet_subsys(&ip6table_security_net_ops);
	अगर (ret < 0) अणु
		kमुक्त(sectbl_ops);
		वापस ret;
	पूर्ण

	ret = ip6table_security_table_init(&init_net);
	अगर (ret) अणु
		unरेजिस्टर_pernet_subsys(&ip6table_security_net_ops);
		kमुक्त(sectbl_ops);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __निकास ip6table_security_fini(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&ip6table_security_net_ops);
	kमुक्त(sectbl_ops);
पूर्ण

module_init(ip6table_security_init);
module_निकास(ip6table_security_fini);
