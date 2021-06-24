<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";
__u32 _version SEC("version") = 1;

काष्ठा tcp_rtt_storage अणु
	__u32 invoked;
	__u32 dsack_dups;
	__u32 delivered;
	__u32 delivered_ce;
	__u32 icsk_retransmits;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, काष्ठा tcp_rtt_storage);
पूर्ण socket_storage_map SEC(".maps");

SEC("sockops")
पूर्णांक _sockops(काष्ठा bpf_sock_ops *ctx)
अणु
	काष्ठा tcp_rtt_storage *storage;
	काष्ठा bpf_tcp_sock *tcp_sk;
	पूर्णांक op = (पूर्णांक) ctx->op;
	काष्ठा bpf_sock *sk;

	sk = ctx->sk;
	अगर (!sk)
		वापस 1;

	storage = bpf_sk_storage_get(&socket_storage_map, sk, 0,
				     BPF_SK_STORAGE_GET_F_CREATE);
	अगर (!storage)
		वापस 1;

	अगर (op == BPF_SOCK_OPS_TCP_CONNECT_CB) अणु
		bpf_sock_ops_cb_flags_set(ctx, BPF_SOCK_OPS_RTT_CB_FLAG);
		वापस 1;
	पूर्ण

	अगर (op != BPF_SOCK_OPS_RTT_CB)
		वापस 1;

	tcp_sk = bpf_tcp_sock(sk);
	अगर (!tcp_sk)
		वापस 1;

	storage->invoked++;

	storage->dsack_dups = tcp_sk->dsack_dups;
	storage->delivered = tcp_sk->delivered;
	storage->delivered_ce = tcp_sk->delivered_ce;
	storage->icsk_retransmits = tcp_sk->icsk_retransmits;

	वापस 1;
पूर्ण
