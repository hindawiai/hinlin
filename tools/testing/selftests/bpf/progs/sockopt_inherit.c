<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";
__u32 _version SEC("version") = 1;

#घोषणा SOL_CUSTOM			0xdeadbeef
#घोषणा CUSTOM_INHERIT1			0
#घोषणा CUSTOM_INHERIT2			1
#घोषणा CUSTOM_LISTENER			2

काष्ठा sockopt_inherit अणु
	__u8 val;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC | BPF_F_CLONE);
	__type(key, पूर्णांक);
	__type(value, काष्ठा sockopt_inherit);
पूर्ण cloned1_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC | BPF_F_CLONE);
	__type(key, पूर्णांक);
	__type(value, काष्ठा sockopt_inherit);
पूर्ण cloned2_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, काष्ठा sockopt_inherit);
पूर्ण listener_only_map SEC(".maps");

अटल __अंतरभूत काष्ठा sockopt_inherit *get_storage(काष्ठा bpf_sockopt *ctx)
अणु
	अगर (ctx->optname == CUSTOM_INHERIT1)
		वापस bpf_sk_storage_get(&cloned1_map, ctx->sk, 0,
					  BPF_SK_STORAGE_GET_F_CREATE);
	अन्यथा अगर (ctx->optname == CUSTOM_INHERIT2)
		वापस bpf_sk_storage_get(&cloned2_map, ctx->sk, 0,
					  BPF_SK_STORAGE_GET_F_CREATE);
	अन्यथा
		वापस bpf_sk_storage_get(&listener_only_map, ctx->sk, 0,
					  BPF_SK_STORAGE_GET_F_CREATE);
पूर्ण

SEC("cgroup/getsockopt")
पूर्णांक _माला_लोockopt(काष्ठा bpf_sockopt *ctx)
अणु
	__u8 *optval_end = ctx->optval_end;
	काष्ठा sockopt_inherit *storage;
	__u8 *optval = ctx->optval;

	अगर (ctx->level != SOL_CUSTOM)
		वापस 1; /* only पूर्णांकerested in SOL_CUSTOM */

	अगर (optval + 1 > optval_end)
		वापस 0; /* EPERM, bounds check */

	storage = get_storage(ctx);
	अगर (!storage)
		वापस 0; /* EPERM, couldn't get sk storage */

	ctx->retval = 0; /* Reset प्रणाली call वापस value to zero */

	optval[0] = storage->val;
	ctx->optlen = 1;

	वापस 1;
पूर्ण

SEC("cgroup/setsockopt")
पूर्णांक _setsockopt(काष्ठा bpf_sockopt *ctx)
अणु
	__u8 *optval_end = ctx->optval_end;
	काष्ठा sockopt_inherit *storage;
	__u8 *optval = ctx->optval;

	अगर (ctx->level != SOL_CUSTOM)
		वापस 1; /* only पूर्णांकerested in SOL_CUSTOM */

	अगर (optval + 1 > optval_end)
		वापस 0; /* EPERM, bounds check */

	storage = get_storage(ctx);
	अगर (!storage)
		वापस 0; /* EPERM, couldn't get sk storage */

	storage->val = optval[0];
	ctx->optlen = -1;

	वापस 1;
पूर्ण
