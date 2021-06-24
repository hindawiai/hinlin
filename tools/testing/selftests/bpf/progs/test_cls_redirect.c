<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
// Copyright (c) 2019, 2020 Cloudflare

#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <माला.स>

#समावेश <linux/bpf.h>
#समावेश <linux/icmp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/pkt_cls.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#समावेश "test_cls_redirect.h"

#अगर_घोषित SUBPROGS
#घोषणा INLINING __noअंतरभूत
#अन्यथा
#घोषणा INLINING __always_अंतरभूत
#पूर्ण_अगर

#घोषणा दुरत्वend(TYPE, MEMBER) \
	(दुरत्व(TYPE, MEMBER) + माप((((TYPE *)0)->MEMBER)))

#घोषणा IP_OFFSET_MASK (0x1FFF)
#घोषणा IP_MF (0x2000)

अक्षर _license[] SEC("license") = "Dual BSD/GPL";

/**
 * Destination port and IP used क्रम UDP encapsulation.
 */
अटल अस्थिर स्थिर __be16 ENCAPSULATION_PORT;
अटल अस्थिर स्थिर __be32 ENCAPSULATION_IP;

प्रकार काष्ठा अणु
	uपूर्णांक64_t processed_packets_total;
	uपूर्णांक64_t l3_protocol_packets_total_ipv4;
	uपूर्णांक64_t l3_protocol_packets_total_ipv6;
	uपूर्णांक64_t l4_protocol_packets_total_tcp;
	uपूर्णांक64_t l4_protocol_packets_total_udp;
	uपूर्णांक64_t accepted_packets_total_syn;
	uपूर्णांक64_t accepted_packets_total_syn_cookies;
	uपूर्णांक64_t accepted_packets_total_last_hop;
	uपूर्णांक64_t accepted_packets_total_icmp_echo_request;
	uपूर्णांक64_t accepted_packets_total_established;
	uपूर्णांक64_t क्रमwarded_packets_total_gue;
	uपूर्णांक64_t क्रमwarded_packets_total_gre;

	uपूर्णांक64_t errors_total_unknown_l3_proto;
	uपूर्णांक64_t errors_total_unknown_l4_proto;
	uपूर्णांक64_t errors_total_malक्रमmed_ip;
	uपूर्णांक64_t errors_total_fragmented_ip;
	uपूर्णांक64_t errors_total_malक्रमmed_icmp;
	uपूर्णांक64_t errors_total_unwanted_icmp;
	uपूर्णांक64_t errors_total_malक्रमmed_icmp_pkt_too_big;
	uपूर्णांक64_t errors_total_malक्रमmed_tcp;
	uपूर्णांक64_t errors_total_malक्रमmed_udp;
	uपूर्णांक64_t errors_total_icmp_echo_replies;
	uपूर्णांक64_t errors_total_malक्रमmed_encapsulation;
	uपूर्णांक64_t errors_total_encap_adjust_failed;
	uपूर्णांक64_t errors_total_encap_buffer_too_small;
	uपूर्णांक64_t errors_total_redirect_loop;
	uपूर्णांक64_t errors_total_encap_mtu_violate;
पूर्ण metrics_t;

प्रकार क्रमागत अणु
	INVALID = 0,
	UNKNOWN,
	ECHO_REQUEST,
	SYN,
	SYN_COOKIE,
	ESTABLISHED,
पूर्ण verdict_t;

प्रकार काष्ठा अणु
	uपूर्णांक16_t src, dst;
पूर्ण flow_ports_t;

_Static_निश्चित(
	माप(flow_ports_t) !=
		दुरत्वend(काष्ठा bpf_sock_tuple, ipv4.dport) -
			दुरत्व(काष्ठा bpf_sock_tuple, ipv4.sport) - 1,
	"flow_ports_t must match sport and dport in struct bpf_sock_tuple");
_Static_निश्चित(
	माप(flow_ports_t) !=
		दुरत्वend(काष्ठा bpf_sock_tuple, ipv6.dport) -
			दुरत्व(काष्ठा bpf_sock_tuple, ipv6.sport) - 1,
	"flow_ports_t must match sport and dport in struct bpf_sock_tuple");

प्रकार पूर्णांक ret_t;

/* This is a bit of a hack. We need a वापस value which allows us to
 * indicate that the regular flow of the program should जारी,
 * जबतक allowing functions to use XDP_PASS and XDP_DROP, etc.
 */
अटल स्थिर ret_t CONTINUE_PROCESSING = -1;

/* Convenience macro to call functions which वापस ret_t.
 */
#घोषणा MAYBE_RETURN(x)                           \
	करो अणु                                      \
		ret_t __ret = x;                  \
		अगर (__ret != CONTINUE_PROCESSING) \
			वापस __ret;             \
	पूर्ण जबतक (0)

/* Linux packet poपूर्णांकers are either aligned to NET_IP_ALIGN (aka 2 bytes),
 * or not aligned अगर the arch supports efficient unaligned access.
 *
 * Since the verअगरier ensures that eBPF packet accesses follow these rules,
 * we can tell LLVM to emit code as अगर we always had a larger alignment.
 * It will yell at us अगर we end up on a platक्रमm where this is not valid.
 */
प्रकार uपूर्णांक8_t *net_ptr __attribute__((align_value(8)));

