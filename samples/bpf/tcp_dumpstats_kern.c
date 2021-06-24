<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Refer to samples/bpf/tcp_bpf.पढ़ोme क्रम the inकाष्ठाions on
 * how to run this sample program.
 */
#समावेश <linux/bpf.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#घोषणा INTERVAL			1000000000ULL

पूर्णांक _version SEC("version") = 1;
अक्षर _license[] SEC("license") = "GPL";

काष्ठा अणु
	__u32 type;
	__u32 map_flags;
	पूर्णांक *key;
	__u64 *value;
पूर्ण bpf_next_dump SEC(".maps") = अणु
	.type = BPF_MAP_TYPE_SK_STORAGE,
	.map_flags = BPF_F_NO_PREALLOC,
पूर्ण;

SEC("sockops")
पूर्णांक _sockops(काष्ठा bpf_sock_ops *ctx)
अणु
	काष्ठा bpf_tcp_sock *tcp_sk;
	काष्ठा bpf_sock *sk;
	__u64 *next_dump;
	__u64 now;

	चयन (ctx->op) अणु
	हाल BPF_SOCK_OPS_TCP_CONNECT_CB:
		bpf_sock_ops_cb_flags_set(ctx, BPF_SOCK_OPS_RTT_CB_FLAG);
		वापस 1;
	हाल BPF_SOCK_OPS_RTT_CB:
		अवरोध;
	शेष:
		वापस 1;
	पूर्ण

	sk = ctx->sk;
	अगर (!sk)
		वापस 1;

	next_dump = bpf_sk_storage_get(&bpf_next_dump, sk, 0,
				       BPF_SK_STORAGE_GET_F_CREATE);
	अगर (!next_dump)
		वापस 1;

	now = bpf_kसमय_get_ns();
	अगर (now < *next_dump)
		वापस 1;

	tcp_sk = bpf_tcp_sock(sk);
	अगर (!tcp_sk)
		वापस 1;

	*next_dump = now + INTERVAL;

	bpf_prपूर्णांकk("dsack_dups=%u delivered=%u\n",
		   tcp_sk->dsack_dups, tcp_sk->delivered);
	bpf_prपूर्णांकk("delivered_ce=%u icsk_retransmits=%u\n",
		   tcp_sk->delivered_ce, tcp_sk->icsk_retransmits);

	वापस 1;
पूर्ण
