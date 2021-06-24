<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_endian.h>
#समावेश <bpf/bpf_helpers.h>

#समावेश <linux/अगर_ether.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/tcp.h>

#समावेश <sys/types.h>
#समावेश <sys/socket.h>

पूर्णांक _version SEC("version") = 1;
अक्षर _license[] SEC("license") = "GPL";

__u16 g_serv_port = 0;

अटल अंतरभूत व्योम set_ip(__u32 *dst, स्थिर काष्ठा in6_addr *src)
अणु
	dst[0] = src->in6_u.u6_addr32[0];
	dst[1] = src->in6_u.u6_addr32[1];
	dst[2] = src->in6_u.u6_addr32[2];
	dst[3] = src->in6_u.u6_addr32[3];
पूर्ण

अटल अंतरभूत व्योम set_tuple(काष्ठा bpf_sock_tuple *tuple,
			     स्थिर काष्ठा ipv6hdr *ip6h,
			     स्थिर काष्ठा tcphdr *tcph)
अणु
	set_ip(tuple->ipv6.saddr, &ip6h->daddr);
	set_ip(tuple->ipv6.daddr, &ip6h->saddr);
	tuple->ipv6.sport = tcph->dest;
	tuple->ipv6.dport = tcph->source;
पूर्ण

अटल अंतरभूत पूर्णांक is_allowed_peer_cg(काष्ठा __sk_buff *skb,
				     स्थिर काष्ठा ipv6hdr *ip6h,
				     स्थिर काष्ठा tcphdr *tcph)
अणु
	__u64 cgid, acgid, peer_cgid, peer_acgid;
	काष्ठा bpf_sock_tuple tuple;
	माप_प्रकार tuple_len = माप(tuple.ipv6);
	काष्ठा bpf_sock *peer_sk;

	set_tuple(&tuple, ip6h, tcph);

	peer_sk = bpf_sk_lookup_tcp(skb, &tuple, tuple_len,
				    BPF_F_CURRENT_NETNS, 0);
	अगर (!peer_sk)
		वापस 0;

	cgid = bpf_skb_cgroup_id(skb);
	peer_cgid = bpf_sk_cgroup_id(peer_sk);

	acgid = bpf_skb_ancestor_cgroup_id(skb, 2);
	peer_acgid = bpf_sk_ancestor_cgroup_id(peer_sk, 2);

	bpf_sk_release(peer_sk);

	वापस cgid && cgid == peer_cgid && acgid && acgid == peer_acgid;
पूर्ण

SEC("cgroup_skb/ingress")
पूर्णांक ingress_lookup(काष्ठा __sk_buff *skb)
अणु
	__u32 serv_port_key = 0;
	काष्ठा ipv6hdr ip6h;
	काष्ठा tcphdr tcph;

	अगर (skb->protocol != bpf_htons(ETH_P_IPV6))
		वापस 1;

	/* For SYN packets coming to listening socket skb->remote_port will be
	 * zero, so IPv6/TCP headers are loaded to identअगरy remote peer
	 * instead.
	 */
	अगर (bpf_skb_load_bytes(skb, 0, &ip6h, माप(ip6h)))
		वापस 1;

	अगर (ip6h.nexthdr != IPPROTO_TCP)
		वापस 1;

	अगर (bpf_skb_load_bytes(skb, माप(ip6h), &tcph, माप(tcph)))
		वापस 1;

	अगर (!g_serv_port)
		वापस 0;

	अगर (tcph.dest != g_serv_port)
		वापस 1;

	वापस is_allowed_peer_cg(skb, &ip6h, &tcph);
पूर्ण
