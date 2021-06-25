<शैली गुरु>
/* Copyright (c) 2015 PLUMgrid, http://plumgrid.com
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/in.h>
#समावेश <uapi/linux/अगर.h>
#समावेश <uapi/linux/अगर_ether.h>
#समावेश <uapi/linux/ip.h>
#समावेश <uapi/linux/ipv6.h>
#समावेश <uapi/linux/अगर_tunnel.h>
#समावेश <uapi/linux/mpls.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश "bpf_legacy.h"
#घोषणा IP_MF		0x2000
#घोषणा IP_OFFSET	0x1FFF

#घोषणा PROG(F) SEC("socket/"__stringअगरy(F)) पूर्णांक bpf_func_##F

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PROG_ARRAY);
	__uपूर्णांक(key_size, माप(u32));
	__uपूर्णांक(value_size, माप(u32));
	__uपूर्णांक(max_entries, 8);
पूर्ण jmp_table SEC(".maps");

#घोषणा PARSE_VLAN 1
#घोषणा PARSE_MPLS 2
#घोषणा PARSE_IP 3
#घोषणा PARSE_IPV6 4

/* Protocol dispatch routine. It tail-calls next BPF program depending
 * on eth proto. Note, we could have used ...
 *
 *   bpf_tail_call(skb, &jmp_table, proto);
 *
 * ... but it would need large prog_array and cannot be optimised given
 * the map key is not अटल.
 */
अटल अंतरभूत व्योम parse_eth_proto(काष्ठा __sk_buff *skb, u32 proto)
अणु
	चयन (proto) अणु
	हाल ETH_P_8021Q:
	हाल ETH_P_8021AD:
		bpf_tail_call(skb, &jmp_table, PARSE_VLAN);
		अवरोध;
	हाल ETH_P_MPLS_UC:
	हाल ETH_P_MPLS_MC:
		bpf_tail_call(skb, &jmp_table, PARSE_MPLS);
		अवरोध;
	हाल ETH_P_IP:
		bpf_tail_call(skb, &jmp_table, PARSE_IP);
		अवरोध;
	हाल ETH_P_IPV6:
		bpf_tail_call(skb, &jmp_table, PARSE_IPV6);
		अवरोध;
	पूर्ण
पूर्ण

काष्ठा vlan_hdr अणु
	__be16 h_vlan_TCI;
	__be16 h_vlan_encapsulated_proto;
पूर्ण;

काष्ठा flow_key_record अणु
	__be32 src;
	__be32 dst;
	जोड़ अणु
		__be32 ports;
		__be16 port16[2];
	पूर्ण;
	__u32 ip_proto;
पूर्ण;

अटल अंतरभूत पूर्णांक ip_is_fragment(काष्ठा __sk_buff *ctx, __u64 nhoff)
अणु
	वापस load_half(ctx, nhoff + दुरत्व(काष्ठा iphdr, frag_off))
		& (IP_MF | IP_OFFSET);
पूर्ण

अटल अंतरभूत __u32 ipv6_addr_hash(काष्ठा __sk_buff *ctx, __u64 off)
अणु
	__u64 w0 = load_word(ctx, off);
	__u64 w1 = load_word(ctx, off + 4);
	__u64 w2 = load_word(ctx, off + 8);
	__u64 w3 = load_word(ctx, off + 12);

	वापस (__u32)(w0 ^ w1 ^ w2 ^ w3);
पूर्ण

काष्ठा globals अणु
	काष्ठा flow_key_record flow;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, __u32);
	__type(value, काष्ठा globals);
	__uपूर्णांक(max_entries, 32);
पूर्ण percpu_map SEC(".maps");

/* user poor man's per_cpu until native support is पढ़ोy */
अटल काष्ठा globals *this_cpu_globals(व्योम)
अणु
	u32 key = bpf_get_smp_processor_id();

	वापस bpf_map_lookup_elem(&percpu_map, &key);
पूर्ण

/* some simple stats क्रम user space consumption */
काष्ठा pair अणु
	__u64 packets;
	__u64 bytes;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, काष्ठा flow_key_record);
	__type(value, काष्ठा pair);
	__uपूर्णांक(max_entries, 1024);
पूर्ण hash_map SEC(".maps");

अटल व्योम update_stats(काष्ठा __sk_buff *skb, काष्ठा globals *g)
अणु
	काष्ठा flow_key_record key = g->flow;
	काष्ठा pair *value;

	value = bpf_map_lookup_elem(&hash_map, &key);
	अगर (value) अणु
		__sync_fetch_and_add(&value->packets, 1);
		__sync_fetch_and_add(&value->bytes, skb->len);
	पूर्ण अन्यथा अणु
		काष्ठा pair val = अणु1, skb->lenपूर्ण;

		bpf_map_update_elem(&hash_map, &key, &val, BPF_ANY);
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम parse_ip_proto(काष्ठा __sk_buff *skb,
					   काष्ठा globals *g, __u32 ip_proto)
