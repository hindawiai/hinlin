<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#घोषणा TEST_COMM_LEN 16

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_CGROUP_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, u32);
	__type(value, u32);
पूर्ण cgroup_map SEC(".maps");

अक्षर _license[] SEC("license") = "GPL";

SEC("classifier/test_skb_helpers")
पूर्णांक test_skb_helpers(काष्ठा __sk_buff *skb)
अणु
	काष्ठा task_काष्ठा *task;
	अक्षर comm[TEST_COMM_LEN];
	__u32 tpid;

	task = (काष्ठा task_काष्ठा *)bpf_get_current_task();
	bpf_probe_पढ़ो_kernel(&tpid , माप(tpid), &task->tgid);
	bpf_probe_पढ़ो_kernel_str(&comm, माप(comm), &task->comm);
	वापस 0;
पूर्ण
