<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 Pablo Neira Ayuso <pablo@netfilter.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nft_reject.h>
#समावेश <net/netfilter/ipv4/nf_reject.h>
#समावेश <net/netfilter/ipv6/nf_reject.h>
#समावेश <linux/ip.h>
#समावेश <net/ip.h>
#समावेश <net/ip6_checksum.h>
#समावेश <linux/netfilter_bridge.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश "../br_private.h"

अटल व्योम nft_reject_br_push_etherhdr(काष्ठा sk_buff *oldskb,
					काष्ठा sk_buff *nskb)
अणु
	काष्ठा ethhdr *eth;

	eth = skb_push(nskb, ETH_HLEN);
	skb_reset_mac_header(nskb);
	ether_addr_copy(eth->h_source, eth_hdr(oldskb)->h_dest);
	ether_addr_copy(eth->h_dest, eth_hdr(oldskb)->h_source);
	eth->h_proto = eth_hdr(oldskb)->h_proto;
	skb_pull(nskb, ETH_HLEN);

	अगर (skb_vlan_tag_present(oldskb)) अणु
		u16 vid = skb_vlan_tag_get(oldskb);

		__vlan_hwaccel_put_tag(nskb, oldskb->vlan_proto, vid);
	पूर्ण
पूर्ण

/* We cannot use oldskb->dev, it can be either bridge device (NF_BRIDGE INPUT)
 * or the bridge port (NF_BRIDGE PREROUTING).
 */
अटल व्योम nft_reject_br_send_v4_tcp_reset(काष्ठा net *net,
					    काष्ठा sk_buff *oldskb,
					    स्थिर काष्ठा net_device *dev,
					    पूर्णांक hook)
अणु
	काष्ठा sk_buff *nskb;

	nskb = nf_reject_skb_v4_tcp_reset(net, oldskb, dev, hook);
	अगर (!nskb)
		वापस;

	nft_reject_br_push_etherhdr(oldskb, nskb);

	br_क्रमward(br_port_get_rcu(dev), nskb, false, true);
पूर्ण

अटल व्योम nft_reject_br_send_v4_unreach(काष्ठा net *net,
					  काष्ठा sk_buff *oldskb,
					  स्थिर काष्ठा net_device *dev,
					  पूर्णांक hook, u8 code)
अणु
	काष्ठा sk_buff *nskb;

	nskb = nf_reject_skb_v4_unreach(net, oldskb, dev, hook, code);
	अगर (!nskb)
		वापस;

	nft_reject_br_push_etherhdr(oldskb, nskb);

	br_क्रमward(br_port_get_rcu(dev), nskb, false, true);
पूर्ण

अटल व्योम nft_reject_br_send_v6_tcp_reset(काष्ठा net *net,
					    काष्ठा sk_buff *oldskb,
					    स्थिर काष्ठा net_device *dev,
					    पूर्णांक hook)
अणु
	काष्ठा sk_buff *nskb;

	nskb = nf_reject_skb_v6_tcp_reset(net, oldskb, dev, hook);
	अगर (!nskb)
		वापस;

	nft_reject_br_push_etherhdr(oldskb, nskb);

	br_क्रमward(br_port_get_rcu(dev), nskb, false, true);
पूर्ण


अटल व्योम nft_reject_br_send_v6_unreach(काष्ठा net *net,
					  काष्ठा sk_buff *oldskb,
					  स्थिर काष्ठा net_device *dev,
					  पूर्णांक hook, u8 code)
अणु
	काष्ठा sk_buff *nskb;

	nskb = nf_reject_skb_v6_unreach(net, oldskb, dev, hook, code);
	अगर (!nskb)
		वापस;

	nft_reject_br_push_etherhdr(oldskb, nskb);

	br_क्रमward(br_port_get_rcu(dev), nskb, false, true);
पूर्ण

