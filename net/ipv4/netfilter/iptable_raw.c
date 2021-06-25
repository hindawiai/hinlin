<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 'raw' table, which is the very first hooked in at PRE_ROUTING and LOCAL_OUT .
 *
 * Copyright (C) 2003 Jozsef Kadlecsik <kadlec@netfilter.org>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/slab.h>
#समावेश <net/ip.h>

#घोषणा RAW_VALID_HOOKS ((1 << NF_INET_PRE_ROUTING) | (1 << NF_INET_LOCAL_OUT))

अटल पूर्णांक __net_init iptable_raw_table_init(काष्ठा net *net);

अटल bool raw_beक्रमe_defrag __पढ़ो_mostly;
MODULE_PARM_DESC(raw_beक्रमe_defrag, "Enable raw table before defrag");
module_param(raw_beक्रमe_defrag, bool, 0000);

अटल स्थिर काष्ठा xt_table packet_raw = अणु
	.name = "raw",
	.valid_hooks =  RAW_VALID_HOOKS,
	.me = THIS_MODULE,
	.af = NFPROTO_IPV4,
	.priority = NF_IP_PRI_RAW,
	.table_init = iptable_raw_table_init,
पूर्ण;

अटल स्थिर काष्ठा xt_table packet_raw_beक्रमe_defrag = अणु
	.name = "raw",
	.valid_hooks =  RAW_VALID_HOOKS,
	.me = THIS_MODULE,
	.af = NFPROTO_IPV4,
	.priority = NF_IP_PRI_RAW_BEFORE_DEFRAG,
	.table_init = iptable_raw_table_init,
पूर्ण;

/* The work comes in here from netfilter.c. */
अटल अचिन्हित पूर्णांक
iptable_raw_hook(व्योम *priv, काष्ठा sk_buff *skb,
		 स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस ipt_करो_table(skb, state, priv);
पूर्ण

अटल काष्ठा nf_hook_ops *rawtable_ops __पढ़ो_mostly;

अटल पूर्णांक __net_init iptable_raw_table_init(काष्ठा net *net)
अणु
	काष्ठा ipt_replace *repl;
	स्थिर काष्ठा xt_table *table = &packet_raw;
	पूर्णांक ret;

	अगर (raw_beक्रमe_defrag)
		table = &packet_raw_beक्रमe_defrag;

	repl = ipt_alloc_initial_table(table);
	अगर (repl == शून्य)
		वापस -ENOMEM;
	ret = ipt_रेजिस्टर_table(net, table, repl, rawtable_ops);
	kमुक्त(repl);
	वापस ret;
पूर्ण

अटल व्योम __net_निकास iptable_raw_net_pre_निकास(काष्ठा net *net)
अणु
	ipt_unरेजिस्टर_table_pre_निकास(net, "raw");
पूर्ण

अटल व्योम __net_निकास iptable_raw_net_निकास(काष्ठा net *net)
अणु
	ipt_unरेजिस्टर_table_निकास(net, "raw");
पूर्ण

अटल काष्ठा pernet_operations iptable_raw_net_ops = अणु
	.pre_निकास = iptable_raw_net_pre_निकास,
	.निकास = iptable_raw_net_निकास,
पूर्ण;

अटल पूर्णांक __init iptable_raw_init(व्योम)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा xt_table *table = &packet_raw;

	अगर (raw_beक्रमe_defrag) अणु
		table = &packet_raw_beक्रमe_defrag;

		pr_info("Enabling raw table before defrag\n");
	पूर्ण

	rawtable_ops = xt_hook_ops_alloc(table, iptable_raw_hook);
	अगर (IS_ERR(rawtable_ops))
		वापस PTR_ERR(rawtable_ops);

	ret = रेजिस्टर_pernet_subsys(&iptable_raw_net_ops);
	अगर (ret < 0) अणु
		kमुक्त(rawtable_ops);
		वापस ret;
	पूर्ण

	ret = iptable_raw_table_init(&init_net);
	अगर (ret) अणु
		unरेजिस्टर_pernet_subsys(&iptable_raw_net_ops);
		kमुक्त(rawtable_ops);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास iptable_raw_fini(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&iptable_raw_net_ops);
	kमुक्त(rawtable_ops);
पूर्ण

module_init(iptable_raw_init);
module_निकास(iptable_raw_fini);
MODULE_LICENSE("GPL");
