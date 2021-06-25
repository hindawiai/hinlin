<शैली गुरु>
/* Copyright (c) 2016 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#घोषणा KBUILD_MODNAME "foo"
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/in.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <net/ip.h>
#समावेश <bpf/bpf_helpers.h>

#घोषणा DEFAULT_PKTGEN_UDP_PORT 9
#घोषणा DEBUG 0

अटल पूर्णांक tcp(व्योम *data, uपूर्णांक64_t tp_off, व्योम *data_end)
अणु
	काष्ठा tcphdr *tcp = data + tp_off;

	अगर (tcp + 1 > data_end)
		वापस 0;
	अगर (tcp->dest == htons(80) || tcp->source == htons(80))
		वापस TC_ACT_SHOT;
	वापस 0;
पूर्ण

अटल पूर्णांक udp(व्योम *data, uपूर्णांक64_t tp_off, व्योम *data_end)
अणु
	काष्ठा udphdr *udp = data + tp_off;

	अगर (udp + 1 > data_end)
		वापस 0;
	अगर (udp->dest == htons(DEFAULT_PKTGEN_UDP_PORT) ||
	    udp->source == htons(DEFAULT_PKTGEN_UDP_PORT)) अणु
		अगर (DEBUG) अणु
			अक्षर fmt[] = "udp port 9 indeed\n";

			bpf_trace_prपूर्णांकk(fmt, माप(fmt));
		पूर्ण
		वापस TC_ACT_SHOT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक parse_ipv4(व्योम *data, uपूर्णांक64_t nh_off, व्योम *data_end)
अणु
	काष्ठा iphdr *iph;
	uपूर्णांक64_t ihl_len;

	iph = data + nh_off;
	अगर (iph + 1 > data_end)
		वापस 0;

	अगर (ip_is_fragment(iph))
		वापस 0;
	ihl_len = iph->ihl * 4;

	अगर (iph->protocol == IPPROTO_IPIP) अणु
		iph = data + nh_off + ihl_len;
		अगर (iph + 1 > data_end)
			वापस 0;
		ihl_len += iph->ihl * 4;
	पूर्ण

	अगर (iph->protocol == IPPROTO_TCP)
		वापस tcp(data, nh_off + ihl_len, data_end);
	अन्यथा अगर (iph->protocol == IPPROTO_UDP)
		वापस udp(data, nh_off + ihl_len, data_end);
	वापस 0;
पूर्ण

अटल पूर्णांक parse_ipv6(व्योम *data, uपूर्णांक64_t nh_off, व्योम *data_end)
अणु
	काष्ठा ipv6hdr *ip6h;
	काष्ठा iphdr *iph;
	uपूर्णांक64_t ihl_len = माप(काष्ठा ipv6hdr);
	uपूर्णांक64_t nexthdr;

	ip6h = data + nh_off;
	अगर (ip6h + 1 > data_end)
		वापस 0;

	nexthdr = ip6h->nexthdr;

	अगर (nexthdr == IPPROTO_IPIP) अणु
		iph = data + nh_off + ihl_len;
		अगर (iph + 1 > data_end)
			वापस 0;
		ihl_len += iph->ihl * 4;
		nexthdr = iph->protocol;
	पूर्ण अन्यथा अगर (nexthdr == IPPROTO_IPV6) अणु
		ip6h = data + nh_off + ihl_len;
		अगर (ip6h + 1 > data_end)
			वापस 0;
		ihl_len += माप(काष्ठा ipv6hdr);
		nexthdr = ip6h->nexthdr;
	पूर्ण

	अगर (nexthdr == IPPROTO_TCP)
		वापस tcp(data, nh_off + ihl_len, data_end);
	अन्यथा अगर (nexthdr == IPPROTO_UDP)
		वापस udp(data, nh_off + ihl_len, data_end);
	वापस 0;
पूर्ण

SEC("varlen")
पूर्णांक handle_ingress(काष्ठा __sk_buff *skb)
अणु
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	काष्ठा ethhdr *eth = data;
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	uपूर्णांक64_t h_proto, nh_off;

	nh_off = माप(*eth);
	अगर (data + nh_off > data_end)
		वापस 0;

	h_proto = eth->h_proto;

	अगर (h_proto == ETH_P_8021Q || h_proto == ETH_P_8021AD) अणु
		काष्ठा vlan_hdr *vhdr;

		vhdr = data + nh_off;
		nh_off += माप(काष्ठा vlan_hdr);
		अगर (data + nh_off > data_end)
			वापस 0;
		h_proto = vhdr->h_vlan_encapsulated_proto;
	पूर्ण
	अगर (h_proto == ETH_P_8021Q || h_proto == ETH_P_8021AD) अणु
		काष्ठा vlan_hdr *vhdr;

		vhdr = data + nh_off;
		nh_off += माप(काष्ठा vlan_hdr);
		अगर (data + nh_off > data_end)
			वापस 0;
		h_proto = vhdr->h_vlan_encapsulated_proto;
	पूर्ण
	अगर (h_proto == htons(ETH_P_IP))
		वापस parse_ipv4(data, nh_off, data_end);
	अन्यथा अगर (h_proto == htons(ETH_P_IPV6))
		वापस parse_ipv6(data, nh_off, data_end);
	वापस 0;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
