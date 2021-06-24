<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश <vmlinux.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <bpf/bpf_core_पढ़ो.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा sk_stg अणु
	__u32 pid;
	__u32 last_notबंद_state;
	अक्षर comm[16];
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, काष्ठा sk_stg);
पूर्ण sk_stg_map SEC(".maps");

/* Testing delete */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण del_sk_stg_map SEC(".maps");

अक्षर task_comm[16] = "";

SEC("tp_btf/inet_sock_set_state")
पूर्णांक BPF_PROG(trace_inet_sock_set_state, काष्ठा sock *sk, पूर्णांक oldstate,
	     पूर्णांक newstate)
अणु
	काष्ठा sk_stg *stg;

	अगर (newstate == BPF_TCP_CLOSE)
		वापस 0;

	stg = bpf_sk_storage_get(&sk_stg_map, sk, 0,
				 BPF_SK_STORAGE_GET_F_CREATE);
	अगर (!stg)
		वापस 0;

	stg->last_notबंद_state = newstate;

	bpf_sk_storage_delete(&del_sk_stg_map, sk);

	वापस 0;
पूर्ण

अटल व्योम set_task_info(काष्ठा sock *sk)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा sk_stg *stg;

	stg = bpf_sk_storage_get(&sk_stg_map, sk, 0,
				 BPF_SK_STORAGE_GET_F_CREATE);
	अगर (!stg)
		वापस;

	stg->pid = bpf_get_current_pid_tgid();

	task = (काष्ठा task_काष्ठा *)bpf_get_current_task();
	bpf_core_पढ़ो_str(&stg->comm, माप(stg->comm), &task->comm);
	bpf_core_पढ़ो_str(&task_comm, माप(task_comm), &task->comm);
पूर्ण

SEC("fentry/inet_csk_listen_start")
पूर्णांक BPF_PROG(trace_inet_csk_listen_start, काष्ठा sock *sk, पूर्णांक backlog)
अणु
	set_task_info(sk);

	वापस 0;
पूर्ण

SEC("fentry/tcp_connect")
पूर्णांक BPF_PROG(trace_tcp_connect, काष्ठा sock *sk)
अणु
	set_task_info(sk);

	वापस 0;
पूर्ण

SEC("fexit/inet_csk_accept")
पूर्णांक BPF_PROG(inet_csk_accept, काष्ठा sock *sk, पूर्णांक flags, पूर्णांक *err, bool kern,
	     काष्ठा sock *accepted_sk)
अणु
	set_task_info(accepted_sk);

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
