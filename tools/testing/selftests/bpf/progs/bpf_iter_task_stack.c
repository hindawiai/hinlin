<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश "bpf_iter.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

#घोषणा MAX_STACK_TRACE_DEPTH   64
अचिन्हित दीर्घ entries[MAX_STACK_TRACE_DEPTH] = अणुपूर्ण;
#घोषणा SIZE_OF_ULONG (माप(अचिन्हित दीर्घ))

SEC("iter/task")
पूर्णांक dump_task_stack(काष्ठा bpf_iter__task *ctx)
अणु
	काष्ठा seq_file *seq = ctx->meta->seq;
	काष्ठा task_काष्ठा *task = ctx->task;
	दीर्घ i, retlen;

	अगर (task == (व्योम *)0)
		वापस 0;

	retlen = bpf_get_task_stack(task, entries,
				    MAX_STACK_TRACE_DEPTH * SIZE_OF_ULONG, 0);
	अगर (retlen < 0)
		वापस 0;

	BPF_SEQ_PRINTF(seq, "pid: %8u num_entries: %8u\n", task->pid,
		       retlen / SIZE_OF_ULONG);
	क्रम (i = 0; i < MAX_STACK_TRACE_DEPTH; i++) अणु
		अगर (retlen > i * SIZE_OF_ULONG)
			BPF_SEQ_PRINTF(seq, "[<0>] %pB\n", (व्योम *)entries[i]);
	पूर्ण
	BPF_SEQ_PRINTF(seq, "\n");

	वापस 0;
पूर्ण

SEC("iter/task")
पूर्णांक get_task_user_stacks(काष्ठा bpf_iter__task *ctx)
अणु
	काष्ठा seq_file *seq = ctx->meta->seq;
	काष्ठा task_काष्ठा *task = ctx->task;
	uपूर्णांक64_t buf_sz = 0;
	पूर्णांक64_t res;

	अगर (task == (व्योम *)0)
		वापस 0;

	res = bpf_get_task_stack(task, entries,
			MAX_STACK_TRACE_DEPTH * SIZE_OF_ULONG, BPF_F_USER_STACK);
	अगर (res <= 0)
		वापस 0;

	buf_sz += res;

	/* If the verअगरier करोesn't refine bpf_get_task_stack res, and instead
	 * assumes res is entirely unknown, this program will fail to load as
	 * the verअगरier will believe that max buf_sz value allows पढ़ोing
	 * past the end of entries in bpf_seq_ग_लिखो call
	 */
	bpf_seq_ग_लिखो(seq, &entries, buf_sz);
	वापस 0;
पूर्ण