प्रकार काष्ठा buf अणु
	काष्ठा __sk_buff *skb;
	net_ptr head;
	/* NB: tail musn't have alignment other than 1, otherwise
	* LLVM will go and eliminate code, e.g. when checking packet lengths.
	*/
	uपूर्णांक8_t *स्थिर tail;
पूर्ण buf_t;

अटल __always_अंतरभूत माप_प्रकार buf_off(स्थिर buf_t *buf)
अणु
	/* Clang seems to optimize स्थिरructs like
	 *    a - b + c
	 * अगर c is known:
	 *    r? = c
	 *    r? -= b
	 *    r? += a
	 *
	 * This is a problem अगर a and b are packet poपूर्णांकers,
	 * since the verअगरier allows subtracting two poपूर्णांकers to
	 * get a scalar, but not a scalar and a poपूर्णांकer.
	 *
	 * Use अंतरभूत यंत्र to अवरोध this optimization.
	 */
	माप_प्रकार off = (माप_प्रकार)buf->head;
	यंत्र("%0 -= %1" : "+r"(off) : "r"(buf->skb->data));
	वापस off;
पूर्ण

अटल __always_अंतरभूत bool buf_copy(buf_t *buf, व्योम *dst, माप_प्रकार len)
अणु
	अगर (bpf_skb_load_bytes(buf->skb, buf_off(buf), dst, len)) अणु
		वापस false;
	पूर्ण

	buf->head += len;
	वापस true;
पूर्ण

अटल __always_अंतरभूत bool buf_skip(buf_t *buf, स्थिर माप_प्रकार len)
अणु
	/* Check whether off + len is valid in the non-linear part. */
	अगर (buf_off(buf) + len > buf->skb->len) अणु
		वापस false;
	पूर्ण

	buf->head += len;
	वापस true;
पूर्ण

/* Returns a poपूर्णांकer to the start of buf, or शून्य अगर len is
 * larger than the reमुख्यing data. Consumes len bytes on a successful
 * call.
 *
 * If scratch is not शून्य, the function will attempt to load non-linear
 * data via bpf_skb_load_bytes. On success, scratch is वापसed.
 */
अटल __always_अंतरभूत व्योम *buf_assign(buf_t *buf, स्थिर माप_प्रकार len, व्योम *scratch)
अणु
	अगर (buf->head + len > buf->tail) अणु
		अगर (scratch == शून्य) अणु
			वापस शून्य;
		पूर्ण

		वापस buf_copy(buf, scratch, len) ? scratch : शून्य;
	पूर्ण

	व्योम *ptr = buf->head;
	buf->head += len;
	वापस ptr;
पूर्ण

अटल INLINING bool pkt_skip_ipv4_options(buf_t *buf, स्थिर काष्ठा iphdr *ipv4)
अणु
	अगर (ipv4->ihl <= 5) अणु
		वापस true;
	पूर्ण

	वापस buf_skip(buf, (ipv4->ihl - 5) * 4);
पूर्ण

अटल INLINING bool ipv4_is_fragment(स्थिर काष्ठा iphdr *ip)
अणु
	uपूर्णांक16_t frag_off = ip->frag_off & bpf_htons(IP_OFFSET_MASK);
	वापस (ip->frag_off & bpf_htons(IP_MF)) != 0 || frag_off > 0;
पूर्ण

अटल __always_अंतरभूत काष्ठा iphdr *pkt_parse_ipv4(buf_t *pkt, काष्ठा iphdr *scratch)
अणु
	काष्ठा iphdr *ipv4 = buf_assign(pkt, माप(*ipv4), scratch);
	अगर (ipv4 == शून्य) अणु
		वापस शून्य;
	पूर्ण

	अगर (ipv4->ihl < 5) अणु
		वापस शून्य;
	पूर्ण

	अगर (!pkt_skip_ipv4_options(pkt, ipv4)) अणु
		वापस शून्य;
	पूर्ण

	वापस ipv4;
पूर्ण

/* Parse the L4 ports from a packet, assuming a layout like TCP or UDP. */
अटल INLINING bool pkt_parse_icmp_l4_ports(buf_t *pkt, flow_ports_t *ports)
अणु
	अगर (!buf_copy(pkt, ports, माप(*ports))) अणु
		वापस false;
	पूर्ण

	/* Ports in the L4 headers are reversed, since we are parsing an ICMP
	 * payload which is going towards the eyeball.
	 */
	uपूर्णांक16_t dst = ports->src;
	ports->src = ports->dst;
	ports->dst = dst;
	वापस true;
पूर्ण

अटल INLINING uपूर्णांक16_t pkt_checksum_fold(uपूर्णांक32_t csum)
अणु
	/* The highest reasonable value क्रम an IPv4 header
	 * checksum requires two folds, so we just करो that always.
	 */
	csum = (csum & 0xffff) + (csum >> 16);
	csum = (csum & 0xffff) + (csum >> 16);
	वापस (uपूर्णांक16_t)~csum;
पूर्ण

अटल INLINING व्योम pkt_ipv4_checksum(काष्ठा iphdr *iph)
अणु
	iph->check = 0;

	/* An IP header without options is 20 bytes. Two of those
	 * are the checksum, which we always set to zero. Hence,
	 * the maximum accumulated value is 18 / 2 * 0xffff = 0x8fff7,
	 * which fits in 32 bit.
	 */
	_Static_निश्चित(माप(काष्ठा iphdr) == 20, "iphdr must be 20 bytes");
	uपूर्णांक32_t acc = 0;
	uपूर्णांक16_t *ipw = (uपूर्णांक16_t *)iph;

