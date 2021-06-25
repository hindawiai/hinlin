<शैली गुरु>
/*  XDP redirect to CPUs via cpumap (BPF_MAP_TYPE_CPUMAP)
 *
 *  GPLv2, Copyright(c) 2017 Jesper Dangaard Brouer, Red Hat, Inc.
 */
#समावेश <uapi/linux/अगर_ether.h>
#समावेश <uapi/linux/अगर_packet.h>
#समावेश <uapi/linux/अगर_vlan.h>
#समावेश <uapi/linux/ip.h>
#समावेश <uapi/linux/ipv6.h>
#समावेश <uapi/linux/in.h>
#समावेश <uapi/linux/tcp.h>
#समावेश <uapi/linux/udp.h>

#समावेश <uapi/linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश "hash_func01.h"

#घोषणा MAX_CPUS NR_CPUS

/* Special map type that can XDP_REसूचीECT frames to another CPU */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_CPUMAP);
	__uपूर्णांक(key_size, माप(u32));
	__uपूर्णांक(value_size, माप(काष्ठा bpf_cpumap_val));
	__uपूर्णांक(max_entries, MAX_CPUS);
पूर्ण cpu_map SEC(".maps");

/* Common stats data record to keep userspace more simple */
काष्ठा datarec अणु
	__u64 processed;
	__u64 dropped;
	__u64 issue;
	__u64 xdp_pass;
	__u64 xdp_drop;
	__u64 xdp_redirect;
पूर्ण;

/* Count RX packets, as XDP bpf_prog करोesn't get direct TX-success
 * feedback.  Redirect TX errors can be caught via a tracepoपूर्णांक.
 */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__type(key, u32);
	__type(value, काष्ठा datarec);
	__uपूर्णांक(max_entries, 1);
पूर्ण rx_cnt SEC(".maps");

/* Used by trace poपूर्णांक */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__type(key, u32);
	__type(value, काष्ठा datarec);
	__uपूर्णांक(max_entries, 2);
	/* TODO: have entries क्रम all possible त्रुटि_सं's */
पूर्ण redirect_err_cnt SEC(".maps");

/* Used by trace poपूर्णांक */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__type(key, u32);
	__type(value, काष्ठा datarec);
	__uपूर्णांक(max_entries, MAX_CPUS);
पूर्ण cpumap_enqueue_cnt SEC(".maps");

/* Used by trace poपूर्णांक */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__type(key, u32);
	__type(value, काष्ठा datarec);
	__uपूर्णांक(max_entries, 1);
पूर्ण cpumap_kthपढ़ो_cnt SEC(".maps");

/* Set of maps controlling available CPU, and क्रम iterating through
 * selectable redirect CPUs.
 */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, u32);
	__type(value, u32);
	__uपूर्णांक(max_entries, MAX_CPUS);
पूर्ण cpus_available SEC(".maps");
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, u32);
	__type(value, u32);
	__uपूर्णांक(max_entries, 1);
पूर्ण cpus_count SEC(".maps");
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__type(key, u32);
	__type(value, u32);
	__uपूर्णांक(max_entries, 1);
पूर्ण cpus_iterator SEC(".maps");

/* Used by trace poपूर्णांक */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__type(key, u32);
	__type(value, काष्ठा datarec);
	__uपूर्णांक(max_entries, 1);
पूर्ण exception_cnt SEC(".maps");

/* Helper parse functions */

/* Parse Ethernet layer 2, extract network layer 3 offset and protocol
 *
 * Returns false on error and non-supported ether-type
 */
काष्ठा vlan_hdr अणु
	__be16 h_vlan_TCI;
	__be16 h_vlan_encapsulated_proto;
पूर्ण;

अटल __always_अंतरभूत
bool parse_eth(काष्ठा ethhdr *eth, व्योम *data_end,
	       u16 *eth_proto, u64 *l3_offset)
