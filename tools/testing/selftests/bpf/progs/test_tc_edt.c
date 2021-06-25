<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानक_निवेशt.h>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/pkt_cls.h>
#समावेश <linux/tcp.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

/* the maximum delay we are willing to add (drop packets beyond that) */
#घोषणा TIME_HORIZON_NS (2000 * 1000 * 1000)
#घोषणा NS_PER_SEC 1000000000
#घोषणा ECN_HORIZON_NS 5000000
#घोषणा THROTTLE_RATE_BPS (5 * 1000 * 1000)

/* flow_key => last_tstamp बारtamp used */
काष्ठा bpf_map_def SEC("maps") flow_map = अणु
	.type = BPF_MAP_TYPE_HASH,
	.key_size = माप(uपूर्णांक32_t),
	.value_size = माप(uपूर्णांक64_t),
	.max_entries = 1,
पूर्ण;

अटल अंतरभूत पूर्णांक throttle_flow(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक key = 0;
	uपूर्णांक64_t *last_tstamp = bpf_map_lookup_elem(&flow_map, &key);
	uपूर्णांक64_t delay_ns = ((uपूर्णांक64_t)skb->len) * NS_PER_SEC /
			THROTTLE_RATE_BPS;
	uपूर्णांक64_t now = bpf_kसमय_get_ns();
	uपूर्णांक64_t tstamp, next_tstamp = 0;

	अगर (last_tstamp)
		next_tstamp = *last_tstamp + delay_ns;

	tstamp = skb->tstamp;
	अगर (tstamp < now)
		tstamp = now;

	/* should we throttle? */
	अगर (next_tstamp <= tstamp) अणु
		अगर (bpf_map_update_elem(&flow_map, &key, &tstamp, BPF_ANY))
			वापस TC_ACT_SHOT;
		वापस TC_ACT_OK;
	पूर्ण

	/* करो not queue past the समय horizon */
	अगर (next_tstamp - now >= TIME_HORIZON_NS)
		वापस TC_ACT_SHOT;

	/* set ecn bit, अगर needed */
	अगर (next_tstamp - now >= ECN_HORIZON_NS)
		bpf_skb_ecn_set_ce(skb);

	अगर (bpf_map_update_elem(&flow_map, &key, &next_tstamp, BPF_EXIST))
		वापस TC_ACT_SHOT;
	skb->tstamp = next_tstamp;

	वापस TC_ACT_OK;
पूर्ण

अटल अंतरभूत पूर्णांक handle_tcp(काष्ठा __sk_buff *skb, काष्ठा tcphdr *tcp)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;

	/* drop malक्रमmed packets */
	अगर ((व्योम *)(tcp + 1) > data_end)
		वापस TC_ACT_SHOT;

	अगर (tcp->dest == bpf_htons(9000))
		वापस throttle_flow(skb);

	वापस TC_ACT_OK;
पूर्ण

अटल अंतरभूत पूर्णांक handle_ipv4(काष्ठा __sk_buff *skb)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	काष्ठा iphdr *iph;
	uपूर्णांक32_t ihl;

	/* drop malक्रमmed packets */
	अगर (data + माप(काष्ठा ethhdr) > data_end)
		वापस TC_ACT_SHOT;
	iph = (काष्ठा iphdr *)(data + माप(काष्ठा ethhdr));
	अगर ((व्योम *)(iph + 1) > data_end)
		वापस TC_ACT_SHOT;
	ihl = iph->ihl * 4;
	अगर (((व्योम *)iph) + ihl > data_end)
		वापस TC_ACT_SHOT;

	अगर (iph->protocol == IPPROTO_TCP)
		वापस handle_tcp(skb, (काष्ठा tcphdr *)(((व्योम *)iph) + ihl));

	वापस TC_ACT_OK;
पूर्ण

SEC("cls_test") पूर्णांक tc_prog(काष्ठा __sk_buff *skb)
अणु
	अगर (skb->protocol == bpf_htons(ETH_P_IP))
		वापस handle_ipv4(skb);

	वापस TC_ACT_OK;
पूर्ण

अक्षर __license[] SEC("license") = "GPL";