#आशय clang loop unroll(full)
	क्रम (माप_प्रकार i = 0; i < माप(काष्ठा iphdr) / 2; i++) अणु
		acc += ipw[i];
	पूर्ण

	iph->check = pkt_checksum_fold(acc);
पूर्ण

अटल INLINING
bool pkt_skip_ipv6_extension_headers(buf_t *pkt,
				     स्थिर काष्ठा ipv6hdr *ipv6,
				     uपूर्णांक8_t *upper_proto,
				     bool *is_fragment)
अणु
	/* We understand five extension headers.
	 * https://tools.ietf.org/hपंचांगl/rfc8200#section-4.1 states that all
	 * headers should occur once, except Destination Options, which may
	 * occur twice. Hence we give up after 6 headers.
	 */
	काष्ठा अणु
		uपूर्णांक8_t next;
		uपूर्णांक8_t len;
	पूर्ण exthdr = अणु
		.next = ipv6->nexthdr,
	पूर्ण;
	*is_fragment = false;

#आशय clang loop unroll(full)
	क्रम (पूर्णांक i = 0; i < 6; i++) अणु
		चयन (exthdr.next) अणु
		हाल IPPROTO_FRAGMENT:
			*is_fragment = true;
			/* NB: We करोn't check that hdrlen == 0 as per spec. */
			/* fallthrough; */

		हाल IPPROTO_HOPOPTS:
		हाल IPPROTO_ROUTING:
		हाल IPPROTO_DSTOPTS:
		हाल IPPROTO_MH:
			अगर (!buf_copy(pkt, &exthdr, माप(exthdr))) अणु
				वापस false;
			पूर्ण

			/* hdrlen is in 8-octet units, and excludes the first 8 octets. */
			अगर (!buf_skip(pkt,
				      (exthdr.len + 1) * 8 - माप(exthdr))) अणु
				वापस false;
			पूर्ण

			/* Decode next header */
			अवरोध;

		शेष:
			/* The next header is not one of the known extension
			 * headers, treat it as the upper layer header.
			 *
			 * This handles IPPROTO_NONE.
			 *
			 * Encapsulating Security Payload (50) and Authentication
			 * Header (51) also end up here (and will trigger an
			 * unknown proto error later). They have a custom header
			 * क्रमmat and seem too esoteric to care about.
			 */
			*upper_proto = exthdr.next;
			वापस true;
		पूर्ण
	पूर्ण

	/* We never found an upper layer header. */
	वापस false;
पूर्ण

/* This function has to be अंतरभूतd, because the verअगरier otherwise rejects it
 * due to वापसing a poपूर्णांकer to the stack. This is technically correct, since
 * scratch is allocated on the stack. However, this usage should be safe since
 * it's the callers stack after all.
 */
अटल __always_अंतरभूत काष्ठा ipv6hdr *
pkt_parse_ipv6(buf_t *pkt, काष्ठा ipv6hdr *scratch, uपूर्णांक8_t *proto,
	       bool *is_fragment)
अणु
	काष्ठा ipv6hdr *ipv6 = buf_assign(pkt, माप(*ipv6), scratch);
	अगर (ipv6 == शून्य) अणु
		वापस शून्य;
	पूर्ण

	अगर (!pkt_skip_ipv6_extension_headers(pkt, ipv6, proto, is_fragment)) अणु
		वापस शून्य;
	पूर्ण

	वापस ipv6;
पूर्ण

/* Global metrics, per CPU
 */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, अचिन्हित पूर्णांक);
	__type(value, metrics_t);
पूर्ण metrics_map SEC(".maps");

अटल INLINING metrics_t *get_global_metrics(व्योम)
अणु
	uपूर्णांक64_t key = 0;
	वापस bpf_map_lookup_elem(&metrics_map, &key);
पूर्ण

अटल INLINING ret_t accept_locally(काष्ठा __sk_buff *skb, encap_headers_t *encap)
अणु
	स्थिर पूर्णांक payload_off =
		माप(*encap) +
		माप(काष्ठा in_addr) * encap->unigue.hop_count;
	पूर्णांक32_t encap_overhead = payload_off - माप(काष्ठा ethhdr);

	// Changing the ethertype अगर the encapsulated packet is ipv6
	अगर (encap->gue.proto_ctype == IPPROTO_IPV6) अणु
		encap->eth.h_proto = bpf_htons(ETH_P_IPV6);
	पूर्ण

	अगर (bpf_skb_adjust_room(skb, -encap_overhead, BPF_ADJ_ROOM_MAC,
				BPF_F_ADJ_ROOM_FIXED_GSO |
				BPF_F_ADJ_ROOM_NO_CSUM_RESET) ||
	    bpf_csum_level(skb, BPF_CSUM_LEVEL_DEC))
		वापस TC_ACT_SHOT;

	वापस bpf_redirect(skb->अगरindex, BPF_F_INGRESS);
पूर्ण

अटल INLINING ret_t क्रमward_with_gre(काष्ठा __sk_buff *skb, encap_headers_t *encap,
				       काष्ठा in_addr *next_hop, metrics_t *metrics)
