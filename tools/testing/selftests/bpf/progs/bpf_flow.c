<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <सीमा.स>
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <linux/pkt_cls.h>
#समावेश <linux/bpf.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/icmp.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/अगर_packet.h>
#समावेश <sys/socket.h>
#समावेश <linux/अगर_tunnel.h>
#समावेश <linux/mpls.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

पूर्णांक _version SEC("version") = 1;
#घोषणा PROG(F) PROG_(F, _##F)
#घोषणा PROG_(NUM, NAME) SEC("flow_dissector/"#NUM) पूर्णांक bpf_func##NAME

/* These are the identअगरiers of the BPF programs that will be used in tail
 * calls. Name is limited to 16 अक्षरacters, with the terminating अक्षरacter and
 * bpf_func_ above, we have only 6 to work with, anything after will be cropped.
 */
#घोषणा IP		0
#घोषणा IPV6		1
#घोषणा IPV6OP		2 /* Destination/Hop-by-Hop Options IPv6 Ext. Header */
#घोषणा IPV6FR		3 /* Fragmentation IPv6 Extension Header */
#घोषणा MPLS		4
#घोषणा VLAN		5
#घोषणा MAX_PROG	6

#घोषणा IP_MF		0x2000
#घोषणा IP_OFFSET	0x1FFF
#घोषणा IP6_MF		0x0001
#घोषणा IP6_OFFSET	0xFFF8

काष्ठा vlan_hdr अणु
	__be16 h_vlan_TCI;
	__be16 h_vlan_encapsulated_proto;
पूर्ण;

काष्ठा gre_hdr अणु
	__be16 flags;
	__be16 proto;
पूर्ण;

काष्ठा frag_hdr अणु
	__u8 nexthdr;
	__u8 reserved;
	__be16 frag_off;
	__be32 identअगरication;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PROG_ARRAY);
	__uपूर्णांक(max_entries, MAX_PROG);
	__uपूर्णांक(key_size, माप(__u32));
	__uपूर्णांक(value_size, माप(__u32));
पूर्ण jmp_table SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 1024);
	__type(key, __u32);
	__type(value, काष्ठा bpf_flow_keys);
पूर्ण last_dissection SEC(".maps");

अटल __always_अंतरभूत पूर्णांक export_flow_keys(काष्ठा bpf_flow_keys *keys,
					    पूर्णांक ret)
अणु
	__u32 key = (__u32)(keys->sport) << 16 | keys->dport;
	काष्ठा bpf_flow_keys val;

	स_नकल(&val, keys, माप(val));
	bpf_map_update_elem(&last_dissection, &key, &val, BPF_ANY);
	वापस ret;
पूर्ण

#घोषणा IPV6_FLOWLABEL_MASK		__bpf_स्थिरant_htonl(0x000FFFFF)
अटल अंतरभूत __be32 ip6_flowlabel(स्थिर काष्ठा ipv6hdr *hdr)
अणु
	वापस *(__be32 *)hdr & IPV6_FLOWLABEL_MASK;
पूर्ण

अटल __always_अंतरभूत व्योम *bpf_flow_dissect_get_header(काष्ठा __sk_buff *skb,
							 __u16 hdr_size,
							 व्योम *buffer)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	__u16 thoff = skb->flow_keys->thoff;
	__u8 *hdr;

	/* Verअगरies this variable offset करोes not overflow */
	अगर (thoff > (अच_लघु_उच्च - hdr_size))
		वापस शून्य;

	hdr = data + thoff;
	अगर (hdr + hdr_size <= data_end)
		वापस hdr;

	अगर (bpf_skb_load_bytes(skb, thoff, buffer, hdr_size))
		वापस शून्य;

	वापस buffer;
पूर्ण

