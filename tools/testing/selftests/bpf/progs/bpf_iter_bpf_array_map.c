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
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 3);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण arraymap1 SEC(".maps");

__u32 key_sum = 0;
__u64 val_sum = 0;

SEC("iter/bpf_map_elem")
पूर्णांक dump_bpf_array_map(काष्ठा bpf_iter__bpf_map_elem *ctx)
अणु
	__u32 *key = ctx->key;
	__u64 *val = ctx->value;

	अगर (key == (व्योम *)0 || val == (व्योम *)0)
		वापस 0;

	bpf_seq_ग_लिखो(ctx->meta->seq, key, माप(__u32));
	bpf_seq_ग_लिखो(ctx->meta->seq, val, माप(__u64));
	key_sum += *key;
	val_sum += *val;
	*val = *key;
	वापस 0;
पूर्ण
