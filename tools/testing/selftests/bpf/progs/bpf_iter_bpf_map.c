<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश "bpf_iter.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

SEC("iter/bpf_map")
पूर्णांक dump_bpf_map(काष्ठा bpf_iter__bpf_map *ctx)
अणु
	काष्ठा seq_file *seq = ctx->meta->seq;
	__u64 seq_num = ctx->meta->seq_num;
	काष्ठा bpf_map *map = ctx->map;

	अगर (map == (व्योम *)0) अणु
		BPF_SEQ_PRINTF(seq, "      %%%%%% END %%%%%%\n");
		वापस 0;
	पूर्ण

	अगर (seq_num == 0)
		BPF_SEQ_PRINTF(seq, "      id   refcnt  usercnt  locked_vm\n");

	BPF_SEQ_PRINTF(seq, "%8u %8ld %8ld %10lu\n", map->id, map->refcnt.counter,
		       map->usercnt.counter,
		       0LLU);
	वापस 0;
पूर्ण
