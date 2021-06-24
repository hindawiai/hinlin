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

अटल __noअंतरभूत
u32 jhash(स्थिर व्योम *key, u32 length, u32 initval)
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

__noअंतरभूत
u32 __jhash_nwords(u32 a, u32 b, u32 c, u32 initval)
अणु
	a += initval;
	b += initval;
	c += initval;
	__jhash_final(a, b, c);
	वापस c;
पूर्ण

__noअंतरभूत
u32 jhash_2words(u32 a, u32 b, u32 initval)
अणु
	वापस __jhash_nwords(a, b, 0, initval + JHASH_INITVAL + (2 << 2));
पूर्ण

काष्ठा flow_key अणु
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
पूर्ण;

काष्ठा packet_description अणु
	काष्ठा flow_key flow;
	__u8 flags;
पूर्ण;

काष्ठा ctl_value अणु
	जोड़ अणु
		__u64 value;
		__u32 अगरindex;
		__u8 mac[6];
	पूर्ण;
पूर्ण;

काष्ठा vip_definition अणु
	जोड़ अणु
		__be32 vip;
		__be32 vipv6[4];
	पूर्ण;
	__u16 port;
	__u16 family;
	__u8 proto;
पूर्ण;

काष्ठा vip_meta अणु
	__u32 flags;
	__u32 vip_num;
पूर्ण;

काष्ठा real_pos_lru अणु
	__u32 pos;
	__u64 aसमय;
पूर्ण;

काष्ठा real_definition अणु
	जोड़ अणु
		__be32 dst;
		__be32 dstv6[4];
	पूर्ण;
	__u8 flags;
पूर्ण;

काष्ठा lb_stats अणु
	__u64 v2;
	__u64 v1;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 512);
	__type(key, काष्ठा vip_definition);
	__type(value, काष्ठा vip_meta);
पूर्ण vip_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_LRU_HASH);
	__uपूर्णांक(max_entries, 300);
	__uपूर्णांक(map_flags, 1U << 1);
	__type(key, काष्ठा flow_key);
	__type(value, काष्ठा real_pos_lru);
पूर्ण lru_cache SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 12 * 655);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण ch_rings SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 40);
	__type(key, __u32);
	__type(value, काष्ठा real_definition);
पूर्ण reals SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(max_entries, 515);
	__type(key, __u32);
	__type(value, काष्ठा lb_stats);
पूर्ण stats SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 16);
	__type(key, __u32);
	__type(value, काष्ठा ctl_value);
पूर्ण ctl_array SEC(".maps");

काष्ठा eth_hdr अणु
	अचिन्हित अक्षर eth_dest[6];
	अचिन्हित अक्षर eth_source[6];
	अचिन्हित लघु eth_proto;
पूर्ण;

अटल __noअंतरभूत __u64 calc_offset(bool is_ipv6, bool is_icmp)
अणु
	__u64 off = माप(काष्ठा eth_hdr);
	अगर (is_ipv6) अणु
		off += माप(काष्ठा ipv6hdr);
		अगर (is_icmp)
			off += माप(काष्ठा icmp6hdr) + माप(काष्ठा ipv6hdr);
	पूर्ण अन्यथा अणु
		off += माप(काष्ठा iphdr);
		अगर (is_icmp)
			off += माप(काष्ठा icmphdr) + माप(काष्ठा iphdr);
	पूर्ण
	वापस off;
पूर्ण

अटल __attribute__ ((noअंतरभूत))
bool parse_udp(व्योम *data, व्योम *data_end,
	       bool is_ipv6, काष्ठा packet_description *pckt)
अणु

	bool is_icmp = !((pckt->flags & (1 << 0)) == 0);
	__u64 off = calc_offset(is_ipv6, is_icmp);
	काष्ठा udphdr *udp;
	udp = data + off;

	अगर (udp + 1 > data_end)
		वापस 0;
	अगर (!is_icmp) अणु
		pckt->flow.port16[0] = udp->source;
		pckt->flow.port16[1] = udp->dest;
	पूर्ण अन्यथा अणु
		pckt->flow.port16[0] = udp->dest;
		pckt->flow.port16[1] = udp->source;
	पूर्ण
	वापस 1;
पूर्ण

