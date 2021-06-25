<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ebtable_filter
 *
 *	Authors:
 *	Bart De Schuymer <bdschuym@panकरोra.be>
 *
 *  April, 2002
 *
 */

#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <uapi/linux/netfilter_bridge.h>
#समावेश <linux/module.h>

#घोषणा FILTER_VALID_HOOKS ((1 << NF_BR_LOCAL_IN) | (1 << NF_BR_FORWARD) | \
			    (1 << NF_BR_LOCAL_OUT))

अटल काष्ठा ebt_entries initial_chains[] = अणु
	अणु
		.name	= "INPUT",
		.policy	= EBT_ACCEPT,
	पूर्ण,
	अणु
		.name	= "FORWARD",
		.policy	= EBT_ACCEPT,
	पूर्ण,
	अणु
		.name	= "OUTPUT",
		.policy	= EBT_ACCEPT,
	पूर्ण,
पूर्ण;

अटल काष्ठा ebt_replace_kernel initial_table = अणु
	.name		= "filter",
	.valid_hooks	= FILTER_VALID_HOOKS,
	.entries_size	= 3 * माप(काष्ठा ebt_entries),
	.hook_entry	= अणु
		[NF_BR_LOCAL_IN]	= &initial_chains[0],
		[NF_BR_FORWARD]		= &initial_chains[1],
		[NF_BR_LOCAL_OUT]	= &initial_chains[2],
	पूर्ण,
	.entries	= (अक्षर *)initial_chains,
पूर्ण;

अटल पूर्णांक check(स्थिर काष्ठा ebt_table_info *info, अचिन्हित पूर्णांक valid_hooks)
अणु
	अगर (valid_hooks & ~FILTER_VALID_HOOKS)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ebt_table frame_filter = अणु
	.name		= "filter",
	.table		= &initial_table,
	.valid_hooks	= FILTER_VALID_HOOKS,
	.check		= check,
	.me		= THIS_MODULE,
पूर्ण;

अटल अचिन्हित पूर्णांक
ebt_filter_hook(व्योम *priv, काष्ठा sk_buff *skb,
		स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस ebt_करो_table(skb, state, priv);
पूर्ण

अटल स्थिर काष्ठा nf_hook_ops ebt_ops_filter[] = अणु
	अणु
		.hook		= ebt_filter_hook,
		.pf		= NFPROTO_BRIDGE,
		.hooknum	= NF_BR_LOCAL_IN,
		.priority	= NF_BR_PRI_FILTER_BRIDGED,
	पूर्ण,
	अणु
		.hook		= ebt_filter_hook,
		.pf		= NFPROTO_BRIDGE,
		.hooknum	= NF_BR_FORWARD,
		.priority	= NF_BR_PRI_FILTER_BRIDGED,
	पूर्ण,
	अणु
		.hook		= ebt_filter_hook,
		.pf		= NFPROTO_BRIDGE,
		.hooknum	= NF_BR_LOCAL_OUT,
		.priority	= NF_BR_PRI_FILTER_OTHER,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __net_init frame_filter_net_init(काष्ठा net *net)
अणु
	वापस ebt_रेजिस्टर_table(net, &frame_filter, ebt_ops_filter);
पूर्ण

अटल व्योम __net_निकास frame_filter_net_pre_निकास(काष्ठा net *net)
अणु
	ebt_unरेजिस्टर_table_pre_निकास(net, "filter");
पूर्ण

अटल व्योम __net_निकास frame_filter_net_निकास(काष्ठा net *net)
अणु
	ebt_unरेजिस्टर_table(net, "filter");
पूर्ण

अटल काष्ठा pernet_operations frame_filter_net_ops = अणु
	.init = frame_filter_net_init,
	.निकास = frame_filter_net_निकास,
	.pre_निकास = frame_filter_net_pre_निकास,
पूर्ण;

अटल पूर्णांक __init ebtable_filter_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&frame_filter_net_ops);
पूर्ण

अटल व्योम __निकास ebtable_filter_fini(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&frame_filter_net_ops);
पूर्ण

module_init(ebtable_filter_init);
module_निकास(ebtable_filter_fini);
MODULE_LICENSE("GPL");