अणु
	metrics->क्रमwarded_packets_total_gre++;

	स्थिर पूर्णांक payload_off =
		माप(*encap) +
		माप(काष्ठा in_addr) * encap->unigue.hop_count;
	पूर्णांक32_t encap_overhead =
		payload_off - माप(काष्ठा ethhdr) - माप(काष्ठा iphdr);
	पूर्णांक32_t delta = माप(काष्ठा gre_base_hdr) - encap_overhead;
	uपूर्णांक16_t proto = ETH_P_IP;
	uपूर्णांक32_t mtu_len = 0;

	/* Loop protection: the inner packet's TTL is decremented as a safeguard
	 * against any क्रमwarding loop. As the only पूर्णांकeresting field is the TTL
	 * hop limit क्रम IPv6, it is easier to use bpf_skb_load_bytes/bpf_skb_store_bytes
	 * as they handle the split packets अगर needed (no need क्रम the data to be
	 * in the linear section).
	 */
	अगर (encap->gue.proto_ctype == IPPROTO_IPV6) अणु
		proto = ETH_P_IPV6;
		uपूर्णांक8_t ttl;
		पूर्णांक rc;

		rc = bpf_skb_load_bytes(
			skb, payload_off + दुरत्व(काष्ठा ipv6hdr, hop_limit),
			&ttl, 1);
		अगर (rc != 0) अणु
			metrics->errors_total_malक्रमmed_encapsulation++;
			वापस TC_ACT_SHOT;
		पूर्ण

		अगर (ttl == 0) अणु
			metrics->errors_total_redirect_loop++;
			वापस TC_ACT_SHOT;
		पूर्ण

		ttl--;
		rc = bpf_skb_store_bytes(
			skb, payload_off + दुरत्व(काष्ठा ipv6hdr, hop_limit),
			&ttl, 1, 0);
		अगर (rc != 0) अणु
			metrics->errors_total_malक्रमmed_encapsulation++;
			वापस TC_ACT_SHOT;
		पूर्ण
	पूर्ण अन्यथा अणु
		uपूर्णांक8_t ttl;
		पूर्णांक rc;

		rc = bpf_skb_load_bytes(
			skb, payload_off + दुरत्व(काष्ठा iphdr, ttl), &ttl,
			1);
		अगर (rc != 0) अणु
			metrics->errors_total_malक्रमmed_encapsulation++;
			वापस TC_ACT_SHOT;
		पूर्ण

		अगर (ttl == 0) अणु
			metrics->errors_total_redirect_loop++;
			वापस TC_ACT_SHOT;
		पूर्ण

		/* IPv4 also has a checksum to patch. While the TTL is only one byte,
		 * this function only works क्रम 2 and 4 bytes arguments (the result is
		 * the same).
		 */
		rc = bpf_l3_csum_replace(
			skb, payload_off + दुरत्व(काष्ठा iphdr, check), ttl,
			ttl - 1, 2);
		अगर (rc != 0) अणु
			metrics->errors_total_malक्रमmed_encapsulation++;
			वापस TC_ACT_SHOT;
		पूर्ण

		ttl--;
		rc = bpf_skb_store_bytes(
			skb, payload_off + दुरत्व(काष्ठा iphdr, ttl), &ttl, 1,
			0);
		अगर (rc != 0) अणु
			metrics->errors_total_malक्रमmed_encapsulation++;
			वापस TC_ACT_SHOT;
		पूर्ण
	पूर्ण

	अगर (bpf_check_mtu(skb, skb->अगरindex, &mtu_len, delta, 0)) अणु
		metrics->errors_total_encap_mtu_violate++;
		वापस TC_ACT_SHOT;
	पूर्ण

	अगर (bpf_skb_adjust_room(skb, delta, BPF_ADJ_ROOM_NET,
				BPF_F_ADJ_ROOM_FIXED_GSO |
				BPF_F_ADJ_ROOM_NO_CSUM_RESET) ||
	    bpf_csum_level(skb, BPF_CSUM_LEVEL_INC)) अणु
		metrics->errors_total_encap_adjust_failed++;
		वापस TC_ACT_SHOT;
	पूर्ण

	अगर (bpf_skb_pull_data(skb, माप(encap_gre_t))) अणु
		metrics->errors_total_encap_buffer_too_small++;
		वापस TC_ACT_SHOT;
	पूर्ण

	buf_t pkt = अणु
		.skb = skb,
		.head = (uपूर्णांक8_t *)(दीर्घ)skb->data,
		.tail = (uपूर्णांक8_t *)(दीर्घ)skb->data_end,
	पूर्ण;

	encap_gre_t *encap_gre = buf_assign(&pkt, माप(encap_gre_t), शून्य);
	अगर (encap_gre == शून्य) अणु
		metrics->errors_total_encap_buffer_too_small++;
		वापस TC_ACT_SHOT;
	पूर्ण

	encap_gre->ip.protocol = IPPROTO_GRE;
	encap_gre->ip.daddr = next_hop->s_addr;
	encap_gre->ip.saddr = ENCAPSULATION_IP;
	encap_gre->ip.tot_len =
		bpf_htons(bpf_ntohs(encap_gre->ip.tot_len) + delta);
	encap_gre->gre.flags = 0;
	encap_gre->gre.protocol = bpf_htons(proto);
	pkt_ipv4_checksum((व्योम *)&encap_gre->ip);

	वापस bpf_redirect(skb->अगरindex, 0);
पूर्ण

अटल INLINING ret_t क्रमward_to_next_hop(काष्ठा __sk_buff *skb, encap_headers_t *encap,
					  काष्ठा in_addr *next_hop, metrics_t *metrics)