अणु
	u16 eth_type;
	u64 offset;

	offset = माप(*eth);
	अगर ((व्योम *)eth + offset > data_end)
		वापस false;

	eth_type = eth->h_proto;

	/* Skip non 802.3 Ethertypes */
	अगर (unlikely(ntohs(eth_type) < ETH_P_802_3_MIN))
		वापस false;

	/* Handle VLAN tagged packet */
	अगर (eth_type == htons(ETH_P_8021Q) || eth_type == htons(ETH_P_8021AD)) अणु
		काष्ठा vlan_hdr *vlan_hdr;

		vlan_hdr = (व्योम *)eth + offset;
		offset += माप(*vlan_hdr);
		अगर ((व्योम *)eth + offset > data_end)
			वापस false;
		eth_type = vlan_hdr->h_vlan_encapsulated_proto;
	पूर्ण
	/* Handle द्विगुन VLAN tagged packet */
	अगर (eth_type == htons(ETH_P_8021Q) || eth_type == htons(ETH_P_8021AD)) अणु
		काष्ठा vlan_hdr *vlan_hdr;

		vlan_hdr = (व्योम *)eth + offset;
		offset += माप(*vlan_hdr);
		अगर ((व्योम *)eth + offset > data_end)
			वापस false;
		eth_type = vlan_hdr->h_vlan_encapsulated_proto;
	पूर्ण

	*eth_proto = ntohs(eth_type);
	*l3_offset = offset;
	वापस true;
पूर्ण

अटल __always_अंतरभूत
u16 get_dest_port_ipv4_udp(काष्ठा xdp_md *ctx, u64 nh_off)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data     = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा iphdr *iph = data + nh_off;
	काष्ठा udphdr *udph;
	u16 dport;

	अगर (iph + 1 > data_end)
		वापस 0;
	अगर (!(iph->protocol == IPPROTO_UDP))
		वापस 0;

	udph = (व्योम *)(iph + 1);
	अगर (udph + 1 > data_end)
		वापस 0;

	dport = ntohs(udph->dest);
	वापस dport;
पूर्ण

अटल __always_अंतरभूत
पूर्णांक get_proto_ipv4(काष्ठा xdp_md *ctx, u64 nh_off)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data     = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा iphdr *iph = data + nh_off;

	अगर (iph + 1 > data_end)
		वापस 0;
	वापस iph->protocol;
पूर्ण

अटल __always_अंतरभूत
पूर्णांक get_proto_ipv6(काष्ठा xdp_md *ctx, u64 nh_off)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data     = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा ipv6hdr *ip6h = data + nh_off;

	अगर (ip6h + 1 > data_end)
		वापस 0;
	वापस ip6h->nexthdr;
पूर्ण

