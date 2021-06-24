<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश "bpf_iter.h"
#समावेश "bpf_tracing_net.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण sk_stg_map SEC(".maps");

__u32 val_sum = 0;
__u32 ipv6_sk_count = 0;

SEC("iter/bpf_sk_storage_map")
पूर्णांक dump_bpf_sk_storage_map(काष्ठा bpf_iter__bpf_sk_storage_map *ctx)
अणु
	काष्ठा sock *sk = ctx->sk;
	__u32 *val = ctx->value;

	अगर (sk == (व्योम *)0 || val == (व्योम *)0)
		वापस 0;

	अगर (sk->sk_family == AF_INET6)
		ipv6_sk_count++;

	val_sum += *val;
	वापस 0;
पूर्ण
