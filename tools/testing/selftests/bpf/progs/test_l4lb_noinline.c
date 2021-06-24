<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017 Facebook
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <linux/pkt_cls.h>
#समावेश <linux/bpf.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/icmp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश "test_iptunnel_common.h"
#समावेश <bpf/bpf_endian.h>

अटल __always_अंतरभूत __u32 rol32(__u32 word, अचिन्हित पूर्णांक shअगरt)
अणु
	वापस (word << shअगरt) | (word >> ((-shअगरt) & 31));
पूर्ण

/* copy paste of jhash from kernel sources to make sure llvm
 * can compile it पूर्णांकo valid sequence of bpf inकाष्ठाions
 */
#घोषणा __jhash_mix(a, b, c)			\
अणु						\
	a -= c;  a ^= rol32(c, 4);  c += b;	\
	b -= a;  b ^= rol32(a, 6);  a += c;	\
	c -= b;  c ^= rol32(b, 8);  b += a;	\
	a -= c;  a ^= rol32(c, 16); c += b;	\
	b -= a;  b ^= rol32(a, 19); a += c;	\
	c -= b;  c ^= rol32(b, 4);  b += a;	\
पूर्ण

#घोषणा __jhash_final(a, b, c)			\
अणु						\
	c ^= b; c -= rol32(b, 14);		\
	a ^= c; a -= rol32(c, 11);		\
	b ^= a; b -= rol32(a, 25);		\
	c ^= b; c -= rol32(b, 16);		\
	a ^= c; a -= rol32(c, 4);		\
	b ^= a; b -= rol32(a, 14);		\
	c ^= b; c -= rol32(b, 24);		\
पूर्ण

#घोषणा JHASH_INITVAL		0xdeadbeef

प्रकार अचिन्हित पूर्णांक u32;

अटल __noअंतरभूत u32 jhash(स्थिर व्योम *key, u32 length, u32 initval)
अणु
	u32 a, b, c;
	स्थिर अचिन्हित अक्षर *k = key;

	a = b = c = JHASH_INITVAL + length + initval;

	जबतक (length > 12) अणु
		a += *(u32 *)(k);
		b += *(u32 *)(k + 4);
		c += *(u32 *)(k + 8);
		__jhash_mix(a, b, c);
		length -= 12;
		k += 12;
	पूर्ण
	चयन (length) अणु
	हाल 12: c += (u32)k[11]<<24;
	हाल 11: c += (u32)k[10]<<16;
	हाल 10: c += (u32)k[9]<<8;
	हाल 9:  c += k[8];
	हाल 8:  b += (u32)k[7]<<24;
	हाल 7:  b += (u32)k[6]<<16;
	हाल 6:  b += (u32)k[5]<<8;
	हाल 5:  b += k[4];
	हाल 4:  a += (u32)k[3]<<24;
	हाल 3:  a += (u32)k[2]<<16;
	हाल 2:  a += (u32)k[1]<<8;
	हाल 1:  a += k[0];
		 __jhash_final(a, b, c);
	हाल 0: /* Nothing left to add */
		अवरोध;
	पूर्ण

	वापस c;
पूर्ण

अटल __noअंतरभूत u32 __jhash_nwords(u32 a, u32 b, u32 c, u32 initval)
अणु
	a += initval;
	b += initval;
	c += initval;
	__jhash_final(a, b, c);
	वापस c;
पूर्ण

अटल __noअंतरभूत u32 jhash_2words(u32 a, u32 b, u32 initval)
अणु
	वापस __jhash_nwords(a, b, 0, initval + JHASH_INITVAL + (2 << 2));
पूर्ण

#घोषणा PCKT_FRAGMENTED 65343
#घोषणा IPV4_HDR_LEN_NO_OPT 20
#घोषणा IPV4_PLUS_ICMP_HDR 28
#घोषणा IPV6_PLUS_ICMP_HDR 48
#घोषणा RING_SIZE 2
#घोषणा MAX_VIPS 12
#घोषणा MAX_REALS 5
#घोषणा CTL_MAP_SIZE 16
#घोषणा CH_RINGS_SIZE (MAX_VIPS * RING_SIZE)
#घोषणा F_IPV6 (1 << 0)
#घोषणा F_HASH_NO_SRC_PORT (1 << 0)
#घोषणा F_ICMP (1 << 0)
#घोषणा F_SYN_SET (1 << 1)

