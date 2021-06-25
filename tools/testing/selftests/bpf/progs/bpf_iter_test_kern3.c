<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश "bpf_iter.h"
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";

SEC("iter/task")
पूर्णांक dump_task(काष्ठा bpf_iter__task *ctx)
अणु
	काष्ठा seq_file *seq = ctx->meta->seq;
	काष्ठा task_काष्ठा *task = ctx->task;
	पूर्णांक tgid;

	tgid = task->tgid;
	bpf_seq_ग_लिखो(seq, &tgid, माप(tgid));
	वापस 0;
पूर्ण
