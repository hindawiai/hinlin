<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020, Oracle and/or its affiliates. */
#समावेश "bpf_iter.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <bpf/bpf_core_पढ़ो.h>

#समावेश <त्रुटिसं.स>

अक्षर _license[] SEC("license") = "GPL";

दीर्घ tasks = 0;
दीर्घ seq_err = 0;
bool skip = false;

SEC("iter/task")
पूर्णांक dump_task_काष्ठा(काष्ठा bpf_iter__task *ctx)
अणु
	काष्ठा seq_file *seq = ctx->meta->seq;
	काष्ठा task_काष्ठा *task = ctx->task;
	अटल काष्ठा btf_ptr ptr = अणु पूर्ण;
	दीर्घ ret;

#अगर __has_builtin(__builtin_btf_type_id)
	ptr.type_id = bpf_core_type_id_kernel(काष्ठा task_काष्ठा);
	ptr.ptr = task;

	अगर (ctx->meta->seq_num == 0)
		BPF_SEQ_PRINTF(seq, "Raw BTF task\n");

	ret = bpf_seq_म_लिखो_btf(seq, &ptr, माप(ptr), 0);
	चयन (ret) अणु
	हाल 0:
		tasks++;
		अवरोध;
	हाल -दुस्फल:
		/* शून्य task or task->fs, करोn't count it as an error. */
		अवरोध;
	हाल -E2BIG:
		वापस 1;
	शेष:
		seq_err = ret;
		अवरोध;
	पूर्ण
#अन्यथा
	skip = true;
#पूर्ण_अगर

	वापस 0;
पूर्ण
