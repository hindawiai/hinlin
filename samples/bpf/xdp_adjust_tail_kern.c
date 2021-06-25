<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Copyright (c) 2018 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program shows how to use bpf_xdp_adjust_tail() by
 * generating ICMPv4 "packet to big" (unreachable/ df bit set frag needed
 * to be more preice in हाल of v4)" where receiving packets bigger then
 * 600 bytes.
 */
#घोषणा KBUILD_MODNAME "foo"
#समावेश <uapi/linux/bpf.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/icmp.h>
#समावेश <bpf/bpf_helpers.h>

#घोषणा DEFAULT_TTL 64
#घोषणा MAX_PCKT_SIZE 600
#घोषणा ICMP_TOOBIG_SIZE 98
#घोषणा ICMP_TOOBIG_PAYLOAD_SIZE 92

/* अस्थिर to prevent compiler optimizations */
अटल अस्थिर __u32 max_pcktsz = MAX_PCKT_SIZE;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, __u32);
	__type(value, __u64);
	__uपूर्णांक(max_entries, 1);
पूर्ण icmpcnt SEC(".maps");

अटल __always_अंतरभूत व्योम count_icmp(व्योम)
अणु
	u64 key = 0;
	u64 *icmp_count;

	icmp_count = bpf_map_lookup_elem(&icmpcnt, &key);
	अगर (icmp_count)
		*icmp_count += 1;
पूर्ण

अटल __always_अंतरभूत व्योम swap_mac(व्योम *data, काष्ठा ethhdr *orig_eth)
अणु
	काष्ठा ethhdr *eth;

	eth = data;
	स_नकल(eth->h_source, orig_eth->h_dest, ETH_ALEN);
	स_नकल(eth->h_dest, orig_eth->h_source, ETH_ALEN);
	eth->h_proto = orig_eth->h_proto;
पूर्ण

अटल __always_अंतरभूत __u16 csum_fold_helper(__u32 csum)
अणु
	वापस ~((csum & 0xffff) + (csum >> 16));
पूर्ण

अटल __always_अंतरभूत व्योम ipv4_csum(व्योम *data_start, पूर्णांक data_size,
				      __u32 *csum)
अणु
	*csum = bpf_csum_dअगरf(0, 0, data_start, data_size, *csum);
	*csum = csum_fold_helper(*csum);
पूर्ण

अटल __always_अंतरभूत पूर्णांक send_icmp4_too_big(काष्ठा xdp_md *xdp)
अणु
	पूर्णांक headroom = (पूर्णांक)माप(काष्ठा iphdr) + (पूर्णांक)माप(काष्ठा icmphdr);

	अगर (bpf_xdp_adjust_head(xdp, 0 - headroom))
		वापस XDP_DROP;
	व्योम *data = (व्योम *)(दीर्घ)xdp->data;
	व्योम *data_end = (व्योम *)(दीर्घ)xdp->data_end;

	अगर (data + (ICMP_TOOBIG_SIZE + headroom) > data_end)
		वापस XDP_DROP;

	काष्ठा iphdr *iph, *orig_iph;
	काष्ठा icmphdr *icmp_hdr;
	काष्ठा ethhdr *orig_eth;
	__u32 csum = 0;
	__u64 off = 0;

	orig_eth = data + headroom;
	swap_mac(data, orig_eth);
	off += माप(काष्ठा ethhdr);
	iph = data + off;
	off += माप(काष्ठा iphdr);
	icmp_hdr = data + off;
	off += माप(काष्ठा icmphdr);
	orig_iph = data + off;
	icmp_hdr->type = ICMP_DEST_UNREACH;
	icmp_hdr->code = ICMP_FRAG_NEEDED;
	icmp_hdr->un.frag.mtu = htons(max_pcktsz - माप(काष्ठा ethhdr));
	icmp_hdr->checksum = 0;
	ipv4_csum(icmp_hdr, ICMP_TOOBIG_PAYLOAD_SIZE, &csum);
	icmp_hdr->checksum = csum;
	iph->ttl = DEFAULT_TTL;
	iph->daddr = orig_iph->saddr;
	iph->saddr = orig_iph->daddr;
	iph->version = 4;
	iph->ihl = 5;
	iph->protocol = IPPROTO_ICMP;
	iph->tos = 0;
	iph->tot_len = htons(
		ICMP_TOOBIG_SIZE + headroom - माप(काष्ठा ethhdr));
	iph->check = 0;
	csum = 0;
	ipv4_csum(iph, माप(काष्ठा iphdr), &csum);
	iph->check = csum;
	count_icmp();
	वापस XDP_TX;
पूर्ण


अटल __always_अंतरभूत पूर्णांक handle_ipv4(काष्ठा xdp_md *xdp)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)xdp->data_end;
	व्योम *data = (व्योम *)(दीर्घ)xdp->data;
	पूर्णांक pckt_size = data_end - data;
	पूर्णांक offset;

	अगर (pckt_size > max(max_pcktsz, ICMP_TOOBIG_SIZE)) अणु
		offset = pckt_size - ICMP_TOOBIG_SIZE;
		अगर (bpf_xdp_adjust_tail(xdp, 0 - offset))
			वापस XDP_PASS;
		वापस send_icmp4_too_big(xdp);
	पूर्ण
	वापस XDP_PASS;
पूर्ण

SEC("xdp_icmp")
पूर्णांक _xdp_icmp(काष्ठा xdp_md *xdp)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)xdp->data_end;
	व्योम *data = (व्योम *)(दीर्घ)xdp->data;
	काष्ठा ethhdr *eth = data;
	__u16 h_proto;

	अगर (eth + 1 > data_end)
		वापस XDP_DROP;

	h_proto = eth->h_proto;

	अगर (h_proto == htons(ETH_P_IP))
		वापस handle_ipv4(xdp);
	अन्यथा
		वापस XDP_PASS;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
