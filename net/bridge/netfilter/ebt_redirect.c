<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ebt_redirect
 *
 *	Authors:
 *	Bart De Schuymer <bdschuym@panकरोra.be>
 *
 *  April, 2002
 *
 */
#समावेश <linux/module.h>
#समावेश <net/sock.h>
#समावेश "../br_private.h"
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/netfilter_bridge/ebt_redirect.h>

अटल अचिन्हित पूर्णांक
ebt_redirect_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ebt_redirect_info *info = par->targinfo;

	अगर (skb_ensure_writable(skb, 0))
		वापस EBT_DROP;

	अगर (xt_hooknum(par) != NF_BR_BROUTING)
		/* rcu_पढ़ो_lock()ed by nf_hook_thresh */
		ether_addr_copy(eth_hdr(skb)->h_dest,
				br_port_get_rcu(xt_in(par))->br->dev->dev_addr);
	अन्यथा
		ether_addr_copy(eth_hdr(skb)->h_dest, xt_in(par)->dev_addr);
	skb->pkt_type = PACKET_HOST;
	वापस info->target;
पूर्ण

अटल पूर्णांक ebt_redirect_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा ebt_redirect_info *info = par->targinfo;
	अचिन्हित पूर्णांक hook_mask;

	अगर (BASE_CHAIN && info->target == EBT_RETURN)
		वापस -EINVAL;

	hook_mask = par->hook_mask & ~(1 << NF_BR_NUMHOOKS);
	अगर ((म_भेद(par->table, "nat") != 0 ||
	    hook_mask & ~(1 << NF_BR_PRE_ROUTING)) &&
	    (म_भेद(par->table, "broute") != 0 ||
	    hook_mask & ~(1 << NF_BR_BROUTING)))
		वापस -EINVAL;
	अगर (ebt_invalid_target(info->target))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा xt_target ebt_redirect_tg_reg __पढ़ो_mostly = अणु
	.name		= "redirect",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.hooks		= (1 << NF_BR_NUMHOOKS) | (1 << NF_BR_PRE_ROUTING) |
			  (1 << NF_BR_BROUTING),
	.target		= ebt_redirect_tg,
	.checkentry	= ebt_redirect_tg_check,
	.tarमाला_लोize	= माप(काष्ठा ebt_redirect_info),
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ebt_redirect_init(व्योम)
अणु
	वापस xt_रेजिस्टर_target(&ebt_redirect_tg_reg);
पूर्ण

अटल व्योम __निकास ebt_redirect_fini(व्योम)
अणु
	xt_unरेजिस्टर_target(&ebt_redirect_tg_reg);
पूर्ण

module_init(ebt_redirect_init);
module_निकास(ebt_redirect_fini);
MODULE_DESCRIPTION("Ebtables: Packet redirection to localhost");
MODULE_LICENSE("GPL");