काष्ठा packet_description अणु
	जोड़ अणु
		__be32 src;
		__be32 srcv6[4];
	पूर्ण;
	जोड़ अणु
		__be32 dst;
		__be32 dstv6[4];
	पूर्ण;
	जोड़ अणु
		__u32 ports;
		__u16 port16[2];
	पूर्ण;
	__u8 proto;
	__u8 flags;
पूर्ण;

काष्ठा ctl_value अणु
	जोड़ अणु
		__u64 value;
		__u32 अगरindex;
		__u8 mac[6];
	पूर्ण;
पूर्ण;

काष्ठा vip_meta अणु
	__u32 flags;
	__u32 vip_num;
पूर्ण;

काष्ठा real_definition अणु
	जोड़ अणु
		__be32 dst;
		__be32 dstv6[4];
	पूर्ण;
	__u8 flags;
पूर्ण;

काष्ठा vip_stats अणु
	__u64 bytes;
	__u64 pkts;
पूर्ण;

काष्ठा eth_hdr अणु
	अचिन्हित अक्षर eth_dest[ETH_ALEN];
	अचिन्हित अक्षर eth_source[ETH_ALEN];
	अचिन्हित लघु eth_proto;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, MAX_VIPS);
	__type(key, काष्ठा vip);
	__type(value, काष्ठा vip_meta);
पूर्ण vip_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, CH_RINGS_SIZE);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण ch_rings SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, MAX_REALS);
	__type(key, __u32);
	__type(value, काष्ठा real_definition);
पूर्ण reals SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(max_entries, MAX_VIPS);
	__type(key, __u32);
	__type(value, काष्ठा vip_stats);
पूर्ण stats SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, CTL_MAP_SIZE);
	__type(key, __u32);
	__type(value, काष्ठा ctl_value);
पूर्ण ctl_array SEC(".maps");

अटल __noअंतरभूत __u32 get_packet_hash(काष्ठा packet_description *pckt, bool ipv6)
अणु
	अगर (ipv6)
		वापस jhash_2words(jhash(pckt->srcv6, 16, MAX_VIPS),
				    pckt->ports, CH_RINGS_SIZE);
	अन्यथा
		वापस jhash_2words(pckt->src, pckt->ports, CH_RINGS_SIZE);
पूर्ण

अटल __noअंतरभूत bool get_packet_dst(काष्ठा real_definition **real,
				      काष्ठा packet_description *pckt,
				      काष्ठा vip_meta *vip_info,
				      bool is_ipv6)
अणु
	__u32 hash = get_packet_hash(pckt, is_ipv6);
	__u32 key = RING_SIZE * vip_info->vip_num + hash % RING_SIZE;
	__u32 *real_pos;

	अगर (hash != 0x358459b7 /* jhash of ipv4 packet */  &&
	    hash != 0x2f4bc6bb /* jhash of ipv6 packet */)
		वापस 0;

	real_pos = bpf_map_lookup_elem(&ch_rings, &key);
	अगर (!real_pos)
		वापस false;
	key = *real_pos;
	*real = bpf_map_lookup_elem(&reals, &key);
	अगर (!(*real))
		वापस false;
	वापस true;
पूर्ण

अटल __noअंतरभूत पूर्णांक parse_icmpv6(व्योम *data, व्योम *data_end, __u64 off,
				   काष्ठा packet_description *pckt)
अणु
	काष्ठा icmp6hdr *icmp_hdr;
	काष्ठा ipv6hdr *ip6h;

	icmp_hdr = data + off;
	अगर (icmp_hdr + 1 > data_end)
		वापस TC_ACT_SHOT;
	अगर (icmp_hdr->icmp6_type != ICMPV6_PKT_TOOBIG)
		वापस TC_ACT_OK;
	off += माप(काष्ठा icmp6hdr);
	ip6h = data + off;
	अगर (ip6h + 1 > data_end)
		वापस TC_ACT_SHOT;
	pckt->proto = ip6h->nexthdr;
	pckt->flags |= F_ICMP;
	स_नकल(pckt->srcv6, ip6h->daddr.s6_addr32, 16);
	स_नकल(pckt->dstv6, ip6h->saddr.s6_addr32, 16);
	वापस TC_ACT_UNSPEC;
पूर्ण

अटल __noअंतरभूत पूर्णांक parse_icmp(व्योम *data, व्योम *data_end, __u64 off,
				 काष्ठा packet_description *pckt)
