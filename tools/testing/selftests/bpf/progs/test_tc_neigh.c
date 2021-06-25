<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकघोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>

#समावेश <linux/bpf.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/pkt_cls.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#अगर_अघोषित ctx_ptr
# define ctx_ptr(field)		(व्योम *)(दीर्घ)(field)
#पूर्ण_अगर

#घोषणा ip4_src			0xac100164 /* 172.16.1.100 */
#घोषणा ip4_dst			0xac100264 /* 172.16.2.100 */

#घोषणा ip6_src			अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
				  0x00, 0x01, 0xde, 0xad, 0xbe, 0xef, 0xca, 0xfe पूर्ण
#घोषणा ip6_dst			अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
				  0x00, 0x02, 0xde, 0xad, 0xbe, 0xef, 0xca, 0xfe पूर्ण

#अगर_अघोषित v6_equal
# define v6_equal(a, b)		(a.s6_addr32[0] == b.s6_addr32[0] && \
				 a.s6_addr32[1] == b.s6_addr32[1] && \
				 a.s6_addr32[2] == b.s6_addr32[2] && \
				 a.s6_addr32[3] == b.s6_addr32[3])
#पूर्ण_अगर

अस्थिर स्थिर __u32 IFINDEX_SRC;
अस्थिर स्थिर __u32 IFINDEX_DST;

अटल __always_अंतरभूत bool is_remote_ep_v4(काष्ठा __sk_buff *skb,
					    __be32 addr)
अणु
	व्योम *data_end = ctx_ptr(skb->data_end);
	व्योम *data = ctx_ptr(skb->data);
	काष्ठा iphdr *ip4h;

	अगर (data + माप(काष्ठा ethhdr) > data_end)
		वापस false;

	ip4h = (काष्ठा iphdr *)(data + माप(काष्ठा ethhdr));
	अगर ((व्योम *)(ip4h + 1) > data_end)
		वापस false;

	वापस ip4h->daddr == addr;
पूर्ण

अटल __always_अंतरभूत bool is_remote_ep_v6(काष्ठा __sk_buff *skb,
					    काष्ठा in6_addr addr)
अणु
	व्योम *data_end = ctx_ptr(skb->data_end);
	व्योम *data = ctx_ptr(skb->data);
	काष्ठा ipv6hdr *ip6h;

	अगर (data + माप(काष्ठा ethhdr) > data_end)
		वापस false;

	ip6h = (काष्ठा ipv6hdr *)(data + माप(काष्ठा ethhdr));
	अगर ((व्योम *)(ip6h + 1) > data_end)
		वापस false;

	वापस v6_equal(ip6h->daddr, addr);
पूर्ण

SEC("classifier/chk_egress")
पूर्णांक tc_chk(काष्ठा __sk_buff *skb)
अणु
	व्योम *data_end = ctx_ptr(skb->data_end);
	व्योम *data = ctx_ptr(skb->data);
	__u32 *raw = data;

	अगर (data + माप(काष्ठा ethhdr) > data_end)
		वापस TC_ACT_SHOT;

	वापस !raw[0] && !raw[1] && !raw[2] ? TC_ACT_SHOT : TC_ACT_OK;
पूर्ण

SEC("classifier/dst_ingress")
पूर्णांक tc_dst(काष्ठा __sk_buff *skb)
अणु
	__u8 zero[ETH_ALEN * 2];
	bool redirect = false;

	चयन (skb->protocol) अणु
	हाल __bpf_स्थिरant_htons(ETH_P_IP):
		redirect = is_remote_ep_v4(skb, __bpf_स्थिरant_htonl(ip4_src));
		अवरोध;
	हाल __bpf_स्थिरant_htons(ETH_P_IPV6):
		redirect = is_remote_ep_v6(skb, (काष्ठा in6_addr)ip6_src);
		अवरोध;
	पूर्ण

	अगर (!redirect)
		वापस TC_ACT_OK;

	__builtin_स_रखो(&zero, 0, माप(zero));
	अगर (bpf_skb_store_bytes(skb, 0, &zero, माप(zero), 0) < 0)
		वापस TC_ACT_SHOT;

	वापस bpf_redirect_neigh(IFINDEX_SRC, शून्य, 0, 0);
पूर्ण

SEC("classifier/src_ingress")
पूर्णांक tc_src(काष्ठा __sk_buff *skb)
अणु
	__u8 zero[ETH_ALEN * 2];
	bool redirect = false;

	चयन (skb->protocol) अणु
	हाल __bpf_स्थिरant_htons(ETH_P_IP):
		redirect = is_remote_ep_v4(skb, __bpf_स्थिरant_htonl(ip4_dst));
		अवरोध;
	हाल __bpf_स्थिरant_htons(ETH_P_IPV6):
		redirect = is_remote_ep_v6(skb, (काष्ठा in6_addr)ip6_dst);
		अवरोध;
	पूर्ण

	अगर (!redirect)
		वापस TC_ACT_OK;

	__builtin_स_रखो(&zero, 0, माप(zero));
	अगर (bpf_skb_store_bytes(skb, 0, &zero, माप(zero), 0) < 0)
		वापस TC_ACT_SHOT;

	वापस bpf_redirect_neigh(IFINDEX_DST, शून्य, 0, 0);
पूर्ण

अक्षर __license[] SEC("license") = "GPL";
