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
पूर्ण map SEC(".maps");

SEC("sockops")
पूर्णांक bpf_sockmap(काष्ठा bpf_sock_ops *skops)
अणु
	__u32 key = 0;

	अगर (skops->sk)
		bpf_map_update_elem(&map, &key, skops->sk, 0);
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
