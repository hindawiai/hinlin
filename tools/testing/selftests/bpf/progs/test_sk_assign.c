<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Cloudflare Ltd.
// Copyright (c) 2020 Isovalent, Inc.

#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/pkt_cls.h>
#समावेश <linux/tcp.h>
#समावेश <sys/socket.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

/* Pin map under /sys/fs/bpf/tc/globals/<map name> */
#घोषणा PIN_GLOBAL_NS 2

/* Must match काष्ठा bpf_elf_map layout from iproute2 */
काष्ठा अणु
	__u32 type;
	__u32 size_key;
	__u32 size_value;
	__u32 max_elem;
	__u32 flags;
	__u32 id;
	__u32 pinning;
पूर्ण server_map SEC("maps") = अणु
	.type = BPF_MAP_TYPE_SOCKMAP,
	.size_key = माप(पूर्णांक),
	.size_value  = माप(__u64),
	.max_elem = 1,
	.pinning = PIN_GLOBAL_NS,
पूर्ण;

पूर्णांक _version SEC("version") = 1;
अक्षर _license[] SEC("license") = "GPL";

/* Fill 'tuple' with L3 info, and attempt to find L4. On fail, वापस शून्य. */
अटल अंतरभूत काष्ठा bpf_sock_tuple *
get_tuple(काष्ठा __sk_buff *skb, bool *ipv4, bool *tcp)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	काष्ठा bpf_sock_tuple *result;
	काष्ठा ethhdr *eth;
	__u64 tuple_len;
	__u8 proto = 0;
	__u64 ihl_len;

	eth = (काष्ठा ethhdr *)(data);
	अगर (eth + 1 > data_end)
		वापस शून्य;

	अगर (eth->h_proto == bpf_htons(ETH_P_IP)) अणु
		काष्ठा iphdr *iph = (काष्ठा iphdr *)(data + माप(*eth));

		अगर (iph + 1 > data_end)
			वापस शून्य;
		अगर (iph->ihl != 5)
			/* Options are not supported */
			वापस शून्य;
		ihl_len = iph->ihl * 4;
		proto = iph->protocol;
		*ipv4 = true;
		result = (काष्ठा bpf_sock_tuple *)&iph->saddr;
	पूर्ण अन्यथा अगर (eth->h_proto == bpf_htons(ETH_P_IPV6)) अणु
		काष्ठा ipv6hdr *ip6h = (काष्ठा ipv6hdr *)(data + माप(*eth));

		अगर (ip6h + 1 > data_end)
			वापस शून्य;
		ihl_len = माप(*ip6h);
		proto = ip6h->nexthdr;
		*ipv4 = false;
		result = (काष्ठा bpf_sock_tuple *)&ip6h->saddr;
	पूर्ण अन्यथा अणु
		वापस (काष्ठा bpf_sock_tuple *)data;
	पूर्ण

	अगर (proto != IPPROTO_TCP && proto != IPPROTO_UDP)
		वापस शून्य;

	*tcp = (proto == IPPROTO_TCP);
	वापस result;
पूर्ण

अटल अंतरभूत पूर्णांक
handle_udp(काष्ठा __sk_buff *skb, काष्ठा bpf_sock_tuple *tuple, bool ipv4)
अणु
	काष्ठा bpf_sock_tuple ln = अणु0पूर्ण;
	काष्ठा bpf_sock *sk;
	स्थिर पूर्णांक zero = 0;
	माप_प्रकार tuple_len;
	__be16 dport;
	पूर्णांक ret;

	tuple_len = ipv4 ? माप(tuple->ipv4) : माप(tuple->ipv6);
	अगर ((व्योम *)tuple + tuple_len > (व्योम *)(दीर्घ)skb->data_end)
		वापस TC_ACT_SHOT;

	sk = bpf_sk_lookup_udp(skb, tuple, tuple_len, BPF_F_CURRENT_NETNS, 0);
	अगर (sk)
		जाओ assign;

	dport = ipv4 ? tuple->ipv4.dport : tuple->ipv6.dport;
	अगर (dport != bpf_htons(4321))
		वापस TC_ACT_OK;

	sk = bpf_map_lookup_elem(&server_map, &zero);
	अगर (!sk)
		वापस TC_ACT_SHOT;

assign:
	ret = bpf_sk_assign(skb, sk, 0);
	bpf_sk_release(sk);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
handle_tcp(काष्ठा __sk_buff *skb, काष्ठा bpf_sock_tuple *tuple, bool ipv4)
अणु
	काष्ठा bpf_sock_tuple ln = अणु0पूर्ण;
	काष्ठा bpf_sock *sk;
	स्थिर पूर्णांक zero = 0;
	माप_प्रकार tuple_len;
	__be16 dport;
	पूर्णांक ret;

	tuple_len = ipv4 ? माप(tuple->ipv4) : माप(tuple->ipv6);
	अगर ((व्योम *)tuple + tuple_len > (व्योम *)(दीर्घ)skb->data_end)
		वापस TC_ACT_SHOT;

	sk = bpf_skc_lookup_tcp(skb, tuple, tuple_len, BPF_F_CURRENT_NETNS, 0);
	अगर (sk) अणु
		अगर (sk->state != BPF_TCP_LISTEN)
			जाओ assign;
		bpf_sk_release(sk);
	पूर्ण

	dport = ipv4 ? tuple->ipv4.dport : tuple->ipv6.dport;
	अगर (dport != bpf_htons(4321))
		वापस TC_ACT_OK;

	sk = bpf_map_lookup_elem(&server_map, &zero);
	अगर (!sk)
		वापस TC_ACT_SHOT;

	अगर (sk->state != BPF_TCP_LISTEN) अणु
		bpf_sk_release(sk);
		वापस TC_ACT_SHOT;
	पूर्ण

assign:
	ret = bpf_sk_assign(skb, sk, 0);
	bpf_sk_release(sk);
	वापस ret;
पूर्ण

SEC("classifier/sk_assign_test")
पूर्णांक bpf_sk_assign_test(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_sock_tuple *tuple, ln = अणु0पूर्ण;
	bool ipv4 = false;
	bool tcp = false;
	पूर्णांक tuple_len;
	पूर्णांक ret = 0;

	tuple = get_tuple(skb, &ipv4, &tcp);
	अगर (!tuple)
		वापस TC_ACT_SHOT;

	/* Note that the verअगरier socket वापस type क्रम bpf_skc_lookup_tcp()
	 * dअगरfers from bpf_sk_lookup_udp(), so even though the C-level type is
	 * the same here, अगर we try to share the implementations they will
	 * fail to verअगरy because we're crossing poपूर्णांकer types.
	 */
	अगर (tcp)
		ret = handle_tcp(skb, tuple, ipv4);
	अन्यथा
		ret = handle_udp(skb, tuple, ipv4);

	वापस ret == 0 ? TC_ACT_OK : TC_ACT_SHOT;
पूर्ण
