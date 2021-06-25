<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>

#समावेश <linux/bpf.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/pkt_cls.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/ip.h>

#समावेश <bpf/bpf_helpers.h>

अस्थिर स्थिर __u32 IFINDEX_SRC;
अस्थिर स्थिर __u32 IFINDEX_DST;

अटल स्थिर __u8 src_mac[] = अणु0x00, 0x11, 0x22, 0x33, 0x44, 0x55पूर्ण;
अटल स्थिर __u8 dst_mac[] = अणु0x00, 0x22, 0x33, 0x44, 0x55, 0x66पूर्ण;

SEC("classifier/chk_egress")
पूर्णांक tc_chk(काष्ठा __sk_buff *skb)
अणु
	वापस TC_ACT_SHOT;
पूर्ण

SEC("classifier/dst_ingress")
पूर्णांक tc_dst(काष्ठा __sk_buff *skb)
अणु
	वापस bpf_redirect_peer(IFINDEX_SRC, 0);
पूर्ण

SEC("classifier/src_ingress")
पूर्णांक tc_src(काष्ठा __sk_buff *skb)
अणु
	वापस bpf_redirect_peer(IFINDEX_DST, 0);
पूर्ण

SEC("classifier/dst_ingress_l3")
पूर्णांक tc_dst_l3(काष्ठा __sk_buff *skb)
अणु
	वापस bpf_redirect(IFINDEX_SRC, 0);
पूर्ण

SEC("classifier/src_ingress_l3")
पूर्णांक tc_src_l3(काष्ठा __sk_buff *skb)
अणु
	__u16 proto = skb->protocol;

	अगर (bpf_skb_change_head(skb, ETH_HLEN, 0) != 0)
		वापस TC_ACT_SHOT;

	अगर (bpf_skb_store_bytes(skb, 0, &src_mac, ETH_ALEN, 0) != 0)
		वापस TC_ACT_SHOT;

	अगर (bpf_skb_store_bytes(skb, ETH_ALEN, &dst_mac, ETH_ALEN, 0) != 0)
		वापस TC_ACT_SHOT;

	अगर (bpf_skb_store_bytes(skb, ETH_ALEN + ETH_ALEN, &proto, माप(__u16), 0) != 0)
		वापस TC_ACT_SHOT;

	वापस bpf_redirect_peer(IFINDEX_DST, 0);
पूर्ण

अक्षर __license[] SEC("license") = "GPL";
