<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IPv6 raw table, a port of the IPv4 raw table to IPv6
 *
 * Copyright (C) 2003 Jozsef Kadlecsik <kadlec@netfilter.org>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <linux/slab.h>

#घोषणा RAW_VALID_HOOKS ((1 << NF_INET_PRE_ROUTING) | (1 << NF_INET_LOCAL_OUT))

अटल पूर्णांक __net_init ip6table_raw_table_init(काष्ठा net *net);

अटल bool raw_beक्रमe_defrag __पढ़ो_mostly;
MODULE_PARM_DESC(raw_beक्रमe_defrag, "Enable raw table before defrag");
module_param(raw_beक्रमe_defrag, bool, 0000);

अटल स्थिर काष्ठा xt_table packet_raw = अणु
	.name = "raw",
	.valid_hooks = RAW_VALID_HOOKS,
	.me = THIS_MODULE,
	.af = NFPROTO_IPV6,
	.priority = NF_IP6_PRI_RAW,
	.table_init = ip6table_raw_table_init,
पूर्ण;

अटल स्थिर काष्ठा xt_table packet_raw_beक्रमe_defrag = अणु
	.name = "raw",
	.valid_hooks = RAW_VALID_HOOKS,
	.me = THIS_MODULE,
	.af = NFPROTO_IPV6,
	.priority = NF_IP6_PRI_RAW_BEFORE_DEFRAG,
	.table_init = ip6table_raw_table_init,
पूर्ण;

/* The work comes in here from netfilter.c. */
अटल अचिन्हित पूर्णांक
ip6table_raw_hook(व्योम *priv, काष्ठा sk_buff *skb,
		  स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस ip6t_करो_table(skb, state, priv);
पूर्ण

अटल काष्ठा nf_hook_ops *rawtable_ops __पढ़ो_mostly;

अटल पूर्णांक __net_init ip6table_raw_table_init(काष्ठा net *net)
अणु
	काष्ठा ip6t_replace *repl;
	स्थिर काष्ठा xt_table *table = &packet_raw;
	पूर्णांक ret;

	अगर (raw_beक्रमe_defrag)
		table = &packet_raw_beक्रमe_defrag;

	repl = ip6t_alloc_initial_table(table);
	अगर (repl == शून्य)
		वापस -ENOMEM;
	ret = ip6t_रेजिस्टर_table(net, table, repl, rawtable_ops);
	kमुक्त(repl);
	वापस ret;
पूर्ण

अटल व्योम __net_निकास ip6table_raw_net_pre_निकास(काष्ठा net *net)
अणु
	ip6t_unरेजिस्टर_table_pre_निकास(net, "raw");
पूर्ण

अटल व्योम __net_निकास ip6table_raw_net_निकास(काष्ठा net *net)
अणु
	ip6t_unरेजिस्टर_table_निकास(net, "raw");
पूर्ण

अटल काष्ठा pernet_operations ip6table_raw_net_ops = अणु
	.pre_निकास = ip6table_raw_net_pre_निकास,
	.निकास = ip6table_raw_net_निकास,
पूर्ण;

अटल पूर्णांक __init ip6table_raw_init(व्योम)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा xt_table *table = &packet_raw;

	अगर (raw_beक्रमe_defrag) अणु
		table = &packet_raw_beक्रमe_defrag;

		pr_info("Enabling raw table before defrag\n");
	पूर्ण

	/* Register hooks */
	rawtable_ops = xt_hook_ops_alloc(table, ip6table_raw_hook);
	अगर (IS_ERR(rawtable_ops))
		वापस PTR_ERR(rawtable_ops);

	ret = रेजिस्टर_pernet_subsys(&ip6table_raw_net_ops);
	अगर (ret < 0) अणु
		kमुक्त(rawtable_ops);
		वापस ret;
	पूर्ण

	ret = ip6table_raw_table_init(&init_net);
	अगर (ret) अणु
		unरेजिस्टर_pernet_subsys(&ip6table_raw_net_ops);
		kमुक्त(rawtable_ops);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __निकास ip6table_raw_fini(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&ip6table_raw_net_ops);
	kमुक्त(rawtable_ops);
पूर्ण

module_init(ip6table_raw_init);
module_निकास(ip6table_raw_fini);
MODULE_LICENSE("GPL");