/* Dispatches on ETHERTYPE */
अटल __always_अंतरभूत पूर्णांक parse_eth_proto(काष्ठा __sk_buff *skb, __be16 proto)
अणु
	काष्ठा bpf_flow_keys *keys = skb->flow_keys;

	चयन (proto) अणु
	हाल bpf_htons(ETH_P_IP):
		bpf_tail_call_अटल(skb, &jmp_table, IP);
		अवरोध;
	हाल bpf_htons(ETH_P_IPV6):
		bpf_tail_call_अटल(skb, &jmp_table, IPV6);
		अवरोध;
	हाल bpf_htons(ETH_P_MPLS_MC):
	हाल bpf_htons(ETH_P_MPLS_UC):
		bpf_tail_call_अटल(skb, &jmp_table, MPLS);
		अवरोध;
	हाल bpf_htons(ETH_P_8021Q):
	हाल bpf_htons(ETH_P_8021AD):
		bpf_tail_call_अटल(skb, &jmp_table, VLAN);
		अवरोध;
	शेष:
		/* Protocol not supported */
		वापस export_flow_keys(keys, BPF_DROP);
	पूर्ण

	वापस export_flow_keys(keys, BPF_DROP);
पूर्ण

SEC("flow_dissector")
पूर्णांक _dissect(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_flow_keys *keys = skb->flow_keys;

	वापस parse_eth_proto(skb, keys->n_proto);
पूर्ण

/* Parses on IPPROTO_* */
अटल __always_अंतरभूत पूर्णांक parse_ip_proto(काष्ठा __sk_buff *skb, __u8 proto)
अणु
	काष्ठा bpf_flow_keys *keys = skb->flow_keys;
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	काष्ठा icmphdr *icmp, _icmp;
	काष्ठा gre_hdr *gre, _gre;
	काष्ठा ethhdr *eth, _eth;
	काष्ठा tcphdr *tcp, _tcp;
	काष्ठा udphdr *udp, _udp;

	चयन (proto) अणु
	हाल IPPROTO_ICMP:
		icmp = bpf_flow_dissect_get_header(skb, माप(*icmp), &_icmp);
		अगर (!icmp)
			वापस export_flow_keys(keys, BPF_DROP);
		वापस export_flow_keys(keys, BPF_OK);
	हाल IPPROTO_IPIP:
		keys->is_encap = true;
		अगर (keys->flags & BPF_FLOW_DISSECTOR_F_STOP_AT_ENCAP)
			वापस export_flow_keys(keys, BPF_OK);

		वापस parse_eth_proto(skb, bpf_htons(ETH_P_IP));
	हाल IPPROTO_IPV6:
		keys->is_encap = true;
		अगर (keys->flags & BPF_FLOW_DISSECTOR_F_STOP_AT_ENCAP)
			वापस export_flow_keys(keys, BPF_OK);

		वापस parse_eth_proto(skb, bpf_htons(ETH_P_IPV6));
	हाल IPPROTO_GRE:
		gre = bpf_flow_dissect_get_header(skb, माप(*gre), &_gre);
		अगर (!gre)
			वापस export_flow_keys(keys, BPF_DROP);

		अगर (bpf_htons(gre->flags & GRE_VERSION))
			/* Only inspect standard GRE packets with version 0 */
			वापस export_flow_keys(keys, BPF_OK);

		keys->thoff += माप(*gre); /* Step over GRE Flags and Proto */
		अगर (GRE_IS_CSUM(gre->flags))
			keys->thoff += 4; /* Step over chksum and Padding */
		अगर (GRE_IS_KEY(gre->flags))
			keys->thoff += 4; /* Step over key */
		अगर (GRE_IS_SEQ(gre->flags))
			keys->thoff += 4; /* Step over sequence number */

		keys->is_encap = true;
		अगर (keys->flags & BPF_FLOW_DISSECTOR_F_STOP_AT_ENCAP)
			वापस export_flow_keys(keys, BPF_OK);

		अगर (gre->proto == bpf_htons(ETH_P_TEB)) अणु
			eth = bpf_flow_dissect_get_header(skb, माप(*eth),
							  &_eth);
			अगर (!eth)
				वापस export_flow_keys(keys, BPF_DROP);

			keys->thoff += माप(*eth);

			वापस parse_eth_proto(skb, eth->h_proto);
		पूर्ण अन्यथा अणु
			वापस parse_eth_proto(skb, gre->proto);
		पूर्ण
	हाल IPPROTO_TCP:
		tcp = bpf_flow_dissect_get_header(skb, माप(*tcp), &_tcp);
		अगर (!tcp)
			वापस export_flow_keys(keys, BPF_DROP);

		अगर (tcp->करोff < 5)
			वापस export_flow_keys(keys, BPF_DROP);

		अगर ((__u8 *)tcp + (tcp->करोff << 2) > data_end)
			वापस export_flow_keys(keys, BPF_DROP);

		keys->sport = tcp->source;
		keys->dport = tcp->dest;
		वापस export_flow_keys(keys, BPF_OK);
	हाल IPPROTO_UDP:
	हाल IPPROTO_UDPLITE:
		udp = bpf_flow_dissect_get_header(skb, माप(*udp), &_udp);
		अगर (!udp)
			वापस export_flow_keys(keys, BPF_DROP);

		keys->sport = udp->source;
		keys->dport = udp->dest;
		वापस export_flow_keys(keys, BPF_OK);
	शेष:
		वापस export_flow_keys(keys, BPF_DROP);
	पूर्ण

	वापस export_flow_keys(keys, BPF_DROP);
पूर्ण

अटल __always_अंतरभूत पूर्णांक parse_ipv6_proto(काष्ठा __sk_buff *skb, __u8 nexthdr)
अणु
	काष्ठा bpf_flow_keys *keys = skb->flow_keys;

	चयन (nexthdr) अणु
	हाल IPPROTO_HOPOPTS:
	हाल IPPROTO_DSTOPTS:
		bpf_tail_call_अटल(skb, &jmp_table, IPV6OP);
		अवरोध;
	हाल IPPROTO_FRAGMENT:
		bpf_tail_call_अटल(skb, &jmp_table, IPV6FR);
		अवरोध;
	शेष:
		वापस parse_ip_proto(skb, nexthdr);
	पूर्ण

	वापस export_flow_keys(keys, BPF_DROP);
पूर्ण

PROG(IP)(काष्ठा __sk_buff *skb)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	काष्ठा bpf_flow_keys *keys = skb->flow_keys;
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	काष्ठा iphdr *iph, _iph;
	bool करोne = false;

	iph = bpf_flow_dissect_get_header(skb, माप(*iph), &_iph);
	अगर (!iph)
		वापस export_flow_keys(keys, BPF_DROP);

	/* IP header cannot be smaller than 20 bytes */
	अगर (iph->ihl < 5)
		वापस export_flow_keys(keys, BPF_DROP);

	keys->addr_proto = ETH_P_IP;
	keys->ipv4_src = iph->saddr;
	keys->ipv4_dst = iph->daddr;
	keys->ip_proto = iph->protocol;

	keys->thoff += iph->ihl << 2;
	अगर (data + keys->thoff > data_end)
		वापस export_flow_keys(keys, BPF_DROP);

	अगर (iph->frag_off & bpf_htons(IP_MF | IP_OFFSET)) अणु
		keys->is_frag = true;
		अगर (iph->frag_off & bpf_htons(IP_OFFSET)) अणु
			/* From second fragment on, packets करो not have headers
			 * we can parse.
			 */
			करोne = true;
		पूर्ण अन्यथा अणु
			keys->is_first_frag = true;
			/* No need to parse fragmented packet unless
			 * explicitly asked क्रम.
			 */
			अगर (!(keys->flags &
			      BPF_FLOW_DISSECTOR_F_PARSE_1ST_FRAG))
				करोne = true;
		पूर्ण
	पूर्ण

	अगर (करोne)
		वापस export_flow_keys(keys, BPF_OK);

	वापस parse_ip_proto(skb, iph->protocol);
पूर्ण

PROG(IPV6)(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_flow_keys *keys = skb->flow_keys;
	काष्ठा ipv6hdr *ip6h, _ip6h;

	ip6h = bpf_flow_dissect_get_header(skb, माप(*ip6h), &_ip6h);
	अगर (!ip6h)
		वापस export_flow_keys(keys, BPF_DROP);

	keys->addr_proto = ETH_P_IPV6;
	स_नकल(&keys->ipv6_src, &ip6h->saddr, 2*माप(ip6h->saddr));

	keys->thoff += माप(काष्ठा ipv6hdr);
	keys->ip_proto = ip6h->nexthdr;
	keys->flow_label = ip6_flowlabel(ip6h);

	अगर (keys->flags & BPF_FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL)
		वापस export_flow_keys(keys, BPF_OK);

	वापस parse_ipv6_proto(skb, ip6h->nexthdr);
पूर्ण

PROG(IPV6OP)(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_flow_keys *keys = skb->flow_keys;
	काष्ठा ipv6_opt_hdr *ip6h, _ip6h;

	ip6h = bpf_flow_dissect_get_header(skb, माप(*ip6h), &_ip6h);
	अगर (!ip6h)
		वापस export_flow_keys(keys, BPF_DROP);

	/* hlen is in 8-octets and करोes not include the first 8 bytes
	 * of the header
	 */
	keys->thoff += (1 + ip6h->hdrlen) << 3;
	keys->ip_proto = ip6h->nexthdr;

	वापस parse_ipv6_proto(skb, ip6h->nexthdr);
पूर्ण

PROG(IPV6FR)(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_flow_keys *keys = skb->flow_keys;
	काष्ठा frag_hdr *fragh, _fragh;

	fragh = bpf_flow_dissect_get_header(skb, माप(*fragh), &_fragh);
	अगर (!fragh)
		वापस export_flow_keys(keys, BPF_DROP);

	keys->thoff += माप(*fragh);
	keys->is_frag = true;
	keys->ip_proto = fragh->nexthdr;

	अगर (!(fragh->frag_off & bpf_htons(IP6_OFFSET))) अणु
		keys->is_first_frag = true;

		/* No need to parse fragmented packet unless
		 * explicitly asked क्रम.
		 */
		अगर (!(keys->flags & BPF_FLOW_DISSECTOR_F_PARSE_1ST_FRAG))
			वापस export_flow_keys(keys, BPF_OK);
	पूर्ण अन्यथा अणु
		वापस export_flow_keys(keys, BPF_OK);
	पूर्ण

	वापस parse_ipv6_proto(skb, fragh->nexthdr);
पूर्ण

PROG(MPLS)(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_flow_keys *keys = skb->flow_keys;
	काष्ठा mpls_label *mpls, _mpls;

	mpls = bpf_flow_dissect_get_header(skb, माप(*mpls), &_mpls);
	अगर (!mpls)
		वापस export_flow_keys(keys, BPF_DROP);

	वापस export_flow_keys(keys, BPF_OK);
पूर्ण

PROG(VLAN)(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_flow_keys *keys = skb->flow_keys;
	काष्ठा vlan_hdr *vlan, _vlan;

	/* Account क्रम द्विगुन-tagging */
	अगर (keys->n_proto == bpf_htons(ETH_P_8021AD)) अणु
		vlan = bpf_flow_dissect_get_header(skb, माप(*vlan), &_vlan);
		अगर (!vlan)
			वापस export_flow_keys(keys, BPF_DROP);

		अगर (vlan->h_vlan_encapsulated_proto != bpf_htons(ETH_P_8021Q))
			वापस export_flow_keys(keys, BPF_DROP);

		keys->nhoff += माप(*vlan);
		keys->thoff += माप(*vlan);
	पूर्ण

	vlan = bpf_flow_dissect_get_header(skb, माप(*vlan), &_vlan);
	अगर (!vlan)
		वापस export_flow_keys(keys, BPF_DROP);

	keys->nhoff += माप(*vlan);
	keys->thoff += माप(*vlan);
	/* Only allow 8021AD + 8021Q द्विगुन tagging and no triple tagging.*/
	अगर (vlan->h_vlan_encapsulated_proto == bpf_htons(ETH_P_8021AD) ||
	    vlan->h_vlan_encapsulated_proto == bpf_htons(ETH_P_8021Q))
		वापस export_flow_keys(keys, BPF_DROP);

	keys->n_proto = vlan->h_vlan_encapsulated_proto;
	वापस parse_eth_proto(skb, vlan->h_vlan_encapsulated_proto);
पूर्ण

अक्षर __license[] SEC("license") = "GPL";
