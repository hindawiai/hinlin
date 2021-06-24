<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	MPLS GSO Support
 *
 *	Authors: Simon Horman (horms@verge.net.au)
 *
 *	Based on: GSO portions of net/ipv4/gre.c
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/netdev_features.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/mpls.h>

अटल काष्ठा sk_buff *mpls_gso_segment(काष्ठा sk_buff *skb,
				       netdev_features_t features)
अणु
	काष्ठा sk_buff *segs = ERR_PTR(-EINVAL);
	u16 mac_offset = skb->mac_header;
	netdev_features_t mpls_features;
	u16 mac_len = skb->mac_len;
	__be16 mpls_protocol;
	अचिन्हित पूर्णांक mpls_hlen;

	skb_reset_network_header(skb);
	mpls_hlen = skb_inner_network_header(skb) - skb_network_header(skb);
	अगर (unlikely(!mpls_hlen || mpls_hlen % MPLS_HLEN))
		जाओ out;
	अगर (unlikely(!pskb_may_pull(skb, mpls_hlen)))
		जाओ out;

	/* Setup inner SKB. */
	mpls_protocol = skb->protocol;
	skb->protocol = skb->inner_protocol;

	__skb_pull(skb, mpls_hlen);

	skb->mac_len = 0;
	skb_reset_mac_header(skb);

	/* Segment inner packet. */
	mpls_features = skb->dev->mpls_features & features;
	segs = skb_mac_gso_segment(skb, mpls_features);
	अगर (IS_ERR_OR_शून्य(segs)) अणु
		skb_gso_error_unwind(skb, mpls_protocol, mpls_hlen, mac_offset,
				     mac_len);
		जाओ out;
	पूर्ण
	skb = segs;

	mpls_hlen += mac_len;
	करो अणु
		skb->mac_len = mac_len;
		skb->protocol = mpls_protocol;

		skb_reset_inner_network_header(skb);

		__skb_push(skb, mpls_hlen);

		skb_reset_mac_header(skb);
		skb_set_network_header(skb, mac_len);
	पूर्ण जबतक ((skb = skb->next));

out:
	वापस segs;
पूर्ण

अटल काष्ठा packet_offload mpls_mc_offload __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_MPLS_MC),
	.priority = 15,
	.callbacks = अणु
		.gso_segment    =	mpls_gso_segment,
	पूर्ण,
पूर्ण;

अटल काष्ठा packet_offload mpls_uc_offload __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_MPLS_UC),
	.priority = 15,
	.callbacks = अणु
		.gso_segment    =	mpls_gso_segment,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mpls_gso_init(व्योम)
अणु
	pr_info("MPLS GSO support\n");

	dev_add_offload(&mpls_uc_offload);
	dev_add_offload(&mpls_mc_offload);

	वापस 0;
पूर्ण

अटल व्योम __निकास mpls_gso_निकास(व्योम)
अणु
	dev_हटाओ_offload(&mpls_uc_offload);
	dev_हटाओ_offload(&mpls_mc_offload);
पूर्ण

module_init(mpls_gso_init);
module_निकास(mpls_gso_निकास);

MODULE_DESCRIPTION("MPLS GSO support");
MODULE_AUTHOR("Simon Horman (horms@verge.net.au)");
MODULE_LICENSE("GPL");