अणु
	/* swap L2 addresses */
	/* This assumes that packets are received from a router.
	 * So just swapping the MAC addresses here will make the packet go back to
	 * the router, which will send it to the appropriate machine.
	 */
	अचिन्हित अक्षर temp[ETH_ALEN];
	स_नकल(temp, encap->eth.h_dest, माप(temp));
	स_नकल(encap->eth.h_dest, encap->eth.h_source,
	       माप(encap->eth.h_dest));
	स_नकल(encap->eth.h_source, temp, माप(encap->eth.h_source));

	अगर (encap->unigue.next_hop == encap->unigue.hop_count - 1 &&
	    encap->unigue.last_hop_gre) अणु
		वापस क्रमward_with_gre(skb, encap, next_hop, metrics);
	पूर्ण

	metrics->क्रमwarded_packets_total_gue++;
	uपूर्णांक32_t old_saddr = encap->ip.saddr;
	encap->ip.saddr = encap->ip.daddr;
	encap->ip.daddr = next_hop->s_addr;
	अगर (encap->unigue.next_hop < encap->unigue.hop_count) अणु
		encap->unigue.next_hop++;
	पूर्ण

	/* Remove ip->saddr, add next_hop->s_addr */
	स्थिर uपूर्णांक64_t off = दुरत्व(typeof(*encap), ip.check);
	पूर्णांक ret = bpf_l3_csum_replace(skb, off, old_saddr, next_hop->s_addr, 4);
	अगर (ret < 0) अणु
		वापस TC_ACT_SHOT;
	पूर्ण

	वापस bpf_redirect(skb->अगरindex, 0);
पूर्ण

अटल INLINING ret_t skip_next_hops(buf_t *pkt, पूर्णांक n)
अणु
	चयन (n) अणु
	हाल 1:
		अगर (!buf_skip(pkt, माप(काष्ठा in_addr)))
			वापस TC_ACT_SHOT;
	हाल 0:
		वापस CONTINUE_PROCESSING;

	शेष:
		वापस TC_ACT_SHOT;
	पूर्ण
पूर्ण

/* Get the next hop from the GLB header.
 *
 * Sets next_hop->s_addr to 0 अगर there are no more hops left.
 * pkt is positioned just after the variable length GLB header
 * अगरf the call is successful.
 */
अटल INLINING ret_t get_next_hop(buf_t *pkt, encap_headers_t *encap,
				   काष्ठा in_addr *next_hop)
अणु
	अगर (encap->unigue.next_hop > encap->unigue.hop_count) अणु
		वापस TC_ACT_SHOT;
	पूर्ण

	/* Skip "used" next hops. */
	MAYBE_RETURN(skip_next_hops(pkt, encap->unigue.next_hop));

	अगर (encap->unigue.next_hop == encap->unigue.hop_count) अणु
		/* No more next hops, we are at the end of the GLB header. */
		next_hop->s_addr = 0;
		वापस CONTINUE_PROCESSING;
	पूर्ण

	अगर (!buf_copy(pkt, next_hop, माप(*next_hop))) अणु
		वापस TC_ACT_SHOT;
	पूर्ण

	/* Skip the reमुख्यig next hops (may be zero). */
	वापस skip_next_hops(pkt, encap->unigue.hop_count -
					   encap->unigue.next_hop - 1);
पूर्ण

/* Fill a bpf_sock_tuple to be used with the socket lookup functions.
 * This is a kludge that let's us work around verअगरier limitations:
 *
 *    fill_tuple(&t, foo, माप(काष्ठा iphdr), 123, 321)
 *
 * clang will substitue a costant क्रम माप, which allows the verअगरier
 * to track it's value. Based on this, it can figure out the स्थिरant
 * वापस value, and calling code works जबतक still being "generic" to
 * IPv4 and IPv6.
 */
अटल INLINING uपूर्णांक64_t fill_tuple(काष्ठा bpf_sock_tuple *tuple, व्योम *iph,
				    uपूर्णांक64_t iphlen, uपूर्णांक16_t sport, uपूर्णांक16_t dport)
अणु
	चयन (iphlen) अणु
	हाल माप(काष्ठा iphdr): अणु
		काष्ठा iphdr *ipv4 = (काष्ठा iphdr *)iph;
		tuple->ipv4.daddr = ipv4->daddr;
		tuple->ipv4.saddr = ipv4->saddr;
		tuple->ipv4.sport = sport;
		tuple->ipv4.dport = dport;
		वापस माप(tuple->ipv4);
	पूर्ण

	हाल माप(काष्ठा ipv6hdr): अणु
		काष्ठा ipv6hdr *ipv6 = (काष्ठा ipv6hdr *)iph;
		स_नकल(&tuple->ipv6.daddr, &ipv6->daddr,
		       माप(tuple->ipv6.daddr));
		स_नकल(&tuple->ipv6.saddr, &ipv6->saddr,
		       माप(tuple->ipv6.saddr));
		tuple->ipv6.sport = sport;
		tuple->ipv6.dport = dport;
		वापस माप(tuple->ipv6);
	पूर्ण

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल INLINING verdict_t classअगरy_tcp(काष्ठा __sk_buff *skb,
				       काष्ठा bpf_sock_tuple *tuple, uपूर्णांक64_t tuplen,
				       व्योम *iph, काष्ठा tcphdr *tcp)
