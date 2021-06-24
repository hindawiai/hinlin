<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ebtable_broute
 *
 *	Authors:
 *	Bart De Schuymer <bdschuym@panकरोra.be>
 *
 *  April, 2002
 *
 *  This table lets you choose between routing and bridging क्रम frames
 *  entering on a bridge enslaved nic. This table is traversed beक्रमe any
 *  other ebtables table. See net/bridge/br_input.c.
 */

#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/module.h>
#समावेश <linux/अगर_bridge.h>

#समावेश "../br_private.h"

/* EBT_ACCEPT means the frame will be bridged
 * EBT_DROP means the frame will be routed
 */
अटल काष्ठा ebt_entries initial_chain = अणु
	.name		= "BROUTING",
	.policy		= EBT_ACCEPT,
पूर्ण;

अटल काष्ठा ebt_replace_kernel initial_table = अणु
	.name		= "broute",
	.valid_hooks	= 1 << NF_BR_BROUTING,
	.entries_size	= माप(काष्ठा ebt_entries),
	.hook_entry	= अणु
		[NF_BR_BROUTING]	= &initial_chain,
	पूर्ण,
	.entries	= (अक्षर *)&initial_chain,
पूर्ण;

अटल पूर्णांक check(स्थिर काष्ठा ebt_table_info *info, अचिन्हित पूर्णांक valid_hooks)
अणु
	अगर (valid_hooks & ~(1 << NF_BR_BROUTING))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ebt_table broute_table = अणु
	.name		= "broute",
	.table		= &initial_table,
	.valid_hooks	= 1 << NF_BR_BROUTING,
	.check		= check,
	.me		= THIS_MODULE,
पूर्ण;

अटल अचिन्हित पूर्णांक ebt_broute(व्योम *priv, काष्ठा sk_buff *skb,
			       स्थिर काष्ठा nf_hook_state *s)
अणु
	काष्ठा net_bridge_port *p = br_port_get_rcu(skb->dev);
	काष्ठा nf_hook_state state;
	अचिन्हित अक्षर *dest;
	पूर्णांक ret;

	अगर (!p || p->state != BR_STATE_FORWARDING)
		वापस NF_ACCEPT;

	nf_hook_state_init(&state, NF_BR_BROUTING,
			   NFPROTO_BRIDGE, s->in, शून्य, शून्य,
			   s->net, शून्य);

	ret = ebt_करो_table(skb, &state, priv);
	अगर (ret != NF_DROP)
		वापस ret;

	/* DROP in ebtables -t broute means that the
	 * skb should be routed, not bridged.
	 * This is awkward, but can't be changed क्रम compatibility
	 * reasons.
	 *
	 * We map DROP to ACCEPT and set the ->br_netfilter_broute flag.
	 */
	BR_INPUT_SKB_CB(skb)->br_netfilter_broute = 1;

	/* unकरो PACKET_HOST mangling करोne in br_input in हाल the dst
	 * address matches the logical bridge but not the port.
	 */
	dest = eth_hdr(skb)->h_dest;
	अगर (skb->pkt_type == PACKET_HOST &&
	    !ether_addr_equal(skb->dev->dev_addr, dest) &&
	     ether_addr_equal(p->br->dev->dev_addr, dest))
		skb->pkt_type = PACKET_OTHERHOST;

	वापस NF_ACCEPT;
पूर्ण

अटल स्थिर काष्ठा nf_hook_ops ebt_ops_broute = अणु
	.hook		= ebt_broute,
	.pf		= NFPROTO_BRIDGE,
	.hooknum	= NF_BR_PRE_ROUTING,
	.priority	= NF_BR_PRI_FIRST,
पूर्ण;

अटल पूर्णांक __net_init broute_net_init(काष्ठा net *net)
अणु
	वापस ebt_रेजिस्टर_table(net, &broute_table, &ebt_ops_broute);
पूर्ण

अटल व्योम __net_निकास broute_net_pre_निकास(काष्ठा net *net)
अणु
	ebt_unरेजिस्टर_table_pre_निकास(net, "broute");
पूर्ण

अटल व्योम __net_निकास broute_net_निकास(काष्ठा net *net)
अणु
	ebt_unरेजिस्टर_table(net, "broute");
पूर्ण

अटल काष्ठा pernet_operations broute_net_ops = अणु
	.init = broute_net_init,
	.निकास = broute_net_निकास,
	.pre_निकास = broute_net_pre_निकास,
पूर्ण;

अटल पूर्णांक __init ebtable_broute_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&broute_net_ops);
पूर्ण

अटल व्योम __निकास ebtable_broute_fini(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&broute_net_ops);
पूर्ण

module_init(ebtable_broute_init);
module_निकास(ebtable_broute_fini);
MODULE_LICENSE("GPL");
