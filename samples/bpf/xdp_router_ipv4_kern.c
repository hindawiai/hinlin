<शैली गुरु>
/* Copyright (C) 2017 Cavium, Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of version 2 of the GNU General Public License
 * as published by the Free Software Foundation.
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
#समावेश <linux/slab.h>
#समावेश <net/ip_fib.h>

काष्ठा trie_value अणु
	__u8 prefix[4];
	__be64 value;
	पूर्णांक अगरindex;
	पूर्णांक metric;
	__be32 gw;
पूर्ण;

/* Key क्रम lpm_trie*/
जोड़ key_4 अणु
	u32 b32[2];
	u8 b8[8];
पूर्ण;

काष्ठा arp_entry अणु
	__be64 mac;
	__be32 dst;
पूर्ण;

काष्ठा direct_map अणु
	काष्ठा arp_entry arp;
	पूर्णांक अगरindex;
	__be64 mac;
पूर्ण;

/* Map क्रम trie implementation*/
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_LPM_TRIE);
	__uपूर्णांक(key_size, 8);
	__uपूर्णांक(value_size, माप(काष्ठा trie_value));
	__uपूर्णांक(max_entries, 50);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
पूर्ण lpm_map SEC(".maps");

/* Map क्रम counter*/
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__type(key, u32);
	__type(value, u64);
	__uपूर्णांक(max_entries, 256);
पूर्ण rxcnt SEC(".maps");

/* Map क्रम ARP table*/
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, __be32);
	__type(value, __be64);
	__uपूर्णांक(max_entries, 50);
पूर्ण arp_table SEC(".maps");

/* Map to keep the exact match entries in the route table*/
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, __be32);
	__type(value, काष्ठा direct_map);
	__uपूर्णांक(max_entries, 50);
पूर्ण exact_match SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_DEVMAP);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
	__uपूर्णांक(max_entries, 100);
पूर्ण tx_port SEC(".maps");

/* Function to set source and destination mac of the packet */
अटल अंतरभूत व्योम set_src_dst_mac(व्योम *data, व्योम *src, व्योम *dst)
अणु
	अचिन्हित लघु *source = src;
	अचिन्हित लघु *dest  = dst;
	अचिन्हित लघु *p = data;

	__builtin_स_नकल(p, dest, 6);
	__builtin_स_नकल(p + 3, source, 6);
पूर्ण

/* Parse IPV4 packet to get SRC, DST IP and protocol */
अटल अंतरभूत पूर्णांक parse_ipv4(व्योम *data, u64 nh_off, व्योम *data_end,
			     __be32 *src, __be32 *dest)
अणु
	काष्ठा iphdr *iph = data + nh_off;

	अगर (iph + 1 > data_end)
		वापस 0;
	*src = iph->saddr;
	*dest = iph->daddr;
	वापस iph->protocol;
पूर्ण

SEC("xdp_router_ipv4")
पूर्णांक xdp_router_ipv4_prog(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	__be64 *dest_mac = शून्य, *src_mac = शून्य;
	व्योम *data = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा trie_value *prefix_value;
	पूर्णांक rc = XDP_DROP, क्रमward_to;
	काष्ठा ethhdr *eth = data;
	जोड़ key_4 key4;
	दीर्घ *value;
	u16 h_proto;
	u32 ipproto;
	u64 nh_off;

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
	अगर (h_proto == htons(ETH_P_ARP)) अणु
		वापस XDP_PASS;
	पूर्ण अन्यथा अगर (h_proto == htons(ETH_P_IP)) अणु
		काष्ठा direct_map *direct_entry;
		__be32 src_ip = 0, dest_ip = 0;

		ipproto = parse_ipv4(data, nh_off, data_end, &src_ip, &dest_ip);
		direct_entry = bpf_map_lookup_elem(&exact_match, &dest_ip);
		/* Check क्रम exact match, this would give a faster lookup*/
		अगर (direct_entry && direct_entry->mac && direct_entry->arp.mac) अणु
			src_mac = &direct_entry->mac;
			dest_mac = &direct_entry->arp.mac;
			क्रमward_to = direct_entry->अगरindex;
		पूर्ण अन्यथा अणु
			/* Look up in the trie क्रम lpm*/
			key4.b32[0] = 32;
			key4.b8[4] = dest_ip & 0xff;
			key4.b8[5] = (dest_ip >> 8) & 0xff;
			key4.b8[6] = (dest_ip >> 16) & 0xff;
			key4.b8[7] = (dest_ip >> 24) & 0xff;
			prefix_value = bpf_map_lookup_elem(&lpm_map, &key4);
			अगर (!prefix_value)
				वापस XDP_DROP;
			src_mac = &prefix_value->value;
			अगर (!src_mac)
				वापस XDP_DROP;
			dest_mac = bpf_map_lookup_elem(&arp_table, &dest_ip);
			अगर (!dest_mac) अणु
				अगर (!prefix_value->gw)
					वापस XDP_DROP;
				dest_ip = prefix_value->gw;
				dest_mac = bpf_map_lookup_elem(&arp_table, &dest_ip);
			पूर्ण
			क्रमward_to = prefix_value->अगरindex;
		पूर्ण
	पूर्ण अन्यथा अणु
		ipproto = 0;
	पूर्ण
	अगर (src_mac && dest_mac) अणु
		set_src_dst_mac(data, src_mac, dest_mac);
		value = bpf_map_lookup_elem(&rxcnt, &ipproto);
		अगर (value)
			*value += 1;
		वापस  bpf_redirect_map(&tx_port, क्रमward_to, 0);
	पूर्ण
	वापस rc;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
