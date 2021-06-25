<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 Pablo Neira Ayuso <pablo@netfilter.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_offload.h>
#समावेश <net/netfilter/nf_dup_netdev.h>

अटल व्योम nf_करो_netdev_egress(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	अगर (skb_mac_header_was_set(skb))
		skb_push(skb, skb->mac_len);

	skb->dev = dev;
	skb->tstamp = 0;
	dev_queue_xmit(skb);
पूर्ण

व्योम nf_fwd_netdev_egress(स्थिर काष्ठा nft_pktinfo *pkt, पूर्णांक oअगर)
अणु
	काष्ठा net_device *dev;

	dev = dev_get_by_index_rcu(nft_net(pkt), oअगर);
	अगर (!dev) अणु
		kमुक्त_skb(pkt->skb);
		वापस;
	पूर्ण

	nf_करो_netdev_egress(pkt->skb, dev);
पूर्ण
EXPORT_SYMBOL_GPL(nf_fwd_netdev_egress);

व्योम nf_dup_netdev_egress(स्थिर काष्ठा nft_pktinfo *pkt, पूर्णांक oअगर)
अणु
	काष्ठा net_device *dev;
	काष्ठा sk_buff *skb;

	dev = dev_get_by_index_rcu(nft_net(pkt), oअगर);
	अगर (dev == शून्य)
		वापस;

	skb = skb_clone(pkt->skb, GFP_ATOMIC);
	अगर (skb)
		nf_करो_netdev_egress(skb, dev);
पूर्ण
EXPORT_SYMBOL_GPL(nf_dup_netdev_egress);

पूर्णांक nft_fwd_dup_netdev_offload(काष्ठा nft_offload_ctx *ctx,
			       काष्ठा nft_flow_rule *flow,
			       क्रमागत flow_action_id id, पूर्णांक oअगर)
अणु
	काष्ठा flow_action_entry *entry;
	काष्ठा net_device *dev;

	/* nft_flow_rule_destroy() releases the reference on this device. */
	dev = dev_get_by_index(ctx->net, oअगर);
	अगर (!dev)
		वापस -EOPNOTSUPP;

	entry = &flow->rule->action.entries[ctx->num_actions++];
	entry->id = id;
	entry->dev = dev;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nft_fwd_dup_netdev_offload);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_DESCRIPTION("Netfilter packet duplication support");
