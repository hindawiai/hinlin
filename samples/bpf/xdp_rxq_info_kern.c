<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Copyright (c) 2017 Jesper Dangaard Brouer, Red Hat Inc.
 *
 *  Example howto extract XDP RX-queue info
 */
#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/अगर_ether.h>
#समावेश <uapi/linux/in.h>
#समावेश <bpf/bpf_helpers.h>

/* Config setup from with userspace
 *
 * User-side setup अगरindex in config_map, to verअगरy that
 * ctx->ingress_अगरindex is correct (against configured अगरindex)
 */
काष्ठा config अणु
	__u32 action;
	पूर्णांक अगरindex;
	__u32 options;
पूर्ण;
क्रमागत cfg_options_flags अणु
	NO_TOUCH = 0x0U,
	READ_MEM = 0x1U,
	SWAP_MAC = 0x2U,
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, पूर्णांक);
	__type(value, काष्ठा config);
	__uपूर्णांक(max_entries, 1);
पूर्ण config_map SEC(".maps");

/* Common stats data record (shared with userspace) */
काष्ठा datarec अणु
	__u64 processed;
	__u64 issue;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__type(key, u32);
	__type(value, काष्ठा datarec);
	__uपूर्णांक(max_entries, 1);
पूर्ण stats_global_map SEC(".maps");

#घोषणा MAX_RXQs 64

/* Stats per rx_queue_index (per CPU) */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__type(key, u32);
	__type(value, काष्ठा datarec);
	__uपूर्णांक(max_entries, MAX_RXQs + 1);
पूर्ण rx_queue_index_map SEC(".maps");

अटल __always_अंतरभूत
व्योम swap_src_dst_mac(व्योम *data)
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

SEC("xdp_prog0")
पूर्णांक  xdp_prognum0(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data     = (व्योम *)(दीर्घ)ctx->data;
	काष्ठा datarec *rec, *rxq_rec;
	पूर्णांक ingress_अगरindex;
	काष्ठा config *config;
	u32 key = 0;

	/* Global stats record */
	rec = bpf_map_lookup_elem(&stats_global_map, &key);
	अगर (!rec)
		वापस XDP_ABORTED;
	rec->processed++;

	/* Accessing ctx->ingress_अगरindex, cause BPF to reग_लिखो BPF
	 * inकाष्ठाions inside kernel to access xdp_rxq->dev->अगरindex
	 */
	ingress_अगरindex = ctx->ingress_अगरindex;

	config = bpf_map_lookup_elem(&config_map, &key);
	अगर (!config)
		वापस XDP_ABORTED;

	/* Simple test: check ctx provided अगरindex is as expected */
	अगर (ingress_अगरindex != config->अगरindex) अणु
		/* count this error हाल */
		rec->issue++;
		वापस XDP_ABORTED;
	पूर्ण

	/* Update stats per rx_queue_index. Handle अगर rx_queue_index
	 * is larger than stats map can contain info क्रम.
	 */
	key = ctx->rx_queue_index;
	अगर (key >= MAX_RXQs)
		key = MAX_RXQs;
	rxq_rec = bpf_map_lookup_elem(&rx_queue_index_map, &key);
	अगर (!rxq_rec)
		वापस XDP_ABORTED;
	rxq_rec->processed++;
	अगर (key == MAX_RXQs)
		rxq_rec->issue++;

	/* Default: Don't touch packet data, only count packets */
	अगर (unlikely(config->options & (READ_MEM|SWAP_MAC))) अणु
		काष्ठा ethhdr *eth = data;

		अगर (eth + 1 > data_end)
			वापस XDP_ABORTED;

		/* Aव्योम compiler removing this: Drop non 802.3 Ethertypes */
		अगर (ntohs(eth->h_proto) < ETH_P_802_3_MIN)
			वापस XDP_ABORTED;

		/* XDP_TX requires changing MAC-addrs, अन्यथा HW may drop.
		 * Can also be enabled with --swapmac (क्रम test purposes)
		 */
		अगर (unlikely(config->options & SWAP_MAC))
			swap_src_dst_mac(data);
	पूर्ण

	वापस config->action;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
