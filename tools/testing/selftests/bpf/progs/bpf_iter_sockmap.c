<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Cloudflare */
#समावेश "bpf_iter.h"
#समावेश "bpf_tracing_net.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <त्रुटिसं.स>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SOCKMAP);
	__uपूर्णांक(max_entries, 64);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण sockmap SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SOCKHASH);
	__uपूर्णांक(max_entries, 64);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण sockhash SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SOCKHASH);
	__uपूर्णांक(max_entries, 64);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण dst SEC(".maps");

__u32 elems = 0;
__u32 socks = 0;

SEC("iter/sockmap")
पूर्णांक copy(काष्ठा bpf_iter__sockmap *ctx)
अणु
	काष्ठा sock *sk = ctx->sk;
	__u32 पंचांगp, *key = ctx->key;
	पूर्णांक ret;

	अगर (!key)
		वापस 0;

	elems++;

	/* We need a temporary buffer on the stack, since the verअगरier करोesn't
	 * let us use the poपूर्णांकer from the context as an argument to the helper.
	 */
	पंचांगp = *key;

	अगर (sk) अणु
		socks++;
		वापस bpf_map_update_elem(&dst, &पंचांगp, sk, 0) != 0;
	पूर्ण

	ret = bpf_map_delete_elem(&dst, &पंचांगp);
	वापस ret && ret != -ENOENT;
पूर्ण
