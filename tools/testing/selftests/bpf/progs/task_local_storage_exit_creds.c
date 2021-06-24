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
	__type(value, __u64);
पूर्ण task_storage SEC(".maps");

पूर्णांक valid_ptr_count = 0;
पूर्णांक null_ptr_count = 0;

SEC("fentry/exit_creds")
पूर्णांक BPF_PROG(trace_निकास_creds, काष्ठा task_काष्ठा *task)
अणु
	__u64 *ptr;

	ptr = bpf_task_storage_get(&task_storage, task, 0,
				   BPF_LOCAL_STORAGE_GET_F_CREATE);
	अगर (ptr)
		__sync_fetch_and_add(&valid_ptr_count, 1);
	अन्यथा
		__sync_fetch_and_add(&null_ptr_count, 1);
	वापस 0;
पूर्ण
