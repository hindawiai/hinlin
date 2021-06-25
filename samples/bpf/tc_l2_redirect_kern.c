<शैली गुरु>
/* Copyright (c) 2016 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#घोषणा KBUILD_MODNAME "foo"
#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/अगर_ether.h>
#समावेश <uapi/linux/अगर_packet.h>
#समावेश <uapi/linux/ip.h>
#समावेश <uapi/linux/ipv6.h>
#समावेश <uapi/linux/in.h>
#समावेश <uapi/linux/tcp.h>
#समावेश <uapi/linux/filter.h>
#समावेश <uapi/linux/pkt_cls.h>
#समावेश <net/ipv6.h>
#समावेश <bpf/bpf_helpers.h>

#घोषणा _htonl __builtin_bswap32

#घोषणा PIN_GLOBAL_NS		2
काष्ठा bpf_elf_map अणु
	__u32 type;
	__u32 size_key;
	__u32 size_value;
	__u32 max_elem;
	__u32 flags;
	__u32 id;
	__u32 pinning;
पूर्ण;

/* copy of 'struct ethhdr' without __packed */
काष्ठा eth_hdr अणु
	अचिन्हित अक्षर   h_dest[ETH_ALEN];
	अचिन्हित अक्षर   h_source[ETH_ALEN];
	अचिन्हित लघु  h_proto;
पूर्ण;

काष्ठा bpf_elf_map SEC("maps") tun_अगरace = अणु
	.type = BPF_MAP_TYPE_ARRAY,
	.size_key = माप(पूर्णांक),
	.size_value = माप(पूर्णांक),
	.pinning = PIN_GLOBAL_NS,
	.max_elem = 1,
पूर्ण;

अटल __always_अंतरभूत bool is_vip_addr(__be16 eth_proto, __be32 daddr)
अणु
	अगर (eth_proto == htons(ETH_P_IP))
		वापस (_htonl(0xffffff00) & daddr) == _htonl(0x0a0a0100);
	अन्यथा अगर (eth_proto == htons(ETH_P_IPV6))
		वापस (daddr == _htonl(0x2401face));

	वापस false;
पूर्ण

