<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Facebook

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण cg_ids SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण pidmap SEC(".maps");

SEC("tracepoint/syscalls/sys_enter_nanosleep")
पूर्णांक trace(व्योम *ctx)
अणु
	__u32 pid = bpf_get_current_pid_tgid();
	__u32 key = 0, *expected_pid;
	__u64 *val;

	expected_pid = bpf_map_lookup_elem(&pidmap, &key);
	अगर (!expected_pid || *expected_pid != pid)
		वापस 0;

	val = bpf_map_lookup_elem(&cg_ids, &key);
	अगर (val)
		*val = bpf_get_current_cgroup_id();

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
__u32 _version SEC("version") = 1; /* ignored by tracepoपूर्णांकs, required by libbpf.a */
