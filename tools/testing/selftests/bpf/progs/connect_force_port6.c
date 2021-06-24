<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <माला.स>

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
	__be32 addr[4];
	__be16 port;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, काष्ठा svc_addr);
पूर्ण service_mapping SEC(".maps");

SEC("cgroup/connect6")
पूर्णांक connect6(काष्ठा bpf_sock_addr *ctx)
अणु
	काष्ठा sockaddr_in6 sa = अणुपूर्ण;
	काष्ठा svc_addr *orig;

	/* Force local address to [::1]:22223. */
	sa.sin6_family = AF_INET6;
	sa.sin6_port = bpf_htons(22223);
	sa.sin6_addr.s6_addr32[3] = bpf_htonl(1);

	अगर (bpf_bind(ctx, (काष्ठा sockaddr *)&sa, माप(sa)) != 0)
		वापस 0;

	/* Rewire service [fc00::1]:60000 to backend [::1]:60124. */
	अगर (ctx->user_port == bpf_htons(60000)) अणु
		orig = bpf_sk_storage_get(&service_mapping, ctx->sk, 0,
					  BPF_SK_STORAGE_GET_F_CREATE);
		अगर (!orig)
			वापस 0;

		orig->addr[0] = ctx->user_ip6[0];
		orig->addr[1] = ctx->user_ip6[1];
		orig->addr[2] = ctx->user_ip6[2];
		orig->addr[3] = ctx->user_ip6[3];
		orig->port = ctx->user_port;

		ctx->user_ip6[0] = 0;
		ctx->user_ip6[1] = 0;
		ctx->user_ip6[2] = 0;
		ctx->user_ip6[3] = bpf_htonl(1);
		ctx->user_port = bpf_htons(60124);
	पूर्ण
	वापस 1;
पूर्ण

SEC("cgroup/getsockname6")
पूर्णांक माला_लोockname6(काष्ठा bpf_sock_addr *ctx)
अणु
	अगर (!get_set_sk_priority(ctx))
		वापस 1;

	/* Expose local server as [fc00::1]:60000 to client. */
	अगर (ctx->user_port == bpf_htons(60124)) अणु
		ctx->user_ip6[0] = bpf_htonl(0xfc000000);
		ctx->user_ip6[1] = 0;
		ctx->user_ip6[2] = 0;
		ctx->user_ip6[3] = bpf_htonl(1);
		ctx->user_port = bpf_htons(60000);
	पूर्ण
	वापस 1;
पूर्ण

SEC("cgroup/getpeername6")
पूर्णांक getpeername6(काष्ठा bpf_sock_addr *ctx)
अणु
	काष्ठा svc_addr *orig;

	अगर (!get_set_sk_priority(ctx))
		वापस 1;

	/* Expose service [fc00::1]:60000 as peer instead of backend. */
	अगर (ctx->user_port == bpf_htons(60124)) अणु
		orig = bpf_sk_storage_get(&service_mapping, ctx->sk, 0, 0);
		अगर (orig) अणु
			ctx->user_ip6[0] = orig->addr[0];
			ctx->user_ip6[1] = orig->addr[1];
			ctx->user_ip6[2] = orig->addr[2];
			ctx->user_ip6[3] = orig->addr[3];
			ctx->user_port = orig->port;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण
