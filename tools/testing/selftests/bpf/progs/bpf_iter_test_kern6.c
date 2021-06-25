<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश "bpf_iter.h"
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";

__u32 value_sum = 0;

SEC("iter/bpf_map_elem")
पूर्णांक dump_bpf_hash_map(काष्ठा bpf_iter__bpf_map_elem *ctx)
अणु
	व्योम *value = ctx->value;

	अगर (value == (व्योम *)0)
		वापस 0;

	/* negative offset, verअगरier failure. */
	value_sum += *(__u32 *)(value - 4);
	वापस 0;
पूर्ण