SEC("xdp_cpu_map0")
पूर्णांक  xdp_prognum0_no_touch(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data     = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा datarec *rec;
	u32 *cpu_selected;
	u32 cpu_dest;
	u32 key = 0;

	/* Only use first entry in cpus_available */
	cpu_selected = bpf_map_lookup_elem(&cpus_available, &key);
	अगर (!cpu_selected)
		वापस XDP_ABORTED;
	cpu_dest = *cpu_selected;

	/* Count RX packet in map */
	rec = bpf_map_lookup_elem(&rx_cnt, &key);
	अगर (!rec)
		वापस XDP_ABORTED;
	rec->processed++;

	अगर (cpu_dest >= MAX_CPUS) अणु
		rec->issue++;
		वापस XDP_ABORTED;
	पूर्ण

	वापस bpf_redirect_map(&cpu_map, cpu_dest, 0);
पूर्ण

SEC("xdp_cpu_map1_touch_data")
पूर्णांक  xdp_prognum1_touch_data(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data     = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा ethhdr *eth = data;
	काष्ठा datarec *rec;
	u32 *cpu_selected;
	u32 cpu_dest;
	u16 eth_type;
	u32 key = 0;

	/* Only use first entry in cpus_available */
	cpu_selected = bpf_map_lookup_elem(&cpus_available, &key);
	अगर (!cpu_selected)
		वापस XDP_ABORTED;
	cpu_dest = *cpu_selected;

	/* Validate packet length is minimum Eth header size */
	अगर (eth + 1 > data_end)
		वापस XDP_ABORTED;

	/* Count RX packet in map */
	rec = bpf_map_lookup_elem(&rx_cnt, &key);
	अगर (!rec)
		वापस XDP_ABORTED;
	rec->processed++;

	/* Read packet data, and use it (drop non 802.3 Ethertypes) */
	eth_type = eth->h_proto;
	अगर (ntohs(eth_type) < ETH_P_802_3_MIN) अणु
		rec->dropped++;
		वापस XDP_DROP;
	पूर्ण

	अगर (cpu_dest >= MAX_CPUS) अणु
		rec->issue++;
		वापस XDP_ABORTED;
	पूर्ण

	वापस bpf_redirect_map(&cpu_map, cpu_dest, 0);
पूर्ण

SEC("xdp_cpu_map2_round_robin")
पूर्णांक  xdp_prognum2_round_robin(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data     = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा ethhdr *eth = data;
	काष्ठा datarec *rec;
	u32 cpu_dest;
	u32 *cpu_lookup;
	u32 key0 = 0;

	u32 *cpu_selected;
	u32 *cpu_iterator;
	u32 *cpu_max;
	u32 cpu_idx;

	cpu_max = bpf_map_lookup_elem(&cpus_count, &key0);
	अगर (!cpu_max)
		वापस XDP_ABORTED;

	cpu_iterator = bpf_map_lookup_elem(&cpus_iterator, &key0);
	अगर (!cpu_iterator)
		वापस XDP_ABORTED;
	cpu_idx = *cpu_iterator;

	*cpu_iterator += 1;
	अगर (*cpu_iterator == *cpu_max)
		*cpu_iterator = 0;

	cpu_selected = bpf_map_lookup_elem(&cpus_available, &cpu_idx);
	अगर (!cpu_selected)
		वापस XDP_ABORTED;
	cpu_dest = *cpu_selected;

	/* Count RX packet in map */
	rec = bpf_map_lookup_elem(&rx_cnt, &key0);
	अगर (!rec)
		वापस XDP_ABORTED;
	rec->processed++;

	अगर (cpu_dest >= MAX_CPUS) अणु
		rec->issue++;
		वापस XDP_ABORTED;
	पूर्ण

	वापस bpf_redirect_map(&cpu_map, cpu_dest, 0);
पूर्ण

SEC("xdp_cpu_map3_proto_separate")
पूर्णांक  xdp_prognum3_proto_separate(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data     = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा ethhdr *eth = data;
	u8 ip_proto = IPPROTO_UDP;
	काष्ठा datarec *rec;
	u16 eth_proto = 0;
	u64 l3_offset = 0;
	u32 cpu_dest = 0;
	u32 cpu_idx = 0;
	u32 *cpu_lookup;
	u32 key = 0;

	/* Count RX packet in map */
	rec = bpf_map_lookup_elem(&rx_cnt, &key);
	अगर (!rec)
		वापस XDP_ABORTED;
	rec->processed++;

	अगर (!(parse_eth(eth, data_end, &eth_proto, &l3_offset)))
		वापस XDP_PASS; /* Just skip */

	/* Extract L4 protocol */
	चयन (eth_proto) अणु
	हाल ETH_P_IP:
		ip_proto = get_proto_ipv4(ctx, l3_offset);
		अवरोध;
	हाल ETH_P_IPV6:
		ip_proto = get_proto_ipv6(ctx, l3_offset);
		अवरोध;
	हाल ETH_P_ARP:
		cpu_idx = 0; /* ARP packet handled on separate CPU */
		अवरोध;
	शेष:
		cpu_idx = 0;
	पूर्ण

	/* Choose CPU based on L4 protocol */
	चयन (ip_proto) अणु
	हाल IPPROTO_ICMP:
	हाल IPPROTO_ICMPV6:
		cpu_idx = 2;
		अवरोध;
	हाल IPPROTO_TCP:
		cpu_idx = 0;
		अवरोध;
	हाल IPPROTO_UDP:
		cpu_idx = 1;
		अवरोध;
	शेष:
		cpu_idx = 0;
	पूर्ण

	cpu_lookup = bpf_map_lookup_elem(&cpus_available, &cpu_idx);
	अगर (!cpu_lookup)
		वापस XDP_ABORTED;
	cpu_dest = *cpu_lookup;

	अगर (cpu_dest >= MAX_CPUS) अणु
		rec->issue++;
		वापस XDP_ABORTED;
	पूर्ण

	वापस bpf_redirect_map(&cpu_map, cpu_dest, 0);
पूर्ण

SEC("xdp_cpu_map4_ddos_filter_pktgen")
पूर्णांक  xdp_prognum4_dकरोs_filter_pktgen(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data     = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा ethhdr *eth = data;
	u8 ip_proto = IPPROTO_UDP;
	काष्ठा datarec *rec;
	u16 eth_proto = 0;
	u64 l3_offset = 0;
	u32 cpu_dest = 0;
	u32 cpu_idx = 0;
	u16 dest_port;
	u32 *cpu_lookup;
	u32 key = 0;

	/* Count RX packet in map */
	rec = bpf_map_lookup_elem(&rx_cnt, &key);
	अगर (!rec)
		वापस XDP_ABORTED;
	rec->processed++;

	अगर (!(parse_eth(eth, data_end, &eth_proto, &l3_offset)))
		वापस XDP_PASS; /* Just skip */

	/* Extract L4 protocol */
	चयन (eth_proto) अणु
	हाल ETH_P_IP:
		ip_proto = get_proto_ipv4(ctx, l3_offset);
		अवरोध;
	हाल ETH_P_IPV6:
		ip_proto = get_proto_ipv6(ctx, l3_offset);
		अवरोध;
	हाल ETH_P_ARP:
		cpu_idx = 0; /* ARP packet handled on separate CPU */
		अवरोध;
	शेष:
		cpu_idx = 0;
	पूर्ण

	/* Choose CPU based on L4 protocol */
	चयन (ip_proto) अणु
	हाल IPPROTO_ICMP:
	हाल IPPROTO_ICMPV6:
		cpu_idx = 2;
		अवरोध;
	हाल IPPROTO_TCP:
		cpu_idx = 0;
		अवरोध;
	हाल IPPROTO_UDP:
		cpu_idx = 1;
		/* DDoS filter UDP port 9 (pktgen) */
		dest_port = get_dest_port_ipv4_udp(ctx, l3_offset);
		अगर (dest_port == 9) अणु
			अगर (rec)
				rec->dropped++;
			वापस XDP_DROP;
		पूर्ण
		अवरोध;
	शेष:
		cpu_idx = 0;
	पूर्ण

	cpu_lookup = bpf_map_lookup_elem(&cpus_available, &cpu_idx);
	अगर (!cpu_lookup)
		वापस XDP_ABORTED;
	cpu_dest = *cpu_lookup;

	अगर (cpu_dest >= MAX_CPUS) अणु
		rec->issue++;
		वापस XDP_ABORTED;
	पूर्ण

	वापस bpf_redirect_map(&cpu_map, cpu_dest, 0);
पूर्ण

/* Hashing initval */
#घोषणा INITVAL 15485863

अटल __always_अंतरभूत
u32 get_ipv4_hash_ip_pair(काष्ठा xdp_md *ctx, u64 nh_off)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data     = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा iphdr *iph = data + nh_off;
	u32 cpu_hash;

	अगर (iph + 1 > data_end)
		वापस 0;

	cpu_hash = iph->saddr + iph->daddr;
	cpu_hash = SuperFastHash((अक्षर *)&cpu_hash, 4, INITVAL + iph->protocol);

	वापस cpu_hash;
पूर्ण

अटल __always_अंतरभूत
u32 get_ipv6_hash_ip_pair(काष्ठा xdp_md *ctx, u64 nh_off)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data     = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा ipv6hdr *ip6h = data + nh_off;
	u32 cpu_hash;

	अगर (ip6h + 1 > data_end)
		वापस 0;

	cpu_hash  = ip6h->saddr.s6_addr32[0] + ip6h->daddr.s6_addr32[0];
	cpu_hash += ip6h->saddr.s6_addr32[1] + ip6h->daddr.s6_addr32[1];
	cpu_hash += ip6h->saddr.s6_addr32[2] + ip6h->daddr.s6_addr32[2];
	cpu_hash += ip6h->saddr.s6_addr32[3] + ip6h->daddr.s6_addr32[3];
	cpu_hash = SuperFastHash((अक्षर *)&cpu_hash, 4, INITVAL + ip6h->nexthdr);

	वापस cpu_hash;
पूर्ण

/* Load-Balance traffic based on hashing IP-addrs + L4-proto.  The
 * hashing scheme is symmetric, meaning swapping IP src/dest still hit
 * same CPU.
 */
SEC("xdp_cpu_map5_lb_hash_ip_pairs")
पूर्णांक  xdp_prognum5_lb_hash_ip_pairs(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data     = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा ethhdr *eth = data;
	u8 ip_proto = IPPROTO_UDP;
	काष्ठा datarec *rec;
	u16 eth_proto = 0;
	u64 l3_offset = 0;
	u32 cpu_dest = 0;
	u32 cpu_idx = 0;
	u32 *cpu_lookup;
	u32 *cpu_max;
	u32 cpu_hash;
	u32 key = 0;

	/* Count RX packet in map */
	rec = bpf_map_lookup_elem(&rx_cnt, &key);
	अगर (!rec)
		वापस XDP_ABORTED;
	rec->processed++;

	cpu_max = bpf_map_lookup_elem(&cpus_count, &key);
	अगर (!cpu_max)
		वापस XDP_ABORTED;

	अगर (!(parse_eth(eth, data_end, &eth_proto, &l3_offset)))
		वापस XDP_PASS; /* Just skip */

	/* Hash क्रम IPv4 and IPv6 */
	चयन (eth_proto) अणु
	हाल ETH_P_IP:
		cpu_hash = get_ipv4_hash_ip_pair(ctx, l3_offset);
		अवरोध;
	हाल ETH_P_IPV6:
		cpu_hash = get_ipv6_hash_ip_pair(ctx, l3_offset);
		अवरोध;
	हाल ETH_P_ARP: /* ARP packet handled on CPU idx 0 */
	शेष:
		cpu_hash = 0;
	पूर्ण

	/* Choose CPU based on hash */
	cpu_idx = cpu_hash % *cpu_max;

	cpu_lookup = bpf_map_lookup_elem(&cpus_available, &cpu_idx);
	अगर (!cpu_lookup)
		वापस XDP_ABORTED;
	cpu_dest = *cpu_lookup;

	अगर (cpu_dest >= MAX_CPUS) अणु
		rec->issue++;
		वापस XDP_ABORTED;
	पूर्ण

	वापस bpf_redirect_map(&cpu_map, cpu_dest, 0);
पूर्ण

अक्षर _license[] SEC("license") = "GPL";

/*** Trace poपूर्णांक code ***/

/* Tracepoपूर्णांक क्रमmat: /sys/kernel/debug/tracing/events/xdp/xdp_redirect/क्रमmat
 * Code in:                kernel/include/trace/events/xdp.h
 */
काष्ठा xdp_redirect_ctx अणु
	u64 __pad;	// First 8 bytes are not accessible by bpf code
	पूर्णांक prog_id;	//	offset:8;  size:4; चिन्हित:1;
	u32 act;	//	offset:12  size:4; चिन्हित:0;
	पूर्णांक अगरindex;	//	offset:16  size:4; चिन्हित:1;
	पूर्णांक err;	//	offset:20  size:4; चिन्हित:1;
	पूर्णांक to_अगरindex;	//	offset:24  size:4; चिन्हित:1;
	u32 map_id;	//	offset:28  size:4; चिन्हित:0;
	पूर्णांक map_index;	//	offset:32  size:4; चिन्हित:1;
पूर्ण;			//	offset:36

क्रमागत अणु
	XDP_REसूचीECT_SUCCESS = 0,
	XDP_REसूचीECT_ERROR = 1
पूर्ण;

अटल __always_अंतरभूत
पूर्णांक xdp_redirect_collect_stat(काष्ठा xdp_redirect_ctx *ctx)
अणु
	u32 key = XDP_REसूचीECT_ERROR;
	काष्ठा datarec *rec;
	पूर्णांक err = ctx->err;

	अगर (!err)
		key = XDP_REसूचीECT_SUCCESS;

	rec = bpf_map_lookup_elem(&redirect_err_cnt, &key);
	अगर (!rec)
		वापस 0;
	rec->dropped += 1;

	वापस 0; /* Indicate event was filtered (no further processing)*/
	/*
	 * Returning 1 here would allow e.g. a perf-record tracepoपूर्णांक
	 * to see and record these events, but it करोesn't work well
	 * in-practice as stopping perf-record also unload this
	 * bpf_prog.  Plus, there is additional overhead of करोing so.
	 */
पूर्ण

SEC("tracepoint/xdp/xdp_redirect_err")
पूर्णांक trace_xdp_redirect_err(काष्ठा xdp_redirect_ctx *ctx)
अणु
	वापस xdp_redirect_collect_stat(ctx);
पूर्ण

SEC("tracepoint/xdp/xdp_redirect_map_err")
पूर्णांक trace_xdp_redirect_map_err(काष्ठा xdp_redirect_ctx *ctx)
अणु
	वापस xdp_redirect_collect_stat(ctx);
पूर्ण

/* Tracepoपूर्णांक क्रमmat: /sys/kernel/debug/tracing/events/xdp/xdp_exception/क्रमmat
 * Code in:                kernel/include/trace/events/xdp.h
 */
काष्ठा xdp_exception_ctx अणु
	u64 __pad;	// First 8 bytes are not accessible by bpf code
	पूर्णांक prog_id;	//	offset:8;  size:4; चिन्हित:1;
	u32 act;	//	offset:12; size:4; चिन्हित:0;
	पूर्णांक अगरindex;	//	offset:16; size:4; चिन्हित:1;
पूर्ण;

SEC("tracepoint/xdp/xdp_exception")
पूर्णांक trace_xdp_exception(काष्ठा xdp_exception_ctx *ctx)
अणु
	काष्ठा datarec *rec;
	u32 key = 0;

	rec = bpf_map_lookup_elem(&exception_cnt, &key);
	अगर (!rec)
		वापस 1;
	rec->dropped += 1;

	वापस 0;
पूर्ण

/* Tracepoपूर्णांक: /sys/kernel/debug/tracing/events/xdp/xdp_cpumap_enqueue/क्रमmat
 * Code in:         kernel/include/trace/events/xdp.h
 */
काष्ठा cpumap_enqueue_ctx अणु
	u64 __pad;		// First 8 bytes are not accessible by bpf code
	पूर्णांक map_id;		//	offset:8;  size:4; चिन्हित:1;
	u32 act;		//	offset:12; size:4; चिन्हित:0;
	पूर्णांक cpu;		//	offset:16; size:4; चिन्हित:1;
	अचिन्हित पूर्णांक drops;	//	offset:20; size:4; चिन्हित:0;
	अचिन्हित पूर्णांक processed;	//	offset:24; size:4; चिन्हित:0;
	पूर्णांक to_cpu;		//	offset:28; size:4; चिन्हित:1;
पूर्ण;

SEC("tracepoint/xdp/xdp_cpumap_enqueue")
पूर्णांक trace_xdp_cpumap_enqueue(काष्ठा cpumap_enqueue_ctx *ctx)
अणु
	u32 to_cpu = ctx->to_cpu;
	काष्ठा datarec *rec;

	अगर (to_cpu >= MAX_CPUS)
		वापस 1;

	rec = bpf_map_lookup_elem(&cpumap_enqueue_cnt, &to_cpu);
	अगर (!rec)
		वापस 0;
	rec->processed += ctx->processed;
	rec->dropped   += ctx->drops;

	/* Record bulk events, then userspace can calc average bulk size */
	अगर (ctx->processed > 0)
		rec->issue += 1;

	/* Inception: It's possible to detect overload situations, via
	 * this tracepoपूर्णांक.  This can be used क्रम creating a feedback
	 * loop to XDP, which can take appropriate actions to mitigate
	 * this overload situation.
	 */
	वापस 0;
पूर्ण

/* Tracepoपूर्णांक: /sys/kernel/debug/tracing/events/xdp/xdp_cpumap_kthपढ़ो/क्रमmat
 * Code in:         kernel/include/trace/events/xdp.h
 */
काष्ठा cpumap_kthपढ़ो_ctx अणु
	u64 __pad;			// First 8 bytes are not accessible
	पूर्णांक map_id;			//	offset:8;  size:4; चिन्हित:1;
	u32 act;			//	offset:12; size:4; चिन्हित:0;
	पूर्णांक cpu;			//	offset:16; size:4; चिन्हित:1;
	अचिन्हित पूर्णांक drops;		//	offset:20; size:4; चिन्हित:0;
	अचिन्हित पूर्णांक processed;		//	offset:24; size:4; चिन्हित:0;
	पूर्णांक sched;			//	offset:28; size:4; चिन्हित:1;
	अचिन्हित पूर्णांक xdp_pass;		//	offset:32; size:4; चिन्हित:0;
	अचिन्हित पूर्णांक xdp_drop;		//	offset:36; size:4; चिन्हित:0;
	अचिन्हित पूर्णांक xdp_redirect;	//	offset:40; size:4; चिन्हित:0;
पूर्ण;

SEC("tracepoint/xdp/xdp_cpumap_kthread")
पूर्णांक trace_xdp_cpumap_kthपढ़ो(काष्ठा cpumap_kthपढ़ो_ctx *ctx)
अणु
	काष्ठा datarec *rec;
	u32 key = 0;

	rec = bpf_map_lookup_elem(&cpumap_kthपढ़ो_cnt, &key);
	अगर (!rec)
		वापस 0;
	rec->processed += ctx->processed;
	rec->dropped   += ctx->drops;
	rec->xdp_pass  += ctx->xdp_pass;
	rec->xdp_drop  += ctx->xdp_drop;
	rec->xdp_redirect  += ctx->xdp_redirect;

	/* Count बार kthपढ़ो yielded CPU via schedule call */
	अगर (ctx->sched)
		rec->issue++;

	वापस 0;
पूर्ण
