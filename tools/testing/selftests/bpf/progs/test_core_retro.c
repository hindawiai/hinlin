<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_core_पढ़ो.h>

काष्ठा task_काष्ठा अणु
	पूर्णांक tgid;
पूर्ण __attribute__((preserve_access_index));

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण exp_tgid_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण results SEC(".maps");

SEC("tp/raw_syscalls/sys_enter")
पूर्णांक handle_sys_enter(व्योम *ctx)
अणु
	काष्ठा task_काष्ठा *task = (व्योम *)bpf_get_current_task();
	पूर्णांक tgid = BPF_CORE_READ(task, tgid);
	पूर्णांक zero = 0;
	पूर्णांक real_tgid = bpf_get_current_pid_tgid() >> 32;
	पूर्णांक *exp_tgid = bpf_map_lookup_elem(&exp_tgid_map, &zero);

	/* only pass through sys_enters from test process */
	अगर (!exp_tgid || *exp_tgid != real_tgid)
		वापस 0;

	bpf_map_update_elem(&results, &zero, &tgid, 0);

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