अणु
	काष्ठा icmphdr *icmp_hdr;
	काष्ठा iphdr *iph;

	icmp_hdr = data + off;
	अगर (icmp_hdr + 1 > data_end)
		वापस TC_ACT_SHOT;
	अगर (icmp_hdr->type != ICMP_DEST_UNREACH ||
	    icmp_hdr->code != ICMP_FRAG_NEEDED)
		वापस TC_ACT_OK;
	off += माप(काष्ठा icmphdr);
	iph = data + off;
	अगर (iph + 1 > data_end)
		वापस TC_ACT_SHOT;
	अगर (iph->ihl != 5)
		वापस TC_ACT_SHOT;
	pckt->proto = iph->protocol;
	pckt->flags |= F_ICMP;
	pckt->src = iph->daddr;
	pckt->dst = iph->saddr;
	वापस TC_ACT_UNSPEC;
पूर्ण

अटल __noअंतरभूत bool parse_udp(व्योम *data, __u64 off, व्योम *data_end,
				 काष्ठा packet_description *pckt)
अणु
	काष्ठा udphdr *udp;
	udp = data + off;

	अगर (udp + 1 > data_end)
		वापस false;

	अगर (!(pckt->flags & F_ICMP)) अणु
		pckt->port16[0] = udp->source;
		pckt->port16[1] = udp->dest;
	पूर्ण अन्यथा अणु
		pckt->port16[0] = udp->dest;
		pckt->port16[1] = udp->source;
	पूर्ण
	वापस true;
पूर्ण

अटल __noअंतरभूत bool parse_tcp(व्योम *data, __u64 off, व्योम *data_end,
				 काष्ठा packet_description *pckt)
अणु
	काष्ठा tcphdr *tcp;

	tcp = data + off;
	अगर (tcp + 1 > data_end)
		वापस false;

	अगर (tcp->syn)
		pckt->flags |= F_SYN_SET;

	अगर (!(pckt->flags & F_ICMP)) अणु
		pckt->port16[0] = tcp->source;
		pckt->port16[1] = tcp->dest;
	पूर्ण अन्यथा अणु
		pckt->port16[0] = tcp->dest;
		pckt->port16[1] = tcp->source;
	पूर्ण
	वापस true;
पूर्ण

अटल __noअंतरभूत पूर्णांक process_packet(व्योम *data, __u64 off, व्योम *data_end,
				     bool is_ipv6, काष्ठा __sk_buff *skb)
