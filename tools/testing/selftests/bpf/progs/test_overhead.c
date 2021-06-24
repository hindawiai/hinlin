<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */
#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <linux/ptrace.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

काष्ठा task_काष्ठा;

SEC("kprobe/__set_task_comm")
पूर्णांक BPF_KPROBE(prog1, काष्ठा task_काष्ठा *tsk, स्थिर अक्षर *buf, bool exec)
अणु
	वापस !tsk;
पूर्ण

SEC("kretprobe/__set_task_comm")
पूर्णांक BPF_KRETPROBE(prog2, पूर्णांक ret)
अणु
	वापस ret;
पूर्ण

SEC("raw_tp/task_rename")
पूर्णांक prog3(काष्ठा bpf_raw_tracepoपूर्णांक_args *ctx)
अणु
	वापस !ctx->args[0];
पूर्ण

SEC("fentry/__set_task_comm")
पूर्णांक BPF_PROG(prog4, काष्ठा task_काष्ठा *tsk, स्थिर अक्षर *buf, bool exec)
अणु
	वापस 0;
पूर्ण

SEC("fexit/__set_task_comm")
पूर्णांक BPF_PROG(prog5, काष्ठा task_काष्ठा *tsk, स्थिर अक्षर *buf, bool exec)
अणु
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