अणु
	काष्ठा bpf_sock *sk =
		bpf_skc_lookup_tcp(skb, tuple, tuplen, BPF_F_CURRENT_NETNS, 0);
	अगर (sk == शून्य) अणु
		वापस UNKNOWN;
	पूर्ण

	अगर (sk->state != BPF_TCP_LISTEN) अणु
		bpf_sk_release(sk);
		वापस ESTABLISHED;
	पूर्ण

	अगर (iph != शून्य && tcp != शून्य) अणु
		/* Kludge: we've run out of arguments, but need the length of the ip header. */
		uपूर्णांक64_t iphlen = माप(काष्ठा iphdr);
		अगर (tuplen == माप(tuple->ipv6)) अणु
			iphlen = माप(काष्ठा ipv6hdr);
		पूर्ण

		अगर (bpf_tcp_check_syncookie(sk, iph, iphlen, tcp,
					    माप(*tcp)) == 0) अणु
			bpf_sk_release(sk);
			वापस SYN_COOKIE;
		पूर्ण
	पूर्ण

	bpf_sk_release(sk);
	वापस UNKNOWN;
पूर्ण

अटल INLINING verdict_t classअगरy_udp(काष्ठा __sk_buff *skb,
				       काष्ठा bpf_sock_tuple *tuple, uपूर्णांक64_t tuplen)
अणु
	काष्ठा bpf_sock *sk =
		bpf_sk_lookup_udp(skb, tuple, tuplen, BPF_F_CURRENT_NETNS, 0);
	अगर (sk == शून्य) अणु
		वापस UNKNOWN;
	पूर्ण

	अगर (sk->state == BPF_TCP_ESTABLISHED) अणु
		bpf_sk_release(sk);
		वापस ESTABLISHED;
	पूर्ण

	bpf_sk_release(sk);
	वापस UNKNOWN;
पूर्ण

अटल INLINING verdict_t classअगरy_icmp(काष्ठा __sk_buff *skb, uपूर्णांक8_t proto,
					काष्ठा bpf_sock_tuple *tuple, uपूर्णांक64_t tuplen,
					metrics_t *metrics)
अणु
	चयन (proto) अणु
	हाल IPPROTO_TCP:
		वापस classअगरy_tcp(skb, tuple, tuplen, शून्य, शून्य);

	हाल IPPROTO_UDP:
		वापस classअगरy_udp(skb, tuple, tuplen);

	शेष:
		metrics->errors_total_malक्रमmed_icmp++;
		वापस INVALID;
	पूर्ण
पूर्ण

अटल INLINING verdict_t process_icmpv4(buf_t *pkt, metrics_t *metrics)
अणु
	काष्ठा icmphdr icmp;
	अगर (!buf_copy(pkt, &icmp, माप(icmp))) अणु
		metrics->errors_total_malक्रमmed_icmp++;
		वापस INVALID;
	पूर्ण

	/* We should never receive encapsulated echo replies. */
	अगर (icmp.type == ICMP_ECHOREPLY) अणु
		metrics->errors_total_icmp_echo_replies++;
		वापस INVALID;
	पूर्ण

	अगर (icmp.type == ICMP_ECHO) अणु
		वापस ECHO_REQUEST;
	पूर्ण

	अगर (icmp.type != ICMP_DEST_UNREACH || icmp.code != ICMP_FRAG_NEEDED) अणु
		metrics->errors_total_unwanted_icmp++;
		वापस INVALID;
	पूर्ण

	काष्ठा iphdr _ip4;
	स्थिर काष्ठा iphdr *ipv4 = pkt_parse_ipv4(pkt, &_ip4);
	अगर (ipv4 == शून्य) अणु
		metrics->errors_total_malक्रमmed_icmp_pkt_too_big++;
		वापस INVALID;
	पूर्ण

	/* The source address in the outer IP header is from the entity that
	 * originated the ICMP message. Use the original IP header to restore
	 * the correct flow tuple.
	 */
	काष्ठा bpf_sock_tuple tuple;
	tuple.ipv4.saddr = ipv4->daddr;
	tuple.ipv4.daddr = ipv4->saddr;

	अगर (!pkt_parse_icmp_l4_ports(pkt, (flow_ports_t *)&tuple.ipv4.sport)) अणु
		metrics->errors_total_malक्रमmed_icmp_pkt_too_big++;
		वापस INVALID;
	पूर्ण

	वापस classअगरy_icmp(pkt->skb, ipv4->protocol, &tuple,
			     माप(tuple.ipv4), metrics);
पूर्ण

