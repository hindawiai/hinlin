<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <sys/socket.h>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

पूर्णांक invocations = 0, in_use = 0;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण sk_map SEC(".maps");

SEC("cgroup/sock_create")
पूर्णांक sock(काष्ठा bpf_sock *ctx)
अणु
	पूर्णांक *sk_storage;
	__u32 key;

	अगर (ctx->type != SOCK_DGRAM)
		वापस 1;

	sk_storage = bpf_sk_storage_get(&sk_map, ctx, 0,
					BPF_SK_STORAGE_GET_F_CREATE);
	अगर (!sk_storage)
		वापस 0;
	*sk_storage = 0xdeadbeef;

	__sync_fetch_and_add(&invocations, 1);

	अगर (in_use > 0) अणु
		/* BPF_CGROUP_INET_SOCK_RELEASE is _not_ called
		 * when we वापस an error from the BPF
		 * program!
		 */
		वापस 0;
	पूर्ण

	__sync_fetch_and_add(&in_use, 1);
	वापस 1;
पूर्ण

SEC("cgroup/sock_release")
पूर्णांक sock_release(काष्ठा bpf_sock *ctx)
अणु
	पूर्णांक *sk_storage;
	__u32 key;

	अगर (ctx->type != SOCK_DGRAM)
		वापस 1;

	sk_storage = bpf_sk_storage_get(&sk_map, ctx, 0, 0);
	अगर (!sk_storage || *sk_storage != 0xdeadbeef)
		वापस 0;

	__sync_fetch_and_add(&invocations, 1);
	__sync_fetch_and_add(&in_use, -1);
	वापस 1;
पूर्ण