अणु
	व्योम *pkt_start = (व्योम *)(दीर्घ)skb->data;
	काष्ठा packet_description pckt = अणुपूर्ण;
	काष्ठा eth_hdr *eth = pkt_start;
	काष्ठा bpf_tunnel_key tkey = अणुपूर्ण;
	काष्ठा vip_stats *data_stats;
	काष्ठा real_definition *dst;
	काष्ठा vip_meta *vip_info;
	काष्ठा ctl_value *cval;
	__u32 v4_पूर्णांकf_pos = 1;
	__u32 v6_पूर्णांकf_pos = 2;
	काष्ठा ipv6hdr *ip6h;
	काष्ठा vip vip = अणुपूर्ण;
	काष्ठा iphdr *iph;
	पूर्णांक tun_flag = 0;
	__u16 pkt_bytes;
	__u64 iph_len;
	__u32 अगरindex;
	__u8 protocol;
	__u32 vip_num;
	पूर्णांक action;

	tkey.tunnel_ttl = 64;
	अगर (is_ipv6) अणु
		ip6h = data + off;
		अगर (ip6h + 1 > data_end)
			वापस TC_ACT_SHOT;

		iph_len = माप(काष्ठा ipv6hdr);
		protocol = ip6h->nexthdr;
		pckt.proto = protocol;
		pkt_bytes = bpf_ntohs(ip6h->payload_len);
		off += iph_len;
		अगर (protocol == IPPROTO_FRAGMENT) अणु
			वापस TC_ACT_SHOT;
		पूर्ण अन्यथा अगर (protocol == IPPROTO_ICMPV6) अणु
			action = parse_icmpv6(data, data_end, off, &pckt);
			अगर (action >= 0)
				वापस action;
			off += IPV6_PLUS_ICMP_HDR;
		पूर्ण अन्यथा अणु
			स_नकल(pckt.srcv6, ip6h->saddr.s6_addr32, 16);
			स_नकल(pckt.dstv6, ip6h->daddr.s6_addr32, 16);
		पूर्ण
	पूर्ण अन्यथा अणु
		iph = data + off;
		अगर (iph + 1 > data_end)
			वापस TC_ACT_SHOT;
		अगर (iph->ihl != 5)
			वापस TC_ACT_SHOT;

		protocol = iph->protocol;
		pckt.proto = protocol;
		pkt_bytes = bpf_ntohs(iph->tot_len);
		off += IPV4_HDR_LEN_NO_OPT;

		अगर (iph->frag_off & PCKT_FRAGMENTED)
			वापस TC_ACT_SHOT;
		अगर (protocol == IPPROTO_ICMP) अणु
			action = parse_icmp(data, data_end, off, &pckt);
			अगर (action >= 0)
				वापस action;
			off += IPV4_PLUS_ICMP_HDR;
		पूर्ण अन्यथा अणु
			pckt.src = iph->saddr;
			pckt.dst = iph->daddr;
		पूर्ण
	पूर्ण
	protocol = pckt.proto;

	अगर (protocol == IPPROTO_TCP) अणु
		अगर (!parse_tcp(data, off, data_end, &pckt))
			वापस TC_ACT_SHOT;
	पूर्ण अन्यथा अगर (protocol == IPPROTO_UDP) अणु
		अगर (!parse_udp(data, off, data_end, &pckt))
			वापस TC_ACT_SHOT;
	पूर्ण अन्यथा अणु
		वापस TC_ACT_SHOT;
	पूर्ण

	अगर (is_ipv6)
		स_नकल(vip.daddr.v6, pckt.dstv6, 16);
	अन्यथा
		vip.daddr.v4 = pckt.dst;

	vip.dport = pckt.port16[1];
	vip.protocol = pckt.proto;
	vip_info = bpf_map_lookup_elem(&vip_map, &vip);
	अगर (!vip_info) अणु
		vip.dport = 0;
		vip_info = bpf_map_lookup_elem(&vip_map, &vip);
		अगर (!vip_info)
			वापस TC_ACT_SHOT;
		pckt.port16[1] = 0;
	पूर्ण

	अगर (vip_info->flags & F_HASH_NO_SRC_PORT)
		pckt.port16[0] = 0;

	अगर (!get_packet_dst(&dst, &pckt, vip_info, is_ipv6))
		वापस TC_ACT_SHOT;

	अगर (dst->flags & F_IPV6) अणु
		cval = bpf_map_lookup_elem(&ctl_array, &v6_पूर्णांकf_pos);
		अगर (!cval)
			वापस TC_ACT_SHOT;
		अगरindex = cval->अगरindex;
		स_नकल(tkey.remote_ipv6, dst->dstv6, 16);
		tun_flag = BPF_F_TUNINFO_IPV6;
	पूर्ण अन्यथा अणु
		cval = bpf_map_lookup_elem(&ctl_array, &v4_पूर्णांकf_pos);
		अगर (!cval)
			वापस TC_ACT_SHOT;
		अगरindex = cval->अगरindex;
		tkey.remote_ipv4 = dst->dst;
	पूर्ण
	vip_num = vip_info->vip_num;
	data_stats = bpf_map_lookup_elem(&stats, &vip_num);
	अगर (!data_stats)
		वापस TC_ACT_SHOT;
	data_stats->pkts++;
	data_stats->bytes += pkt_bytes;
	bpf_skb_set_tunnel_key(skb, &tkey, माप(tkey), tun_flag);
	*(u32 *)eth->eth_dest = tkey.remote_ipv4;
	वापस bpf_redirect(अगरindex, 0);
पूर्ण

SEC("l4lb-demo")
पूर्णांक balancer_ingress(काष्ठा __sk_buff *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा eth_hdr *eth = data;
	__u32 eth_proto;
	__u32 nh_off;

	nh_off = माप(काष्ठा eth_hdr);
	अगर (data + nh_off > data_end)
		वापस TC_ACT_SHOT;
	eth_proto = eth->eth_proto;
	अगर (eth_proto == bpf_htons(ETH_P_IP))
		वापस process_packet(data, nh_off, data_end, false, ctx);
	अन्यथा अगर (eth_proto == bpf_htons(ETH_P_IPV6))
		वापस process_packet(data, nh_off, data_end, true, ctx);
	अन्यथा
		वापस TC_ACT_SHOT;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