अटल INLINING verdict_t process_icmpv6(buf_t *pkt, metrics_t *metrics)
अणु
	काष्ठा icmp6hdr icmp6;
	अगर (!buf_copy(pkt, &icmp6, माप(icmp6))) अणु
		metrics->errors_total_malक्रमmed_icmp++;
		वापस INVALID;
	पूर्ण

	/* We should never receive encapsulated echo replies. */
	अगर (icmp6.icmp6_type == ICMPV6_ECHO_REPLY) अणु
		metrics->errors_total_icmp_echo_replies++;
		वापस INVALID;
	पूर्ण

	अगर (icmp6.icmp6_type == ICMPV6_ECHO_REQUEST) अणु
		वापस ECHO_REQUEST;
	पूर्ण

	अगर (icmp6.icmp6_type != ICMPV6_PKT_TOOBIG) अणु
		metrics->errors_total_unwanted_icmp++;
		वापस INVALID;
	पूर्ण

	bool is_fragment;
	uपूर्णांक8_t l4_proto;
	काष्ठा ipv6hdr _ipv6;
	स्थिर काष्ठा ipv6hdr *ipv6 =
		pkt_parse_ipv6(pkt, &_ipv6, &l4_proto, &is_fragment);
	अगर (ipv6 == शून्य) अणु
		metrics->errors_total_malक्रमmed_icmp_pkt_too_big++;
		वापस INVALID;
	पूर्ण

	अगर (is_fragment) अणु
		metrics->errors_total_fragmented_ip++;
		वापस INVALID;
	पूर्ण

	/* Swap source and dest addresses. */
	काष्ठा bpf_sock_tuple tuple;
	स_नकल(&tuple.ipv6.saddr, &ipv6->daddr, माप(tuple.ipv6.saddr));
	स_नकल(&tuple.ipv6.daddr, &ipv6->saddr, माप(tuple.ipv6.daddr));

	अगर (!pkt_parse_icmp_l4_ports(pkt, (flow_ports_t *)&tuple.ipv6.sport)) अणु
		metrics->errors_total_malक्रमmed_icmp_pkt_too_big++;
		वापस INVALID;
	पूर्ण

	वापस classअगरy_icmp(pkt->skb, l4_proto, &tuple, माप(tuple.ipv6),
			     metrics);
पूर्ण

अटल INLINING verdict_t process_tcp(buf_t *pkt, व्योम *iph, uपूर्णांक64_t iphlen,
				      metrics_t *metrics)
अणु
	metrics->l4_protocol_packets_total_tcp++;

	काष्ठा tcphdr _tcp;
	काष्ठा tcphdr *tcp = buf_assign(pkt, माप(_tcp), &_tcp);
	अगर (tcp == शून्य) अणु
		metrics->errors_total_malक्रमmed_tcp++;
		वापस INVALID;
	पूर्ण

	अगर (tcp->syn) अणु
		वापस SYN;
	पूर्ण

	काष्ठा bpf_sock_tuple tuple;
	uपूर्णांक64_t tuplen =
		fill_tuple(&tuple, iph, iphlen, tcp->source, tcp->dest);
	वापस classअगरy_tcp(pkt->skb, &tuple, tuplen, iph, tcp);
पूर्ण

अटल INLINING verdict_t process_udp(buf_t *pkt, व्योम *iph, uपूर्णांक64_t iphlen,
				      metrics_t *metrics)
अणु
	metrics->l4_protocol_packets_total_udp++;

	काष्ठा udphdr _udp;
	काष्ठा udphdr *udph = buf_assign(pkt, माप(_udp), &_udp);
	अगर (udph == शून्य) अणु
		metrics->errors_total_malक्रमmed_udp++;
		वापस INVALID;
	पूर्ण

	काष्ठा bpf_sock_tuple tuple;
	uपूर्णांक64_t tuplen =
		fill_tuple(&tuple, iph, iphlen, udph->source, udph->dest);
	वापस classअगरy_udp(pkt->skb, &tuple, tuplen);
पूर्ण

अटल INLINING verdict_t process_ipv4(buf_t *pkt, metrics_t *metrics)
अणु
	metrics->l3_protocol_packets_total_ipv4++;

	काष्ठा iphdr _ip4;
	काष्ठा iphdr *ipv4 = pkt_parse_ipv4(pkt, &_ip4);
	अगर (ipv4 == शून्य) अणु
		metrics->errors_total_malक्रमmed_ip++;
		वापस INVALID;
	पूर्ण

	अगर (ipv4->version != 4) अणु
		metrics->errors_total_malक्रमmed_ip++;
		वापस INVALID;
	पूर्ण

	अगर (ipv4_is_fragment(ipv4)) अणु
		metrics->errors_total_fragmented_ip++;
		वापस INVALID;
	पूर्ण

	चयन (ipv4->protocol) अणु
	हाल IPPROTO_ICMP:
		वापस process_icmpv4(pkt, metrics);

	हाल IPPROTO_TCP:
		वापस process_tcp(pkt, ipv4, माप(*ipv4), metrics);

	हाल IPPROTO_UDP:
		वापस process_udp(pkt, ipv4, माप(*ipv4), metrics);

	शेष:
		metrics->errors_total_unknown_l4_proto++;
		वापस INVALID;
	पूर्ण
पूर्ण

अटल INLINING verdict_t process_ipv6(buf_t *pkt, metrics_t *metrics)
अणु
	metrics->l3_protocol_packets_total_ipv6++;

	uपूर्णांक8_t l4_proto;
	bool is_fragment;
	काष्ठा ipv6hdr _ipv6;
	काष्ठा ipv6hdr *ipv6 =
		pkt_parse_ipv6(pkt, &_ipv6, &l4_proto, &is_fragment);
	अगर (ipv6 == शून्य) अणु
		metrics->errors_total_malक्रमmed_ip++;
		वापस INVALID;
	पूर्ण

	अगर (ipv6->version != 6) अणु
		metrics->errors_total_malक्रमmed_ip++;
		वापस INVALID;
	पूर्ण

	अगर (is_fragment) अणु
		metrics->errors_total_fragmented_ip++;
		वापस INVALID;
	पूर्ण

	चयन (l4_proto) अणु
	हाल IPPROTO_ICMPV6:
		वापस process_icmpv6(pkt, metrics);

	हाल IPPROTO_TCP:
		वापस process_tcp(pkt, ipv6, माप(*ipv6), metrics);

	हाल IPPROTO_UDP:
		वापस process_udp(pkt, ipv6, माप(*ipv6), metrics);

	शेष:
		metrics->errors_total_unknown_l4_proto++;
		वापस INVALID;
	पूर्ण
