<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश "bpf_iter.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा key_t अणु
	पूर्णांक a;
	पूर्णांक b;
	पूर्णांक c;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 3);
	__type(key, काष्ठा key_t);
	__type(value, __u64);
पूर्ण hashmap1 SEC(".maps");

__u32 key_sum = 0;

SEC("iter/bpf_map_elem")
पूर्णांक dump_bpf_hash_map(काष्ठा bpf_iter__bpf_map_elem *ctx)
अणु
	व्योम *key = ctx->key;

	अगर (key == (व्योम *)0)
		वापस 0;

	/* out of bound access w.r.t. hashmap1 */
	key_sum += *(__u32 *)(key + माप(काष्ठा key_t));
	वापस 0;
पूर्ण
