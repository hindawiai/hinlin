<शैली गुरु>
/* Copyright (c) 2016,2017 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/in.h>
#समावेश <linux/udp.h>
#समावेश <linux/tcp.h>
#समावेश <linux/pkt_cls.h>
#समावेश <sys/socket.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>
#समावेश "test_iptunnel_common.h"

पूर्णांक _version SEC("version") = 1;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(max_entries, 256);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण rxcnt SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, MAX_IPTNL_ENTRIES);
	__type(key, काष्ठा vip);
	__type(value, काष्ठा iptnl_info);
पूर्ण vip2tnl SEC(".maps");

अटल __always_अंतरभूत व्योम count_tx(__u32 protocol)
अणु
	__u64 *rxcnt_count;

	rxcnt_count = bpf_map_lookup_elem(&rxcnt, &protocol);
	अगर (rxcnt_count)
		*rxcnt_count += 1;
पूर्ण

अटल __always_अंतरभूत पूर्णांक get_dport(व्योम *trans_data, व्योम *data_end,
				     __u8 protocol)
अणु
	काष्ठा tcphdr *th;
	काष्ठा udphdr *uh;

	चयन (protocol) अणु
	हाल IPPROTO_TCP:
		th = (काष्ठा tcphdr *)trans_data;
		अगर (th + 1 > data_end)
			वापस -1;
		वापस th->dest;
	हाल IPPROTO_UDP:
		uh = (काष्ठा udphdr *)trans_data;
		अगर (uh + 1 > data_end)
			वापस -1;
		वापस uh->dest;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम set_ethhdr(काष्ठा ethhdr *new_eth,
				       स्थिर काष्ठा ethhdr *old_eth,
				       स्थिर काष्ठा iptnl_info *tnl,
				       __be16 h_proto)
अणु
	स_नकल(new_eth->h_source, old_eth->h_dest, माप(new_eth->h_source));
	स_नकल(new_eth->h_dest, tnl->dmac, माप(new_eth->h_dest));
	new_eth->h_proto = h_proto;
पूर्ण

अटल __always_अंतरभूत पूर्णांक handle_ipv4(काष्ठा xdp_md *xdp)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)xdp->data_end;
	व्योम *data = (व्योम *)(दीर्घ)xdp->data;
	काष्ठा iptnl_info *tnl;
	काष्ठा ethhdr *new_eth;
	काष्ठा ethhdr *old_eth;
	काष्ठा iphdr *iph = data + माप(काष्ठा ethhdr);
	__u16 *next_iph;
	__u16 payload_len;
	काष्ठा vip vip = अणुपूर्ण;
	पूर्णांक dport;
	__u32 csum = 0;
	पूर्णांक i;

	अगर (iph + 1 > data_end)
		वापस XDP_DROP;

	dport = get_dport(iph + 1, data_end, iph->protocol);
	अगर (dport == -1)
		वापस XDP_DROP;

	vip.protocol = iph->protocol;
	vip.family = AF_INET;
	vip.daddr.v4 = iph->daddr;
	vip.dport = dport;
	payload_len = bpf_ntohs(iph->tot_len);

	tnl = bpf_map_lookup_elem(&vip2tnl, &vip);
	/* It only करोes v4-in-v4 */
	अगर (!tnl || tnl->family != AF_INET)
		वापस XDP_PASS;

	अगर (bpf_xdp_adjust_head(xdp, 0 - (पूर्णांक)माप(काष्ठा iphdr)))
		वापस XDP_DROP;

	data = (व्योम *)(दीर्घ)xdp->data;
	data_end = (व्योम *)(दीर्घ)xdp->data_end;

	new_eth = data;
	iph = data + माप(*new_eth);
	old_eth = data + माप(*iph);

	अगर (new_eth + 1 > data_end ||
	    old_eth + 1 > data_end ||
	    iph + 1 > data_end)
		वापस XDP_DROP;

	set_ethhdr(new_eth, old_eth, tnl, bpf_htons(ETH_P_IP));

	iph->version = 4;
	iph->ihl = माप(*iph) >> 2;
	iph->frag_off =	0;
	iph->protocol = IPPROTO_IPIP;
	iph->check = 0;
	iph->tos = 0;
	iph->tot_len = bpf_htons(payload_len + माप(*iph));
	iph->daddr = tnl->daddr.v4;
	iph->saddr = tnl->saddr.v4;
	iph->ttl = 8;

	next_iph = (__u16 *)iph;