SEC("l2_to_iptun_ingress_forward")
पूर्णांक _l2_to_iptun_ingress_क्रमward(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_tunnel_key tkey = अणुपूर्ण;
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	काष्ठा eth_hdr *eth = data;
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	पूर्णांक key = 0, *अगरindex;

	पूर्णांक ret;

	अगर (data + माप(*eth) > data_end)
		वापस TC_ACT_OK;

	अगरindex = bpf_map_lookup_elem(&tun_अगरace, &key);
	अगर (!अगरindex)
		वापस TC_ACT_OK;

	अगर (eth->h_proto == htons(ETH_P_IP)) अणु
		अक्षर fmt4[] = "ingress forward to ifindex:%d daddr4:%x\n";
		काष्ठा iphdr *iph = data + माप(*eth);

		अगर (data + माप(*eth) + माप(*iph) > data_end)
			वापस TC_ACT_OK;

		अगर (iph->protocol != IPPROTO_IPIP)
			वापस TC_ACT_OK;

		bpf_trace_prपूर्णांकk(fmt4, माप(fmt4), *अगरindex,
				 _htonl(iph->daddr));
		वापस bpf_redirect(*अगरindex, BPF_F_INGRESS);
	पूर्ण अन्यथा अगर (eth->h_proto == htons(ETH_P_IPV6)) अणु
		अक्षर fmt6[] = "ingress forward to ifindex:%d daddr6:%x::%x\n";
		काष्ठा ipv6hdr *ip6h = data + माप(*eth);

		अगर (data + माप(*eth) + माप(*ip6h) > data_end)
			वापस TC_ACT_OK;

		अगर (ip6h->nexthdr != IPPROTO_IPIP &&
		    ip6h->nexthdr != IPPROTO_IPV6)
			वापस TC_ACT_OK;

		bpf_trace_prपूर्णांकk(fmt6, माप(fmt6), *अगरindex,
				 _htonl(ip6h->daddr.s6_addr32[0]),
				 _htonl(ip6h->daddr.s6_addr32[3]));
		वापस bpf_redirect(*अगरindex, BPF_F_INGRESS);
	पूर्ण

	वापस TC_ACT_OK;
पूर्ण

SEC("l2_to_iptun_ingress_redirect")
पूर्णांक _l2_to_iptun_ingress_redirect(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_tunnel_key tkey = अणुपूर्ण;
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	काष्ठा eth_hdr *eth = data;
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	पूर्णांक key = 0, *अगरindex;

	पूर्णांक ret;

	अगर (data + माप(*eth) > data_end)
		वापस TC_ACT_OK;

	अगरindex = bpf_map_lookup_elem(&tun_अगरace, &key);
	अगर (!अगरindex)
		वापस TC_ACT_OK;

	अगर (eth->h_proto == htons(ETH_P_IP)) अणु
		अक्षर fmt4[] = "e/ingress redirect daddr4:%x to ifindex:%d\n";
		काष्ठा iphdr *iph = data + माप(*eth);
		__be32 daddr = iph->daddr;

		अगर (data + माप(*eth) + माप(*iph) > data_end)
			वापस TC_ACT_OK;

		अगर (!is_vip_addr(eth->h_proto, daddr))
			वापस TC_ACT_OK;

		bpf_trace_prपूर्णांकk(fmt4, माप(fmt4), _htonl(daddr), *अगरindex);
	पूर्ण अन्यथा अणु
		वापस TC_ACT_OK;
	पूर्ण

	tkey.tunnel_id = 10000;
	tkey.tunnel_ttl = 64;
	tkey.remote_ipv4 = 0x0a020166; /* 10.2.1.102 */
	bpf_skb_set_tunnel_key(skb, &tkey, माप(tkey), 0);
	वापस bpf_redirect(*अगरindex, 0);
पूर्ण

SEC("l2_to_ip6tun_ingress_redirect")
पूर्णांक _l2_to_ip6tun_ingress_redirect(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_tunnel_key tkey = अणुपूर्ण;
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	काष्ठा eth_hdr *eth = data;
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	पूर्णांक key = 0, *अगरindex;

	अगर (data + माप(*eth) > data_end)
		वापस TC_ACT_OK;

	अगरindex = bpf_map_lookup_elem(&tun_अगरace, &key);
	अगर (!अगरindex)
		वापस TC_ACT_OK;

	अगर (eth->h_proto == htons(ETH_P_IP)) अणु
		अक्षर fmt4[] = "e/ingress redirect daddr4:%x to ifindex:%d\n";
		काष्ठा iphdr *iph = data + माप(*eth);

		अगर (data + माप(*eth) + माप(*iph) > data_end)
			वापस TC_ACT_OK;

		अगर (!is_vip_addr(eth->h_proto, iph->daddr))
			वापस TC_ACT_OK;

		bpf_trace_prपूर्णांकk(fmt4, माप(fmt4), _htonl(iph->daddr),
				 *अगरindex);
	पूर्ण अन्यथा अगर (eth->h_proto == htons(ETH_P_IPV6)) अणु
		अक्षर fmt6[] = "e/ingress redirect daddr6:%x to ifindex:%d\n";
		काष्ठा ipv6hdr *ip6h = data + माप(*eth);

		अगर (data + माप(*eth) + माप(*ip6h) > data_end)
			वापस TC_ACT_OK;

		अगर (!is_vip_addr(eth->h_proto, ip6h->daddr.s6_addr32[0]))
			वापस TC_ACT_OK;

		bpf_trace_prपूर्णांकk(fmt6, माप(fmt6),
				 _htonl(ip6h->daddr.s6_addr32[0]), *अगरindex);
	पूर्ण अन्यथा अणु
		वापस TC_ACT_OK;
	पूर्ण

	tkey.tunnel_id = 10000;
	tkey.tunnel_ttl = 64;
	/* 2401:db02:0:0:0:0:0:66 */
	tkey.remote_ipv6[0] = _htonl(0x2401db02);
	tkey.remote_ipv6[1] = 0;
	tkey.remote_ipv6[2] = 0;
	tkey.remote_ipv6[3] = _htonl(0x00000066);
	bpf_skb_set_tunnel_key(skb, &tkey, माप(tkey), BPF_F_TUNINFO_IPV6);
	वापस bpf_redirect(*अगरindex, 0);
पूर्ण

SEC("drop_non_tun_vip")
पूर्णांक _drop_non_tun_vip(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_tunnel_key tkey = अणुपूर्ण;
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	काष्ठा eth_hdr *eth = data;
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;

	अगर (data + माप(*eth) > data_end)
		वापस TC_ACT_OK;

	अगर (eth->h_proto == htons(ETH_P_IP)) अणु
		काष्ठा iphdr *iph = data + माप(*eth);

		अगर (data + माप(*eth) + माप(*iph) > data_end)
			वापस TC_ACT_OK;

		अगर (is_vip_addr(eth->h_proto, iph->daddr))
			वापस TC_ACT_SHOT;
	पूर्ण अन्यथा अगर (eth->h_proto == htons(ETH_P_IPV6)) अणु
		काष्ठा ipv6hdr *ip6h = data + माप(*eth);

		अगर (data + माप(*eth) + माप(*ip6h) > data_end)
			वापस TC_ACT_OK;

		अगर (is_vip_addr(eth->h_proto, ip6h->daddr.s6_addr32[0]))
			वापस TC_ACT_SHOT;
	पूर्ण

	वापस TC_ACT_OK;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
