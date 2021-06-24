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
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(max_entries, 3);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण arraymap1 SEC(".maps");

/* will set beक्रमe prog run */
अस्थिर स्थिर __u32 num_cpus = 0;

__u32 key_sum = 0, val_sum = 0;

SEC("iter/bpf_map_elem")
पूर्णांक dump_bpf_percpu_array_map(काष्ठा bpf_iter__bpf_map_elem *ctx)
अणु
	__u32 *key = ctx->key;
	व्योम *pptr = ctx->value;
	__u32 step;
	पूर्णांक i;

	अगर (key == (व्योम *)0 || pptr == (व्योम *)0)
		वापस 0;

	key_sum += *key;

	step = 8;
	क्रम (i = 0; i < num_cpus; i++) अणु
		val_sum += *(__u32 *)pptr;
		pptr += step;
	पूर्ण
	वापस 0;
पूर्ण
