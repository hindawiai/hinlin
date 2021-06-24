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
पूर्ण enter_id SEC(".maps");

#घोषणा MAGIC_VALUE 0xabcd1234

pid_t target_pid = 0;
पूर्णांक mismatch_cnt = 0;
पूर्णांक enter_cnt = 0;
पूर्णांक निकास_cnt = 0;

SEC("tp_btf/sys_enter")
पूर्णांक BPF_PROG(on_enter, काष्ठा pt_regs *regs, दीर्घ id)
अणु
	काष्ठा task_काष्ठा *task;
	दीर्घ *ptr;

	task = bpf_get_current_task_btf();
	अगर (task->pid != target_pid)
		वापस 0;

	ptr = bpf_task_storage_get(&enter_id, task, 0,
				   BPF_LOCAL_STORAGE_GET_F_CREATE);
	अगर (!ptr)
		वापस 0;

	__sync_fetch_and_add(&enter_cnt, 1);
	*ptr = MAGIC_VALUE + enter_cnt;

	वापस 0;
पूर्ण

SEC("tp_btf/sys_exit")
पूर्णांक BPF_PROG(on_निकास, काष्ठा pt_regs *regs, दीर्घ id)
अणु
	काष्ठा task_काष्ठा *task;
	दीर्घ *ptr;

	task = bpf_get_current_task_btf();
	अगर (task->pid != target_pid)
		वापस 0;

	ptr = bpf_task_storage_get(&enter_id, task, 0,
				   BPF_LOCAL_STORAGE_GET_F_CREATE);
	अगर (!ptr)
		वापस 0;

	__sync_fetch_and_add(&निकास_cnt, 1);
	अगर (*ptr != MAGIC_VALUE + निकास_cnt)
		__sync_fetch_and_add(&mismatch_cnt, 1);
	वापस 0;
पूर्ण
