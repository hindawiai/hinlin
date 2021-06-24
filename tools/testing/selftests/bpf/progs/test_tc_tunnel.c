<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* In-place tunneling */

#समावेश <stdbool.h>
#समावेश <माला.स>

#समावेश <linux/मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/mpls.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/pkt_cls.h>
#समावेश <linux/types.h>

#समावेश <bpf/bpf_endian.h>
#समावेश <bpf/bpf_helpers.h>

अटल स्थिर पूर्णांक cfg_port = 8000;

अटल स्थिर पूर्णांक cfg_udp_src = 20000;

#घोषणा	L2_PAD_SZ	(माप(काष्ठा vxlanhdr) + ETH_HLEN)

#घोषणा	UDP_PORT		5555
#घोषणा	MPLS_OVER_UDP_PORT	6635
#घोषणा	ETH_OVER_UDP_PORT	7777
#घोषणा	VXLAN_UDP_PORT		8472

#घोषणा	EXTPROTO_VXLAN	0x1

#घोषणा	VXLAN_N_VID     (1u << 24)
#घोषणा	VXLAN_VNI_MASK	bpf_htonl((VXLAN_N_VID - 1) << 8)
#घोषणा	VXLAN_FLAGS     0x8
#घोषणा	VXLAN_VNI       1

/* MPLS label 1000 with S bit (last label) set and ttl of 255. */
अटल स्थिर __u32 mpls_label = __bpf_स्थिरant_htonl(1000 << 12 |
						     MPLS_LS_S_MASK | 0xff);

काष्ठा vxlanhdr अणु
	__be32 vx_flags;
	__be32 vx_vni;
पूर्ण __attribute__((packed));

काष्ठा gre_hdr अणु
	__be16 flags;
	__be16 protocol;
पूर्ण __attribute__((packed));

जोड़ l4hdr अणु
	काष्ठा udphdr udp;
	काष्ठा gre_hdr gre;
पूर्ण;

काष्ठा v4hdr अणु
	काष्ठा iphdr ip;
	जोड़ l4hdr l4hdr;
	__u8 pad[L2_PAD_SZ];		/* space क्रम L2 header / vxlan header ... */
पूर्ण __attribute__((packed));

काष्ठा v6hdr अणु
	काष्ठा ipv6hdr ip;
	जोड़ l4hdr l4hdr;
	__u8 pad[L2_PAD_SZ];		/* space क्रम L2 header / vxlan header ... */
पूर्ण __attribute__((packed));

अटल __always_अंतरभूत व्योम set_ipv4_csum(काष्ठा iphdr *iph)
अणु
	__u16 *iph16 = (__u16 *)iph;
	__u32 csum;
	पूर्णांक i;

	iph->check = 0;

#आशय clang loop unroll(full)
	क्रम (i = 0, csum = 0; i < माप(*iph) >> 1; i++)
		csum += *iph16++;

	iph->check = ~((csum & 0xffff) + (csum >> 16));
पूर्ण

अटल __always_अंतरभूत पूर्णांक __encap_ipv4(काष्ठा __sk_buff *skb, __u8 encap_proto,
					__u16 l2_proto, __u16 ext_proto)
