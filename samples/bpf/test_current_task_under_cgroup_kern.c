<शैली गुरु>
/* Copyright (c) 2016 Sargun Dhillon <sargun@sargun.me>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */

#समावेश <linux/ptrace.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <linux/version.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <uapi/linux/utsname.h>
#समावेश "trace_common.h"

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_CGROUP_ARRAY);
	__uपूर्णांक(key_size, माप(u32));
	__uपूर्णांक(value_size, माप(u32));
	__uपूर्णांक(max_entries, 1);
पूर्ण cgroup_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, u32);
	__type(value, u64);
	__uपूर्णांक(max_entries, 1);
पूर्ण perf_map SEC(".maps");

/* Writes the last PID that called sync to a map at index 0 */
SEC("kprobe/" SYSCALL(sys_sync))
पूर्णांक bpf_prog1(काष्ठा pt_regs *ctx)
अणु
	u64 pid = bpf_get_current_pid_tgid();
	पूर्णांक idx = 0;

	अगर (!bpf_current_task_under_cgroup(&cgroup_map, 0))
		वापस 0;

	bpf_map_update_elem(&perf_map, &idx, &pid, BPF_ANY);
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