अटल __attribute__ ((noअंतरभूत))
bool parse_tcp(व्योम *data, व्योम *data_end,
	       bool is_ipv6, काष्ठा packet_description *pckt)
अणु

	bool is_icmp = !((pckt->flags & (1 << 0)) == 0);
	__u64 off = calc_offset(is_ipv6, is_icmp);
	काष्ठा tcphdr *tcp;

	tcp = data + off;
	अगर (tcp + 1 > data_end)
		वापस 0;
	अगर (tcp->syn)
		pckt->flags |= (1 << 1);
	अगर (!is_icmp) अणु
		pckt->flow.port16[0] = tcp->source;
		pckt->flow.port16[1] = tcp->dest;
	पूर्ण अन्यथा अणु
		pckt->flow.port16[0] = tcp->dest;
		pckt->flow.port16[1] = tcp->source;
	पूर्ण
	वापस 1;
पूर्ण

अटल __attribute__ ((noअंतरभूत))
bool encap_v6(काष्ठा xdp_md *xdp, काष्ठा ctl_value *cval,
	      काष्ठा packet_description *pckt,
	      काष्ठा real_definition *dst, __u32 pkt_bytes)
अणु
	काष्ठा eth_hdr *new_eth;
	काष्ठा eth_hdr *old_eth;
	काष्ठा ipv6hdr *ip6h;
	__u32 ip_suffix;
	व्योम *data_end;
	व्योम *data;

	अगर (bpf_xdp_adjust_head(xdp, 0 - (पूर्णांक)माप(काष्ठा ipv6hdr)))
		वापस 0;
	data = (व्योम *)(दीर्घ)xdp->data;
	data_end = (व्योम *)(दीर्घ)xdp->data_end;
	new_eth = data;
	ip6h = data + माप(काष्ठा eth_hdr);
	old_eth = data + माप(काष्ठा ipv6hdr);
	अगर (new_eth + 1 > data_end ||
	    old_eth + 1 > data_end || ip6h + 1 > data_end)
		वापस 0;
	स_नकल(new_eth->eth_dest, cval->mac, 6);
	स_नकल(new_eth->eth_source, old_eth->eth_dest, 6);
	new_eth->eth_proto = 56710;
	ip6h->version = 6;
	ip6h->priority = 0;
	स_रखो(ip6h->flow_lbl, 0, माप(ip6h->flow_lbl));

	ip6h->nexthdr = IPPROTO_IPV6;
	ip_suffix = pckt->flow.srcv6[3] ^ pckt->flow.port16[0];
	ip6h->payload_len =
	    bpf_htons(pkt_bytes + माप(काष्ठा ipv6hdr));
	ip6h->hop_limit = 4;

	ip6h->saddr.in6_u.u6_addr32[0] = 1;
	ip6h->saddr.in6_u.u6_addr32[1] = 2;
	ip6h->saddr.in6_u.u6_addr32[2] = 3;
	ip6h->saddr.in6_u.u6_addr32[3] = ip_suffix;
	स_नकल(ip6h->daddr.in6_u.u6_addr32, dst->dstv6, 16);
	वापस 1;
पूर्ण

अटल __attribute__ ((noअंतरभूत))
bool encap_v4(काष्ठा xdp_md *xdp, काष्ठा ctl_value *cval,
	      काष्ठा packet_description *pckt,
	      काष्ठा real_definition *dst, __u32 pkt_bytes)
अणु

	__u32 ip_suffix = bpf_ntohs(pckt->flow.port16[0]);
	काष्ठा eth_hdr *new_eth;
	काष्ठा eth_hdr *old_eth;
	__u16 *next_iph_u16;
	काष्ठा iphdr *iph;
	__u32 csum = 0;
	व्योम *data_end;
	व्योम *data;

	ip_suffix <<= 15;
	ip_suffix ^= pckt->flow.src;
	अगर (bpf_xdp_adjust_head(xdp, 0 - (पूर्णांक)माप(काष्ठा iphdr)))
		वापस 0;
	data = (व्योम *)(दीर्घ)xdp->data;
	data_end = (व्योम *)(दीर्घ)xdp->data_end;
	new_eth = data;
	iph = data + माप(काष्ठा eth_hdr);
	old_eth = data + माप(काष्ठा iphdr);
	अगर (new_eth + 1 > data_end ||
	    old_eth + 1 > data_end || iph + 1 > data_end)
		वापस 0;
	स_नकल(new_eth->eth_dest, cval->mac, 6);
	स_नकल(new_eth->eth_source, old_eth->eth_dest, 6);
	new_eth->eth_proto = 8;
	iph->version = 4;
	iph->ihl = 5;
	iph->frag_off = 0;
	iph->protocol = IPPROTO_IPIP;
	iph->check = 0;
	iph->tos = 1;
	iph->tot_len = bpf_htons(pkt_bytes + माप(काष्ठा iphdr));
	/* करोn't update iph->daddr, since it will overग_लिखो old eth_proto
	 * and multiple iterations of bpf_prog_run() will fail
	 */

	iph->saddr = ((0xFFFF0000 & ip_suffix) | 4268) ^ dst->dst;
	iph->ttl = 4;

	next_iph_u16 = (__u16 *) iph;
#आशय clang loop unroll(full)
	क्रम (पूर्णांक i = 0; i < माप(काष्ठा iphdr) >> 1; i++)
		csum += *next_iph_u16++;
	iph->check = ~((csum & 0xffff) + (csum >> 16));
	अगर (bpf_xdp_adjust_head(xdp, (पूर्णांक)माप(काष्ठा iphdr)))
		वापस 0;
	वापस 1;
पूर्ण

अटल __attribute__ ((noअंतरभूत))
bool decap_v6(काष्ठा xdp_md *xdp, व्योम **data, व्योम **data_end, bool inner_v4)
अणु
	काष्ठा eth_hdr *new_eth;
	काष्ठा eth_hdr *old_eth;

	old_eth = *data;
	new_eth = *data + माप(काष्ठा ipv6hdr);
	स_नकल(new_eth->eth_source, old_eth->eth_source, 6);
	स_नकल(new_eth->eth_dest, old_eth->eth_dest, 6);
	अगर (inner_v4)
		new_eth->eth_proto = 8;
	अन्यथा
		new_eth->eth_proto = 56710;
	अगर (bpf_xdp_adjust_head(xdp, (पूर्णांक)माप(काष्ठा ipv6hdr)))
		वापस 0;
	*data = (व्योम *)(दीर्घ)xdp->data;
	*data_end = (व्योम *)(दीर्घ)xdp->data_end;
	वापस 1;
पूर्ण

अटल __attribute__ ((noअंतरभूत))
bool decap_v4(काष्ठा xdp_md *xdp, व्योम **data, व्योम **data_end)
अणु
	काष्ठा eth_hdr *new_eth;
	काष्ठा eth_hdr *old_eth;

	old_eth = *data;
	new_eth = *data + माप(काष्ठा iphdr);
	स_नकल(new_eth->eth_source, old_eth->eth_source, 6);
	स_नकल(new_eth->eth_dest, old_eth->eth_dest, 6);
	new_eth->eth_proto = 8;
	अगर (bpf_xdp_adjust_head(xdp, (पूर्णांक)माप(काष्ठा iphdr)))
		वापस 0;
	*data = (व्योम *)(दीर्घ)xdp->data;
	*data_end = (व्योम *)(दीर्घ)xdp->data_end;
	वापस 1;
पूर्ण

अटल __attribute__ ((noअंतरभूत))
पूर्णांक swap_mac_and_send(व्योम *data, व्योम *data_end)
अणु
	अचिन्हित अक्षर पंचांगp_mac[6];
	काष्ठा eth_hdr *eth;

	eth = data;
	स_नकल(पंचांगp_mac, eth->eth_source, 6);
	स_नकल(eth->eth_source, eth->eth_dest, 6);
	स_नकल(eth->eth_dest, पंचांगp_mac, 6);
	वापस XDP_TX;
पूर्ण

अटल __attribute__ ((noअंतरभूत))
पूर्णांक send_icmp_reply(व्योम *data, व्योम *data_end)
अणु
	काष्ठा icmphdr *icmp_hdr;
	__u16 *next_iph_u16;
	__u32 पंचांगp_addr = 0;
	काष्ठा iphdr *iph;
	__u32 csum1 = 0;
	__u32 csum = 0;
	__u64 off = 0;

	अगर (data + माप(काष्ठा eth_hdr)
	     + माप(काष्ठा iphdr) + माप(काष्ठा icmphdr) > data_end)
		वापस XDP_DROP;
	off += माप(काष्ठा eth_hdr);
	iph = data + off;
	off += माप(काष्ठा iphdr);
	icmp_hdr = data + off;
	icmp_hdr->type = 0;
	icmp_hdr->checksum += 0x0007;
	iph->ttl = 4;
	पंचांगp_addr = iph->daddr;
	iph->daddr = iph->saddr;
	iph->saddr = पंचांगp_addr;
	iph->check = 0;
	next_iph_u16 = (__u16 *) iph;
#आशय clang loop unroll(full)
	क्रम (पूर्णांक i = 0; i < माप(काष्ठा iphdr) >> 1; i++)
		csum += *next_iph_u16++;
	iph->check = ~((csum & 0xffff) + (csum >> 16));
	वापस swap_mac_and_send(data, data_end);
पूर्ण

अटल __attribute__ ((noअंतरभूत))
पूर्णांक send_icmp6_reply(व्योम *data, व्योम *data_end)
अणु
	काष्ठा icmp6hdr *icmp_hdr;
	काष्ठा ipv6hdr *ip6h;
	__be32 पंचांगp_addr[4];
	__u64 off = 0;

	अगर (data + माप(काष्ठा eth_hdr)
	     + माप(काष्ठा ipv6hdr) + माप(काष्ठा icmp6hdr) > data_end)
		वापस XDP_DROP;
	off += माप(काष्ठा eth_hdr);
	ip6h = data + off;
	off += माप(काष्ठा ipv6hdr);
	icmp_hdr = data + off;
	icmp_hdr->icmp6_type = 129;
	icmp_hdr->icmp6_cksum -= 0x0001;
	ip6h->hop_limit = 4;
	स_नकल(पंचांगp_addr, ip6h->saddr.in6_u.u6_addr32, 16);
	स_नकल(ip6h->saddr.in6_u.u6_addr32, ip6h->daddr.in6_u.u6_addr32, 16);
	स_नकल(ip6h->daddr.in6_u.u6_addr32, पंचांगp_addr, 16);
	वापस swap_mac_and_send(data, data_end);
पूर्ण

अटल __attribute__ ((noअंतरभूत))
पूर्णांक parse_icmpv6(व्योम *data, व्योम *data_end, __u64 off,
		 काष्ठा packet_description *pckt)
अणु
	काष्ठा icmp6hdr *icmp_hdr;
	काष्ठा ipv6hdr *ip6h;

	icmp_hdr = data + off;
	अगर (icmp_hdr + 1 > data_end)
		वापस XDP_DROP;
	अगर (icmp_hdr->icmp6_type == 128)
		वापस send_icmp6_reply(data, data_end);
	अगर (icmp_hdr->icmp6_type != 3)
		वापस XDP_PASS;
	off += माप(काष्ठा icmp6hdr);
	ip6h = data + off;
	अगर (ip6h + 1 > data_end)
		वापस XDP_DROP;
	pckt->flow.proto = ip6h->nexthdr;
	pckt->flags |= (1 << 0);
	स_नकल(pckt->flow.srcv6, ip6h->daddr.in6_u.u6_addr32, 16);
	स_नकल(pckt->flow.dstv6, ip6h->saddr.in6_u.u6_addr32, 16);
	वापस -1;
पूर्ण

अटल __attribute__ ((noअंतरभूत))
पूर्णांक parse_icmp(व्योम *data, व्योम *data_end, __u64 off,
	       काष्ठा packet_description *pckt)
अणु
	काष्ठा icmphdr *icmp_hdr;
	काष्ठा iphdr *iph;

	icmp_hdr = data + off;
	अगर (icmp_hdr + 1 > data_end)
		वापस XDP_DROP;
	अगर (icmp_hdr->type == 8)
		वापस send_icmp_reply(data, data_end);
	अगर ((icmp_hdr->type != 3) || (icmp_hdr->code != 4))
		वापस XDP_PASS;
	off += माप(काष्ठा icmphdr);
	iph = data + off;
	अगर (iph + 1 > data_end)
		वापस XDP_DROP;
	अगर (iph->ihl != 5)
		वापस XDP_DROP;
	pckt->flow.proto = iph->protocol;
	pckt->flags |= (1 << 0);
	pckt->flow.src = iph->daddr;
	pckt->flow.dst = iph->saddr;
	वापस -1;
