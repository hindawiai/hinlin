<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

काष्ठा task_काष्ठा;

SEC("fentry/__set_task_comm")
पूर्णांक BPF_PROG(prog1, काष्ठा task_काष्ठा *tsk, स्थिर अक्षर *buf, bool exec)
अणु
	वापस 0;
पूर्ण

SEC("fexit/__set_task_comm")
पूर्णांक BPF_PROG(prog2, काष्ठा task_काष्ठा *tsk, स्थिर अक्षर *buf, bool exec)
अणु
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
