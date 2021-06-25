<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <sys/types.h>
#समावेश <sys/socket.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

अटल __always_अंतरभूत पूर्णांक bind_prog(काष्ठा bpf_sock_addr *ctx, पूर्णांक family)
अणु
	काष्ठा bpf_sock *sk;

	sk = ctx->sk;
	अगर (!sk)
		वापस 0;

	अगर (sk->family != family)
		वापस 0;

	अगर (ctx->type != SOCK_STREAM)
		वापस 0;

	/* Return 1 OR'ed with the first bit set to indicate
	 * that CAP_NET_BIND_SERVICE should be bypassed.
	 */
	अगर (ctx->user_port == bpf_htons(111))
		वापस (1 | 2);

	वापस 1;
पूर्ण

SEC("cgroup/bind4")
पूर्णांक bind_v4_prog(काष्ठा bpf_sock_addr *ctx)
अणु
	वापस bind_prog(ctx, AF_INET);
पूर्ण

SEC("cgroup/bind6")
पूर्णांक bind_v6_prog(काष्ठा bpf_sock_addr *ctx)
अणु
	वापस bind_prog(ctx, AF_INET6);
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