पूर्ण

अटल __attribute__ ((noअंतरभूत))
__u32 get_packet_hash(काष्ठा packet_description *pckt,
		      bool hash_16bytes)
अणु
	अगर (hash_16bytes)
		वापस jhash_2words(jhash(pckt->flow.srcv6, 16, 12),
				    pckt->flow.ports, 24);
	अन्यथा
		वापस jhash_2words(pckt->flow.src, pckt->flow.ports,
				    24);
पूर्ण

__attribute__ ((noअंतरभूत))
अटल bool get_packet_dst(काष्ठा real_definition **real,
			   काष्ठा packet_description *pckt,
			   काष्ठा vip_meta *vip_info,
			   bool is_ipv6, व्योम *lru_map)
अणु
	काष्ठा real_pos_lru new_dst_lru = अणु पूर्ण;
	bool hash_16bytes = is_ipv6;
	__u32 *real_pos, hash, key;
	__u64 cur_समय;

	अगर (vip_info->flags & (1 << 2))
		hash_16bytes = 1;
	अगर (vip_info->flags & (1 << 3)) अणु
		pckt->flow.port16[0] = pckt->flow.port16[1];
		स_रखो(pckt->flow.srcv6, 0, 16);
	पूर्ण
	hash = get_packet_hash(pckt, hash_16bytes);
	अगर (hash != 0x358459b7 /* jhash of ipv4 packet */  &&
	    hash != 0x2f4bc6bb /* jhash of ipv6 packet */)
		वापस 0;
	key = 2 * vip_info->vip_num + hash % 2;
	real_pos = bpf_map_lookup_elem(&ch_rings, &key);
	अगर (!real_pos)
		वापस 0;
	key = *real_pos;
	*real = bpf_map_lookup_elem(&reals, &key);
	अगर (!(*real))
		वापस 0;
	अगर (!(vip_info->flags & (1 << 1))) अणु
		__u32 conn_rate_key = 512 + 2;
		काष्ठा lb_stats *conn_rate_stats =
		    bpf_map_lookup_elem(&stats, &conn_rate_key);

		अगर (!conn_rate_stats)
			वापस 1;
		cur_समय = bpf_kसमय_get_ns();
		अगर ((cur_समय - conn_rate_stats->v2) >> 32 > 0xffFFFF) अणु
			conn_rate_stats->v1 = 1;
			conn_rate_stats->v2 = cur_समय;
		पूर्ण अन्यथा अणु
			conn_rate_stats->v1 += 1;
			अगर (conn_rate_stats->v1 >= 1)
				वापस 1;
		पूर्ण
		अगर (pckt->flow.proto == IPPROTO_UDP)
			new_dst_lru.aसमय = cur_समय;
		new_dst_lru.pos = key;
		bpf_map_update_elem(lru_map, &pckt->flow, &new_dst_lru, 0);
	पूर्ण
	वापस 1;
पूर्ण

__attribute__ ((noअंतरभूत))
अटल व्योम connection_table_lookup(काष्ठा real_definition **real,
				    काष्ठा packet_description *pckt,
				    व्योम *lru_map)
अणु

	काष्ठा real_pos_lru *dst_lru;
	__u64 cur_समय;
	__u32 key;

	dst_lru = bpf_map_lookup_elem(lru_map, &pckt->flow);
	अगर (!dst_lru)
		वापस;
	अगर (pckt->flow.proto == IPPROTO_UDP) अणु
		cur_समय = bpf_kसमय_get_ns();
		अगर (cur_समय - dst_lru->aसमय > 300000)
			वापस;
		dst_lru->aसमय = cur_समय;
	पूर्ण
	key = dst_lru->pos;
	*real = bpf_map_lookup_elem(&reals, &key);
पूर्ण

/* करोn't believe your eyes!
 * below function has 6 arguments whereas bpf and llvm allow maximum of 5
 * but since it's _अटल_ llvm can optimize one argument away
 */
