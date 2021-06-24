<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Facebook
// Copyright (c) 2019 Cloudflare

#समावेश <माला.स>

#समावेश <linux/bpf.h>
#समावेश <linux/pkt_cls.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <sys/socket.h>
#समावेश <linux/tcp.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

काष्ठा bpf_map_def SEC("maps") results = अणु
	.type = BPF_MAP_TYPE_ARRAY,
	.key_size = माप(__u32),
	.value_size = माप(__u32),
	.max_entries = 3,
पूर्ण;

अटल __always_अंतरभूत __s64 gen_syncookie(व्योम *data_end, काष्ठा bpf_sock *sk,
					   व्योम *iph, __u32 ip_size,
					   काष्ठा tcphdr *tcph)
अणु
	__u32 thlen = tcph->करोff * 4;

	अगर (tcph->syn && !tcph->ack) अणु
		// packet should only have an MSS option
		अगर (thlen != 24)
			वापस 0;

		अगर ((व्योम *)tcph + thlen > data_end)
			वापस 0;

		वापस bpf_tcp_gen_syncookie(sk, iph, ip_size, tcph, thlen);
	पूर्ण
	वापस 0;
पूर्ण

अटल __always_अंतरभूत व्योम check_syncookie(व्योम *ctx, व्योम *data,
					    व्योम *data_end)
अणु
	काष्ठा bpf_sock_tuple tup;
	काष्ठा bpf_sock *sk;
	काष्ठा ethhdr *ethh;
	काष्ठा iphdr *ipv4h;
	काष्ठा ipv6hdr *ipv6h;
	काष्ठा tcphdr *tcph;
	पूर्णांक ret;
	__u32 key_mss = 2;
	__u32 key_gen = 1;
	__u32 key = 0;
	__s64 seq_mss;

	ethh = data;
	अगर (ethh + 1 > data_end)
		वापस;

	चयन (bpf_ntohs(ethh->h_proto)) अणु
	हाल ETH_P_IP:
		ipv4h = data + माप(काष्ठा ethhdr);
		अगर (ipv4h + 1 > data_end)
			वापस;

		अगर (ipv4h->ihl != 5)
			वापस;

		tcph = data + माप(काष्ठा ethhdr) + माप(काष्ठा iphdr);
		अगर (tcph + 1 > data_end)
			वापस;

		tup.ipv4.saddr = ipv4h->saddr;
		tup.ipv4.daddr = ipv4h->daddr;
		tup.ipv4.sport = tcph->source;
		tup.ipv4.dport = tcph->dest;

		sk = bpf_skc_lookup_tcp(ctx, &tup, माप(tup.ipv4),
					BPF_F_CURRENT_NETNS, 0);
		अगर (!sk)
			वापस;

		अगर (sk->state != BPF_TCP_LISTEN)
			जाओ release;

		seq_mss = gen_syncookie(data_end, sk, ipv4h, माप(*ipv4h),
					tcph);

		ret = bpf_tcp_check_syncookie(sk, ipv4h, माप(*ipv4h),
					      tcph, माप(*tcph));
		अवरोध;

	हाल ETH_P_IPV6:
		ipv6h = data + माप(काष्ठा ethhdr);
		अगर (ipv6h + 1 > data_end)
			वापस;

		अगर (ipv6h->nexthdr != IPPROTO_TCP)
			वापस;

		tcph = data + माप(काष्ठा ethhdr) + माप(काष्ठा ipv6hdr);
		अगर (tcph + 1 > data_end)
			वापस;

		स_नकल(tup.ipv6.saddr, &ipv6h->saddr, माप(tup.ipv6.saddr));
		स_नकल(tup.ipv6.daddr, &ipv6h->daddr, माप(tup.ipv6.daddr));
		tup.ipv6.sport = tcph->source;
		tup.ipv6.dport = tcph->dest;

		sk = bpf_skc_lookup_tcp(ctx, &tup, माप(tup.ipv6),
					BPF_F_CURRENT_NETNS, 0);
		अगर (!sk)
			वापस;

		अगर (sk->state != BPF_TCP_LISTEN)
			जाओ release;

		seq_mss = gen_syncookie(data_end, sk, ipv6h, माप(*ipv6h),
					tcph);

		ret = bpf_tcp_check_syncookie(sk, ipv6h, माप(*ipv6h),
					      tcph, माप(*tcph));
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	अगर (seq_mss > 0) अणु
		__u32 cookie = (__u32)seq_mss;
		__u32 mss = seq_mss >> 32;

		bpf_map_update_elem(&results, &key_gen, &cookie, 0);
		bpf_map_update_elem(&results, &key_mss, &mss, 0);
	पूर्ण

	अगर (ret == 0) अणु
		__u32 cookie = bpf_ntohl(tcph->ack_seq) - 1;

		bpf_map_update_elem(&results, &key, &cookie, 0);
	पूर्ण

release:
	bpf_sk_release(sk);
पूर्ण

SEC("clsact/check_syncookie")
पूर्णांक check_syncookie_clsact(काष्ठा __sk_buff *skb)
अणु
	check_syncookie(skb, (व्योम *)(दीर्घ)skb->data,
			(व्योम *)(दीर्घ)skb->data_end);
	वापस TC_ACT_OK;
पूर्ण

SEC("xdp/check_syncookie")
पूर्णांक check_syncookie_xdp(काष्ठा xdp_md *ctx)
अणु
	check_syncookie(ctx, (व्योम *)(दीर्घ)ctx->data,
			(व्योम *)(दीर्घ)ctx->data_end);
	वापस XDP_PASS;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
