<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश "bpf_iter.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

SEC("iter/task")
पूर्णांक dump_task(काष्ठा bpf_iter__task *ctx)
अणु
	काष्ठा seq_file *seq = ctx->meta->seq;
	काष्ठा task_काष्ठा *task = ctx->task;
	अटल अक्षर info[] = "    === END ===";

	अगर (task == (व्योम *)0) अणु
		BPF_SEQ_PRINTF(seq, "%s\n", info);
		वापस 0;
	पूर्ण

	अगर (ctx->meta->seq_num == 0)
		BPF_SEQ_PRINTF(seq, "    tgid      gid\n");

	BPF_SEQ_PRINTF(seq, "%8d %8d\n", task->tgid, task->pid);
	वापस 0;
पूर्ण