पूर्ण

SEC("classifier/cls_redirect")
पूर्णांक cls_redirect(काष्ठा __sk_buff *skb)
अणु
	metrics_t *metrics = get_global_metrics();
	अगर (metrics == शून्य) अणु
		वापस TC_ACT_SHOT;
	पूर्ण

	metrics->processed_packets_total++;

	/* Pass bogus packets as दीर्घ as we're not sure they're
	 * destined क्रम us.
	 */
	अगर (skb->protocol != bpf_htons(ETH_P_IP)) अणु
		वापस TC_ACT_OK;
	पूर्ण

	encap_headers_t *encap;

	/* Make sure that all encapsulation headers are available in
	 * the linear portion of the skb. This makes it easy to manipulate them.
	 */
	अगर (bpf_skb_pull_data(skb, माप(*encap))) अणु
		वापस TC_ACT_OK;
	पूर्ण

	buf_t pkt = अणु
		.skb = skb,
		.head = (uपूर्णांक8_t *)(दीर्घ)skb->data,
		.tail = (uपूर्णांक8_t *)(दीर्घ)skb->data_end,
	पूर्ण;

	encap = buf_assign(&pkt, माप(*encap), शून्य);
	अगर (encap == शून्य) अणु
		वापस TC_ACT_OK;
	पूर्ण

	अगर (encap->ip.ihl != 5) अणु
		/* We never have any options. */
		वापस TC_ACT_OK;
	पूर्ण

	अगर (encap->ip.daddr != ENCAPSULATION_IP ||
	    encap->ip.protocol != IPPROTO_UDP) अणु
		वापस TC_ACT_OK;
	पूर्ण

	/* TODO Check UDP length? */
	अगर (encap->udp.dest != ENCAPSULATION_PORT) अणु
		वापस TC_ACT_OK;
	पूर्ण

	/* We now know that the packet is destined to us, we can
	 * drop bogus ones.
	 */
	अगर (ipv4_is_fragment((व्योम *)&encap->ip)) अणु
		metrics->errors_total_fragmented_ip++;
		वापस TC_ACT_SHOT;
	पूर्ण

	अगर (encap->gue.variant != 0) अणु
		metrics->errors_total_malक्रमmed_encapsulation++;
		वापस TC_ACT_SHOT;
	पूर्ण

	अगर (encap->gue.control != 0) अणु
		metrics->errors_total_malक्रमmed_encapsulation++;
		वापस TC_ACT_SHOT;
	पूर्ण

	अगर (encap->gue.flags != 0) अणु
		metrics->errors_total_malक्रमmed_encapsulation++;
		वापस TC_ACT_SHOT;
	पूर्ण

	अगर (encap->gue.hlen !=
	    माप(encap->unigue) / 4 + encap->unigue.hop_count) अणु
		metrics->errors_total_malक्रमmed_encapsulation++;
		वापस TC_ACT_SHOT;
	पूर्ण

	अगर (encap->unigue.version != 0) अणु
		metrics->errors_total_malक्रमmed_encapsulation++;
		वापस TC_ACT_SHOT;
	पूर्ण

	अगर (encap->unigue.reserved != 0) अणु
		वापस TC_ACT_SHOT;
	पूर्ण

	काष्ठा in_addr next_hop;
	MAYBE_RETURN(get_next_hop(&pkt, encap, &next_hop));

	अगर (next_hop.s_addr == 0) अणु
		metrics->accepted_packets_total_last_hop++;
		वापस accept_locally(skb, encap);
	पूर्ण

	verdict_t verdict;
	चयन (encap->gue.proto_ctype) अणु
	हाल IPPROTO_IPIP:
		verdict = process_ipv4(&pkt, metrics);
		अवरोध;

	हाल IPPROTO_IPV6:
		verdict = process_ipv6(&pkt, metrics);
		अवरोध;

	शेष:
		metrics->errors_total_unknown_l3_proto++;
		वापस TC_ACT_SHOT;
	पूर्ण

	चयन (verdict) अणु
	हाल INVALID:
		/* metrics have alपढ़ोy been bumped */
		वापस TC_ACT_SHOT;

	हाल UNKNOWN:
		वापस क्रमward_to_next_hop(skb, encap, &next_hop, metrics);

	हाल ECHO_REQUEST:
		metrics->accepted_packets_total_icmp_echo_request++;
		अवरोध;

	हाल SYN:
		अगर (encap->unigue.क्रमward_syn) अणु
			वापस क्रमward_to_next_hop(skb, encap, &next_hop,
						   metrics);
		पूर्ण

		metrics->accepted_packets_total_syn++;
		अवरोध;

	हाल SYN_COOKIE:
		metrics->accepted_packets_total_syn_cookies++;
		अवरोध;

	हाल ESTABLISHED:
		metrics->accepted_packets_total_established++;
		अवरोध;
	पूर्ण

	वापस accept_locally(skb, encap);
पूर्ण