अटल व्योम nft_reject_bridge_eval(स्थिर काष्ठा nft_expr *expr,
				   काष्ठा nft_regs *regs,
				   स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_reject *priv = nft_expr_priv(expr);
	स्थिर अचिन्हित अक्षर *dest = eth_hdr(pkt->skb)->h_dest;

	अगर (is_broadcast_ether_addr(dest) ||
	    is_multicast_ether_addr(dest))
		जाओ out;

	चयन (eth_hdr(pkt->skb)->h_proto) अणु
	हाल htons(ETH_P_IP):
		चयन (priv->type) अणु
		हाल NFT_REJECT_ICMP_UNREACH:
			nft_reject_br_send_v4_unreach(nft_net(pkt), pkt->skb,
						      nft_in(pkt),
						      nft_hook(pkt),
						      priv->icmp_code);
			अवरोध;
		हाल NFT_REJECT_TCP_RST:
			nft_reject_br_send_v4_tcp_reset(nft_net(pkt), pkt->skb,
							nft_in(pkt),
							nft_hook(pkt));
			अवरोध;
		हाल NFT_REJECT_ICMPX_UNREACH:
			nft_reject_br_send_v4_unreach(nft_net(pkt), pkt->skb,
						      nft_in(pkt),
						      nft_hook(pkt),
						      nft_reject_icmp_code(priv->icmp_code));
			अवरोध;
		पूर्ण
		अवरोध;
	हाल htons(ETH_P_IPV6):
		चयन (priv->type) अणु
		हाल NFT_REJECT_ICMP_UNREACH:
			nft_reject_br_send_v6_unreach(nft_net(pkt), pkt->skb,
						      nft_in(pkt),
						      nft_hook(pkt),
						      priv->icmp_code);
			अवरोध;
		हाल NFT_REJECT_TCP_RST:
			nft_reject_br_send_v6_tcp_reset(nft_net(pkt), pkt->skb,
							nft_in(pkt),
							nft_hook(pkt));
			अवरोध;
		हाल NFT_REJECT_ICMPX_UNREACH:
			nft_reject_br_send_v6_unreach(nft_net(pkt), pkt->skb,
						      nft_in(pkt),
						      nft_hook(pkt),
						      nft_reject_icmpv6_code(priv->icmp_code));
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		/* No explicit way to reject this protocol, drop it. */
		अवरोध;
	पूर्ण
out:
	regs->verdict.code = NF_DROP;
पूर्ण

अटल पूर्णांक nft_reject_bridge_validate(स्थिर काष्ठा nft_ctx *ctx,
				      स्थिर काष्ठा nft_expr *expr,
				      स्थिर काष्ठा nft_data **data)
अणु
	वापस nft_chain_validate_hooks(ctx->chain, (1 << NF_BR_PRE_ROUTING) |
						    (1 << NF_BR_LOCAL_IN));
पूर्ण

अटल काष्ठा nft_expr_type nft_reject_bridge_type;
अटल स्थिर काष्ठा nft_expr_ops nft_reject_bridge_ops = अणु
	.type		= &nft_reject_bridge_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_reject)),
	.eval		= nft_reject_bridge_eval,
	.init		= nft_reject_init,
	.dump		= nft_reject_dump,
	.validate	= nft_reject_bridge_validate,
पूर्ण;

अटल काष्ठा nft_expr_type nft_reject_bridge_type __पढ़ो_mostly = अणु
	.family		= NFPROTO_BRIDGE,
	.name		= "reject",
	.ops		= &nft_reject_bridge_ops,
	.policy		= nft_reject_policy,
	.maxattr	= NFTA_REJECT_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_reject_bridge_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_reject_bridge_type);
पूर्ण

अटल व्योम __निकास nft_reject_bridge_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_reject_bridge_type);
पूर्ण

module_init(nft_reject_bridge_module_init);
module_निकास(nft_reject_bridge_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_ALIAS_NFT_AF_EXPR(AF_BRIDGE, "reject");
MODULE_DESCRIPTION("Reject packets from bridge via nftables");
