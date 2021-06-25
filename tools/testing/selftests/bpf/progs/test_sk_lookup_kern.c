<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (c) 2018 Covalent IO, Inc. http://covalent.io

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

पूर्णांक _version SEC("version") = 1;
अक्षर _license[] SEC("license") = "GPL";

/* Fill 'tuple' with L3 info, and attempt to find L4. On fail, वापस शून्य. */
अटल काष्ठा bpf_sock_tuple *get_tuple(व्योम *data, __u64 nh_off,
					व्योम *data_end, __u16 eth_proto,
					bool *ipv4)
अणु
	काष्ठा bpf_sock_tuple *result;
	__u8 proto = 0;
	__u64 ihl_len;

	अगर (eth_proto == bpf_htons(ETH_P_IP)) अणु
		काष्ठा iphdr *iph = (काष्ठा iphdr *)(data + nh_off);

		अगर (iph + 1 > data_end)
			वापस शून्य;
		ihl_len = iph->ihl * 4;
		proto = iph->protocol;
		*ipv4 = true;
		result = (काष्ठा bpf_sock_tuple *)&iph->saddr;
	पूर्ण अन्यथा अगर (eth_proto == bpf_htons(ETH_P_IPV6)) अणु
		काष्ठा ipv6hdr *ip6h = (काष्ठा ipv6hdr *)(data + nh_off);

		अगर (ip6h + 1 > data_end)
			वापस शून्य;
		ihl_len = माप(*ip6h);
		proto = ip6h->nexthdr;
		*ipv4 = true;
		result = (काष्ठा bpf_sock_tuple *)&ip6h->saddr;
	पूर्ण

	अगर (data + nh_off + ihl_len > data_end || proto != IPPROTO_TCP)
		वापस शून्य;

	वापस result;
पूर्ण

SEC("classifier/sk_lookup_success")
पूर्णांक bpf_sk_lookup_test0(काष्ठा __sk_buff *skb)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)skb->data_end;
	व्योम *data = (व्योम *)(दीर्घ)skb->data;
	काष्ठा ethhdr *eth = (काष्ठा ethhdr *)(data);
	काष्ठा bpf_sock_tuple *tuple;
	काष्ठा bpf_sock *sk;
	माप_प्रकार tuple_len;
	bool ipv4;

	अगर (eth + 1 > data_end)
		वापस TC_ACT_SHOT;

	tuple = get_tuple(data, माप(*eth), data_end, eth->h_proto, &ipv4);
	अगर (!tuple || tuple + माप *tuple > data_end)
		वापस TC_ACT_SHOT;

	tuple_len = ipv4 ? माप(tuple->ipv4) : माप(tuple->ipv6);
	sk = bpf_sk_lookup_tcp(skb, tuple, tuple_len, BPF_F_CURRENT_NETNS, 0);
	bpf_prपूर्णांकk("sk=%d\n", sk ? 1 : 0);
	अगर (sk)
		bpf_sk_release(sk);
	वापस sk ? TC_ACT_OK : TC_ACT_UNSPEC;
पूर्ण

SEC("classifier/sk_lookup_success_simple")
पूर्णांक bpf_sk_lookup_test1(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_sock_tuple tuple = अणुपूर्ण;
	काष्ठा bpf_sock *sk;

	sk = bpf_sk_lookup_tcp(skb, &tuple, माप(tuple), BPF_F_CURRENT_NETNS, 0);
	अगर (sk)
		bpf_sk_release(sk);
	वापस 0;
पूर्ण

SEC("classifier/fail_use_after_free")
पूर्णांक bpf_sk_lookup_uaf(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_sock_tuple tuple = अणुपूर्ण;
	काष्ठा bpf_sock *sk;
	__u32 family = 0;

	sk = bpf_sk_lookup_tcp(skb, &tuple, माप(tuple), BPF_F_CURRENT_NETNS, 0);
	अगर (sk) अणु
		bpf_sk_release(sk);
		family = sk->family;
	पूर्ण
	वापस family;
पूर्ण

SEC("classifier/fail_modify_sk_pointer")
पूर्णांक bpf_sk_lookup_modptr(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_sock_tuple tuple = अणुपूर्ण;
	काष्ठा bpf_sock *sk;
	__u32 family;

	sk = bpf_sk_lookup_tcp(skb, &tuple, माप(tuple), BPF_F_CURRENT_NETNS, 0);
	अगर (sk) अणु
		sk += 1;
		bpf_sk_release(sk);
	पूर्ण
	वापस 0;
पूर्ण

SEC("classifier/fail_modify_sk_or_null_pointer")
पूर्णांक bpf_sk_lookup_modptr_or_null(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_sock_tuple tuple = अणुपूर्ण;
	काष्ठा bpf_sock *sk;
	__u32 family;

	sk = bpf_sk_lookup_tcp(skb, &tuple, माप(tuple), BPF_F_CURRENT_NETNS, 0);
	sk += 1;
	अगर (sk)
		bpf_sk_release(sk);
	वापस 0;
पूर्ण

SEC("classifier/fail_no_release")
पूर्णांक bpf_sk_lookup_test2(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_sock_tuple tuple = अणुपूर्ण;

	bpf_sk_lookup_tcp(skb, &tuple, माप(tuple), BPF_F_CURRENT_NETNS, 0);
	वापस 0;
पूर्ण

SEC("classifier/fail_release_twice")
पूर्णांक bpf_sk_lookup_test3(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_sock_tuple tuple = अणुपूर्ण;
	काष्ठा bpf_sock *sk;

	sk = bpf_sk_lookup_tcp(skb, &tuple, माप(tuple), BPF_F_CURRENT_NETNS, 0);
	bpf_sk_release(sk);
	bpf_sk_release(sk);
	वापस 0;
पूर्ण

SEC("classifier/fail_release_unchecked")
पूर्णांक bpf_sk_lookup_test4(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_sock_tuple tuple = अणुपूर्ण;
	काष्ठा bpf_sock *sk;

	sk = bpf_sk_lookup_tcp(skb, &tuple, माप(tuple), BPF_F_CURRENT_NETNS, 0);
	bpf_sk_release(sk);
	वापस 0;
पूर्ण

व्योम lookup_no_release(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_sock_tuple tuple = अणुपूर्ण;
	bpf_sk_lookup_tcp(skb, &tuple, माप(tuple), BPF_F_CURRENT_NETNS, 0);
पूर्ण

SEC("classifier/fail_no_release_subcall")
पूर्णांक bpf_sk_lookup_test5(काष्ठा __sk_buff *skb)
अणु
	lookup_no_release(skb);
	वापस 0;
पूर्ण