अणु
	__u32 nhoff = skb->cb[0];
	पूर्णांक poff;

	चयन (ip_proto) अणु
	हाल IPPROTO_GRE: अणु
		काष्ठा gre_hdr अणु
			__be16 flags;
			__be16 proto;
		पूर्ण;

		__u32 gre_flags = load_half(skb,
					    nhoff + दुरत्व(काष्ठा gre_hdr, flags));
		__u32 gre_proto = load_half(skb,
					    nhoff + दुरत्व(काष्ठा gre_hdr, proto));

		अगर (gre_flags & (GRE_VERSION|GRE_ROUTING))
			अवरोध;

		nhoff += 4;
		अगर (gre_flags & GRE_CSUM)
			nhoff += 4;
		अगर (gre_flags & GRE_KEY)
			nhoff += 4;
		अगर (gre_flags & GRE_SEQ)
			nhoff += 4;

		skb->cb[0] = nhoff;
		parse_eth_proto(skb, gre_proto);
		अवरोध;
	पूर्ण
	हाल IPPROTO_IPIP:
		parse_eth_proto(skb, ETH_P_IP);
		अवरोध;
	हाल IPPROTO_IPV6:
		parse_eth_proto(skb, ETH_P_IPV6);
		अवरोध;
	हाल IPPROTO_TCP:
	हाल IPPROTO_UDP:
		g->flow.ports = load_word(skb, nhoff);
	हाल IPPROTO_ICMP:
		g->flow.ip_proto = ip_proto;
		update_stats(skb, g);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

PROG(PARSE_IP)(काष्ठा __sk_buff *skb)
अणु
	काष्ठा globals *g = this_cpu_globals();
	__u32 nhoff, verlen, ip_proto;

	अगर (!g)
		वापस 0;

	nhoff = skb->cb[0];

	अगर (unlikely(ip_is_fragment(skb, nhoff)))
		वापस 0;

	ip_proto = load_byte(skb, nhoff + दुरत्व(काष्ठा iphdr, protocol));

	अगर (ip_proto != IPPROTO_GRE) अणु
		g->flow.src = load_word(skb, nhoff + दुरत्व(काष्ठा iphdr, saddr));
		g->flow.dst = load_word(skb, nhoff + दुरत्व(काष्ठा iphdr, daddr));
	पूर्ण

	verlen = load_byte(skb, nhoff + 0/*दुरत्व(काष्ठा iphdr, ihl)*/);
	nhoff += (verlen & 0xF) << 2;

	skb->cb[0] = nhoff;
	parse_ip_proto(skb, g, ip_proto);
	वापस 0;
पूर्ण

PROG(PARSE_IPV6)(काष्ठा __sk_buff *skb)
अणु
	काष्ठा globals *g = this_cpu_globals();
	__u32 nhoff, ip_proto;

	अगर (!g)
		वापस 0;

	nhoff = skb->cb[0];

	ip_proto = load_byte(skb,
			     nhoff + दुरत्व(काष्ठा ipv6hdr, nexthdr));
	g->flow.src = ipv6_addr_hash(skb,
				     nhoff + दुरत्व(काष्ठा ipv6hdr, saddr));
	g->flow.dst = ipv6_addr_hash(skb,
				     nhoff + दुरत्व(काष्ठा ipv6hdr, daddr));
	nhoff += माप(काष्ठा ipv6hdr);

	skb->cb[0] = nhoff;
	parse_ip_proto(skb, g, ip_proto);
	वापस 0;
पूर्ण

PROG(PARSE_VLAN)(काष्ठा __sk_buff *skb)
अणु
	__u32 nhoff, proto;

	nhoff = skb->cb[0];

	proto = load_half(skb, nhoff + दुरत्व(काष्ठा vlan_hdr,
						h_vlan_encapsulated_proto));
	nhoff += माप(काष्ठा vlan_hdr);
	skb->cb[0] = nhoff;

	parse_eth_proto(skb, proto);

	वापस 0;
पूर्ण

PROG(PARSE_MPLS)(काष्ठा __sk_buff *skb)
अणु
	__u32 nhoff, label;

	nhoff = skb->cb[0];

	label = load_word(skb, nhoff);
	nhoff += माप(काष्ठा mpls_label);
	skb->cb[0] = nhoff;

	अगर (label & MPLS_LS_S_MASK) अणु
		__u8 verlen = load_byte(skb, nhoff);
		अगर ((verlen & 0xF0) == 4)
			parse_eth_proto(skb, ETH_P_IP);
		अन्यथा
			parse_eth_proto(skb, ETH_P_IPV6);
	पूर्ण अन्यथा अणु
		parse_eth_proto(skb, ETH_P_MPLS_UC);
	पूर्ण

	वापस 0;
पूर्ण

SEC("socket/0")
पूर्णांक मुख्य_prog(काष्ठा __sk_buff *skb)
अणु
	__u32 nhoff = ETH_HLEN;
	__u32 proto = load_half(skb, 12);

	skb->cb[0] = nhoff;
	parse_eth_proto(skb, proto);
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
