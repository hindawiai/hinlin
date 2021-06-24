<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2017-18 David Ahern <dsahern@gmail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License क्रम more details.
 */
#घोषणा KBUILD_MODNAME "foo"
#समावेश <uapi/linux/bpf.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>

#समावेश <bpf/bpf_helpers.h>

#घोषणा IPV6_FLOWINFO_MASK              cpu_to_be32(0x0FFFFFFF)

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_DEVMAP);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
	__uपूर्णांक(max_entries, 64);
पूर्ण xdp_tx_ports SEC(".maps");

/* from include/net/ip.h */
अटल __always_अंतरभूत पूर्णांक ip_decrease_ttl(काष्ठा iphdr *iph)
अणु
	u32 check = (__क्रमce u32)iph->check;

	check += (__क्रमce u32)htons(0x0100);
	iph->check = (__क्रमce __sum16)(check + (check >= 0xFFFF));
	वापस --iph->ttl;
पूर्ण

अटल __always_अंतरभूत पूर्णांक xdp_fwd_flags(काष्ठा xdp_md *ctx, u32 flags)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा bpf_fib_lookup fib_params;
	काष्ठा ethhdr *eth = data;
	काष्ठा ipv6hdr *ip6h;
	काष्ठा iphdr *iph;
	u16 h_proto;
	u64 nh_off;
	पूर्णांक rc;

	nh_off = माप(*eth);
	अगर (data + nh_off > data_end)
		वापस XDP_DROP;

	__builtin_स_रखो(&fib_params, 0, माप(fib_params));

	h_proto = eth->h_proto;
	अगर (h_proto == htons(ETH_P_IP)) अणु
		iph = data + nh_off;

		अगर (iph + 1 > data_end)
			वापस XDP_DROP;

		अगर (iph->ttl <= 1)
			वापस XDP_PASS;

		fib_params.family	= AF_INET;
		fib_params.tos		= iph->tos;
		fib_params.l4_protocol	= iph->protocol;
		fib_params.sport	= 0;
		fib_params.dport	= 0;
		fib_params.tot_len	= ntohs(iph->tot_len);
		fib_params.ipv4_src	= iph->saddr;
		fib_params.ipv4_dst	= iph->daddr;
	पूर्ण अन्यथा अगर (h_proto == htons(ETH_P_IPV6)) अणु
		काष्ठा in6_addr *src = (काष्ठा in6_addr *) fib_params.ipv6_src;
		काष्ठा in6_addr *dst = (काष्ठा in6_addr *) fib_params.ipv6_dst;

		ip6h = data + nh_off;
		अगर (ip6h + 1 > data_end)
			वापस XDP_DROP;

		अगर (ip6h->hop_limit <= 1)
			वापस XDP_PASS;

		fib_params.family	= AF_INET6;
		fib_params.flowinfo	= *(__be32 *)ip6h & IPV6_FLOWINFO_MASK;
		fib_params.l4_protocol	= ip6h->nexthdr;
		fib_params.sport	= 0;
		fib_params.dport	= 0;
		fib_params.tot_len	= ntohs(ip6h->payload_len);
		*src			= ip6h->saddr;
		*dst			= ip6h->daddr;
	पूर्ण अन्यथा अणु
		वापस XDP_PASS;
	पूर्ण

	fib_params.अगरindex = ctx->ingress_अगरindex;

	rc = bpf_fib_lookup(ctx, &fib_params, माप(fib_params), flags);
	/*
	 * Some rc (वापस codes) from bpf_fib_lookup() are important,
	 * to understand how this XDP-prog पूर्णांकeracts with network stack.
	 *
	 * BPF_FIB_LKUP_RET_NO_NEIGH:
	 *  Even अगर route lookup was a success, then the MAC-addresses are also
	 *  needed.  This is obtained from arp/neighbour table, but अगर table is
	 *  (still) empty then BPF_FIB_LKUP_RET_NO_NEIGH is वापसed.  To aव्योम
	 *  करोing ARP lookup directly from XDP, then send packet to normal
	 *  network stack via XDP_PASS and expect it will करो ARP resolution.
	 *
	 * BPF_FIB_LKUP_RET_FWD_DISABLED:
	 *  The bpf_fib_lookup respect sysctl net.ipvअणु4,6पूर्ण.conf.all.क्रमwarding
	 *  setting, and will वापस BPF_FIB_LKUP_RET_FWD_DISABLED अगर not
	 *  enabled this on ingress device.
	 */
	अगर (rc == BPF_FIB_LKUP_RET_SUCCESS) अणु
		/* Verअगरy egress index has been configured as TX-port.
		 * (Note: User can still have inserted an egress अगरindex that
		 * करोesn't support XDP xmit, which will result in packet drops).
		 *
		 * Note: lookup in devmap supported since 0cdbb4b09a0.
		 * If not supported will fail with:
		 *  cannot pass map_type 14 पूर्णांकo func bpf_map_lookup_elem#1:
		 */
		अगर (!bpf_map_lookup_elem(&xdp_tx_ports, &fib_params.अगरindex))
			वापस XDP_PASS;

		अगर (h_proto == htons(ETH_P_IP))
			ip_decrease_ttl(iph);
		अन्यथा अगर (h_proto == htons(ETH_P_IPV6))
			ip6h->hop_limit--;

		स_नकल(eth->h_dest, fib_params.dmac, ETH_ALEN);
		स_नकल(eth->h_source, fib_params.smac, ETH_ALEN);
		वापस bpf_redirect_map(&xdp_tx_ports, fib_params.अगरindex, 0);
	पूर्ण

	वापस XDP_PASS;
पूर्ण

SEC("xdp_fwd")
पूर्णांक xdp_fwd_prog(काष्ठा xdp_md *ctx)
अणु
	वापस xdp_fwd_flags(ctx, 0);
पूर्ण

SEC("xdp_fwd_direct")
पूर्णांक xdp_fwd_direct_prog(काष्ठा xdp_md *ctx)
अणु
	वापस xdp_fwd_flags(ctx, BPF_FIB_LOOKUP_सूचीECT);
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