__attribute__ ((noअंतरभूत))
अटल पूर्णांक process_l3_headers_v6(काष्ठा packet_description *pckt,
				 __u8 *protocol, __u64 off,
				 __u16 *pkt_bytes, व्योम *data,
				 व्योम *data_end)
अणु
	काष्ठा ipv6hdr *ip6h;
	__u64 iph_len;
	पूर्णांक action;

	ip6h = data + off;
	अगर (ip6h + 1 > data_end)
		वापस XDP_DROP;
	iph_len = माप(काष्ठा ipv6hdr);
	*protocol = ip6h->nexthdr;
	pckt->flow.proto = *protocol;
	*pkt_bytes = bpf_ntohs(ip6h->payload_len);
	off += iph_len;
	अगर (*protocol == 45) अणु
		वापस XDP_DROP;
	पूर्ण अन्यथा अगर (*protocol == 59) अणु
		action = parse_icmpv6(data, data_end, off, pckt);
		अगर (action >= 0)
			वापस action;
	पूर्ण अन्यथा अणु
		स_नकल(pckt->flow.srcv6, ip6h->saddr.in6_u.u6_addr32, 16);
		स_नकल(pckt->flow.dstv6, ip6h->daddr.in6_u.u6_addr32, 16);
	पूर्ण
	वापस -1;
पूर्ण

__attribute__ ((noअंतरभूत))
अटल पूर्णांक process_l3_headers_v4(काष्ठा packet_description *pckt,
				 __u8 *protocol, __u64 off,
				 __u16 *pkt_bytes, व्योम *data,
				 व्योम *data_end)
अणु
	काष्ठा iphdr *iph;
	__u64 iph_len;
	पूर्णांक action;

	iph = data + off;
	अगर (iph + 1 > data_end)
		वापस XDP_DROP;
	अगर (iph->ihl != 5)
		वापस XDP_DROP;
	*protocol = iph->protocol;
	pckt->flow.proto = *protocol;
	*pkt_bytes = bpf_ntohs(iph->tot_len);
	off += 20;
	अगर (iph->frag_off & 65343)
		वापस XDP_DROP;
	अगर (*protocol == IPPROTO_ICMP) अणु
		action = parse_icmp(data, data_end, off, pckt);
		अगर (action >= 0)
			वापस action;
	पूर्ण अन्यथा अणु
		pckt->flow.src = iph->saddr;
		pckt->flow.dst = iph->daddr;
	पूर्ण
	वापस -1;
पूर्ण

__attribute__ ((noअंतरभूत))
अटल पूर्णांक process_packet(व्योम *data, __u64 off, व्योम *data_end,
			  bool is_ipv6, काष्ठा xdp_md *xdp)
