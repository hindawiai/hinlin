<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Filtering ARP tables module.
 *
 * Copyright (C) 2002 David S. Miller (davem@redhat.com)
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_arp/arp_tables.h>
#समावेश <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David S. Miller <davem@redhat.com>");
MODULE_DESCRIPTION("arptables filter table");

#घोषणा FILTER_VALID_HOOKS ((1 << NF_ARP_IN) | (1 << NF_ARP_OUT) | \
			   (1 << NF_ARP_FORWARD))

अटल पूर्णांक __net_init arptable_filter_table_init(काष्ठा net *net);

अटल स्थिर काष्ठा xt_table packet_filter = अणु
	.name		= "filter",
	.valid_hooks	= FILTER_VALID_HOOKS,
	.me		= THIS_MODULE,
	.af		= NFPROTO_ARP,
	.priority	= NF_IP_PRI_FILTER,
	.table_init	= arptable_filter_table_init,
पूर्ण;

/* The work comes in here from netfilter.c */
अटल अचिन्हित पूर्णांक
arptable_filter_hook(व्योम *priv, काष्ठा sk_buff *skb,
		     स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस arpt_करो_table(skb, state, priv);
पूर्ण

अटल काष्ठा nf_hook_ops *arpfilter_ops __पढ़ो_mostly;

अटल पूर्णांक __net_init arptable_filter_table_init(काष्ठा net *net)
अणु
	काष्ठा arpt_replace *repl;
	पूर्णांक err;

	repl = arpt_alloc_initial_table(&packet_filter);
	अगर (repl == शून्य)
		वापस -ENOMEM;
	err = arpt_रेजिस्टर_table(net, &packet_filter, repl, arpfilter_ops);
	kमुक्त(repl);
	वापस err;
पूर्ण

अटल व्योम __net_निकास arptable_filter_net_pre_निकास(काष्ठा net *net)
अणु
	arpt_unरेजिस्टर_table_pre_निकास(net, "filter");
पूर्ण

अटल व्योम __net_निकास arptable_filter_net_निकास(काष्ठा net *net)
अणु
	arpt_unरेजिस्टर_table(net, "filter");
पूर्ण

अटल काष्ठा pernet_operations arptable_filter_net_ops = अणु
	.निकास = arptable_filter_net_निकास,
	.pre_निकास = arptable_filter_net_pre_निकास,
पूर्ण;

अटल पूर्णांक __init arptable_filter_init(व्योम)
अणु
	पूर्णांक ret;

	arpfilter_ops = xt_hook_ops_alloc(&packet_filter, arptable_filter_hook);
	अगर (IS_ERR(arpfilter_ops))
		वापस PTR_ERR(arpfilter_ops);

	ret = रेजिस्टर_pernet_subsys(&arptable_filter_net_ops);
	अगर (ret < 0) अणु
		kमुक्त(arpfilter_ops);
		वापस ret;
	पूर्ण

	ret = arptable_filter_table_init(&init_net);
	अगर (ret) अणु
		unरेजिस्टर_pernet_subsys(&arptable_filter_net_ops);
		kमुक्त(arpfilter_ops);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास arptable_filter_fini(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&arptable_filter_net_ops);
	kमुक्त(arpfilter_ops);
पूर्ण

module_init(arptable_filter_init);
module_निकास(arptable_filter_fini);
