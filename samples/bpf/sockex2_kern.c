<शैली गुरु>
#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/in.h>
#समावेश <uapi/linux/अगर.h>
#समावेश <uapi/linux/अगर_ether.h>
#समावेश <uapi/linux/ip.h>
#समावेश <uapi/linux/ipv6.h>
#समावेश <uapi/linux/अगर_tunnel.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश "bpf_legacy.h"
#घोषणा IP_MF		0x2000
#घोषणा IP_OFFSET	0x1FFF

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
	__u16 thoff;
	__u8 ip_proto;
पूर्ण;

अटल अंतरभूत पूर्णांक proto_ports_offset(__u64 proto)
अणु
	चयन (proto) अणु
	हाल IPPROTO_TCP:
	हाल IPPROTO_UDP:
	हाल IPPROTO_DCCP:
	हाल IPPROTO_ESP:
	हाल IPPROTO_SCTP:
	हाल IPPROTO_UDPLITE:
		वापस 0;
	हाल IPPROTO_AH:
		वापस 4;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

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

अटल अंतरभूत __u64 parse_ip(काष्ठा __sk_buff *skb, __u64 nhoff, __u64 *ip_proto,
			     काष्ठा flow_key_record *flow)
अणु
	__u64 verlen;

	अगर (unlikely(ip_is_fragment(skb, nhoff)))
		*ip_proto = 0;
	अन्यथा
		*ip_proto = load_byte(skb, nhoff + दुरत्व(काष्ठा iphdr, protocol));

	अगर (*ip_proto != IPPROTO_GRE) अणु
		flow->src = load_word(skb, nhoff + दुरत्व(काष्ठा iphdr, saddr));
		flow->dst = load_word(skb, nhoff + दुरत्व(काष्ठा iphdr, daddr));
	पूर्ण

	verlen = load_byte(skb, nhoff + 0/*दुरत्व(काष्ठा iphdr, ihl)*/);
	अगर (likely(verlen == 0x45))
		nhoff += 20;
	अन्यथा
		nhoff += (verlen & 0xF) << 2;

	वापस nhoff;
पूर्ण

अटल अंतरभूत __u64 parse_ipv6(काष्ठा __sk_buff *skb, __u64 nhoff, __u64 *ip_proto,
			       काष्ठा flow_key_record *flow)
अणु
	*ip_proto = load_byte(skb,
			      nhoff + दुरत्व(काष्ठा ipv6hdr, nexthdr));
	flow->src = ipv6_addr_hash(skb,
				   nhoff + दुरत्व(काष्ठा ipv6hdr, saddr));
	flow->dst = ipv6_addr_hash(skb,
				   nhoff + दुरत्व(काष्ठा ipv6hdr, daddr));
	nhoff += माप(काष्ठा ipv6hdr);

	वापस nhoff;
पूर्ण

अटल अंतरभूत bool flow_dissector(काष्ठा __sk_buff *skb,
				  काष्ठा flow_key_record *flow)
अणु
	__u64 nhoff = ETH_HLEN;
	__u64 ip_proto;
	__u64 proto = load_half(skb, 12);
	पूर्णांक poff;

	अगर (proto == ETH_P_8021AD) अणु
		proto = load_half(skb, nhoff + दुरत्व(काष्ठा vlan_hdr,
							h_vlan_encapsulated_proto));
		nhoff += माप(काष्ठा vlan_hdr);
	पूर्ण

	अगर (proto == ETH_P_8021Q) अणु
		proto = load_half(skb, nhoff + दुरत्व(काष्ठा vlan_hdr,
							h_vlan_encapsulated_proto));
		nhoff += माप(काष्ठा vlan_hdr);
	पूर्ण

	अगर (likely(proto == ETH_P_IP))
		nhoff = parse_ip(skb, nhoff, &ip_proto, flow);
	अन्यथा अगर (proto == ETH_P_IPV6)
		nhoff = parse_ipv6(skb, nhoff, &ip_proto, flow);
	अन्यथा
		वापस false;

	चयन (ip_proto) अणु
	हाल IPPROTO_GRE: अणु
		काष्ठा gre_hdr अणु
			__be16 flags;
			__be16 proto;
		पूर्ण;

		__u64 gre_flags = load_half(skb,
					    nhoff + दुरत्व(काष्ठा gre_hdr, flags));
		__u64 gre_proto = load_half(skb,
					    nhoff + दुरत्व(काष्ठा gre_hdr, proto));

		अगर (gre_flags & (GRE_VERSION|GRE_ROUTING))
			अवरोध;

		proto = gre_proto;
		nhoff += 4;
		अगर (gre_flags & GRE_CSUM)
			nhoff += 4;
		अगर (gre_flags & GRE_KEY)
			nhoff += 4;
		अगर (gre_flags & GRE_SEQ)
			nhoff += 4;

		अगर (proto == ETH_P_8021Q) अणु
			proto = load_half(skb,
					  nhoff + दुरत्व(काष्ठा vlan_hdr,
							   h_vlan_encapsulated_proto));
			nhoff += माप(काष्ठा vlan_hdr);
		पूर्ण

		अगर (proto == ETH_P_IP)
			nhoff = parse_ip(skb, nhoff, &ip_proto, flow);
		अन्यथा अगर (proto == ETH_P_IPV6)
			nhoff = parse_ipv6(skb, nhoff, &ip_proto, flow);
		अन्यथा
			वापस false;
		अवरोध;
	पूर्ण
	हाल IPPROTO_IPIP:
		nhoff = parse_ip(skb, nhoff, &ip_proto, flow);
		अवरोध;
	हाल IPPROTO_IPV6:
		nhoff = parse_ipv6(skb, nhoff, &ip_proto, flow);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	flow->ip_proto = ip_proto;
	poff = proto_ports_offset(ip_proto);
	अगर (poff >= 0) अणु
		nhoff += poff;
		flow->ports = load_word(skb, nhoff);
	पूर्ण

	flow->thoff = (__u16) nhoff;

	वापस true;
पूर्ण

काष्ठा pair अणु
	दीर्घ packets;
	दीर्घ bytes;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, __be32);
	__type(value, काष्ठा pair);
	__uपूर्णांक(max_entries, 1024);
पूर्ण hash_map SEC(".maps");

SEC("socket2")
पूर्णांक bpf_prog2(काष्ठा __sk_buff *skb)
अणु
	काष्ठा flow_key_record flow = अणुपूर्ण;
	काष्ठा pair *value;
	u32 key;

	अगर (!flow_dissector(skb, &flow))
		वापस 0;

	key = flow.dst;
	value = bpf_map_lookup_elem(&hash_map, &key);
	अगर (value) अणु
		__sync_fetch_and_add(&value->packets, 1);
		__sync_fetch_and_add(&value->bytes, skb->len);
	पूर्ण अन्यथा अणु
		काष्ठा pair val = अणु1, skb->lenपूर्ण;

		bpf_map_update_elem(&hash_map, &key, &val, BPF_ANY);
	पूर्ण
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