अणु

	काष्ठा real_definition *dst = शून्य;
	काष्ठा packet_description pckt = अणु पूर्ण;
	काष्ठा vip_definition vip = अणु पूर्ण;
	काष्ठा lb_stats *data_stats;
	काष्ठा eth_hdr *eth = data;
	व्योम *lru_map = &lru_cache;
	काष्ठा vip_meta *vip_info;
	__u32 lru_stats_key = 513;
	__u32 mac_addr_pos = 0;
	__u32 stats_key = 512;
	काष्ठा ctl_value *cval;
	__u16 pkt_bytes;
	__u64 iph_len;
	__u8 protocol;
	__u32 vip_num;
	पूर्णांक action;

	अगर (is_ipv6)
		action = process_l3_headers_v6(&pckt, &protocol, off,
					       &pkt_bytes, data, data_end);
	अन्यथा
		action = process_l3_headers_v4(&pckt, &protocol, off,
					       &pkt_bytes, data, data_end);
	अगर (action >= 0)
		वापस action;
	protocol = pckt.flow.proto;
	अगर (protocol == IPPROTO_TCP) अणु
		अगर (!parse_tcp(data, data_end, is_ipv6, &pckt))
			वापस XDP_DROP;
	पूर्ण अन्यथा अगर (protocol == IPPROTO_UDP) अणु
		अगर (!parse_udp(data, data_end, is_ipv6, &pckt))
			वापस XDP_DROP;
	पूर्ण अन्यथा अणु
		वापस XDP_TX;
	पूर्ण

	अगर (is_ipv6)
		स_नकल(vip.vipv6, pckt.flow.dstv6, 16);
	अन्यथा
		vip.vip = pckt.flow.dst;
	vip.port = pckt.flow.port16[1];
	vip.proto = pckt.flow.proto;
	vip_info = bpf_map_lookup_elem(&vip_map, &vip);
	अगर (!vip_info) अणु
		vip.port = 0;
		vip_info = bpf_map_lookup_elem(&vip_map, &vip);
		अगर (!vip_info)
			वापस XDP_PASS;
		अगर (!(vip_info->flags & (1 << 4)))
			pckt.flow.port16[1] = 0;
	पूर्ण
	अगर (data_end - data > 1400)
		वापस XDP_DROP;
	data_stats = bpf_map_lookup_elem(&stats, &stats_key);
	अगर (!data_stats)
		वापस XDP_DROP;
	data_stats->v1 += 1;
	अगर (!dst) अणु
		अगर (vip_info->flags & (1 << 0))
			pckt.flow.port16[0] = 0;
		अगर (!(pckt.flags & (1 << 1)) && !(vip_info->flags & (1 << 1)))
			connection_table_lookup(&dst, &pckt, lru_map);
		अगर (dst)
			जाओ out;
		अगर (pckt.flow.proto == IPPROTO_TCP) अणु
			काष्ठा lb_stats *lru_stats =
			    bpf_map_lookup_elem(&stats, &lru_stats_key);

			अगर (!lru_stats)
				वापस XDP_DROP;
			अगर (pckt.flags & (1 << 1))
				lru_stats->v1 += 1;
			अन्यथा
				lru_stats->v2 += 1;
		पूर्ण
		अगर (!get_packet_dst(&dst, &pckt, vip_info, is_ipv6, lru_map))
			वापस XDP_DROP;
		data_stats->v2 += 1;
	पूर्ण
out:
	cval = bpf_map_lookup_elem(&ctl_array, &mac_addr_pos);
	अगर (!cval)
		वापस XDP_DROP;
	अगर (dst->flags & (1 << 0)) अणु
		अगर (!encap_v6(xdp, cval, &pckt, dst, pkt_bytes))
			वापस XDP_DROP;
	पूर्ण अन्यथा अणु
		अगर (!encap_v4(xdp, cval, &pckt, dst, pkt_bytes))
			वापस XDP_DROP;
	पूर्ण
	vip_num = vip_info->vip_num;
	data_stats = bpf_map_lookup_elem(&stats, &vip_num);
	अगर (!data_stats)
		वापस XDP_DROP;
	data_stats->v1 += 1;
	data_stats->v2 += pkt_bytes;

	data = (व्योम *)(दीर्घ)xdp->data;
	data_end = (व्योम *)(दीर्घ)xdp->data_end;
	अगर (data + 4 > data_end)
		वापस XDP_DROP;
	*(u32 *)data = dst->dst;
	वापस XDP_DROP;
पूर्ण

SEC("xdp-test-v4")
पूर्णांक balancer_ingress_v4(काष्ठा xdp_md *ctx)
अणु
	व्योम *data = (व्योम *)(दीर्घ)ctx->data;
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	काष्ठा eth_hdr *eth = data;
	__u32 eth_proto;
	__u32 nh_off;

	nh_off = माप(काष्ठा eth_hdr);
	अगर (data + nh_off > data_end)
		वापस XDP_DROP;
	eth_proto = bpf_ntohs(eth->eth_proto);
	अगर (eth_proto == ETH_P_IP)
		वापस process_packet(data, nh_off, data_end, 0, ctx);
	अन्यथा
		वापस XDP_DROP;
पूर्ण

SEC("xdp-test-v6")
पूर्णांक balancer_ingress_v6(काष्ठा xdp_md *ctx)
अणु
	व्योम *data = (व्योम *)(दीर्घ)ctx->data;
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	काष्ठा eth_hdr *eth = data;
	__u32 eth_proto;
	__u32 nh_off;

	nh_off = माप(काष्ठा eth_hdr);
	अगर (data + nh_off > data_end)
		वापस XDP_DROP;
	eth_proto = bpf_ntohs(eth->eth_proto);
	अगर (eth_proto == ETH_P_IPV6)
		वापस process_packet(data, nh_off, data_end, 1, ctx);
	अन्यथा
		वापस XDP_DROP;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