अणु
	__u16 udp_dst = UDP_PORT;
	काष्ठा iphdr iph_inner;
	काष्ठा v4hdr h_outer;
	काष्ठा tcphdr tcph;
	पूर्णांक olen, l2_len;
	__u8 *l2_hdr = शून्य;
	पूर्णांक tcp_off;
	__u64 flags;

	/* Most tests encapsulate a packet पूर्णांकo a tunnel with the same
	 * network protocol, and derive the outer header fields from
	 * the inner header.
	 *
	 * The 6in4 हाल tests dअगरferent inner and outer protocols. As
	 * the inner is ipv6, but the outer expects an ipv4 header as
	 * input, manually build a काष्ठा iphdr based on the ipv6hdr.
	 */
	अगर (encap_proto == IPPROTO_IPV6) अणु
		स्थिर __u32 saddr = (192 << 24) | (168 << 16) | (1 << 8) | 1;
		स्थिर __u32 daddr = (192 << 24) | (168 << 16) | (1 << 8) | 2;
		काष्ठा ipv6hdr iph6_inner;

		/* Read the IPv6 header */
		अगर (bpf_skb_load_bytes(skb, ETH_HLEN, &iph6_inner,
				       माप(iph6_inner)) < 0)
			वापस TC_ACT_OK;

		/* Derive the IPv4 header fields from the IPv6 header */
		स_रखो(&iph_inner, 0, माप(iph_inner));
		iph_inner.version = 4;
		iph_inner.ihl = 5;
		iph_inner.tot_len = bpf_htons(माप(iph6_inner) +
				    bpf_ntohs(iph6_inner.payload_len));
		iph_inner.ttl = iph6_inner.hop_limit - 1;
		iph_inner.protocol = iph6_inner.nexthdr;
		iph_inner.saddr = __bpf_स्थिरant_htonl(saddr);
		iph_inner.daddr = __bpf_स्थिरant_htonl(daddr);

		tcp_off = माप(iph6_inner);
	पूर्ण अन्यथा अणु
		अगर (bpf_skb_load_bytes(skb, ETH_HLEN, &iph_inner,
				       माप(iph_inner)) < 0)
			वापस TC_ACT_OK;

		tcp_off = माप(iph_inner);
	पूर्ण

	/* filter only packets we want */
	अगर (iph_inner.ihl != 5 || iph_inner.protocol != IPPROTO_TCP)
		वापस TC_ACT_OK;

	अगर (bpf_skb_load_bytes(skb, ETH_HLEN + tcp_off,
			       &tcph, माप(tcph)) < 0)
		वापस TC_ACT_OK;

	अगर (tcph.dest != __bpf_स्थिरant_htons(cfg_port))
		वापस TC_ACT_OK;

	olen = माप(h_outer.ip);
	l2_len = 0;

	flags = BPF_F_ADJ_ROOM_FIXED_GSO | BPF_F_ADJ_ROOM_ENCAP_L3_IPV4;

	चयन (l2_proto) अणु
	हाल ETH_P_MPLS_UC:
		l2_len = माप(mpls_label);
		udp_dst = MPLS_OVER_UDP_PORT;
		अवरोध;
	हाल ETH_P_TEB:
		l2_len = ETH_HLEN;
		अगर (ext_proto & EXTPROTO_VXLAN) अणु
			udp_dst = VXLAN_UDP_PORT;
			l2_len += माप(काष्ठा vxlanhdr);
		पूर्ण अन्यथा
			udp_dst = ETH_OVER_UDP_PORT;
		अवरोध;
	पूर्ण
	flags |= BPF_F_ADJ_ROOM_ENCAP_L2(l2_len);

	चयन (encap_proto) अणु
	हाल IPPROTO_GRE:
		flags |= BPF_F_ADJ_ROOM_ENCAP_L4_GRE;
		olen += माप(h_outer.l4hdr.gre);
		h_outer.l4hdr.gre.protocol = bpf_htons(l2_proto);
		h_outer.l4hdr.gre.flags = 0;
		अवरोध;
	हाल IPPROTO_UDP:
		flags |= BPF_F_ADJ_ROOM_ENCAP_L4_UDP;
		olen += माप(h_outer.l4hdr.udp);
		h_outer.l4hdr.udp.source = __bpf_स्थिरant_htons(cfg_udp_src);
		h_outer.l4hdr.udp.dest = bpf_htons(udp_dst);
		h_outer.l4hdr.udp.check = 0;
		h_outer.l4hdr.udp.len = bpf_htons(bpf_ntohs(iph_inner.tot_len) +
						  माप(h_outer.l4hdr.udp) +
						  l2_len);
		अवरोध;
	हाल IPPROTO_IPIP:
	हाल IPPROTO_IPV6:
		अवरोध;
	शेष:
		वापस TC_ACT_OK;
	पूर्ण

	/* add L2 encap (अगर specअगरied) */
	l2_hdr = (__u8 *)&h_outer + olen;
	चयन (l2_proto) अणु
	हाल ETH_P_MPLS_UC:
		*(__u32 *)l2_hdr = mpls_label;
		अवरोध;
	हाल ETH_P_TEB:
		flags |= BPF_F_ADJ_ROOM_ENCAP_L2_ETH;

		अगर (ext_proto & EXTPROTO_VXLAN) अणु
			काष्ठा vxlanhdr *vxlan_hdr = (काष्ठा vxlanhdr *)l2_hdr;

			vxlan_hdr->vx_flags = VXLAN_FLAGS;
			vxlan_hdr->vx_vni = bpf_htonl((VXLAN_VNI & VXLAN_VNI_MASK) << 8);

			l2_hdr += माप(काष्ठा vxlanhdr);
		पूर्ण

		अगर (bpf_skb_load_bytes(skb, 0, l2_hdr, ETH_HLEN))
			वापस TC_ACT_SHOT;

		अवरोध;
	पूर्ण
	olen += l2_len;

	/* add room between mac and network header */
	अगर (bpf_skb_adjust_room(skb, olen, BPF_ADJ_ROOM_MAC, flags))
		वापस TC_ACT_SHOT;

	/* prepare new outer network header */
	h_outer.ip = iph_inner;
	h_outer.ip.tot_len = bpf_htons(olen +
				       bpf_ntohs(h_outer.ip.tot_len));
	h_outer.ip.protocol = encap_proto;

	set_ipv4_csum((व्योम *)&h_outer.ip);

	/* store new outer network header */
	अगर (bpf_skb_store_bytes(skb, ETH_HLEN, &h_outer, olen,
				BPF_F_INVALIDATE_HASH) < 0)
		वापस TC_ACT_SHOT;

	/* अगर changing outer proto type, update eth->h_proto */
	अगर (encap_proto == IPPROTO_IPV6) अणु
		काष्ठा ethhdr eth;

		अगर (bpf_skb_load_bytes(skb, 0, &eth, माप(eth)) < 0)
			वापस TC_ACT_SHOT;
		eth.h_proto = bpf_htons(ETH_P_IP);
		अगर (bpf_skb_store_bytes(skb, 0, &eth, माप(eth), 0) < 0)
			वापस TC_ACT_SHOT;
	पूर्ण

	वापस TC_ACT_OK;
