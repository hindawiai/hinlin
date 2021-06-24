<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <माला.स>
#समावेश <stdbool.h>

#समावेश <linux/bpf.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <sys/socket.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#समावेश <bpf_sockopt_helpers.h>

अक्षर _license[] SEC("license") = "GPL";
पूर्णांक _version SEC("version") = 1;

काष्ठा svc_addr अणु
	__be32 addr;
	__be16 port;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, काष्ठा svc_addr);
पूर्ण service_mapping SEC(".maps");

SEC("cgroup/connect4")
पूर्णांक connect4(काष्ठा bpf_sock_addr *ctx)
अणु
	काष्ठा sockaddr_in sa = अणुपूर्ण;
	काष्ठा svc_addr *orig;

	/* Force local address to 127.0.0.1:22222. */
	sa.sin_family = AF_INET;
	sa.sin_port = bpf_htons(22222);
	sa.sin_addr.s_addr = bpf_htonl(0x7f000001);

	अगर (bpf_bind(ctx, (काष्ठा sockaddr *)&sa, माप(sa)) != 0)
		वापस 0;

	/* Rewire service 1.2.3.4:60000 to backend 127.0.0.1:60123. */
	अगर (ctx->user_port == bpf_htons(60000)) अणु
		orig = bpf_sk_storage_get(&service_mapping, ctx->sk, 0,
					  BPF_SK_STORAGE_GET_F_CREATE);
		अगर (!orig)
			वापस 0;

		orig->addr = ctx->user_ip4;
		orig->port = ctx->user_port;

		ctx->user_ip4 = bpf_htonl(0x7f000001);
		ctx->user_port = bpf_htons(60123);
	पूर्ण
	वापस 1;
पूर्ण

SEC("cgroup/getsockname4")
पूर्णांक माला_लोockname4(काष्ठा bpf_sock_addr *ctx)
अणु
	अगर (!get_set_sk_priority(ctx))
		वापस 1;

	/* Expose local server as 1.2.3.4:60000 to client. */
	अगर (ctx->user_port == bpf_htons(60123)) अणु
		ctx->user_ip4 = bpf_htonl(0x01020304);
		ctx->user_port = bpf_htons(60000);
	पूर्ण
	वापस 1;
पूर्ण

SEC("cgroup/getpeername4")
पूर्णांक getpeername4(काष्ठा bpf_sock_addr *ctx)
अणु
	काष्ठा svc_addr *orig;

	अगर (!get_set_sk_priority(ctx))
		वापस 1;

	/* Expose service 1.2.3.4:60000 as peer instead of backend. */
	अगर (ctx->user_port == bpf_htons(60123)) अणु
		orig = bpf_sk_storage_get(&service_mapping, ctx->sk, 0, 0);
		अगर (orig) अणु
			ctx->user_ip4 = orig->addr;
			ctx->user_port = orig->port;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण
