<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Network Service Header
 *
 * Copyright (c) 2017 Red Hat, Inc. -- Jiri Benc <jbenc@redhat.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/nsh.h>
#समावेश <net/tun_proto.h>

पूर्णांक nsh_push(काष्ठा sk_buff *skb, स्थिर काष्ठा nshhdr *pushed_nh)
अणु
	काष्ठा nshhdr *nh;
	माप_प्रकार length = nsh_hdr_len(pushed_nh);
	u8 next_proto;

	अगर (skb->mac_len) अणु
		next_proto = TUN_P_ETHERNET;
	पूर्ण अन्यथा अणु
		next_proto = tun_p_from_eth_p(skb->protocol);
		अगर (!next_proto)
			वापस -EAFNOSUPPORT;
	पूर्ण

	/* Add the NSH header */
	अगर (skb_cow_head(skb, length) < 0)
		वापस -ENOMEM;

	skb_push(skb, length);
	nh = (काष्ठा nshhdr *)(skb->data);
	स_नकल(nh, pushed_nh, length);
	nh->np = next_proto;
	skb_postpush_rcsum(skb, nh, length);

	skb->protocol = htons(ETH_P_NSH);
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb_reset_mac_len(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nsh_push);

पूर्णांक nsh_pop(काष्ठा sk_buff *skb)
अणु
	काष्ठा nshhdr *nh;
	माप_प्रकार length;
	__be16 inner_proto;

	अगर (!pskb_may_pull(skb, NSH_BASE_HDR_LEN))
		वापस -ENOMEM;
	nh = (काष्ठा nshhdr *)(skb->data);
	length = nsh_hdr_len(nh);
	अगर (length < NSH_BASE_HDR_LEN)
		वापस -EINVAL;
	inner_proto = tun_p_to_eth_p(nh->np);
	अगर (!pskb_may_pull(skb, length))
		वापस -ENOMEM;

	अगर (!inner_proto)
		वापस -EAFNOSUPPORT;

	skb_pull_rcsum(skb, length);
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb_reset_mac_len(skb);
	skb->protocol = inner_proto;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nsh_pop);

अटल काष्ठा sk_buff *nsh_gso_segment(काष्ठा sk_buff *skb,
				       netdev_features_t features)
अणु
	काष्ठा sk_buff *segs = ERR_PTR(-EINVAL);
	अचिन्हित पूर्णांक nsh_len, mac_len;
	__be16 proto;
	पूर्णांक nhoff;

	skb_reset_network_header(skb);

	nhoff = skb->network_header - skb->mac_header;
	mac_len = skb->mac_len;

	अगर (unlikely(!pskb_may_pull(skb, NSH_BASE_HDR_LEN)))
		जाओ out;
	nsh_len = nsh_hdr_len(nsh_hdr(skb));
	अगर (nsh_len < NSH_BASE_HDR_LEN)
		जाओ out;
	अगर (unlikely(!pskb_may_pull(skb, nsh_len)))
		जाओ out;

	proto = tun_p_to_eth_p(nsh_hdr(skb)->np);
	अगर (!proto)
		जाओ out;

	__skb_pull(skb, nsh_len);

	skb_reset_mac_header(skb);
	skb->mac_len = proto == htons(ETH_P_TEB) ? ETH_HLEN : 0;
	skb->protocol = proto;

	features &= NETIF_F_SG;
	segs = skb_mac_gso_segment(skb, features);
	अगर (IS_ERR_OR_शून्य(segs)) अणु
		skb_gso_error_unwind(skb, htons(ETH_P_NSH), nsh_len,
				     skb->network_header - nhoff,
				     mac_len);
		जाओ out;
	पूर्ण

	क्रम (skb = segs; skb; skb = skb->next) अणु
		skb->protocol = htons(ETH_P_NSH);
		__skb_push(skb, nsh_len);
		skb_set_mac_header(skb, -nhoff);
		skb->network_header = skb->mac_header + mac_len;
		skb->mac_len = mac_len;
	पूर्ण

out:
	वापस segs;
पूर्ण

अटल काष्ठा packet_offload nsh_packet_offload __पढ़ो_mostly = अणु
	.type = htons(ETH_P_NSH),
	.priority = 15,
	.callbacks = अणु
		.gso_segment = nsh_gso_segment,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init nsh_init_module(व्योम)
अणु
	dev_add_offload(&nsh_packet_offload);
	वापस 0;
पूर्ण

अटल व्योम __निकास nsh_cleanup_module(व्योम)
अणु
	dev_हटाओ_offload(&nsh_packet_offload);
पूर्ण

module_init(nsh_init_module);
module_निकास(nsh_cleanup_module);

MODULE_AUTHOR("Jiri Benc <jbenc@redhat.com>");
MODULE_DESCRIPTION("NSH protocol");
MODULE_LICENSE("GPL v2");