पूर्ण

अटल __always_अंतरभूत पूर्णांक encap_ipv4(काष्ठा __sk_buff *skb, __u8 encap_proto,
				      __u16 l2_proto)
अणु
	वापस __encap_ipv4(skb, encap_proto, l2_proto, 0);
पूर्ण

अटल __always_अंतरभूत पूर्णांक __encap_ipv6(काष्ठा __sk_buff *skb, __u8 encap_proto,
					__u16 l2_proto, __u16 ext_proto)
अणु
	__u16 udp_dst = UDP_PORT;
	काष्ठा ipv6hdr iph_inner;
	काष्ठा v6hdr h_outer;
	काष्ठा tcphdr tcph;
	पूर्णांक olen, l2_len;
	__u8 *l2_hdr = शून्य;
	__u16 tot_len;
	__u64 flags;

	अगर (bpf_skb_load_bytes(skb, ETH_HLEN, &iph_inner,
			       माप(iph_inner)) < 0)
		वापस TC_ACT_OK;

	/* filter only packets we want */
	अगर (bpf_skb_load_bytes(skb, ETH_HLEN + माप(iph_inner),
			       &tcph, माप(tcph)) < 0)
		वापस TC_ACT_OK;

	अगर (tcph.dest != __bpf_स्थिरant_htons(cfg_port))
		वापस TC_ACT_OK;

	olen = माप(h_outer.ip);
	l2_len = 0;

	flags = BPF_F_ADJ_ROOM_FIXED_GSO | BPF_F_ADJ_ROOM_ENCAP_L3_IPV6;

	चयन (l2_proto) अणु
	हाल ETH_P_MPLS_UC:
		l2_len = माप(mpls_label);
		udp_dst = MPLS_OVER_UDP_PORT;
		अवरोध;
	हाल ETH_P_TEB:
		l2_len = ETH_HLEN;
		अगर (ext_proto & EXTPROTO_VXLAN) अणु
			udp_dst = VXLAN_UDP_PORT;
			l2_len += माप(काष्ठा vxlanhdr);
		पूर्ण अन्यथा
			udp_dst = ETH_OVER_UDP_PORT;
		अवरोध;
	पूर्ण
	flags |= BPF_F_ADJ_ROOM_ENCAP_L2(l2_len);

	चयन (encap_proto) अणु
	हाल IPPROTO_GRE:
		flags |= BPF_F_ADJ_ROOM_ENCAP_L4_GRE;
		olen += माप(h_outer.l4hdr.gre);
		h_outer.l4hdr.gre.protocol = bpf_htons(l2_proto);
		h_outer.l4hdr.gre.flags = 0;
		अवरोध;
	हाल IPPROTO_UDP:
		flags |= BPF_F_ADJ_ROOM_ENCAP_L4_UDP;
		olen += माप(h_outer.l4hdr.udp);
		h_outer.l4hdr.udp.source = __bpf_स्थिरant_htons(cfg_udp_src);
		h_outer.l4hdr.udp.dest = bpf_htons(udp_dst);
		tot_len = bpf_ntohs(iph_inner.payload_len) + माप(iph_inner) +
			  माप(h_outer.l4hdr.udp) + l2_len;
		h_outer.l4hdr.udp.check = 0;
		h_outer.l4hdr.udp.len = bpf_htons(tot_len);
		अवरोध;
	हाल IPPROTO_IPV6:
		अवरोध;
	शेष:
		वापस TC_ACT_OK;
	पूर्ण

	/* add L2 encap (अगर specअगरied) */
	l2_hdr = (__u8 *)&h_outer + olen;
	चयन (l2_proto) अणु
	हाल ETH_P_MPLS_UC:
		*(__u32 *)l2_hdr = mpls_label;
		अवरोध;
	हाल ETH_P_TEB:
		flags |= BPF_F_ADJ_ROOM_ENCAP_L2_ETH;

		अगर (ext_proto & EXTPROTO_VXLAN) अणु
			काष्ठा vxlanhdr *vxlan_hdr = (काष्ठा vxlanhdr *)l2_hdr;

			vxlan_hdr->vx_flags = VXLAN_FLAGS;
			vxlan_hdr->vx_vni = bpf_htonl((VXLAN_VNI & VXLAN_VNI_MASK) << 8);

			l2_hdr += माप(काष्ठा vxlanhdr);
		पूर्ण

		अगर (bpf_skb_load_bytes(skb, 0, l2_hdr, ETH_HLEN))
			वापस TC_ACT_SHOT;
		अवरोध;
	पूर्ण
	olen += l2_len;

	/* add room between mac and network header */
	अगर (bpf_skb_adjust_room(skb, olen, BPF_ADJ_ROOM_MAC, flags))
		वापस TC_ACT_SHOT;

	/* prepare new outer network header */
	h_outer.ip = iph_inner;
	h_outer.ip.payload_len = bpf_htons(olen +
					   bpf_ntohs(h_outer.ip.payload_len));

	h_outer.ip.nexthdr = encap_proto;

	/* store new outer network header */
	अगर (bpf_skb_store_bytes(skb, ETH_HLEN, &h_outer, olen,
				BPF_F_INVALIDATE_HASH) < 0)
		वापस TC_ACT_SHOT;

	वापस TC_ACT_OK;