#आशय clang loop unroll(full)
	क्रम (i = 0; i < माप(*iph) >> 1; i++)
		csum += *next_iph++;

	iph->check = ~((csum & 0xffff) + (csum >> 16));

	count_tx(vip.protocol);

	वापस XDP_TX;
पूर्ण

अटल __always_अंतरभूत पूर्णांक handle_ipv6(काष्ठा xdp_md *xdp)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)xdp->data_end;
	व्योम *data = (व्योम *)(दीर्घ)xdp->data;
	काष्ठा iptnl_info *tnl;
	काष्ठा ethhdr *new_eth;
	काष्ठा ethhdr *old_eth;
	काष्ठा ipv6hdr *ip6h = data + माप(काष्ठा ethhdr);
	__u16 payload_len;
	काष्ठा vip vip = अणुपूर्ण;
	पूर्णांक dport;

	अगर (ip6h + 1 > data_end)
		वापस XDP_DROP;

	dport = get_dport(ip6h + 1, data_end, ip6h->nexthdr);
	अगर (dport == -1)
		वापस XDP_DROP;

	vip.protocol = ip6h->nexthdr;
	vip.family = AF_INET6;
	स_नकल(vip.daddr.v6, ip6h->daddr.s6_addr32, माप(vip.daddr));
	vip.dport = dport;
	payload_len = ip6h->payload_len;

	tnl = bpf_map_lookup_elem(&vip2tnl, &vip);
	/* It only करोes v6-in-v6 */
	अगर (!tnl || tnl->family != AF_INET6)
		वापस XDP_PASS;

	अगर (bpf_xdp_adjust_head(xdp, 0 - (पूर्णांक)माप(काष्ठा ipv6hdr)))
		वापस XDP_DROP;

	data = (व्योम *)(दीर्घ)xdp->data;
	data_end = (व्योम *)(दीर्घ)xdp->data_end;

	new_eth = data;
	ip6h = data + माप(*new_eth);
	old_eth = data + माप(*ip6h);

	अगर (new_eth + 1 > data_end || old_eth + 1 > data_end ||
	    ip6h + 1 > data_end)
		वापस XDP_DROP;

	set_ethhdr(new_eth, old_eth, tnl, bpf_htons(ETH_P_IPV6));

	ip6h->version = 6;
	ip6h->priority = 0;
	स_रखो(ip6h->flow_lbl, 0, माप(ip6h->flow_lbl));
	ip6h->payload_len = bpf_htons(bpf_ntohs(payload_len) + माप(*ip6h));
	ip6h->nexthdr = IPPROTO_IPV6;
	ip6h->hop_limit = 8;
	स_नकल(ip6h->saddr.s6_addr32, tnl->saddr.v6, माप(tnl->saddr.v6));
	स_नकल(ip6h->daddr.s6_addr32, tnl->daddr.v6, माप(tnl->daddr.v6));

	count_tx(vip.protocol);

	वापस XDP_TX;
पूर्ण

SEC("xdp_tx_iptunnel")
पूर्णांक _xdp_tx_iptunnel(काष्ठा xdp_md *xdp)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)xdp->data_end;
	व्योम *data = (व्योम *)(दीर्घ)xdp->data;
	काष्ठा ethhdr *eth = data;
	__u16 h_proto;

	अगर (eth + 1 > data_end)
		वापस XDP_DROP;

	h_proto = eth->h_proto;

	अगर (h_proto == bpf_htons(ETH_P_IP))
		वापस handle_ipv4(xdp);
	अन्यथा अगर (h_proto == bpf_htons(ETH_P_IPV6))

		वापस handle_ipv6(xdp);
	अन्यथा
		वापस XDP_DROP;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
