<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ebt_dnat
 *
 *	Authors:
 *	Bart De Schuymer <bdschuym@panकरोra.be>
 *
 *  June, 2002
 *
 */
#समावेश <linux/module.h>
#समावेश <net/sock.h>
#समावेश "../br_private.h"
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/netfilter_bridge/ebt_nat.h>

अटल अचिन्हित पूर्णांक
ebt_dnat_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ebt_nat_info *info = par->targinfo;

	अगर (skb_ensure_writable(skb, 0))
		वापस EBT_DROP;

	ether_addr_copy(eth_hdr(skb)->h_dest, info->mac);

	अगर (is_multicast_ether_addr(info->mac)) अणु
		अगर (is_broadcast_ether_addr(info->mac))
			skb->pkt_type = PACKET_BROADCAST;
		अन्यथा
			skb->pkt_type = PACKET_MULTICAST;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा net_device *dev;

		चयन (xt_hooknum(par)) अणु
		हाल NF_BR_BROUTING:
			dev = xt_in(par);
			अवरोध;
		हाल NF_BR_PRE_ROUTING:
			dev = br_port_get_rcu(xt_in(par))->br->dev;
			अवरोध;
		शेष:
			dev = शून्य;
			अवरोध;
		पूर्ण

		अगर (!dev) /* NF_BR_LOCAL_OUT */
			वापस info->target;

		अगर (ether_addr_equal(info->mac, dev->dev_addr))
			skb->pkt_type = PACKET_HOST;
		अन्यथा
			skb->pkt_type = PACKET_OTHERHOST;
	पूर्ण

	वापस info->target;
पूर्ण

अटल पूर्णांक ebt_dnat_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा ebt_nat_info *info = par->targinfo;
	अचिन्हित पूर्णांक hook_mask;

	अगर (BASE_CHAIN && info->target == EBT_RETURN)
		वापस -EINVAL;

	hook_mask = par->hook_mask & ~(1 << NF_BR_NUMHOOKS);
	अगर ((म_भेद(par->table, "nat") != 0 ||
	    (hook_mask & ~((1 << NF_BR_PRE_ROUTING) |
	    (1 << NF_BR_LOCAL_OUT)))) &&
	    (म_भेद(par->table, "broute") != 0 ||
	    hook_mask & ~(1 << NF_BR_BROUTING)))
		वापस -EINVAL;
	अगर (ebt_invalid_target(info->target))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा xt_target ebt_dnat_tg_reg __पढ़ो_mostly = अणु
	.name		= "dnat",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.hooks		= (1 << NF_BR_NUMHOOKS) | (1 << NF_BR_PRE_ROUTING) |
			  (1 << NF_BR_LOCAL_OUT) | (1 << NF_BR_BROUTING),
	.target		= ebt_dnat_tg,
	.checkentry	= ebt_dnat_tg_check,
	.tarमाला_लोize	= माप(काष्ठा ebt_nat_info),
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ebt_dnat_init(व्योम)
अणु
	वापस xt_रेजिस्टर_target(&ebt_dnat_tg_reg);
पूर्ण

अटल व्योम __निकास ebt_dnat_fini(व्योम)
अणु
	xt_unरेजिस्टर_target(&ebt_dnat_tg_reg);
पूर्ण

module_init(ebt_dnat_init);
module_निकास(ebt_dnat_fini);
MODULE_DESCRIPTION("Ebtables: Destination MAC address translation");
MODULE_LICENSE("GPL");