पूर्ण

अटल __always_अंतरभूत पूर्णांक encap_ipv6(काष्ठा __sk_buff *skb, __u8 encap_proto,
				      __u16 l2_proto)
अणु
	वापस __encap_ipv6(skb, encap_proto, l2_proto, 0);
पूर्ण

SEC("encap_ipip_none")
पूर्णांक __encap_ipip_none(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == __bpf_स्थिरant_htons(ETH_P_IP))
		वापस encap_ipv4(skb, IPPROTO_IPIP, ETH_P_IP);
	अन्यथा
		वापस TC_ACT_OK;
पूर्ण

SEC("encap_gre_none")
पूर्णांक __encap_gre_none(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == __bpf_स्थिरant_htons(ETH_P_IP))
		वापस encap_ipv4(skb, IPPROTO_GRE, ETH_P_IP);
	अन्यथा
		वापस TC_ACT_OK;
पूर्ण

SEC("encap_gre_mpls")
पूर्णांक __encap_gre_mpls(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == __bpf_स्थिरant_htons(ETH_P_IP))
		वापस encap_ipv4(skb, IPPROTO_GRE, ETH_P_MPLS_UC);
	अन्यथा
		वापस TC_ACT_OK;
पूर्ण

SEC("encap_gre_eth")
पूर्णांक __encap_gre_eth(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == __bpf_स्थिरant_htons(ETH_P_IP))
		वापस encap_ipv4(skb, IPPROTO_GRE, ETH_P_TEB);
	अन्यथा
		वापस TC_ACT_OK;
