<शैली गुरु>
/* Copyright (c) 2016 PLUMgrid
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
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

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__type(key, u32);
	__type(value, दीर्घ);
	__uपूर्णांक(max_entries, 256);
पूर्ण rxcnt SEC(".maps");

अटल व्योम swap_src_dst_mac(व्योम *data)
अणु
	अचिन्हित लघु *p = data;
	अचिन्हित लघु dst[3];

	dst[0] = p[0];
	dst[1] = p[1];
	dst[2] = p[2];
	p[0] = p[3];
	p[1] = p[4];
	p[2] = p[5];
	p[3] = dst[0];
	p[4] = dst[1];
	p[5] = dst[2];
पूर्ण

अटल पूर्णांक parse_ipv4(व्योम *data, u64 nh_off, व्योम *data_end)
अणु
	काष्ठा iphdr *iph = data + nh_off;

	अगर (iph + 1 > data_end)
		वापस 0;
	वापस iph->protocol;
पूर्ण

अटल पूर्णांक parse_ipv6(व्योम *data, u64 nh_off, व्योम *data_end)
अणु
	काष्ठा ipv6hdr *ip6h = data + nh_off;

	अगर (ip6h + 1 > data_end)
		वापस 0;
	वापस ip6h->nexthdr;
पूर्ण

SEC("xdp1")
पूर्णांक xdp_prog1(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा ethhdr *eth = data;
	पूर्णांक rc = XDP_DROP;
	दीर्घ *value;
	u16 h_proto;
	u64 nh_off;
	u32 ipproto;

	nh_off = माप(*eth);
	अगर (data + nh_off > data_end)
		वापस rc;

	h_proto = eth->h_proto;

	अगर (h_proto == htons(ETH_P_8021Q) || h_proto == htons(ETH_P_8021AD)) अणु
		काष्ठा vlan_hdr *vhdr;

		vhdr = data + nh_off;
		nh_off += माप(काष्ठा vlan_hdr);
		अगर (data + nh_off > data_end)
			वापस rc;
		h_proto = vhdr->h_vlan_encapsulated_proto;
	पूर्ण
	अगर (h_proto == htons(ETH_P_8021Q) || h_proto == htons(ETH_P_8021AD)) अणु
		काष्ठा vlan_hdr *vhdr;

		vhdr = data + nh_off;
		nh_off += माप(काष्ठा vlan_hdr);
		अगर (data + nh_off > data_end)
			वापस rc;
		h_proto = vhdr->h_vlan_encapsulated_proto;
	पूर्ण

	अगर (h_proto == htons(ETH_P_IP))
		ipproto = parse_ipv4(data, nh_off, data_end);
	अन्यथा अगर (h_proto == htons(ETH_P_IPV6))
		ipproto = parse_ipv6(data, nh_off, data_end);
	अन्यथा
		ipproto = 0;

	value = bpf_map_lookup_elem(&rxcnt, &ipproto);
	अगर (value)
		*value += 1;

	अगर (ipproto == IPPROTO_UDP) अणु
		swap_src_dst_mac(data);
		rc = XDP_TX;
	पूर्ण

	वापस rc;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
