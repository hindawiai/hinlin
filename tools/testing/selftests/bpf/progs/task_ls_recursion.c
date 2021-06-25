<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_TASK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, दीर्घ);
पूर्ण map_a SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_TASK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, दीर्घ);
पूर्ण map_b SEC(".maps");

SEC("fentry/bpf_local_storage_lookup")
पूर्णांक BPF_PROG(on_lookup)
अणु
	काष्ठा task_काष्ठा *task = bpf_get_current_task_btf();

	bpf_task_storage_delete(&map_a, task);
	bpf_task_storage_delete(&map_b, task);
	वापस 0;
पूर्ण

SEC("fentry/bpf_local_storage_update")
पूर्णांक BPF_PROG(on_update)
अणु
	काष्ठा task_काष्ठा *task = bpf_get_current_task_btf();
	दीर्घ *ptr;

	ptr = bpf_task_storage_get(&map_a, task, 0,
				   BPF_LOCAL_STORAGE_GET_F_CREATE);
	अगर (ptr)
		*ptr += 1;

	ptr = bpf_task_storage_get(&map_b, task, 0,
				   BPF_LOCAL_STORAGE_GET_F_CREATE);
	अगर (ptr)
		*ptr += 1;

	वापस 0;
पूर्ण

SEC("tp_btf/sys_enter")
पूर्णांक BPF_PROG(on_enter, काष्ठा pt_regs *regs, दीर्घ id)
अणु
	काष्ठा task_काष्ठा *task;
	दीर्घ *ptr;

	task = bpf_get_current_task_btf();
	ptr = bpf_task_storage_get(&map_a, task, 0,
				   BPF_LOCAL_STORAGE_GET_F_CREATE);
	अगर (ptr)
		*ptr = 200;

	ptr = bpf_task_storage_get(&map_b, task, 0,
				   BPF_LOCAL_STORAGE_GET_F_CREATE);
	अगर (ptr)
		*ptr = 100;
	वापस 0;
पूर्ण
