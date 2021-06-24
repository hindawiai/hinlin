<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश <vmlinux.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण sk_stg_map SEC(".maps");

SEC("fentry/bpf_sk_storage_free")
पूर्णांक BPF_PROG(trace_bpf_sk_storage_मुक्त, काष्ठा sock *sk)
अणु
	पूर्णांक *value;

	value = bpf_sk_storage_get(&sk_stg_map, sk, 0,
				   BPF_SK_STORAGE_GET_F_CREATE);

	अगर (value)
		*value = 1;

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
