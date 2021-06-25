<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ebtable_nat
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

#घोषणा NAT_VALID_HOOKS ((1 << NF_BR_PRE_ROUTING) | (1 << NF_BR_LOCAL_OUT) | \
			 (1 << NF_BR_POST_ROUTING))

अटल काष्ठा ebt_entries initial_chains[] = अणु
	अणु
		.name	= "PREROUTING",
		.policy	= EBT_ACCEPT,
	पूर्ण,
	अणु
		.name	= "OUTPUT",
		.policy	= EBT_ACCEPT,
	पूर्ण,
	अणु
		.name	= "POSTROUTING",
		.policy	= EBT_ACCEPT,
	पूर्ण
पूर्ण;

अटल काष्ठा ebt_replace_kernel initial_table = अणु
	.name		= "nat",
	.valid_hooks	= NAT_VALID_HOOKS,
	.entries_size	= 3 * माप(काष्ठा ebt_entries),
	.hook_entry	= अणु
		[NF_BR_PRE_ROUTING]	= &initial_chains[0],
		[NF_BR_LOCAL_OUT]	= &initial_chains[1],
		[NF_BR_POST_ROUTING]	= &initial_chains[2],
	पूर्ण,
	.entries	= (अक्षर *)initial_chains,
पूर्ण;

अटल पूर्णांक check(स्थिर काष्ठा ebt_table_info *info, अचिन्हित पूर्णांक valid_hooks)
अणु
	अगर (valid_hooks & ~NAT_VALID_HOOKS)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ebt_table frame_nat = अणु
	.name		= "nat",
	.table		= &initial_table,
	.valid_hooks	= NAT_VALID_HOOKS,
	.check		= check,
	.me		= THIS_MODULE,
पूर्ण;

अटल अचिन्हित पूर्णांक ebt_nat_hook(व्योम *priv, काष्ठा sk_buff *skb,
				 स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस ebt_करो_table(skb, state, priv);
पूर्ण

अटल स्थिर काष्ठा nf_hook_ops ebt_ops_nat[] = अणु
	अणु
		.hook		= ebt_nat_hook,
		.pf		= NFPROTO_BRIDGE,
		.hooknum	= NF_BR_LOCAL_OUT,
		.priority	= NF_BR_PRI_NAT_DST_OTHER,
	पूर्ण,
	अणु
		.hook		= ebt_nat_hook,
		.pf		= NFPROTO_BRIDGE,
		.hooknum	= NF_BR_POST_ROUTING,
		.priority	= NF_BR_PRI_NAT_SRC,
	पूर्ण,
	अणु
		.hook		= ebt_nat_hook,
		.pf		= NFPROTO_BRIDGE,
		.hooknum	= NF_BR_PRE_ROUTING,
		.priority	= NF_BR_PRI_NAT_DST_BRIDGED,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __net_init frame_nat_net_init(काष्ठा net *net)
अणु
	वापस ebt_रेजिस्टर_table(net, &frame_nat, ebt_ops_nat);
पूर्ण

अटल व्योम __net_निकास frame_nat_net_pre_निकास(काष्ठा net *net)
अणु
	ebt_unरेजिस्टर_table_pre_निकास(net, "nat");
पूर्ण

अटल व्योम __net_निकास frame_nat_net_निकास(काष्ठा net *net)
अणु
	ebt_unरेजिस्टर_table(net, "nat");
पूर्ण

अटल काष्ठा pernet_operations frame_nat_net_ops = अणु
	.init = frame_nat_net_init,
	.निकास = frame_nat_net_निकास,
	.pre_निकास = frame_nat_net_pre_निकास,
पूर्ण;

अटल पूर्णांक __init ebtable_nat_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&frame_nat_net_ops);
पूर्ण

अटल व्योम __निकास ebtable_nat_fini(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&frame_nat_net_ops);
पूर्ण

module_init(ebtable_nat_init);
module_निकास(ebtable_nat_fini);
MODULE_LICENSE("GPL");
