<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

__u32 count = 0;
__u32 on_cpu = 0xffffffff;

SEC("raw_tp/task_rename")
पूर्णांक BPF_PROG(नाम, काष्ठा task_काष्ठा *task, अक्षर *comm)
अणु

	count++;
	अगर ((__u64) task == 0x1234ULL && (__u64) comm == 0x5678ULL) अणु
		on_cpu = bpf_get_smp_processor_id();
		वापस (दीर्घ)task + (दीर्घ)comm;
	पूर्ण

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
