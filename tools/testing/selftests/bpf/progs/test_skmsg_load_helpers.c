<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Isovalent, Inc.
#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SOCKMAP);
	__uपूर्णांक(max_entries, 2);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण sock_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SOCKHASH);
	__uपूर्णांक(max_entries, 2);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण sock_hash SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण socket_storage SEC(".maps");

SEC("sk_msg")
पूर्णांक prog_msg_verdict(काष्ठा sk_msg_md *msg)
अणु
	काष्ठा task_काष्ठा *task = (काष्ठा task_काष्ठा *)bpf_get_current_task();
	पूर्णांक verdict = SK_PASS;
	__u32 pid, tpid;
	__u64 *sk_stg;

	pid = bpf_get_current_pid_tgid() >> 32;
	sk_stg = bpf_sk_storage_get(&socket_storage, msg->sk, 0, BPF_SK_STORAGE_GET_F_CREATE);
	अगर (!sk_stg)
		वापस SK_DROP;
	*sk_stg = pid;
	bpf_probe_पढ़ो_kernel(&tpid , माप(tpid), &task->tgid);
	अगर (pid != tpid)
		verdict = SK_DROP;
	bpf_sk_storage_delete(&socket_storage, (व्योम *)msg->sk);
	वापस verdict;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
