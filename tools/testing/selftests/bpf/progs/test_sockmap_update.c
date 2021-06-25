<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Cloudflare
#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SOCKMAP);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण src SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SOCKMAP);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण dst_sock_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SOCKHASH);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण dst_sock_hash SEC(".maps");

SEC("classifier/copy_sock_map")
पूर्णांक copy_sock_map(व्योम *ctx)
अणु
	काष्ठा bpf_sock *sk;
	bool failed = false;
	__u32 key = 0;

	sk = bpf_map_lookup_elem(&src, &key);
	अगर (!sk)
		वापस SK_DROP;

	अगर (bpf_map_update_elem(&dst_sock_map, &key, sk, 0))
		failed = true;

	अगर (bpf_map_update_elem(&dst_sock_hash, &key, sk, 0))
		failed = true;

	bpf_sk_release(sk);
	वापस failed ? SK_DROP : SK_PASS;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