पूर्ण

SEC("encap_udp_none")
पूर्णांक __encap_udp_none(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == __bpf_स्थिरant_htons(ETH_P_IP))
		वापस encap_ipv4(skb, IPPROTO_UDP, ETH_P_IP);
	अन्यथा
		वापस TC_ACT_OK;
पूर्ण

SEC("encap_udp_mpls")
पूर्णांक __encap_udp_mpls(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == __bpf_स्थिरant_htons(ETH_P_IP))
		वापस encap_ipv4(skb, IPPROTO_UDP, ETH_P_MPLS_UC);
	अन्यथा
		वापस TC_ACT_OK;
पूर्ण

SEC("encap_udp_eth")
पूर्णांक __encap_udp_eth(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == __bpf_स्थिरant_htons(ETH_P_IP))
		वापस encap_ipv4(skb, IPPROTO_UDP, ETH_P_TEB);
	अन्यथा
		वापस TC_ACT_OK;
पूर्ण

SEC("encap_vxlan_eth")
पूर्णांक __encap_vxlan_eth(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == __bpf_स्थिरant_htons(ETH_P_IP))
		वापस __encap_ipv4(skb, IPPROTO_UDP,
				    ETH_P_TEB,
				    EXTPROTO_VXLAN);
	अन्यथा
		वापस TC_ACT_OK;
पूर्ण

SEC("encap_sit_none")
पूर्णांक __encap_sit_none(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == __bpf_स्थिरant_htons(ETH_P_IPV6))
		वापस encap_ipv4(skb, IPPROTO_IPV6, ETH_P_IP);
	अन्यथा
		वापस TC_ACT_OK;
पूर्ण

SEC("encap_ip6tnl_none")
पूर्णांक __encap_ip6tnl_none(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == __bpf_स्थिरant_htons(ETH_P_IPV6))
		वापस encap_ipv6(skb, IPPROTO_IPV6, ETH_P_IPV6);
	अन्यथा
		वापस TC_ACT_OK;
पूर्ण

SEC("encap_ip6gre_none")
पूर्णांक __encap_ip6gre_none(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == __bpf_स्थिरant_htons(ETH_P_IPV6))
		वापस encap_ipv6(skb, IPPROTO_GRE, ETH_P_IPV6);
	अन्यथा
		वापस TC_ACT_OK;
पूर्ण

SEC("encap_ip6gre_mpls")
पूर्णांक __encap_ip6gre_mpls(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == __bpf_स्थिरant_htons(ETH_P_IPV6))
		वापस encap_ipv6(skb, IPPROTO_GRE, ETH_P_MPLS_UC);
	अन्यथा
		वापस TC_ACT_OK;
पूर्ण

SEC("encap_ip6gre_eth")
पूर्णांक __encap_ip6gre_eth(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == __bpf_स्थिरant_htons(ETH_P_IPV6))
		वापस encap_ipv6(skb, IPPROTO_GRE, ETH_P_TEB);
	अन्यथा
		वापस TC_ACT_OK;
पूर्ण

SEC("encap_ip6udp_none")
पूर्णांक __encap_ip6udp_none(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == __bpf_स्थिरant_htons(ETH_P_IPV6))
		वापस encap_ipv6(skb, IPPROTO_UDP, ETH_P_IPV6);
	अन्यथा
		वापस TC_ACT_OK;
पूर्ण

SEC("encap_ip6udp_mpls")
पूर्णांक __encap_ip6udp_mpls(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == __bpf_स्थिरant_htons(ETH_P_IPV6))
		वापस encap_ipv6(skb, IPPROTO_UDP, ETH_P_MPLS_UC);
	अन्यथा
		वापस TC_ACT_OK;
पूर्ण

