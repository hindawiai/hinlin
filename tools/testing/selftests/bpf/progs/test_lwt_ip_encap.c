<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <linux/bpf.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

काष्ठा grehdr अणु
	__be16 flags;
	__be16 protocol;
पूर्ण;

SEC("encap_gre")
पूर्णांक bpf_lwt_encap_gre(काष्ठा __sk_buff *skb)
अणु
	काष्ठा encap_hdr अणु
		काष्ठा iphdr iph;
		काष्ठा grehdr greh;
	पूर्ण hdr;
	पूर्णांक err;

	स_रखो(&hdr, 0, माप(काष्ठा encap_hdr));

	hdr.iph.ihl = 5;
	hdr.iph.version = 4;
	hdr.iph.ttl = 0x40;
	hdr.iph.protocol = 47;  /* IPPROTO_GRE */
#अगर __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	hdr.iph.saddr = 0x640110ac;  /* 172.16.1.100 */
	hdr.iph.daddr = 0x641010ac;  /* 172.16.16.100 */
#या_अगर __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	hdr.iph.saddr = 0xac100164;  /* 172.16.1.100 */
	hdr.iph.daddr = 0xac101064;  /* 172.16.16.100 */
#अन्यथा
#त्रुटि "Fix your compiler's __BYTE_ORDER__?!"
#पूर्ण_अगर
	hdr.iph.tot_len = bpf_htons(skb->len + माप(काष्ठा encap_hdr));

	hdr.greh.protocol = skb->protocol;

	err = bpf_lwt_push_encap(skb, BPF_LWT_ENCAP_IP, &hdr,
				 माप(काष्ठा encap_hdr));
	अगर (err)
		वापस BPF_DROP;

	वापस BPF_LWT_REROUTE;
पूर्ण

SEC("encap_gre6")
पूर्णांक bpf_lwt_encap_gre6(काष्ठा __sk_buff *skb)
अणु
	काष्ठा encap_hdr अणु
		काष्ठा ipv6hdr ip6hdr;
		काष्ठा grehdr greh;
	पूर्ण hdr;
	पूर्णांक err;

	स_रखो(&hdr, 0, माप(काष्ठा encap_hdr));

	hdr.ip6hdr.version = 6;
	hdr.ip6hdr.payload_len = bpf_htons(skb->len + माप(काष्ठा grehdr));
	hdr.ip6hdr.nexthdr = 47;  /* IPPROTO_GRE */
	hdr.ip6hdr.hop_limit = 0x40;
	/* fb01::1 */
	hdr.ip6hdr.saddr.s6_addr[0] = 0xfb;
	hdr.ip6hdr.saddr.s6_addr[1] = 1;
	hdr.ip6hdr.saddr.s6_addr[15] = 1;
	/* fb10::1 */
	hdr.ip6hdr.daddr.s6_addr[0] = 0xfb;
	hdr.ip6hdr.daddr.s6_addr[1] = 0x10;
	hdr.ip6hdr.daddr.s6_addr[15] = 1;

	hdr.greh.protocol = skb->protocol;

	err = bpf_lwt_push_encap(skb, BPF_LWT_ENCAP_IP, &hdr,
				 माप(काष्ठा encap_hdr));
	अगर (err)
		वापस BPF_DROP;

	वापस BPF_LWT_REROUTE;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
