<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश "bpf_iter.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

पूर्णांक count = 0;
पूर्णांक tgid = 0;

SEC("iter/task_file")
पूर्णांक dump_task_file(काष्ठा bpf_iter__task_file *ctx)
अणु
	काष्ठा seq_file *seq = ctx->meta->seq;
	काष्ठा task_काष्ठा *task = ctx->task;
	__u32 fd = ctx->fd;
	काष्ठा file *file = ctx->file;

	अगर (task == (व्योम *)0 || file == (व्योम *)0)
		वापस 0;

	अगर (ctx->meta->seq_num == 0) अणु
		count = 0;
		BPF_SEQ_PRINTF(seq, "    tgid      gid       fd      file\n");
	पूर्ण

	अगर (tgid == task->tgid && task->tgid != task->pid)
		count++;

	BPF_SEQ_PRINTF(seq, "%8d %8d %8d %lx\n", task->tgid, task->pid, fd,
		       (दीर्घ)file->f_op);
	वापस 0;
पूर्ण