SEC("encap_ip6udp_eth")
पूर्णांक __encap_ip6udp_eth(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == __bpf_स्थिरant_htons(ETH_P_IPV6))
		वापस encap_ipv6(skb, IPPROTO_UDP, ETH_P_TEB);
	अन्यथा
		वापस TC_ACT_OK;
पूर्ण

SEC("encap_ip6vxlan_eth")
पूर्णांक __encap_ip6vxlan_eth(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == __bpf_स्थिरant_htons(ETH_P_IPV6))
		वापस __encap_ipv6(skb, IPPROTO_UDP,
				    ETH_P_TEB,
				    EXTPROTO_VXLAN);
	अन्यथा
		वापस TC_ACT_OK;
पूर्ण

अटल पूर्णांक decap_पूर्णांकernal(काष्ठा __sk_buff *skb, पूर्णांक off, पूर्णांक len, अक्षर proto)
अणु
	अक्षर buf[माप(काष्ठा v6hdr)];
	काष्ठा gre_hdr greh;
	काष्ठा udphdr udph;
	पूर्णांक olen = len;

	चयन (proto) अणु
	हाल IPPROTO_IPIP:
	हाल IPPROTO_IPV6:
		अवरोध;
	हाल IPPROTO_GRE:
		olen += माप(काष्ठा gre_hdr);
		अगर (bpf_skb_load_bytes(skb, off + len, &greh, माप(greh)) < 0)
			वापस TC_ACT_OK;
		चयन (bpf_ntohs(greh.protocol)) अणु
		हाल ETH_P_MPLS_UC:
			olen += माप(mpls_label);
			अवरोध;
		हाल ETH_P_TEB:
			olen += ETH_HLEN;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IPPROTO_UDP:
		olen += माप(काष्ठा udphdr);
		अगर (bpf_skb_load_bytes(skb, off + len, &udph, माप(udph)) < 0)
			वापस TC_ACT_OK;
		चयन (bpf_ntohs(udph.dest)) अणु
		हाल MPLS_OVER_UDP_PORT:
			olen += माप(mpls_label);
			अवरोध;
		हाल ETH_OVER_UDP_PORT:
			olen += ETH_HLEN;
			अवरोध;
		हाल VXLAN_UDP_PORT:
			olen += ETH_HLEN + माप(काष्ठा vxlanhdr);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		वापस TC_ACT_OK;
	पूर्ण

	अगर (bpf_skb_adjust_room(skb, -olen, BPF_ADJ_ROOM_MAC,
				BPF_F_ADJ_ROOM_FIXED_GSO))
		वापस TC_ACT_SHOT;

	वापस TC_ACT_OK;
पूर्ण

अटल पूर्णांक decap_ipv4(काष्ठा __sk_buff *skb)
अणु
	काष्ठा iphdr iph_outer;

	अगर (bpf_skb_load_bytes(skb, ETH_HLEN, &iph_outer,
			       माप(iph_outer)) < 0)
		वापस TC_ACT_OK;

	अगर (iph_outer.ihl != 5)
		वापस TC_ACT_OK;

	वापस decap_पूर्णांकernal(skb, ETH_HLEN, माप(iph_outer),
			      iph_outer.protocol);
पूर्ण

अटल पूर्णांक decap_ipv6(काष्ठा __sk_buff *skb)
अणु
	काष्ठा ipv6hdr iph_outer;

	अगर (bpf_skb_load_bytes(skb, ETH_HLEN, &iph_outer,
			       माप(iph_outer)) < 0)
		वापस TC_ACT_OK;

	वापस decap_पूर्णांकernal(skb, ETH_HLEN, माप(iph_outer),
			      iph_outer.nexthdr);
पूर्ण

SEC("decap")
पूर्णांक decap_f(काष्ठा __sk_buff *skb)
अणु
	चयन (skb->protocol) अणु
	हाल __bpf_स्थिरant_htons(ETH_P_IP):
		वापस decap_ipv4(skb);
	हाल __bpf_स्थिरant_htons(ETH_P_IPV6):
		वापस decap_ipv6(skb);
	शेष:
		/* करोes not match, ignore */
		वापस TC_ACT_OK;
	पूर्ण
पूर्ण

अक्षर __license[] SEC("license") = "GPL";
